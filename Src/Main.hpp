#pragma once

#ifndef AB_MAIN_HPP
#define AB_MAIN_HPP




#include <cstdio>
#include <cstdlib>
#include <csignal>
// ReSharper disable once CppUnusedIncludeDirective
#include <cassert>
// ReSharper disable once CppUnusedIncludeDirective
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

/** Can the window subsystem handle and
 *    provide multiple windows simultaneously.
 *  Or the system only works with one main
 *    window alone?
 */
#if defined(IS_MULTI_WINDOW_SUPPORTED)
  /* Empty */
#elif IS_USING_SDL_1
  #define IS_MULTI_WINDOW_SUPPORTED 0
#elif IS_OS_LINUX || IS_OS_WINDOWS
  #define IS_MULTI_WINDOW_SUPPORTED 1
#else
  #define IS_MULTI_WINDOW_SUPPORTED 0
#endif

#if defined(AB_UUID)
  /* Empty */
#else
  #define AB_UUID "2c76398e-612f-4bb0-ada6-d2ef8fa68246"
#endif

#if defined(AB_VERSION_DATE)
  /* Empty */
#else
  #define AB_VERSION_DATE 8503
#endif

#if defined(AB_VERSION_EDITION)
  /* Empty */
#else
  #define AB_VERSION_EDITION 1
#endif

#if defined(AB_VERSION_MAJOR)
  /* Empty */
#else
  #define AB_VERSION_DATE 0
#endif

#if defined(AB_VERSION_MINOR)
  /* Empty */
#else
  #define AB_VERSION_MINOR 1
#endif

#if defined(AB_VERSION_PATCH)
  /* Empty */
#else
  #define AB_VERSION_PATCH 0
#endif

#if defined(AB_VULKAN)
  /* Empty */
#else
  #define AB_VULKAN 0
#endif

#if defined(AB_CONCUR)
  /* Empty */
#else
  #define AB_CONCUR 0
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
#elif IS_USING_SDL_1
  #include <SDL/SDL_stdinc.h>
#else
  #error "Failed to detect SDL version."
#endif




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
#elif   IS_C_99   ||       ( !(IS_C_PLUS_PLUS  &&  IS_C  &&  IS_COMPILER_MSVC_2013) )
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
   ██████╗ ██████╗ ███╗   ██╗ ██████╗██╗   ██╗██████╗
  ██╔════╝██╔═══██╗████╗  ██║██╔════╝██║   ██║██╔══██╗
  ██║     ██║   ██║██╔██╗ ██║██║     ██║   ██║██████╔╝
  ██║     ██║   ██║██║╚██╗██║██║     ██║   ██║██╔══██╗
  ╚██████╗╚██████╔╝██║ ╚████║╚██████╗╚██████╔╝██║  ██║
   ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝
*/

/*  A note about SDL1 Concur support.
 *  SDL1 is at the edge of our compatibility support.
 *  It lacks full implementation for all SDL1 supported platforms.
 *  It lacks MutexTryLock function.
 *  It only supports atomics on modern versions of two specific compilers (gcc, clang).
 *  And there is a known possible bug that may or may not cause SemaphoreWaitTimeout to
 *    report Failure in case of just a timeout. (On some SDL 1.2.15 implementations.)
 *  SDL1 support exist at the very edge of our compatibility support, just to make builds
 *    on some older GNU/Linux distros possible and convenient; the ones that does not come
 *    SDL2 in their official repositories. This is for accessibility mostly, so you don't
 *    have to build SDL2 from source, or get it from an unofficial repository.
 *  Or if you want to actually do push the compatibility and add full SDl1 support by yourself!
 */

/** CMake option, and compiler define.
 *  1 = Enable concurrency and threading.
 *  0 = Disable concurrency and threading.
 */
#if AB_CONCUR

#if IS_USING_SDL_1 || IS_USING_SDL_2 || IS_USING_SDL_3
  /* Empty */
#else
  #error "Need to add `Concur.hpp` support for your platform."
#endif

