#pragma once

#ifndef ABAN_SCALAR_HPP
#define ABAN_SCALAR_HPP




#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <cassert>
#include <cstring>

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
  #define WIN32_LEAN_AND_MEAN
  #define NOCOMM
  #include <windows.h>
  #include <basetsd.h>
#endif




#if defined(IS_OS_WINDOWS)
  /* Empty */
#elif defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
  #define IS_OS_WINDOWS 1
#else
  #define IS_OS_WINDOWS 0
#endif

#if defined(IS_OS_LINUX)
  /* Empty */
#elif defined(__linux__)
  #define IS_OS_LINUX 1
#else
  #define IS_OS_LINUX 0
#endif

#if defined(IS_OS_ANDROID)
  /* Empty */
#elif defined(__ANDROID__)
  #define IS_OS_ANDROID 1
#else
  #define IS_OS_ANDROID 0
#endif

#if defined(IS_OS_EMSCRIPTEN)
  /* Empty */
#elif defined(EMSCRIPTEN) || defined(__EMSCRIPTEN__)
  #define IS_OS_EMSCRIPTEN 1
#else
  #define IS_OS_EMSCRIPTEN 0
#endif

#if defined(IS_COMPILER_GNU)
  /* Empty */
#elif defined(__GNUC__)
  #define IS_COMPILER_GNU	1
#else
  #define IS_COMPILER_GNU 0
#endif

#if defined(IS_COMPILER_TINY_C)
  /* Empty */
#elif defined(__TINYC__)
  #define IS_COMPILER_TINY_C 1
#else
  #define IS_COMPILER_TINY_C 0
#endif

#if defined(IS_COMPILER_LLVM)
  /* Empty */
#elif defined(__llvm__)
  #define IS_COMPILER_LLVM 1
#else
  #define IS_COMPILER_LLVM 0
#endif

#if defined(IS_COMPILER_CLANG)
  /* Empty */
#elif defined(__clang__)
  #define IS_COMPILER_CLANG 1
#else
  #define IS_COMPILER_CLANG 0
#endif

#if defined(IS_COMPILER_MINGW64)
  /* Empty */
#elif defined(__MINGW64__)
  #define IS_COMPILER_MINGW64 1
#else
  #define IS_COMPILER_MINGW64 0
#endif

#if defined(IS_COMPILER_MINGW32)
  /* Empty */
#elif !(IS_COMPILER_MINGW64) && defined(__MINGW32__) && !defined(__MINGW64__)
  #define IS_COMPILER_MINGW32 1
#else
  #define IS_COMPILER_MINGW32 0
#endif

#if defined(IS_COMPILER_MSVC)
  /* Empty */
#elif defined(_MSC_VER) || defined(_MSC_FULL_VER)
  #define IS_COMPILER_MSVC 1
#else
  #define IS_COMPILER_MSVC 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1100)
  #define IS_COMPILER_MSVC_5  1
  #define IS_COMPILER_MSVC_97 1
#else
  #define IS_COMPILER_MSVC_5  0
  #define IS_COMPILER_MSVC_97 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1200)
  #define IS_COMPILER_MSVC_6 1
#else
  #define IS_COMPILER_MSVC_6 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1300)
  #define IS_COMPILER_MSVC_7    1
  #define IS_COMPILER_MSVC_2002 1
#else
  #define IS_COMPILER_MSVC_7    0
  #define IS_COMPILER_MSVC_2002 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1400)
  #define IS_COMPILER_MSVC_8    1
  #define IS_COMPILER_MSVC_2005 1
#else
  #define IS_COMPILER_MSVC_8    0
  #define IS_COMPILER_MSVC_2005 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1500)
  #define IS_COMPILER_MSVC_9    1
  #define IS_COMPILER_MSVC_2008 1
#else
  #define IS_COMPILER_MSVC_9    0
  #define IS_COMPILER_MSVC_2008 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1600)
  #define IS_COMPILER_MSVC_10   1
  #define IS_COMPILER_MSVC_2010 1
#else
  #define IS_COMPILER_MSVC_10   0
  #define IS_COMPILER_MSVC_2010 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1700)
  #define IS_COMPILER_MSVC_11   1
  #define IS_COMPILER_MSVC_2012 1
#else
  #define IS_COMPILER_MSVC_11   0
  #define IS_COMPILER_MSVC_2012 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1800)
  #define IS_COMPILER_MSVC_12   1
  #define IS_COMPILER_MSVC_2013 1
#else
  #define IS_COMPILER_MSVC_12   0
  #define IS_COMPILER_MSVC_2013 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1900)
  #define IS_COMPILER_MSVC_14   1
  #define IS_COMPILER_MSVC_2015 1
#else
  #define IS_COMPILER_MSVC_14   0
  #define IS_COMPILER_MSVC_2015 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1910)
  #define IS_COMPILER_MSVC_15   1
  #define IS_COMPILER_MSVC_2017 1
#else
  #define IS_COMPILER_MSVC_15   0
  #define IS_COMPILER_MSVC_2017 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1920)
  #define IS_COMPILER_MSVC_16   1
  #define IS_COMPILER_MSVC_2019 1
#else
  #define IS_COMPILER_MSVC_16   0
  #define IS_COMPILER_MSVC_2019 0
#endif

