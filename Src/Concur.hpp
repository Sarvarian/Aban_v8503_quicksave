#pragma once

#ifndef AB_CONCUR_HPP
#define AB_CONCUR_HPP

/** Multithreading And Concurrency */

#include "Main.hpp"

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
           "If you don't need concurency, you can disable this by"                     \
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

/** @return May return null.
 *  Use SDL_GetError() for diagnosis.
 */
Mutex* mutexCreate(void);

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

#endif /* AB_CONCUR_HPP */