#if IS_USING_SDL_3
  #include <SDL3/SDL_thread.h>
  #include <SDL3/SDL_atomic.h>
  #include <SDL3/SDL_mutex.h>

  typedef SDL_Thread             Thread;
  typedef SDL_ThreadID           ThreadID;
  typedef SDL_AtomicInt          Atomic;
  typedef SDL_Mutex              Mutex;
  typedef SDL_Condition          Condvar;
  typedef SDL_Semaphore          Semaphore;

  #define atomicGet SDL_GetAtomicInt
  #define atomicSet SDL_SetAtomicInt
  #define atomicAdd SDL_AddAtomicInt
  #define atomicCAS SDL_CompareAndSwapAtomicInt
  #define atomicGetPtr SDL_GetAtomicPointer
  #define atomicSetPtr SDL_SetAtomicPointer
  #define atomicCASPtr SDL_CompareAndSwapAtomicPointer

#elif IS_USING_SDL_2
  #include <SDL2/SDL_thread.h>
  #include <SDL2/SDL_atomic.h>
  #include <SDL2/SDL_mutex.h>

  typedef SDL_Thread             Thread;
  typedef SDL_threadID           ThreadID;
  typedef SDL_atomic_t           Atomic;
  typedef SDL_mutex              Mutex;
  typedef SDL_cond               Condvar;
  typedef SDL_sem                Semaphore;

  #define atomicGet SDL_AtomicGet
  #define atomicSet SDL_AtomicSet
  #define atomicAdd SDL_AtomicAdd
  #define atomicCAS SDL_AtomicCAS
  #define atomicGetPtr SDL_AtomicGetPtr
  #define atomicSetPtr SDL_AtomicSetPtr
  #define atomicCASPtr SDL_AtomicCASPtr

#elif IS_USING_SDL_1

  #define IS_ATOMIC_AVAILABLE 0
  #if defined(__clang__)
  #  if __has_extension(c_atomic)
  #    undef IS_ATOMIC_AVAILABLE
  #    define IS_ATOMIC_AVAILABLE 1
  #  endif
  #endif
  #if defined(__GNUC__)
  #  if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)
  #    undef IS_ATOMIC_AVAILABLE
  #    define IS_ATOMIC_AVAILABLE 1
  #  endif
  #endif
  #if !IS_ATOMIC_AVAILABLE
  #  error "SDL1 support, minimum GCC 4.7 or Clang support for `__atomic` is require." \
           "If you don't need concurrency, you can disable this by"                    \
           "setting AB_CONCUR to OFF as a CMake option"                                \
           "or by passing AB_CONCUR=0 as a compiler define."
  #endif

  #include <SDL/SDL_thread.h>

  typedef SDL_Thread             Thread;
  typedef u32                    ThreadID;
  typedef struct { int value; }  Atomic;
  typedef SDL_mutex              Mutex;
  typedef SDL_cond               Condvar;
  typedef SDL_sem                Semaphore;

  int atomicGet(const Atomic* atom);
  int atomicSet(Atomic* atom, const int new_value);
  int atomicAdd(Atomic* atom, const int amount);
  bool atomicCAS(Atomic* atom, const int old_value, const int new_value);
  void* atomicGetPtr(void** ptr);
  void* atomicSetPtr(void** ptr, void* new_ptr);
  bool atomicCASPtr(void** ptr, void* old_ptr, void* new_ptr);

#else
  #error "Failed to detect SDL version."

#endif

/** Use SDL_GetError() to
 *  diagnose failures such as
 *  `E_MUTEX_FAILED` or `null`.
 */
typedef enum EMutexResult {
  E_MUTEX_FAILED = -1,
  E_MUTEX_SUCCEEDED = 0,
  E_MUTEX_TIMED_OUT = 1
} EMutexResult;

/*
 *  Note: Currently the following functions
 *  implementation exist at the end of `Main.cpp`
 */

/** @return May return null.
 *  Use SDL_GetError() for diagnosis.
 */
Mutex* mutexCreate(void); /* NOLINT(*-redundant-void-arg) */

/** @return Always return null.
 */
Mutex* mutexDestroy(Mutex*);

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult mutexLock(Mutex*);

#if IS_USING_SDL_1
/* Unfortunately SDL1 does not have MutexTryLock. */
/* If someone wants to write a compatibility function, go ahead. */
#else
/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_TIMED_OUT` on timeout,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult mutexTryLock(Mutex*);
#endif

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult mutexUnlock(Mutex*);

/** @return May return null.
 *  Use SDL_GetError() for diagnosis.
 */
Condvar* condvarCreate(void);

/** @return Always return null.
 */
Condvar* condvarDestroy(Condvar*);

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult condvarWait(Condvar*, Mutex*);

/** @param timeoutMS Avoid passing negative timeout.
 *  @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_TIMED_OUT` on timeout,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult condvarWaitTimeout(Condvar*, Mutex*, const i32 timeoutMS);

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult condvarSignal(Condvar*);

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult condvarBroadcast(Condvar*);