#if IS_COMPILER_MSVC && defined(_MSC_VER) && (_MSC_VER >= 1930)
  #define IS_COMPILER_MSVC_17   1
  #define IS_COMPILER_MSVC_2022 1
#else
  #define IS_COMPILER_MSVC_17   0
  #define IS_COMPILER_MSVC_2022 0
#endif

#if defined(__TURBOC__)
  #define IS_COMPILER_TURBOC  1
#else
  #define IS_COMPILER_TURBOC  0
#endif

#if defined(IS_C_PLUS_PLUS)
  /* Empty */
#elif (!IS_COMPILER_MSVC && defined(__cplusplus)) || defined(_MSVC_LANG)
  #define IS_C_PLUS_PLUS 1
#else
  #define IS_C_PLUS_PLUS 0
#endif

#if defined(IS_C_PLUS_PLUS_98)
  /* Empty */
#elif IS_C_PLUS_PLUS && defined(__cplusplus) && __cplusplus >= 199711L
  #define IS_C_PLUS_PLUS_98 1
#else
  #define IS_C_PLUS_PLUS_98 0
#endif

#if defined(IS_C_PLUS_PLUS_11)
  /* Empty */
#elif IS_C_PLUS_PLUS && defined(__cplusplus) && __cplusplus >= 201103L
  #define IS_C_PLUS_PLUS_11 1
#else
  #define IS_C_PLUS_PLUS_11 0
#endif

#if defined(IS_C_PLUS_PLUS_14)
  /* Empty */
#elif IS_C_PLUS_PLUS && defined(__cplusplus) && __cplusplus >= 201402L
  #define IS_C_PLUS_PLUS_14 1
#else
  #define IS_C_PLUS_PLUS_14 0
#endif

#if defined(IS_C_PLUS_PLUS_17)
  /* Empty */
#elif IS_C_PLUS_PLUS && defined(__cplusplus) && __cplusplus >= 201703L
  #define IS_C_PLUS_PLUS_17 1
#else
  #define IS_C_PLUS_PLUS_17 0
#endif

#if defined(IS_C_PLUS_PLUS_20)
  /* Empty */
#elif IS_C_PLUS_PLUS && defined(__cplusplus) && __cplusplus >= 202002L
  #define IS_C_PLUS_PLUS_20 1
#else
  #define IS_C_PLUS_PLUS_20 0
#endif

#if defined(IS_C_PLUS_PLUS_23)
  /* Empty */
#elif IS_C_PLUS_PLUS && defined(__cplusplus) && __cplusplus >= 202302L
  #define IS_C_PLUS_PLUS_23 1
#else
  #define IS_C_PLUS_PLUS_23 0
#endif

#if defined(IS_C)
  /* Empty */
#elif !(IS_C_PLUS_PLUS) && ( defined(__STDC__) || defined(__STDC_VERSION__) || (defined(IS_COMPILER_MSVC)) )
  #define IS_C 1
#else
  #define IS_C 0
#endif

#if defined(IS_C_99)
  /* Empty */
#elif IS_C && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
  #define IS_C_99 1
#else
  #define IS_C_99 0
#endif

#if defined(IS_C_11)
  /* Empty */
#elif IS_C && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
  #define IS_C_11 1
#else
  #define IS_C_11 0
#endif

#if defined(IS_C_17)
  /* Empty */
#elif IS_C && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201710L
  #define IS_C_17 1
#else
  #define IS_C_17 0
#endif

#if defined(IS_C_23)
  /* Empty */
#elif IS_C && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
  #define IS_C_23 1
#else
  #define IS_C_23 0
#endif

#if defined(IS_USING_SDL)
  /* Empty */
#elif defined(USE_SDL) && (USE_SDL != 0)
  #define IS_USING_SDL 1
#else
  #define IS_USING_SDL 0
#endif

#if defined(IS_USING_SDL_3)
  /* Empty */
#elif IS_USING_SDL && (USE_SDL == 3)
  #define IS_USING_SDL_3 1
#else
  #define IS_USING_SDL_3 0
#endif

#if defined(IS_USING_SDL_2)
  /* Empty */
#elif IS_USING_SDL && (USE_SDL == 2)
  #define IS_USING_SDL_2 1
#else
  #define IS_USING_SDL_2 0
#endif

#if defined(IS_USING_SDL_1)
  /* Empty */
#elif IS_USING_SDL && (USE_SDL == 1)
  #define IS_USING_SDL_1 1
#else
  #define IS_USING_SDL_1 0
#endif




/*
███████╗██╗   ██╗███████╗    ██╗███╗   ██╗████████╗
██╔════╝╚██╗ ██╔╝██╔════╝    ██║████╗  ██║╚══██╔══╝
███████╗ ╚████╔╝ ███████╗    ██║██╔██╗ ██║   ██║
╚════██║  ╚██╔╝  ╚════██║    ██║██║╚██╗██║   ██║
███████║   ██║   ███████║    ██║██║ ╚████║   ██║
╚══════╝   ╚═╝   ╚══════╝    ╚═╝╚═╝  ╚═══╝   ╚═╝
*/
#if !(IS_COMPILER_MSVC)
  #if !(IS_OS_WINDOWS && IS_COMPILER_TINY_C)
    #include <unistd.h>
  #endif
  #include <stdint.h>
