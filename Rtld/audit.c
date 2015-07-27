#include <link.h>
#include <stdio.h>
#include <stdlib.h>
#include "env.h"

static Elist	*bindto_list = NULL;
static Elist	*bindfrom_list = NULL; 
static FILE	*output = stdout;
 
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

	build_env_list(&bindto_list, (const char *)"BT_BINDTO");
	build_env_list(&bindfrom_list, (const char *)"BT_BINDFROM");
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

	return (sym->st_value);
}

/*uintptr_t la_i86_pltenter(Elf32_Sym *sym, uint_t ndx,
        uintptr_t *refcook, uintptr_t *defcook,
        La_i86_regs *regs, uint_t *flags){
     (void) printf("pltEnter: %s loaded\n", sym->st_name);
        
}*/

/*void la_activity(uintptr_t *cookie, uint_t flags) {
    //if(flags == LA_ACT_ADD)
        //(void) printf("Activity Add : %s \n", *cookie );
    
}*/
