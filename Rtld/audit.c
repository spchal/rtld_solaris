#include        <link.h>
#include        <stdio.h>
 
uint_t
la_version(uint_t version)
{
        return (LAV_CURRENT);
}
 
uint_t
la_objopen(Link_map *lmp, Lmid_t lmid, uintptr_t *cookie)
{
        if (lmid == LM_ID_BASE)
                (void) printf("file: %s loaded\n", lmp->l_name);
        return (LA_FLG_BINDTO);
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
