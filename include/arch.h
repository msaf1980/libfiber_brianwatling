#ifndef _CONCURRENT_ARCH_H_
#define _CONCURRENT_ARCH_H_

#if MSVC
#if _M_IA64
#define CACHE_LINE_SIZE 128 /* Itanium */
#elif _M_X64
#define ARCH_x86_64
#define CACHE_LINE_SIZE 64 /* x86_64 */
#elif _M_X86
#define CACHE_LINE_SIZE 64 /* i386 */
#define ARCH_x86
#endif
#else
#if __powerpc || __ia64__ || __ia64
#define CACHE_LINE_SIZE 128 /* Itanium, PowerPC */
#elif __amd64__
#define ARCH_x86_64
#define CACHE_LINE_SIZE 64 /* x86_64 */
#elif  __sparc__ || __sparc
#define CACHE_LINE_SIZE 64 /* x86_64 */
#elif __i386__
#define CACHE_LINE_SIZE 32 /* i386 */
#elif ARM_CPU_ARM7
/* irrelevant, no consistent cache */
#define CACHE_LINE_SIZE 32
#elif ARM_CPU_ARM926
#define CACHE_LINE_SIZE 32
#elif ARM_CPU_ARM1136
#define CACHE_LINE_SIZE 32
#elif ARM_CPU_ARMEMU
#define CACHE_LINE_SIZE 32
#elif ARM_CPU_CORTEX_A7
#define CACHE_LINE_SIZE 64 /* XXX L1 icache is 32 bytes */
#elif ARM_CPU_CORTEX_A8
#define CACHE_LINE_SIZE 64
#elif ARM_CPU_CORTEX_A9
#define CACHE_LINE_SIZE 32
#elif ARM_CPU_CORTEX_M0 || ARM_CPU_CORTEX_M0_PLUS || ARM_CPU_CORTEX_M3 ||      \
    ARM_CPU_CORTEX_M4
#define CACHE_LINE_SIZE 32
#elif ARM_CPU_CORTEX_M7
#define CACHE_LINE_SIZE 32
#elif ARM_CPU_CORTEX_A15
#define CACHE_LINE_SIZE 64
#elif ARM_CPU_CORTEX_R4F
#define CACHE_LINE_SIZE 64
#endif
#endif
#ifndef CACHE_LINE_SIZE
#error unknown cpu, need to define CACHE_LINE_SIZE
#endif

#endif /* _CONCURRENT_ARCH_H_ */
