
/*
 * This is from a demo program of link_audit by Oracle with minor changes
 */
#ifndef _MACH_DOT_H
#define	_MACH_DOT_H

#include <sys/reg.h>
#include <sys/types.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	GETARG0(regset)		(((ulong_t *)regset->lr_esp)[1])
#define	GETARG1(regset)		(((ulong_t *)regset->lr_esp)[2])
#define	GETARG2(regset)		(((ulong_t *)regset->lr_esp)[3])
#define	GETARG3(regset)		(((ulong_t *)regset->lr_esp)[4])
#define	GETARG4(regset)		(((ulong_t *)regset->lr_esp)[5])
#define	GETARG5(regset)		(((ulong_t *)regset->lr_esp)[6])

#define	GETFRAME(regset)	(regset->lr_ebp)
#define	GETPREVPC(regset)	(*(uintptr_t *)regset->lr_esp)

#ifdef	__cplusplus
}
#endif

#endif /* _MACH_DOT_H */