/** @return May return null.
 *  Use SDL_GetError() for diagnosis.
 */
Semaphore* semaphoreCreate(const u32 initial_value);

/** @return Always return null.
 */
Semaphore* semaphoreDestroy(Semaphore*);

u32 semaphoreValue(Semaphore*);

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult semaphoreWait(Semaphore*);

/** @param timeoutMS Avoid passing negative timeout.
 *  @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_TIMED_OUT` on timeout,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult semaphoreWaitTimeout(Semaphore*, const i32 timeoutMS);

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_TIMED_OUT` on timeout,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult semaphoreTryWait(Semaphore*);

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult semaphoreSignal(Semaphore*);

#endif /* AB_CONCUR */




/*
  ███████╗██████╗ ██╗         ██╗      ██████╗  ██████╗
  ██╔════╝██╔══██╗██║         ██║     ██╔═══██╗██╔════╝
  ███████╗██║  ██║██║         ██║     ██║   ██║██║  ███╗
  ╚════██║██║  ██║██║         ██║     ██║   ██║██║   ██║
  ███████║██████╔╝███████╗    ███████╗╚██████╔╝╚██████╔╝
  ╚══════╝╚═════╝ ╚══════╝    ╚══════╝ ╚═════╝  ╚═════╝
*/
#if IS_USING_SDL_3
  // ReSharper disable once CppUnusedIncludeDirective
  #include <SDL3/SDL_log.h>
  // ReSharper disable once CppUnusedIncludeDirective
  #include <SDL3/SDL_messagebox.h>
#elif IS_USING_SDL_2
  // ReSharper disable once CppUnusedIncludeDirective
  #include <SDL2/SDL_log.h>
  // ReSharper disable once CppUnusedIncludeDirective
  #include <SDL2/SDL_messagebox.h>
  #define SDL_GetLogOutputFunction  SDL_LogGetOutputFunction
  #define SDL_GetLogPriority        SDL_LogGetPriority
  #define SDL_ResetLogPriorities    SDL_LogResetPriorities
  #define SDL_SetLogPriorities      SDL_LogSetAllPriority
  #define SDL_SetLogOutputFunction  SDL_LogSetOutputFunction
  #define SDL_SetLogPriority        SDL_LogSetPriority
  #define SDL_LOG_PRIORITY_COUNT    SDL_NUM_LOG_PRIORITIES
#elif IS_USING_SDL_1
#else
  #error "Failed to detect SDL version."
#endif

#if IS_USING_SDL_3
  #include <SDL3/SDL_init.h>
  typedef enum ESysStatus {
    E_SYS_CONTINUE = SDL_APP_CONTINUE,
    E_SYS_QUIT = SDL_APP_SUCCESS,
    E_SYS_FATALITY = SDL_APP_FAILURE,
    E_SYS_REPEAT
  } ESysStatus;
#else
  typedef enum ESysStatus {
    E_SYS_CONTINUE, /**<< Continue to the next procedure. */
    E_SYS_QUIT, /**<< Exit normally. */
    E_SYS_FATALITY, /**<< Exit with error. */
    E_SYS_REPEAT /**<< Repeat the same procedure. */
  } ESysStatus;
#endif

#if IS_USING_SDL_3
  #include <SDL3/SDL_main.h>
  #define SDL_INIT_TIMER 0
#elif IS_USING_SDL_2
  #include <SDL2/SDL.h>
  #define SDL_INIT_GAMEPAD SDL_INIT_GAMECONTROLLER
#elif IS_USING_SDL_1
  #include <SDL/SDL.h>
#else
  #error "Failed to detect SDL version."
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
  // ReSharper disable once CppUnusedIncludeDirective
  #include <SDL3/SDL_timer.h>
#elif IS_USING_SDL_2
  // ReSharper disable once CppUnusedIncludeDirective
  #include <SDL2/SDL_timer.h>
  #define SDL_GetTicks SDL_GetTicks64
#elif IS_USING_SDL_1
  // ReSharper disable once CppUnusedIncludeDirective
  #include <SDL/SDL_timer.h>
#else
  #error "Failed to detect SDL version."
