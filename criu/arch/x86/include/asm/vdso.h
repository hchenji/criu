#ifndef __CR_ASM_VDSO_H__
#define __CR_ASM_VDSO_H__

#include "asm/int.h"
#include "asm-generic/vdso.h"

/* This definition is used in pie/util-vdso.c to initialize the vdso symbol
 * name string table 'vdso_symbols'
 */

/*
 * This is a minimal amount of symbols
 * we should support at the moment.
 */
#define VDSO_SYMBOL_MAX	7

#define ARCH_VDSO_SYMBOLS			\
	"__vdso_clock_gettime",			\
	"__vdso_getcpu",			\
	"__vdso_gettimeofday",			\
	"__vdso_time",				\
	"__kernel_vsyscall",			\
	"__kernel_sigreturn",			\
	"__kernel_rt_sigreturn"

#ifndef ARCH_MAP_VDSO_32
# define ARCH_MAP_VDSO_32		0x2002
#endif

#ifndef ARCH_MAP_VDSO_64
# define ARCH_MAP_VDSO_64		0x2003
#endif

#if defined(CONFIG_COMPAT) && !defined(__ASSEMBLY__)
struct vdso_symtable;
extern int vdso_fill_symtable(uintptr_t mem, size_t size,
			      struct vdso_symtable *t);
extern int vdso_fill_symtable_compat(uintptr_t mem, size_t size,
				     struct vdso_symtable *t);

static inline int __vdso_fill_symtable(uintptr_t mem, size_t size,
			struct vdso_symtable *t, bool compat_vdso)
{
	if (compat_vdso)
		return vdso_fill_symtable_compat(mem, size, t);
	else
		return vdso_fill_symtable(mem, size, t);
}
#endif

#endif /* __CR_ASM_VDSO_H__ */
