# Linux Memory Barriers

Linux provides functions for use within the kernel.


## Software Memory Barriers

```c
#include <asm/barrier.h>
void barrier(void);
```

This is compiler-specific:

```c
// <asm/barrier.h>
void barrier(void);
#include <asm-generic/barrier.h>

// asm-generic/barrier.h
#include <linux/compiler.h>

// <linux/compiler.h>
#ifdef __GNUC__
#include <linux/compiler-gcc.h>
#endif

/* Intel compiler defines __GNUC__. So we will overwrite implementations
 * coming from above header files here
 */
#ifdef __INTEL_COMPILER
# include <linux/compiler-intel.h>
#endif

/* Clang compiler defines __GNUC__. So we will overwrite implementations
 * coming from above header files here
 */
#ifdef __clang__
#include <linux/compiler-clang.h>
#endif

/* Optimization barrier */
#ifndef barrier
# define barrier() __memory_barrier()
#endif
```

The kernel includes compiler-specific header files to allow for compiler-specific definitions of `barrier()` but
provides a fallback definition of `barrier()`: `__memory_barrier()`. Note that `__memory_barrier()` is not implemented
by GCC or Clang!

For GCC (inherited by Clang):

```c
#ifdef __GNUC__
#include <linux/compiler-gcc.h>
#endif
```

Intel compilers redefine this:

```c
/* Intel ECC compiler doesn't support gcc specific asm stmts.
 * It uses intrinsics to do the equivalent things.
 */
#undef barrier
#define barrier() __memory_barrier()
```

This function seems to be an Intel-specific operation.

Linux also provides the macro `OPTIMIZER_HIDE_VAR()`. This operates on a single variable instead of all registers.

This macro is defined similarly:

```c
// <linux/compiler-gcc.h>
/* Make the optimizer believe the variable can be manipulated arbitrarily. */
#define OPTIMIZER_HIDE_VAR(var)                     \
    __asm__ ("" : "=r" (var) : "0" (var))

// <linux/clang.h>
// empty - inherit from gcc

// <linux/compiler-intel.h>
/* This should act as an optimization barrier on var.
 * Given that this compiler does not have inline assembly, a compiler barrier
 * is the best we can do.
 */
#undef OPTIMIZER_HIDE_VAR
#define OPTIMIZER_HIDE_VAR(var) barrier()

// <linux/compiler.h>
#ifndef OPTIMIZER_HIDE_VAR
#define OPTIMIZER_HIDE_VAR(var) barrier()
#endif
```

Again, this allows for a compiler-specific operation to "hide" a specific variable from the optimizer. TODO how does
this relate to the volatile keyword?


## Hardware Memory Barriers

```c
#include <arch/x86/include/asm/barrier.h>

#ifdef CONFIG_X86_32
#define mb() asm volatile(ALTERNATIVE("lock; addl $0,0(%%esp)", "mfence", \
                      X86_FEATURE_XMM2) ::: "memory", "cc")
#define rmb() asm volatile(ALTERNATIVE("lock; addl $0,0(%%esp)", "lfence", \
                       X86_FEATURE_XMM2) ::: "memory", "cc")
#define wmb() asm volatile(ALTERNATIVE("lock; addl $0,0(%%esp)", "sfence", \
                       X86_FEATURE_XMM2) ::: "memory", "cc")
#else
#define mb()    asm volatile("mfence":::"memory")
#define rmb()   asm volatile("lfence":::"memory")
#define wmb()   asm volatile("sfence" ::: "memory")

#include <asm-generic/barrier.h>
#endif
```

```c
// <arch/avr32/include/asm/barrier.h>

/*
 * Weirdest thing ever.. no full barrier, but it has a write barrier!
 */
#define wmb()   asm volatile("sync 0" : : : "memory")

#include <asm-generic/barrier.h>
```

```c
// <arch/xtensa/include/asm/barrier.h>

#define mb()  ({ __asm__ __volatile__("memw" : : : "memory"); })
#define rmb() barrier()
#define wmb() mb()

#include <asm-generic/barrier.h>
```

ARM can get complex:

```c
// arch/arm/include/asm/barrier.h
#if defined(CONFIG_ARM_DMA_MEM_BUFFERABLE) || defined(CONFIG_SMP)
#define mb()        __arm_heavy_mb()
#define rmb()       dsb()
#define wmb()       __arm_heavy_mb(st)
#define dma_rmb()   dmb(osh)
#define dma_wmb()   dmb(oshst)
#else
#define mb()        barrier()
#define rmb()       barrier()
#define wmb()       barrier()
#define dma_rmb()   barrier()
#define dma_wmb()   barrier()
#endif

#include <asm-generic/barrier.h>
```

```c
// arch/arm64/include/asm/barrier.h
#define dsb(opt)    asm volatile("dsb " #opt : : : "memory")

#define mb()        dsb(sy)
#define rmb()       dsb(ld)
#define wmb()       dsb(st)

#include <asm-generic/barrier.h>
```

```c
// arch/blackfin/include/asm/barrier.h

/* Force Core data cache coherence */
# define mb()   do { barrier(); smp_check_barrier(); smp_mark_barrier(); } while (0)
# define rmb()  do { barrier(); smp_check_barrier(); } while (0)
# define wmb()  do { barrier(); smp_mark_barrier(); } while (0)

#include <asm-generic/barrier.h>
```

OpenRISC does not implement `<asm/barrier.h>`!