#endif

#define MSPS 1000        /* Milliseconds Per Second */
#define USPS 1000000     /* Microseconds Per Second */
#define NSPS 1000000000  /* Nanoseconds Per Second */

#if IS_USING_SDL_1
#define clockU64()            castU64(SDL_GetTicks())
#define clockFrequencyU64()   castU64(MSPS)
#define clockMsU64()          castU64(SDL_GetTicks())
#else

/** @brief Get high-resolution performance counter (ticks since SDL init).
 *  @return uint64_t Tick count.
 */
#define clockU64() SDL_GetPerformanceCounter()

/** @brief Get performance frequency (ticks per second).
 *  @return uint64_t Frequency in ticks/second.
 */
#define clockFrequencyU64() SDL_GetPerformanceFrequency()

/** @brief Get wall-clock time in milliseconds (since SDL init).
 *  @return uint64_t Milliseconds.
 */
#define clockMsU64() SDL_GetTicks()

#endif




/*
  ██████╗ ███████╗██████╗ ██╗   ██╗ ██████╗
  ██╔══██╗██╔════╝██╔══██╗██║   ██║██╔════╝
  ██║  ██║█████╗  ██████╔╝██║   ██║██║  ███╗
  ██║  ██║██╔══╝  ██╔══██╗██║   ██║██║   ██║
  ██████╔╝███████╗██████╔╝╚██████╔╝╚██████╔╝
  ╚═════╝ ╚══════╝╚═════╝  ╚═════╝  ╚═════╝
*/

#ifndef AB_OPTIMIZE
#define AB_OPTIMIZE 0
#endif

#ifndef AB_SANITIZE
#define AB_SANITIZE 0
#endif

#ifndef AB_DEBUG
#define AB_DEBUG 0
#endif

#if IS_COMPILER_MSVC || IS_OS_WINDOWS
  #define _ab_debugBreak__ DebugBreak();
#else
  #define _ab_debugBreak__ raise(SIGTRAP);
#endif

#if IS_USING_SDL_1
  #define _ab_print__ printf
#else
  #define _ab_print__ SDL_Log
#endif

#if AB_DEBUG
  #define debugBreak _ab_debugBreak__
  #define print _ab_print__
#else
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
#endif

/** Like debugBreak but should work on release as well. */
#define hardBreak _ab_debugBreak__
/** Like print but should work on release as well. */
#define hardPrint _ab_print__

#define _stringify__(X) #X
#define stringify(X) _stringify__(X)


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




/*
  ███████╗██████╗ ██╗
  ██╔════╝██╔══██╗██║
  ███████╗██║  ██║██║
  ╚════██║██║  ██║██║
  ███████║██████╔╝███████╗
  ╚══════╝╚═════╝ ╚══════╝
*/

/** SDL Initializer */
class Sdl {
public:

  enum Status {
    INIT_FAILED = false,
    INIT_SUCCEED = true
  };

  static Sdl def();
  Status init();
  static void quit();