#endif




/*
███████╗██╗   ██╗███████╗    ███╗   ███╗ █████╗ ████████╗██╗  ██╗
██╔════╝╚██╗ ██╔╝██╔════╝    ████╗ ████║██╔══██╗╚══██╔══╝██║  ██║
███████╗ ╚████╔╝ ███████╗    ██╔████╔██║███████║   ██║   ███████║
╚════██║  ╚██╔╝  ╚════██║    ██║╚██╔╝██║██╔══██║   ██║   ██╔══██║
███████║   ██║   ███████║    ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║
╚══════╝   ╚═╝   ╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝
*/
#if IS_COMPILER_MSVC
  #define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <climits>
#if IS_COMPILER_MSVC
  #define HAVE_M_PI
#endif
#if IS_USING_SDL_3
  #include <SDL3/SDL_stdinc.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL_stdinc.h>
#else
  #error "Failed to detect SDL version."
#endif




/*
███████╗██████╗ ██╗         ██╗      ██████╗  ██████╗
██╔════╝██╔══██╗██║         ██║     ██╔═══██╗██╔════╝
███████╗██║  ██║██║         ██║     ██║   ██║██║  ███╗
╚════██║██║  ██║██║         ██║     ██║   ██║██║   ██║
███████║██████╔╝███████╗    ███████╗╚██████╔╝╚██████╔╝
╚══════╝╚═════╝ ╚══════╝    ╚══════╝ ╚═════╝  ╚═════╝
*/
#if IS_USING_SDL_3
  #include <SDL3/SDL_log.h>
  #include <SDL3/SDL_messagebox.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL_log.h>
  #include <SDL2/SDL_messagebox.h>
  #define SDL_GetLogOutputFunction  SDL_LogGetOutputFunction
  #define SDL_GetLogPriority        SDL_LogGetPriority
  #define SDL_ResetLogPriorities    SDL_LogResetPriorities
  #define SDL_SetLogPriorities      SDL_LogSetAllPriority
  #define SDL_SetLogOutputFunction  SDL_LogSetOutputFunction
  #define SDL_SetLogPriority        SDL_LogSetPriority
  #define SDL_LOG_PRIORITY_COUNT    SDL_NUM_LOG_PRIORITIES
#else
  #error "Failed to detect SDL version."
#endif

#if IS_USING_SDL_3
  #include <SDL3/SDL_init.h>
  typedef enum ESysStatus {
    E_SYS_CONTINUE = SDL_APP_CONTINUE,
    E_SYS_QUIT = SDL_APP_SUCCESS,
    E_SYS_FATALITY = SDL_APP_FAILURE,
  } ESysStatus;
#else
  typedef enum ESysStatus {
    E_SYS_CONTINUE,
    E_SYS_QUIT,
    E_SYS_FATALITY
  } ESysStatus;
#endif

#if IS_USING_SDL_3
  #include <SDL3/SDL_main.h>
  #define SDL_INIT_TIMER 0
#elif IS_USING_SDL_2
  #include <SDL2/SDL.h>
  #define SDL_INIT_GAMEPAD SDL_INIT_GAMECONTROLLER
#else
  #error "Failed to detect SDL version."
#endif

#if IS_USING_SDL_3
  #include <SDL3/SDL_events.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL_events.h>
  enum {
    SDL_EVENT_QUIT = SDL_QUIT
  };
#else
  #error "Failed to detect SDL version."
#endif

#if IS_USING_SDL_3
#elif IS_USING_SDL_2
  #include <SDL2/SDL_video.h>
#define SDL_CreateWindow(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, FLAGS) \
        SDL_CreateWindow(                                           \
          TITLE,                                                    \
          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,         \
          WINDOW_WIDTH, WINDOW_HEIGHT,                              \
          FLAGS                                                     \
        )
#endif




/*
 ██████╗██╗      ██████╗  ██████╗██╗  ██╗
██╔════╝██║     ██╔═══██╗██╔════╝██║ ██╔╝
██║     ██║     ██║   ██║██║     █████╔╝
██║     ██║     ██║   ██║██║     ██╔═██╗
╚██████╗███████╗╚██████╔╝╚██████╗██║  ██╗
 ╚═════╝╚══════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝
*/

#if IS_USING_SDL_3
  #include <SDL3/SDL_timer.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL_timer.h>
  #define SDL_GetTicks SDL_GetTicks64
#else
  #error "Failed to detect SDL version."
#endif

#define MSPS 1000        /* Milliseconds Per Second */
#define USPS 1000000     /* Microseconds Per Second */
#define NSPS 1000000000  /* Nanoseconds Per Second */

/**
 * @brief Get high-resolution performance counter (ticks since SDL init).
 * @return uint64_t Tick count.
 */
#define clockU64() SDL_GetPerformanceCounter()

/**
 * @brief Get performance frequency (ticks per second).
 * @return uint64_t Frequency in ticks/second.
 */
#define clockFrequencyU64() SDL_GetPerformanceFrequency()

/**
 * @brief Get wall-clock time in milliseconds (since SDL init).
 * @return uint64_t Milliseconds.
 */
#define clockMsU64() SDL_GetTicks()




