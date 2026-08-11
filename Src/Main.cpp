// ReSharper disable CppMemberFunctionMayBeStatic
#include "Main.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL.h>
  /* ReSharper disable once CppUnusedIncludeDirective */
  #include <SDL3/SDL_main.h>
  #include <SDL3/SDL_init.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL.h>
  /* ReSharper disable once CppUnusedIncludeDirective */
  #include <SDL2/SDL_main.h>
#elif IS_USING_SDL_1
  #include <SDL/SDL.h>
  /* ReSharper disable once CppUnusedIncludeDirective */
  #include <SDL/SDL_main.h>
#endif

#include "Engine.hpp"

struct Timing {
private:
  const u64 frequency_; /* Clock frequency in millisecond. */
  u64 next_; /* Next Step Starts At */
  Timing()
  : frequency_(clockFrequencyU64() / MSPS)
  , next_(0)
  {}
public:
  void frameEnd(const u32 target_delta_ms) {
    const u64 now = clockU64();
    if (now < next_) {
      u32 delay = (next_ - now) / frequency_;
      delay = delay > 1 ? (delay - 1) : 0;
      if (delay > 0) { SDL_Delay(delay); }
    }
    while (clockU64() < next_) { /* Waste Clock */ }
    next_ = clockU64() + (target_delta_ms * frequency_);
  }
  static Timing def() {
    return Timing();
  }
};

static int shutdown(Engine& engine) {
  const int exit_code = engine.exit_code;
  engine.shutEngine();
  engine.shutSdl();
  return exit_code;
}

#define CHECK(ROUTINE_CALL) \
  if ((ROUTINE_CALL) != E_SYS_CONTINUE) { return shutdown(engine); }

/* ReSharper disable once CppParameterMayBeConst */
int main(int argc, char** argv) {
  Engine engine = Engine::def();
  CHECK(engine.preSdlInit(argc, argv))
  CHECK(engine.initSdl(argc, argv));
  CHECK(engine.initEngine(argc, argv));
  Timing timing = Timing::def();
  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      CHECK(engine.eventSdl(event));
    }
    switch (engine.stepEngine()) {
      case E_SYS_CONTINUE: timing.frameEnd(engine.target_delta_ms); break;
      case E_SYS_REPEAT: break;
      default: return shutdown(engine);
    }
  }
  /* ReSharper disable once CppDFAUnreachableCode */
  return shutdown(engine);
}




/*
   ██████╗ ██████╗ ███╗   ██╗ ██████╗██╗   ██╗██████╗
  ██╔════╝██╔═══██╗████╗  ██║██╔════╝██║   ██║██╔══██╗
  ██║     ██║   ██║██╔██╗ ██║██║     ██║   ██║██████╔╝
  ██║     ██║   ██║██║╚██╗██║██║     ██║   ██║██╔══██╗
  ╚██████╗╚██████╔╝██║ ╚████║╚██████╗╚██████╔╝██║  ██║
   ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝
*/

#if AB_CONCUR

#if IS_USING_SDL_1

int atomicGet(const Atomic* atom) {
  return __atomic_load_n(&(atom->value), __ATOMIC_SEQ_CST);
}

int atomicSet(Atomic* atom, const int new_value) {
  return __atomic_exchange_n(&(atom->value), new_value, __ATOMIC_SEQ_CST);
}

int atomicAdd(Atomic* atom, const int amount) {
  return __atomic_fetch_add(&(atom->value), amount, __ATOMIC_SEQ_CST);
}