  /** Add timer subsystem to init flags. */
  Sdl& timer();
  /** Add audio subsystem to init flags. */
  Sdl& audio();
  /** Add video subsystem to init flags. */
  Sdl& video();
  /** Add joystick subsystem to init flags. */
  Sdl& joystick();
  /** Add haptic subsystem to init flags. */
  Sdl& haptic();
  /** Add gamepad subsystem to init flags. */
  Sdl& gamepad();
  /** Add events subsystem to init flags. */
  Sdl& events();
  /** Add sensor subsystem to init flags. */
  Sdl& sensor();
  /** Add camera subsystem to init flags. */
  Sdl& camera();
  /** Add event thread subsystem to init flags. */
  Sdl& eventThread();

private:
  Sdl();
  unsigned int subsystem_flags_;

public:
  /** For SDL1 these will be equivalent to SDLKey.
   *  For SDL2 and SDL3 these will be equivalent to SDL_Scancode.
   */
  enum Key {
#if IS_USING_SDL_1
    BACKSPACE = SDLK_BACKSPACE,
    TAB = SDLK_TAB,
    CLEAR = SDLK_CLEAR,
    RETURN = SDLK_RETURN,
    PAUSE = SDLK_PAUSE,
    ESCAPE = SDLK_ESCAPE,
    SPACE = SDLK_SPACE,
    APOSTROPHE = SDLK_QUOTE,
    COMMA = SDLK_COMMA,
    MINUS = SDLK_MINUS,
    PERIOD = SDLK_PERIOD,
    SLASH = SDLK_SLASH,
    NUM_0 = SDLK_0,
    NUM_1 = SDLK_1,
    NUM_2 = SDLK_2,
    NUM_3 = SDLK_3,
    NUM_4 = SDLK_4,
    NUM_5 = SDLK_5,
    NUM_6 = SDLK_6,
    NUM_7 = SDLK_7,
    NUM_8 = SDLK_8,
    NUM_9 = SDLK_9,
    SEMICOLON = SDLK_SEMICOLON,
    EQUALS = SDLK_EQUALS,
    LEFTBRACKET = SDLK_LEFTBRACKET,
    BACKSLASH = SDLK_BACKSLASH,
    RIGHTBRACKET = SDLK_RIGHTBRACKET,
    GRAVE = SDLK_BACKQUOTE,
    A = SDLK_a,
    B = SDLK_b,
    C = SDLK_c,
    D = SDLK_d,
    E = SDLK_e,
    F = SDLK_f,
    G = SDLK_g,
    H = SDLK_h,
    I = SDLK_i,
    J = SDLK_j,
    K = SDLK_k,
    L = SDLK_l,
    M = SDLK_m,
    N = SDLK_n,
    O = SDLK_o,
    P = SDLK_p,
    Q = SDLK_q,
    R = SDLK_r,
    S = SDLK_s,
    T = SDLK_t,
    U = SDLK_u,
    V = SDLK_v,
    W = SDLK_w,
    X = SDLK_x,
    Y = SDLK_y,
    Z = SDLK_z,
    DELETE = SDLK_DELETE,
    KP_0 = SDLK_KP0,
    KP_1 = SDLK_KP1,
    KP_2 = SDLK_KP2,
    KP_3 = SDLK_KP3,
    KP_4 = SDLK_KP4,
    KP_5 = SDLK_KP5,
    KP_6 = SDLK_KP6,
    KP_7 = SDLK_KP7,
    KP_8 = SDLK_KP8,
    KP_9 = SDLK_KP9,
    KP_PERIOD = SDLK_KP_PERIOD,
    KP_DIVIDE = SDLK_KP_DIVIDE,
    KP_MULTIPLY = SDLK_KP_MULTIPLY,
    KP_MINUS = SDLK_KP_MINUS,
    KP_PLUS = SDLK_KP_PLUS,
    KP_ENTER = SDLK_KP_ENTER,
    KP_EQUALS = SDLK_KP_EQUALS,
    UP = SDLK_UP,
    DOWN = SDLK_DOWN,
    RIGHT = SDLK_RIGHT,
    LEFT = SDLK_LEFT,
    INSERT = SDLK_INSERT,
    HOME = SDLK_HOME,
    END = SDLK_END,
    PAGEUP = SDLK_PAGEUP,
    PAGEDOWN = SDLK_PAGEDOWN,
    F1 = SDLK_F1,
    F2 = SDLK_F2,
    F3 = SDLK_F3,
    F4 = SDLK_F4,
    F5 = SDLK_F5,
    F6 = SDLK_F6,
    F7 = SDLK_F7,
    F8 = SDLK_F8,
    F9 = SDLK_F9,
    F10 = SDLK_F10,
    F11 = SDLK_F11,
    F12 = SDLK_F12,
    F13 = SDLK_F13,
    F14 = SDLK_F14,
    F15 = SDLK_F15,
    NUMLOCKCLEAR = SDLK_NUMLOCK,
    CAPSLOCK = SDLK_CAPSLOCK,
    SCROLLLOCK = SDLK_SCROLLOCK,
    RSHIFT = SDLK_RSHIFT,
    LSHIFT = SDLK_LSHIFT,
    RCTRL = SDLK_RCTRL,
    LCTRL = SDLK_LCTRL,
    RALT = SDLK_RALT,
    LALT = SDLK_LALT,
    RGUI = SDLK_RMETA,
    LGUI = SDLK_LMETA,
    MODE = SDLK_MODE,
    HELP = SDLK_HELP,
    PRINTSCREEN = SDLK_PRINT,
    SYSREQ = SDLK_SYSREQ,
    MENU = SDLK_MENU,
    POWER = SDLK_POWER,
    UNDO = SDLK_UNDO
#elif IS_USING_SDL_2 || IS_USING_SDL_3
    A = SDL_SCANCODE_A,
    B = SDL_SCANCODE_B,
    C = SDL_SCANCODE_C,
    D = SDL_SCANCODE_D,
    E = SDL_SCANCODE_E,
    F = SDL_SCANCODE_F,
    G = SDL_SCANCODE_G,
    H = SDL_SCANCODE_H,
    I = SDL_SCANCODE_I,
    J = SDL_SCANCODE_J,
    K = SDL_SCANCODE_K,
    L = SDL_SCANCODE_L,
    M = SDL_SCANCODE_M,
    N = SDL_SCANCODE_N,
    O = SDL_SCANCODE_O,
    P = SDL_SCANCODE_P,
    Q = SDL_SCANCODE_Q,
    R = SDL_SCANCODE_R,
    S = SDL_SCANCODE_S,
    T = SDL_SCANCODE_T,
    U = SDL_SCANCODE_U,
    V = SDL_SCANCODE_V,
    W = SDL_SCANCODE_W,
    X = SDL_SCANCODE_X,
    Y = SDL_SCANCODE_Y,
    Z = SDL_SCANCODE_Z,
    NUM_1 = SDL_SCANCODE_1,
    NUM_2 = SDL_SCANCODE_2,
    NUM_3 = SDL_SCANCODE_3,
    NUM_4 = SDL_SCANCODE_4,
    NUM_5 = SDL_SCANCODE_5,
    NUM_6 = SDL_SCANCODE_6,
    NUM_7 = SDL_SCANCODE_7,
    NUM_8 = SDL_SCANCODE_8,
    NUM_9 = SDL_SCANCODE_9,
    NUM_0 = SDL_SCANCODE_0,
    RETURN = SDL_SCANCODE_RETURN,
    ESCAPE = SDL_SCANCODE_ESCAPE,
    BACKSPACE = SDL_SCANCODE_BACKSPACE,
    TAB = SDL_SCANCODE_TAB,
    SPACE = SDL_SCANCODE_SPACE,
    MINUS = SDL_SCANCODE_MINUS,
    EQUALS = SDL_SCANCODE_EQUALS,
    LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET,
    RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET,
    BACKSLASH = SDL_SCANCODE_BACKSLASH,
    SEMICOLON = SDL_SCANCODE_SEMICOLON,
    APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
    GRAVE = SDL_SCANCODE_GRAVE,
    COMMA = SDL_SCANCODE_COMMA,
    PERIOD = SDL_SCANCODE_PERIOD,
    SLASH = SDL_SCANCODE_SLASH,
    CAPSLOCK = SDL_SCANCODE_CAPSLOCK,
    F1 = SDL_SCANCODE_F1,
    F2 = SDL_SCANCODE_F2,
    F3 = SDL_SCANCODE_F3,
    F4 = SDL_SCANCODE_F4,
    F5 = SDL_SCANCODE_F5,
    F6 = SDL_SCANCODE_F6,
    F7 = SDL_SCANCODE_F7,
    F8 = SDL_SCANCODE_F8,
    F9 = SDL_SCANCODE_F9,
    F10 = SDL_SCANCODE_F10,
    F11 = SDL_SCANCODE_F11,
    F12 = SDL_SCANCODE_F12,
    PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN,
    SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK,
    PAUSE = SDL_SCANCODE_PAUSE,
    INSERT = SDL_SCANCODE_INSERT,
    HOME = SDL_SCANCODE_HOME,
    PAGEUP = SDL_SCANCODE_PAGEUP,
    DELETE = SDL_SCANCODE_DELETE,
    END = SDL_SCANCODE_END,
    PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
    RIGHT = SDL_SCANCODE_RIGHT,
    LEFT = SDL_SCANCODE_LEFT,
    DOWN = SDL_SCANCODE_DOWN,
    UP = SDL_SCANCODE_UP,
    NUMLOCKCLEAR = SDL_SCANCODE_NUMLOCKCLEAR,
    KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE,
    KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY,
    KP_MINUS = SDL_SCANCODE_KP_MINUS,
    KP_PLUS = SDL_SCANCODE_KP_PLUS,
    KP_ENTER = SDL_SCANCODE_KP_ENTER,
    KP_1 = SDL_SCANCODE_KP_1,
    KP_2 = SDL_SCANCODE_KP_2,
    KP_3 = SDL_SCANCODE_KP_3,
    KP_4 = SDL_SCANCODE_KP_4,
    KP_5 = SDL_SCANCODE_KP_5,
    KP_6 = SDL_SCANCODE_KP_6,
    KP_7 = SDL_SCANCODE_KP_7,
    KP_8 = SDL_SCANCODE_KP_8,
    KP_9 = SDL_SCANCODE_KP_9,
    KP_0 = SDL_SCANCODE_KP_0,
    KP_PERIOD = SDL_SCANCODE_KP_PERIOD,
    POWER = SDL_SCANCODE_POWER,
    KP_EQUALS = SDL_SCANCODE_KP_EQUALS,
    F13 = SDL_SCANCODE_F13,
    F14 = SDL_SCANCODE_F14,
    F15 = SDL_SCANCODE_F15,
    HELP = SDL_SCANCODE_HELP,
    MENU = SDL_SCANCODE_MENU,
    UNDO = SDL_SCANCODE_UNDO,
    SYSREQ = SDL_SCANCODE_SYSREQ,
    CLEAR = SDL_SCANCODE_CLEAR,
    LCTRL = SDL_SCANCODE_LCTRL,
    LSHIFT = SDL_SCANCODE_LSHIFT,
    LALT = SDL_SCANCODE_LALT,
    LGUI = SDL_SCANCODE_LGUI,
    RCTRL = SDL_SCANCODE_RCTRL,
    RSHIFT = SDL_SCANCODE_RSHIFT,
    RALT = SDL_SCANCODE_RALT,
    RGUI = SDL_SCANCODE_RGUI,
    MODE = SDL_SCANCODE_MODE
#endif
  };