/*
██████╗ ███████╗██████╗ ██╗   ██╗ ██████╗
██╔══██╗██╔════╝██╔══██╗██║   ██║██╔════╝
██║  ██║█████╗  ██████╔╝██║   ██║██║  ███╗
██║  ██║██╔══╝  ██╔══██╗██║   ██║██║   ██║
██████╔╝███████╗██████╔╝╚██████╔╝╚██████╔╝
*/

#ifndef DEBUG
  #define DEBUG 0
#endif

#if IS_COMPILER_MSVC || IS_OS_WINDOWS
  #define _ab_debugBreak__ DebugBreak();
#else
  #define _ab_debugBreak__ raise(SIGTRAP);
#endif

#define _ab_print__ SDL_Log

#if !defined(NDEBUG) || DEBUG
  #define debugBreak _ab_debugBreak__
  #define print _ab_print__
#else /* !defined(NDEBUG) */
  #ifndef assert
    #define assert(CONDITION)
  #endif /* assert */
  #define debugBreak
  #define print(...)
  #define perror(...)
  #ifdef assert
    #undef assert
  #endif
  #define assert(...)
#endif /* !defined(NDEBUG) */

/** Like debugBreak but should work on release as well. */
#define hardBreak _ab_debugBreak__
/** Like print but should work on release as well. */
#define hardPrint _ab_print__

#define _stringify__(X) #X
#define stringify(X) _stringify__(X)


