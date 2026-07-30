#include "Concur.hpp"

#if AB_CONCUR

#if IS_USING_SDL_1
  #error "TODO: Implement SDL1 routines."

#elif IS_USING_SDL_2

Mutex* mutexCreate(void) {
  return SDL_CreateMutex();
}

Mutex* mutexDestroy(Mutex* mutex) {
  SDL_DestroyMutex(mutex);
  return null;
}

EMutexResult mutexLock(Mutex* mutex) {
  return SDL_LockMutex(mutex) == 0
    ? E_MUTEX_SUCCEEDED
    : E_MUTEX_FAILED;
}

EMutexResult mutexTryLock(Mutex* mutex) {
  switch (SDL_TryLockMutex(mutex)) {
    case 0: return E_MUTEX_SUCCEEDED;
    case SDL_MUTEX_TIMEDOUT: return E_MUTEX_TIMED_OUT;
    default: return E_MUTEX_FAILED;
  }
}

EMutexResult mutexUnlock(Mutex* mutex) {
  return SDL_UnlockMutex(mutex) == 0
    ? E_MUTEX_SUCCEEDED
    : E_MUTEX_FAILED;
}

Condvar* condvarCreate(void) {
  return SDL_CreateCond();
}

Condvar* condvarDestroy(Condvar* condvar) {
  SDL_DestroyCond(condvar);
  return null;
}

EMutexResult condvarWait(Condvar* condvar, Mutex* mutex) {
  return SDL_CondWait(condvar, mutex) == 0
    ? E_MUTEX_SUCCEEDED
    : E_MUTEX_FAILED;
}

EMutexResult condvarWaitTimeout(Condvar* condvar, Mutex* mutex, const i32 timeoutMS) {
  switch (SDL_CondWaitTimeout(condvar, mutex, castU32(timeoutMS))) {
    case 0: return E_MUTEX_SUCCEEDED;
    case SDL_MUTEX_TIMEDOUT: return E_MUTEX_TIMED_OUT;
    default: return E_MUTEX_FAILED;
  }
}

EMutexResult condvarSignal(Condvar* condvar) {
  return SDL_CondSignal(condvar) == 0
    ? E_MUTEX_SUCCEEDED
    : E_MUTEX_FAILED;
}

EMutexResult condvarBroadcast(Condvar* condvar) {
  return SDL_CondBroadcast(condvar) == 0
    ? E_MUTEX_SUCCEEDED
    : E_MUTEX_FAILED;
}

Semaphore* semaphoreCreate(const u32 initial_value) {
  return SDL_CreateSemaphore(initial_value);
}

Semaphore* semaphoreDestroy(Semaphore* semaphore) {
  SDL_DestroySemaphore(semaphore);
  return null;
}

u32 semaphoreValue(Semaphore* semaphore) {
  return SDL_SemValue(semaphore);
}

EMutexResult semaphoreWait(Semaphore* semaphore) {
  return SDL_SemWait(semaphore) == 0
    ? E_MUTEX_SUCCEEDED
    : E_MUTEX_FAILED;
}

EMutexResult semaphoreWaitTimeout(Semaphore* semaphore, const i32 timeoutMS) {
  switch (SDL_SemWaitTimeout(semaphore, castU32(timeoutMS))) {
    case 0: return E_MUTEX_SUCCEEDED;
    case SDL_MUTEX_TIMEDOUT: return E_MUTEX_TIMED_OUT;
    default: return E_MUTEX_FAILED;
  }
}

EMutexResult semaphoreTryWait(Semaphore* semaphore) {
  switch (SDL_SemTryWait(semaphore)) {
    case 0: return E_MUTEX_SUCCEEDED;
    case SDL_MUTEX_TIMEDOUT: return E_MUTEX_TIMED_OUT;
    default: return E_MUTEX_FAILED;
  }
}

EMutexResult semaphoreSignal(Semaphore* semaphore) {
  return SDL_SemPost(semaphore) == 0
    ? E_MUTEX_SUCCEEDED
    : E_MUTEX_FAILED;
}

#elif IS_USING_SDL_3

Mutex* mutexCreate(void) {
  return SDL_CreateMutex();
}

Mutex* mutexDestroy(Mutex* mutex) {
  SDL_DestroyMutex(mutex);
  return null;
}

EMutexResult mutexLock(Mutex* mutex) {
  SDL_LockMutex(mutex);
  return E_MUTEX_SUCCEEDED;
}

EMutexResult mutexTryLock(Mutex* mutex) {
  return SDL_TryLockMutex(mutex) == true ?
  E_MUTEX_SUCCEEDED : E_MUTEX_TIMED_OUT;
}

EMutexResult mutexUnlock(Mutex* mutex) {
  SDL_UnlockMutex(mutex);
  return E_MUTEX_SUCCEEDED;
}

Condvar* condvarCreate(void) {
  return SDL_CreateCondition();
}

Condvar* condvarDestroy(Condvar* condvar) {
  SDL_DestroyCondition(condvar);
  return null;
}

EMutexResult condvarWait(Condvar* condvar, Mutex* mutex) {
  SDL_WaitCondition(condvar, mutex);
  return E_MUTEX_SUCCEEDED;
}

EMutexResult condvarWaitTimeout(Condvar* condvar, Mutex* mutex, const i32 timeoutMS) {
  return SDL_WaitConditionTimeout(condvar, mutex, timeoutMS) == true ?
  E_MUTEX_SUCCEEDED : E_MUTEX_TIMED_OUT;
}

EMutexResult condvarSignal(Condvar* condvar) {
  SDL_SignalCondition(condvar);
  return E_MUTEX_SUCCEEDED;
}

EMutexResult condvarBroadcast(Condvar* condvar) {
  SDL_BroadcastCondition(condvar);
  return E_MUTEX_SUCCEEDED;
}

Semaphore* semaphoreCreate(const u32 initial_value) {
  return SDL_CreateSemaphore(initial_value);
}

Semaphore* semaphoreDestroy(Semaphore* semaphore) {
  SDL_DestroySemaphore(semaphore);
  return null;
}

u32 semaphoreValue(Semaphore* semaphore) {
  return SDL_GetSemaphoreValue(semaphore);
}

EMutexResult semaphoreWait(Semaphore* semaphore) {
  SDL_WaitSemaphore(semaphore);
  return E_MUTEX_SUCCEEDED;
}

EMutexResult semaphoreWaitTimeout(Semaphore* semaphore, const i32 timeoutMS) {
  return SDL_WaitSemaphoreTimeout(semaphore, timeoutMS) == true ?
  E_MUTEX_SUCCEEDED : E_MUTEX_TIMED_OUT;
}

EMutexResult semaphoreTryWait(Semaphore* semaphore) {
  return SDL_TryWaitSemaphore(semaphore) == true ?
  E_MUTEX_SUCCEEDED : E_MUTEX_TIMED_OUT;
}

EMutexResult semaphoreSignal(Semaphore* semaphore) {
  SDL_SignalSemaphore(semaphore);
  return E_MUTEX_SUCCEEDED;
}

#endif

#endif /* !AB_NO_CONCUR */