  /** - On SDL1 returns `key.keysym.sym`
   *  - On SDL2 returns `key.keysym.scancode`
   *  - On SDL2 returns `key.scancode`
   *  - Check the return against `Sdl::Key` enum constants.
   */
  static unsigned int checkKey(const SDL_KeyboardEvent& key);

};

/** SDL Window Handle Manager */
class SdlWindow {
public:

  static SdlWindow def();

#if IS_USING_SDL_1
  typedef SDL_Surface Handle;
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  typedef SDL_Window Handle;
#endif

  /** Returns null in case of failure. Call SDL_GetError() for more information. */
  Handle* create();
  /** Always returns null.*/
  Handle* destroy();

  /** Wrapper around `SDL_GetNumVideoDrivers`
   *  - SDL1: Will always return -1
   */
  static int getVideoDriverCount();

  /** Wrapper around `SDL_GetVideoDriver`
   *  - SDL1: Will always return null
   */
  static const char* getVideoDriverName(const int index);

  /** Wrapper around `SDL_GetCurrentVideoDriver`
   *  - SDL1: Will return result of `SDL_VideoDriverName`
   *  - SDL1: Returns null if video has not been initialized with SDL_Init
   */
  static const char* getCurrentVideoDriverName();

  /** \returns true on success or false on failure; call SDL_GetError() for more information. */
  bool setTitle(const char* title);

private:
  SdlWindow();