/*
 █████╗ ███████╗███████╗███████╗██████╗ ████████╗
██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗╚══██╔══╝
███████║███████╗███████╗█████╗  ██████╔╝   ██║
██╔══██║╚════██║╚════██║██╔══╝  ██╔══██╗   ██║
██║  ██║███████║███████║███████╗██║  ██║   ██║
╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝
*/
#if IS_C_11
  #define staticAssert(EXPRESSION, MESSAGE) \
  static_assert((EXPRESSION), #MESSAGE);
#else
  #define staticAssert(EXPRESSION, MESSAGE) \
  typedef char staticAssert_##MESSAGE[(EXPRESSION) ? 1 : -1];
#endif
/*  System Assert Include End */




/*
██████╗  ██████╗  ██████╗ ██╗
██╔══██╗██╔═══██╗██╔═══██╗██║
██████╔╝██║   ██║██║   ██║██║
██╔══██╗██║   ██║██║   ██║██║
██████╔╝╚██████╔╝╚██████╔╝███████╗
╚═════╝  ╚═════╝  ╚═════╝ ╚══════╝
*/
#if  !(IS_C_PLUS_PLUS)  &&  !(IS_C_23)  &&  ( !(IS_COMPILER_MSVC) || IS_COMPILER_MSVC_2013 )
  #include <stdbool.h>
#endif
#if IS_C_PLUS_PLUS || IS_C_23
  /* empty */
#elif defined(_STDBOOL_H) || defined(__STDBOOL_H)
  /* empty */
#elif defined(bool) && defined(true) && defined(false)
  /* empty */
#elif defined(SDL_stdinc_h_)
  #define bool SDL_bool
  #define false SDL_FALSE
  #define true SDL_TRUE
#elif   IS_C99   ||       ( !(IS_C_PLUS_PLUS  &&  IS_C  &&  IS_COMPILER_MSVC_2013) )
  #define bool _Bool
  #define false 0
  #define true 1
#else
  typedef enum {
    false = 0,
    true = 1
  } bool;
#endif


/*
███╗   ██╗██╗   ██╗██╗     ██╗
████╗  ██║██║   ██║██║     ██║
██╔██╗ ██║██║   ██║██║     ██║
██║╚██╗██║██║   ██║██║     ██║
██║ ╚████║╚██████╔╝███████╗███████╗
╚═╝  ╚═══╝ ╚═════╝ ╚══════╝╚══════╝
*/
#if IS_C_PLUS_PLUS_11
#define null nullptr
#else
#if !defined(NULL)
#include <stddef.h>
#endif
#define null NULL
#endif


/*
██████╗ ████████╗██████╗
██╔══██╗╚══██╔══╝██╔══██╗
██████╔╝   ██║   ██████╔╝
██╔═══╝    ██║   ██╔══██╗
██║        ██║   ██║  ██║
╚═╝        ╚═╝   ╚═╝  ╚═╝
*/
/* Exponent that results in the pointer size in byte. */
#if ULONG_MAX == 0xFFFFFFFFU /* system is 32 bit. */
#define PTR_EXPONENT 2 /* 32-bit, 4 byte, 2^2. */
#elif ULONG_MAX == UINT64_MAX
#define PTR_EXPONENT 3 /* 64-bit, 8 byte, 2^3. */
#else
#error "Failed to recognize pointer size."
#endif
#define PTR_SIZE ( 1 << PTR_EXPONENT ) /* 2^PTR_EXPONENT */
#define PTR_BITS  ( PTR_SIZE << 3 ) /* 8×PTR_SIZE */
#define IS_PTR_32_BIT ( PTR_BITS == 32 )
#define IS_PTR_64_BIT ( PTR_BITS == 64 )
staticAssert(sizeof(void*) == (1<<PTR_EXPONENT), PTR_EXPONENT_IS_PICKED_INCORRECTLY)


/*
 █████╗ ██╗     ██╗ ██████╗ ███╗   ██╗
██╔══██╗██║     ██║██╔════╝ ████╗  ██║
███████║██║     ██║██║  ███╗██╔██╗ ██║
██╔══██║██║     ██║██║   ██║██║╚██╗██║
██║  ██║███████╗██║╚██████╔╝██║ ╚████║
╚═╝  ╚═╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝
*/
#if IS_C_PLUS_PLUS_11
  /* Empty */
#elif defined(alignof)
  /* Empty */
#elif IS_C_11
  #define alignof(T) (_Alignof(T))
#elif IS_COMPILER_MSVC
  #define alignof(T) (__alignof(T))
#else
  #define alignof(T) (__alignof__(T))
#endif




/*
██╗███╗   ██╗████████╗███████╗ ██████╗ ███████╗██████╗ ███████╗
██║████╗  ██║╚══██╔══╝██╔════╝██╔════╝ ██╔════╝██╔══██╗██╔════╝
██║██╔██╗ ██║   ██║   █████╗  ██║  ███╗█████╗  ██████╔╝███████╗
██║██║╚██╗██║   ██║   ██╔══╝  ██║   ██║██╔══╝  ██╔══██╗╚════██║
██║██║ ╚████║   ██║   ███████╗╚██████╔╝███████╗██║  ██║███████║
╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝
*/

typedef Sint8 i8;
typedef Sint16 i16;
typedef Sint32 i32;
typedef Sint64 i64;
typedef Uint8 u8;
typedef Uint16 u16;
typedef Uint32 u32;
typedef Uint64 u64;
typedef size_t usize;
#if IS_OS_WINDOWS
  typedef SSIZE_T isize;
#else
  typedef ssize_t isize;
#endif

#if IS_C_PLUS_PLUS_98
  #define castI8(value) (static_cast<i8>(value))
  #define castI16(value) (static_cast<i16>(value))
  #define castI32(value) (static_cast<i32>(value))
  #define castI64(value) (static_cast<i64>(value))
  #define castU8(value) (static_cast<u8>(value))
  #define castU16(value) (static_cast<u16>(value))
  #define castU32(value) (static_cast<u32>(value))
  #define castU64(value) (static_cast<u64>(value))
  #define castUSize(value) (static_cast<usize>(value))
  #define castISize(value) (static_cast<isize>(value))
  #define castPtr(value) (static_cast<void*>(value))
  #define castFloat(value) (static_cast<float>(value))
  #define castDouble(value) (static_cast<double>(value))
#else
  #define castI8(value) ((i8)(value))
  #define castI16(value) ((i16)(value))
  #define castI32(value) ((i32)(value))
  #define castI64(value) ((i64)(value))
  #define castU8(value) ((u8)(value))
  #define castU16(value) ((u16)(value))
  #define castU32(value) ((u32)(value))
  #define castU64(value) ((u64)(value))
  #define castUSize(value) ((usize)(value))
  #define castISize(value) ((isize)(value))
  #define castPtr(value) ((void*)(value))
  #define castFloat(value) ((float)(value))
  #define castDouble(value) ((double)(value))
#endif

#define I8_WIDTH 8
#define I16_WIDTH 16
#define I32_WIDTH 32
#define I64_WIDTH 64
#define U8_WIDTH 8
#define U16_WIDTH 16
#define U32_WIDTH 32
#define U64_WIDTH 64
#if IS_PTR_32_BIT
  #define ISIZE_WIDTH I32_WIDTH
  #define USIZE_WIDTH U32_WIDTH
#elif IS_PTR_64_BIT
  #define ISIZE_WIDTH I64_WIDTH
  #define USIZE_WIDTH U64_WIDTH
#endif

#define I8_MIN SDL_MIN_SINT8
#define I8_MAX SDL_MAX_SINT8
#define I16_MIN SDL_MIN_SINT16
#define I16_MAX SDL_MAX_SINT16
#define I32_MIN SDL_MIN_SINT32
#define I32_MAX SDL_MAX_SINT32
#define I64_MIN SDL_MIN_SINT64
#define I64_MAX SDL_MAX_SINT64
#define U8_MIN SDL_MIN_UINT8
#define U8_MAX SDL_MAX_UINT8
#define U16_MIN SDL_MIN_UINT16
#define U16_MAX SDL_MAX_UINT16
#define U32_MIN SDL_MIN_UINT32
#define U32_MAX SDL_MAX_UINT32
#define U64_MIN SDL_MIN_UINT64
#define U64_MAX SDL_MAX_UINT64
#if IS_PTR_32_BIT
  #define ISIZE_MIN I32_MIN
  #define ISIZE_MAX I32_MAX
  #define USIZE_MIN U32_MIN
  #define USIZE_MAX U32_MAX
#elif IS_PTR_64_BIT
  #define ISIZE_MIN I64_MIN
  #define ISIZE_MAX I64_MAX
  #define USIZE_MIN U64_MIN
  #define USIZE_MAX U64_MAX
#endif

/** Maximum number that can be held by this type.
 *  Assumes unsigned integer type.
 */
#define maxOfUnsignedIntegerType(TYPE) (tttUSize(mul1BL(BINLOG_8, sizeof(TYPE))) - 1)

/** Capacity. Unique states that can be held by this type.
 *  Assumes unsigned integer type.
 */
#define capOfUnsignedIntegerType(TYPE) tttUSize(mul1BL(BINLOG_8, sizeof(TYPE)))




/*
 ██████╗██╗     ███████╗
██╔════╝██║     ╚══███╔╝
██║     ██║       ███╔╝
██║     ██║      ███╔╝
╚██████╗███████╗███████╗
 ╚═════╝╚══════╝╚══════╝
*/
#if IS_COMPILER_GNU || IS_COMPILER_LLVM || IS_COMPILER_CLANG
  #define clzU32Inline(x) ((x) == 0 ? 32 : __builtin_clz(x))
  #define clzU64Inline(x) ((x) == 0 ? 64 : __builtin_clzll(x))
#else
#define clzU32Inline(x) (           \
  (x) == 0 ? 32 :                   \
  (x) & castU32(0x80000000) ?  0 :  \
  (x) & castU32(0x40000000) ?  1 :  \
  (x) & castU32(0x20000000) ?  2 :  \
  (x) & castU32(0x10000000) ?  3 :  \
  (x) & castU32(0x08000000) ?  4 :  \
  (x) & castU32(0x04000000) ?  5 :  \
  (x) & castU32(0x02000000) ?  6 :  \
  (x) & castU32(0x01000000) ?  7 :  \
  (x) & castU32(0x00800000) ?  8 :  \
  (x) & castU32(0x00400000) ?  9 :  \
  (x) & castU32(0x00200000) ? 10 :  \
  (x) & castU32(0x00100000) ? 11 :  \
  (x) & castU32(0x00080000) ? 12 :  \
  (x) & castU32(0x00040000) ? 13 :  \
  (x) & castU32(0x00020000) ? 14 :  \
  (x) & castU32(0x00010000) ? 15 :  \
  (x) & castU32(0x00008000) ? 16 :  \
  (x) & castU32(0x00004000) ? 17 :  \
  (x) & castU32(0x00002000) ? 18 :  \
  (x) & castU32(0x00001000) ? 19 :  \
  (x) & castU32(0x00000800) ? 20 :  \
  (x) & castU32(0x00000400) ? 21 :  \
  (x) & castU32(0x00000200) ? 22 :  \
  (x) & castU32(0x00000100) ? 23 :  \
  (x) & castU32(0x00000080) ? 24 :  \
  (x) & castU32(0x00000040) ? 25 :  \
  (x) & castU32(0x00000020) ? 26 :  \
  (x) & castU32(0x00000010) ? 27 :  \
  (x) & castU32(0x00000008) ? 28 :  \
  (x) & castU32(0x00000004) ? 29 :  \
  (x) & castU32(0x00000002) ? 30 :  \
  (x) & castU32(0x00000001) ? 31 :  \
  32                                \
)
#define clzU64Inline(x) (                   \
  (x) == 0 ? 64 :                           \
  (x) & castU64(0x8000000000000000) ?  0 :  \
  (x) & castU64(0x4000000000000000) ?  1 :  \
  (x) & castU64(0x2000000000000000) ?  2 :  \
  (x) & castU64(0x1000000000000000) ?  3 :  \
  (x) & castU64(0x0800000000000000) ?  4 :  \
  (x) & castU64(0x0400000000000000) ?  5 :  \
  (x) & castU64(0x0200000000000000) ?  6 :  \
  (x) & castU64(0x0100000000000000) ?  7 :  \
  (x) & castU64(0x0080000000000000) ?  8 :  \
  (x) & castU64(0x0040000000000000) ?  9 :  \
  (x) & castU64(0x0020000000000000) ? 10 :  \
  (x) & castU64(0x0010000000000000) ? 11 :  \
  (x) & castU64(0x0008000000000000) ? 12 :  \
  (x) & castU64(0x0004000000000000) ? 13 :  \
  (x) & castU64(0x0002000000000000) ? 14 :  \
  (x) & castU64(0x0001000000000000) ? 15 :  \
  (x) & castU64(0x0000800000000000) ? 16 :  \
  (x) & castU64(0x0000400000000000) ? 17 :  \
  (x) & castU64(0x0000200000000000) ? 18 :  \
  (x) & castU64(0x0000100000000000) ? 19 :  \
  (x) & castU64(0x0000080000000000) ? 20 :  \
  (x) & castU64(0x0000040000000000) ? 21 :  \
  (x) & castU64(0x0000020000000000) ? 22 :  \
  (x) & castU64(0x0000010000000000) ? 23 :  \
  (x) & castU64(0x0000008000000000) ? 24 :  \
  (x) & castU64(0x0000004000000000) ? 25 :  \
  (x) & castU64(0x0000002000000000) ? 26 :  \
  (x) & castU64(0x0000001000000000) ? 27 :  \
  (x) & castU64(0x0000000800000000) ? 28 :  \
  (x) & castU64(0x0000000400000000) ? 29 :  \
  (x) & castU64(0x0000000200000000) ? 30 :  \
  (x) & castU64(0x0000000100000000) ? 31 :  \
  (x) & castU64(0x0000000080000000) ? 32 :  \
  (x) & castU64(0x0000000040000000) ? 33 :  \
  (x) & castU64(0x0000000020000000) ? 34 :  \
  (x) & castU64(0x0000000010000000) ? 35 :  \
  (x) & castU64(0x0000000008000000) ? 36 :  \
  (x) & castU64(0x0000000004000000) ? 37 :  \
  (x) & castU64(0x0000000002000000) ? 38 :  \
  (x) & castU64(0x0000000001000000) ? 39 :  \
  (x) & castU64(0x0000000000800000) ? 40 :  \
  (x) & castU64(0x0000000000400000) ? 41 :  \
  (x) & castU64(0x0000000000200000) ? 42 :  \
  (x) & castU64(0x0000000000100000) ? 43 :  \
  (x) & castU64(0x0000000000080000) ? 44 :  \
  (x) & castU64(0x0000000000040000) ? 45 :  \
  (x) & castU64(0x0000000000020000) ? 46 :  \
  (x) & castU64(0x0000000000010000) ? 47 :  \
  (x) & castU64(0x0000000000008000) ? 48 :  \
  (x) & castU64(0x0000000000004000) ? 49 :  \
  (x) & castU64(0x0000000000002000) ? 50 :  \
  (x) & castU64(0x0000000000001000) ? 51 :  \
  (x) & castU64(0x0000000000000800) ? 52 :  \
  (x) & castU64(0x0000000000000400) ? 53 :  \
  (x) & castU64(0x0000000000000200) ? 54 :  \
  (x) & castU64(0x0000000000000100) ? 55 :  \
  (x) & castU64(0x0000000000000080) ? 56 :  \
  (x) & castU64(0x0000000000000040) ? 57 :  \
  (x) & castU64(0x0000000000000020) ? 58 :  \
  (x) & castU64(0x0000000000000010) ? 59 :  \
  (x) & castU64(0x0000000000000008) ? 60 :  \
  (x) & castU64(0x0000000000000004) ? 61 :  \
  (x) & castU64(0x0000000000000002) ? 62 :  \
  (x) & castU64(0x0000000000000001) ? 63 :  \
  64                                        \
)
#endif
#if IS_PTR_32_BIT
  #define clzUSizeInline clzU32Inline