bool atomicCAS(Atomic* atom, const int old_value, const int new_value) {
  int expected = old_value;
  return __atomic_compare_exchange_n(&(atom->value), &expected, new_value, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

void* atomicGetPtr(void** ptr) {
  return __atomic_load_n(ptr, __ATOMIC_SEQ_CST);
}

void* atomicSetPtr(void** ptr, void* new_ptr) {
  return __atomic_exchange_n(ptr, new_ptr, __ATOMIC_SEQ_CST);
}

bool atomicCASPtr(void** ptr, void* old_ptr, void* new_ptr) {
  void* expected = old_ptr;
  return __atomic_compare_exchange_n(ptr, &expected, new_ptr, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

Mutex* mutexCreate(void) {
  return SDL_CreateMutex();
}

Mutex* mutexDestroy(Mutex* mutex) {
  SDL_DestroyMutex(mutex);
  return null;
}

EMutexResult mutexLock(Mutex* mutex) {
  return SDL_mutexP(mutex) == 0 ?
  E_MUTEX_SUCCEEDED : E_MUTEX_FAILED;
}

/* Unfortunately SDL1 does not have MutexTryLock. */
/* If someone wants to write a compatibility function, go ahead. */
/*
EMutexResult mutexTryLock(Mutex* mutex) {
}
*/

EMutexResult mutexUnlock(Mutex* mutex) {
  return SDL_mutexV(mutex) == 0 ?
  E_MUTEX_SUCCEEDED : E_MUTEX_FAILED;
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


#elif IS_USING_SDL_2

Mutex* mutexCreate(void) { /* NOLINT(*-redundant-void-arg) */
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

Condvar* condvarCreate(void) { /* NOLINT(*-redundant-void-arg) */
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

Mutex* mutexCreate(void) { /* NOLINT(*-redundant-void-arg) */
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

Condvar* condvarCreate(void) { /* NOLINT(*-redundant-void-arg) */
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

ThreadID getCurrentThreadID(void) { /* NOLINT(*-redundant-void-arg) */
  return SDL_GetCurrentThreadID();
}

ThreadID getThreadID(Thread* thread) {
  return SDL_GetThreadID(thread);
}

#endif

#endif /* AB_CONCUR */




/*
  ███████╗██████╗ ██╗
  ██╔════╝██╔══██╗██║
  ███████╗██║  ██║██║
  ╚════██║██║  ██║██║
  ███████║██████╔╝███████╗
  ╚══════╝╚═════╝ ╚══════╝
*/

Sdl::Sdl() {
  subsystem_flags_ = 0;
}

Sdl Sdl::def() {
  return Sdl();
}

// ReSharper disable once CppMemberFunctionMayBeConst
Sdl::Status Sdl::init() { // NOLINT(*-make-member-function-const)
#if !AB_SANITIZE
  atexit(SDL_Quit);
#endif
#if IS_USING_SDL_1 || IS_USING_SDL_2
  const int res = SDL_Init(subsystem_flags_);
  return res == 0 ? INIT_SUCCEED : INIT_FAILED;
#elif IS_USING_SDL_3
  const bool res = SDL_Init(subsystem_flags_);
  return res == true ? INIT_SUCCEED : INIT_FAILED;
#endif
}

void Sdl::quit() {
  SDL_Quit();
}

Sdl& Sdl::timer() {
#if IS_USING_SDL_1 || IS_USING_SDL_2
  subsystem_flags_ |= SDL_INIT_TIMER;
#elif IS_USING_SDL_3
  /* No Such Init For SDL3 */
#endif
  return *this;
}

Sdl & Sdl::audio() {
  subsystem_flags_ |= SDL_INIT_AUDIO;
  return *this;
}

Sdl& Sdl::video() {
  subsystem_flags_ |= SDL_INIT_VIDEO;
  return *this;
}

Sdl& Sdl::joystick() {
  subsystem_flags_ |= SDL_INIT_JOYSTICK;
  return *this;
}

Sdl& Sdl::haptic() {
#if IS_USING_SDL_1
  /* No Such Init For SDL1 */
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_HAPTIC;
#endif
  return *this;
}

Sdl& Sdl::gamepad() {
#if IS_USING_SDL_1
  /* No Such Init For SDL1 */
#elif IS_USING_SDL_2
  subsystem_flags_ |= SDL_INIT_GAMECONTROLLER;
#elif IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_GAMEPAD;
#endif
  return *this;
}

Sdl& Sdl::events() {
#if IS_USING_SDL_1
  /* No Such Init For SDL1 */
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_EVENTS;
#endif
  return *this;
}

Sdl& Sdl::sensor() {
#if IS_USING_SDL_1
  /* No Such Init For SDL1 */
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_SENSOR;
#endif
  return *this;
}

Sdl& Sdl::camera() {
#if IS_USING_SDL_1 || IS_USING_SDL_2
  /* No Such Init For SDL1 */
  /* No Such Init For SDL2 */
#elif IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_CAMERA;
#endif
  return *this;
}

Sdl& Sdl::eventThread() {
#if IS_USING_SDL_1
  subsystem_flags_ |= SDL_INIT_EVENTTHREAD;
#elif  IS_USING_SDL_2 || IS_USING_SDL_3
  /* SDL1 Feature Only. */
#endif
  return *this;
}

unsigned int Sdl::checkKey(const SDL_KeyboardEvent& key) {
#if IS_USING_SDL_1
  return key.keysym.sym;
#elif IS_USING_SDL_2
  return key.keysym.scancode;
#elif IS_USING_SDL_3
  return key.scancode;
#endif
}