  /** On SDL1 this will be `SDL_Surface`
   *  while in SDl2 and SDL3 this will be `SDL_Window` */
  Handle* handle_;
};
staticAssert(sizeof(SdlWindow) == sizeof(void*), SdlWindow_IS_JUST_A_CONTAINER_FOR_ITS_HANDLE)

#if AB_VULKAN
#include <volk.h>
class VulkanAppInfo : private VkApplicationInfo {
public:
  static VulkanAppInfo def();
  VkApplicationInfo castVkApplicationInfo() const;
  VulkanAppInfo& setApplicationName(const char* c_str);
  VulkanAppInfo& setApplicationVersion(const u8 major, const u8 minor, const u8 patch);
  VulkanAppInfo& setApiVersionTo1Point0();
  VulkanAppInfo& setApiVersionTo1Point1();
  VulkanAppInfo& setApiVersionTo1Point2();
  VulkanAppInfo& setApiVersionTo1Point3();
  VulkanAppInfo& setApiVersionTo1Point4();
private:
  VulkanAppInfo();
};
staticAssert(sizeof(VulkanAppInfo) == sizeof(VkApplicationInfo), VulkanAppInfor_IS_JUST_A_THIN_WRAPPER_FOR_VkApplicationInfo)
#endif /* AB_VULKAN */

#endif /* AB_MAIN_HPP */