#elif IS_PTR_64_BIT
  #define clzUSizeInline clzU64Inline
#endif




/*
████████╗████████╗████████╗
╚══██╔══╝╚══██╔══╝╚══██╔══╝
   ██║      ██║      ██║
   ██║      ██║      ██║
   ██║      ██║      ██║
   ╚═╝      ╚═╝      ╚═╝
*/
/** Two To The X */
#define TTT_0 1
#define TTT_1 2
#define TTT_2 4
#define TTT_3 8
#define TTT_4 16
#define TTT_5 32
#define TTT_6 64
#define TTT_7 128
#define TTT_8 256
#define TTT_9 512
#define TTT_10 1024
#define TTT_11 2048
#define TTT_12 4096
#define TTT_13 8192
#define TTT_14 16384
#define TTT_15 32768
#define TTT_16 65536
#define TTT_17 131072
#define TTT_18 262144
#define TTT_19 524288
#define TTT_20 1048576
#define TTT_21 2097152
#define TTT_22 4194304
#define TTT_23 8388608
#define TTT_24 16777216
#define TTT_25 33554432
#define TTT_26 67108864
#define TTT_27 134217728
#define TTT_28 268435456
#define TTT_29 536870912
#define TTT_30 1073741824
#define TTT_31 2147483648u
#define TTT_32 4294967296ul
#define TTT_33 8589934592ul
#define TTT_34 17179869184ul
#define TTT_35 34359738368ul
#define TTT_36 68719476736ul
#define TTT_37 137438953472ul
#define TTT_38 274877906944ul
#define TTT_39 549755813888ul
#define TTT_40 1099511627776ul
#define TTT_41 2199023255552ul
#define TTT_42 4398046511104ul
#define TTT_43 8796093022208ul
#define TTT_44 17592186044416ul
#define TTT_45 35184372088832ul
#define TTT_46 70368744177664ul
#define TTT_47 140737488355328ul
#define TTT_48 281474976710656ul
#define TTT_49 562949953421312ul
#define TTT_50 1125899906842624ul
#define TTT_51 2251799813685248ul
#define TTT_52 4503599627370496ul
#define TTT_53 9007199254740992ul
#define TTT_54 18014398509481984ul
#define TTT_55 36028797018963968ul
#define TTT_56 72057594037927936ul
#define TTT_57 144115188075855872ul
#define TTT_58 288230376151711744ul
#define TTT_59 576460752303423488ul
#define TTT_60 1152921504606846976ul
#define TTT_61 2305843009213693952ul
#define TTT_62 4611686018427387904ul
#define TTT_63 9223372036854775808ul
/** Two To The Power of X */
#define tttU32(POWER)  ( castU32(1) << (POWER) )
#define tttU64(POWER)  ( castU64(1) << (POWER) )
#if IS_PTR_32_BIT
  #define tttUSize tttU32
