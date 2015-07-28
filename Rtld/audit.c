#include <link.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/param.h>
#include <unistd.h>
#include <string.h>
#include "env.h"
#include "mach.h"

static Elist *bindto_list = NULL;
static Elist *bindfrom_list = NULL; 
static FILE *output = stdout;
static uint_t nopltexit = 0;
static uint_t pidout = 0;
static uint_t indent_level = 1;
static sigset_t	iset;
static pid_t pid;
static uint_t indent = 1;
/*
 * Following symbols are dependant on the stack frame structure.
 * Audit.so.1 will disable la_pltexit() entry point for these 
 * routines. Thus there wont be any extra stack frame 
 * that is created by the interface.
 * 
 */

static char *spec_sym[] = {
	"__getcontext",
	"_getcontext",
	"_getsp",
	"_longjmp",
	"_setcontext",
	"_setjmp",
	"_siglongjmp",
	"_sigsetjmp",
	"_vfork",
	"getcontext",
	"getsp",
	"longjmp",
	"setcontext",
	"setjmp",
	"siglongjmp",
	"sigsetjmp",
	"vfork",
	NULL
};
 
uint_t
la_version(uint_t version)
{
	int	fd;
	sigset_t mask;

	if (version < LAV_CURRENT) {
		(void) fprintf(stderr,
		    "audit.so.1: unexpected version: %d\n",
		    version);
		return (0);
	}

	build_env_list(&bindto_list, (const char *)"AUDIT_BINDTO");
	build_env_list(&bindfrom_list, (const char *)"AUDIT_BINDFROM");
        (void) sigfillset(&iset);
        return (LAV_CURRENT);
}
 
uint_t
la_objopen(Link_map *lmp, Lmid_t lmid, uintptr_t *cookie)
{
        uint_t	flags;
        //if (lmid == LM_ID_BASE)
           //     (void) fprintf(output,"file: %s loaded\n", lmp->l_name);
         
	if ((bindto_list == NULL) ||
	    (check_list(bindto_list, lmp->l_name)))
		flags = LA_FLG_BINDTO;
	else
		flags = 0;

	if ((bindfrom_list == NULL) ||
	    (check_list(bindfrom_list, lmp->l_name)))
		flags |= LA_FLG_BINDFROM;
        *cookie = (uintptr_t)lmp->l_name;
	return (flags);
}
uintptr_t la_symbind32(Elf32_Sym *sym, uint_t ndx,
        uintptr_t *refcook, uintptr_t *defcook, uint_t *flags) {
        const char *sym_name = (const char *)sym->st_name;
        (void) fprintf(output, "%-28s %-28s %s\n", (char *)(*refcook),
		(char *)(*defcook), sym_name);
        
        if ((*flags & LA_SYMB_NOPLTEXIT) == 0) {
		uint_t	ndx;
		char	*str;
		/* LINTED */
		for (ndx = 0; str = spec_sym[ndx]; ndx++) {
			int	cmpval;
			cmpval = strcmp(sym_name, str);
			if (cmpval < 0)
				break;
			if (cmpval == 0) {
				*flags |= LA_SYMB_NOPLTEXIT;
				break;
			}
		}
	}

	return (sym->st_value);
}

//Function similar to source code of truss.c. 

uintptr_t la_i86_pltenter(Elf32_Sym *symp, uint_t ndx,
        uintptr_t *refcook, uintptr_t *defcook,
        La_i86_regs *regs, uint_t *flags){
     //(void) printf("pltEnter: %s loaded\n", sym->st_name);
      char		*istr;
	char		*defname = (char *)(*defcook);
	char		*refname = (char *)(*refcook);
	const char	*sym_name = (const char *)symp->st_name;
	sigset_t	oset;

	(void) sigprocmask(SIG_BLOCK, &iset, &oset);

	if (pidout)
		(void) fprintf(output, "%5d:", (int)getpid());

	if ((*flags & LA_SYMB_NOPLTEXIT) == 0)
		istr = "";
	else
		istr = "*";

	(void) fprintf(output, "%-15s -> %15s:%-*s%s(0x%lx, 0x%lx, 0x%lx)\n",
		refname, defname, indent_level, istr, sym_name,
		(long)GETARG0(regs), (long)GETARG1(regs),
		(long)GETARG2(regs));

	(void) fflush(output);
	if (indent && ((*flags & LA_SYMB_NOPLTEXIT) == 0))
		indent_level++;
	(void) sigprocmask(SIG_SETMASK, &oset, NULL);
	return (symp->st_value);
        
}

uintptr_t 
la_pltexit(Elf32_Sym *symp, uint_t symndx, uintptr_t *refcookie,
	uintptr_t *defcookie, uintptr_t retval)
{
	char		*defname = (char *)(*defcookie);
	char		*refname = (char *)(*refcookie);
	sigset_t	oset;
        const char	*sym_name = (const char *)symp->st_name;
	(void) sigprocmask(SIG_BLOCK, &iset, &oset);

	if (pidout)
		(void) fprintf(output, "%5d:", (int)pid);
	if (indent)
		indent_level--;
	(void) fprintf(output, "%-15s -> %15s:%*s%s - 0x%lx\n", refname,
		defname, indent_level, "", sym_name, (ulong_t)retval);
	(void) fflush(output);
	(void) sigprocmask(SIG_SETMASK, &oset, NULL);
	return (retval);
}

/*void la_activity(uintptr_t *cookie, uint_t flags) {
    //if(flags == LA_ACT_ADD)
        //(void) printf("Activity Add : %s \n", *cookie );
    
}*/
