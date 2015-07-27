#include        <link.h>
#include        <stdio.h>

static Elist	*bindto_list = NULL;
static Elist	*bindfrom_list = NULL; 
 
uint_t
la_version(uint_t version)
{
	int	fd;
	sigset_t	omask;

	if (version < LAV_CURRENT) {
		(void) fprintf(stderr,
		    "bindings.so: unexpected link_audit version: %d\n",
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
        if (lmid == LM_ID_BASE)
                (void) printf("file: %s loaded\n", lmp->l_name);
         
	if ((bindto_list == NULL) ||
	    (check_list(bindto_list, lmp->l_name)))
		flags = LA_FLG_BINDTO;
	else
		flags = 0;

	if ((bindfrom_list == NULL) ||
	    (check_list(bindfrom_list, lmp->l_name)))
		flags |= LA_FLG_BINDFROM;

	return (flags);
}
uintptr_t la_symbind32(Elf32_Sym *sym, uint_t ndx,
        uintptr_t *refcook, uintptr_t *defcook, uint_t *flags) {
        //if (lmid == LM_ID_BASE)
         (void) printf("symbol: %s loaded\n", sym->st_name);
        return(0);
}

/*uintptr_t la_i86_pltenter(Elf32_Sym *sym, uint_t ndx,
        uintptr_t *refcook, uintptr_t *defcook,
        La_i86_regs *regs, uint_t *flags){
     (void) printf("pltEnter: %s loaded\n", sym->st_name);
        
}*/

void la_activity(uintptr_t *cookie, uint_t flags) {
    if(flags == LA_ACT_ADD)
        (void) printf("Activity Add : %s \n", *cookie );
    
}