#elif IS_PTR_64_BIT
  #define tttUSize tttU64
#endif




/*
██████╗ ██╗███╗   ██╗██╗      ██████╗  ██████╗
██╔══██╗██║████╗  ██║██║     ██╔═══██╗██╔════╝
██████╔╝██║██╔██╗ ██║██║     ██║   ██║██║  ███╗
██╔══██╗██║██║╚██╗██║██║     ██║   ██║██║   ██║
██████╔╝██║██║ ╚████║███████╗╚██████╔╝╚██████╔╝
╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝ ╚═════╝  ╚═════╝
*/
#define BINLOG_1          0
#define BINLOG_2          1
#define BINLOG_4          2
#define BINLOG_8          3
#define BINLOG_16         4
#define BINLOG_32         5
#define BINLOG_64         6
#define BINLOG_128        7
#define BINLOG_256        8
#define BINLOG_512        9
#define BINLOG_1024       10
#define BINLOG_2048       11
#define BINLOG_4096       12
#define BINLOG_8192       13
#define BINLOG_16384      14
#define BINLOG_32768      15
#define BINLOG_65536      16
#define BINLOG_131072     17
#define BINLOG_262144     18
#define BINLOG_524288     19
#define BINLOG_1048576    20
#define BINLOG_2097152    21
#define BINLOG_4194304    22
#define BINLOG_8388608    23
#define BINLOG_16777216   24
#define BINLOG_33554432   25
#define BINLOG_67108864   26
#define BINLOG_134217728  27
#define BINLOG_268435456  28
#define BINLOG_536870912  29
#define BINLOG_1073741824 30
#define BINLOG_2147483648 31
#define BINLOG_4294967296 32

#define binlogFloorInline(n) (                         \
  castU64(n) == castU64(0) ? -1                        \
  : (int)( (U64_WIDTH-1) - clzU64Inline(castU64(n)) )  \
)

#define binlogCeilInline(n) (                               \
  castU64(n) == castU64(0) ? -1 : (                         \
    castU64(0) == (castU64(n) & (castU64(n) - castU64(1)))  \
    ? binlogFloorInline(n)                                  \
    : binlogFloorInline(n) + 1                              \
  )                                                         \
)

/** @param MULTIPLIER_EXPONENT Should be an exponent to base 2,
 *  that result in your multiplier.
 *  So, multiplier should be a positive power of 2.
 *  @param MULTIPICALND Any positive integer.
 */
#define mul1BL(MULTIPLIER_EXPONENT, MULTIPLICAND) ((MULTIPLICAND) << (MULTIPLIER_EXPONENT))

/** Result would be binary logarithm of the result number.
 *  @param MULTIPLIER_EXPONENT Any positive integer that represent binary logarithm of another number.
 *  @param MULTIPLICAND_EXPONENT Any positive integer that represent binary logarithm of another number.
 */
#define mul2BL(MULTIPLIER_EXPONENT, MULTIPLICAND_EXPONENT) ((MULTIPLICAND_EXPONENT) + (MULTIPLIER_EXPONENT))

/** Result would be binary logarithm of the result number.
 *  @param DIVIDEND_EXPONENT Any positive integer that represent binary logarithm of another number.
 *  @param DIVISOR_EXPONENT Any positive integer that represent binary logarithm of another number.
 */
#define div2BL(DIVIDEND_EXPONENT, DIVISOR_EXPONENT) ((DIVIDEND_EXPONENT) - (DIVISOR_EXPONENT))

/** @param NUMBER Any positive integer.
 */
#define doubleBL(NUMBER) ((NUMBER) << 1)

/** @param NUMBER Any positive integer.
 */
#define halfBL(NUMBER) ((NUMBER) >> 1)

/** @param DIVIDEND Any positive integer.
 *  @param DIVISOR_EXPONENT should be an exponent to base 2,
 *  that results in your divisor.
 *  So, divisor should be a positive power of 2.
 */
#define div1BL(DIVIDEND, DIVISOR_EXPONENT) ((DIVIDEND) >> (DIVISOR_EXPONENT))

/** @param DIVIDEND Any positive integer.
 *  @param DIVISOR Should be a positive power of 2.
 */
#define remBL(DIVIDEND, DIVISOR) ((DIVIDEND) & ((DIVISOR) - 1 ))

/** @param NUMBER Any positive integer.
 */
#define isEvenBL(NUMBER) ( ((NUMBER)&1) == 0 )

/** @param NUMBER Any positive integer.
 */
#define isOddBL(NUMBER) ( ((NUMBER)&1) != 0 )




#define F32_EPSILON FLT_EPSILON
#define F64_EPSILON DBL_EPSILON
#define feq(a, b, epsilon) (fabs(a - b) < epsilon ? true : false)


class IEngine {
public:
  virtual ESysStatus preSdlInit(int, char**) = 0;
  virtual ESysStatus initSdl(int, char**) = 0;
  virtual ESysStatus initEngine(int, char**) = 0;
  virtual ESysStatus eventSdl(const SDL_Event*) = 0;
  virtual ESysStatus stepEngine() = 0;
  virtual void       shutEngine() = 0;
  virtual void       shutSdl() = 0;


  /* Target milliseconds per step.
     Should be sub second.
     Set to zero for uncapped step frequency.
     To calculate this you can use following formula:
       (millisecond_per_seconds / target_frequency) => (1000 / 260)
       Also, there is a macro name `MSPS` in `Scalar.hpp`
       which is a constant for 'millisecond per seconds'.
   */
  u32 target_delta_ms;

  int exit_code;

  IEngine() : target_delta_ms(0), exit_code(EXIT_SUCCESS) {}
  virtual ~IEngine() {}

};



#endif /* ABAN_SCALAR_HPP */
