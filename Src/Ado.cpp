#include "Ado.hpp"




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

Sdl& Sdl::noParachute() {
#if IS_USING_SDL_1
  subsystem_flags_ |= SDL_INIT_NOPARACHUTE;
#elif  IS_USING_SDL_2 || IS_USING_SDL_3
  /* SDL1 Feature Only. */
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




/*
  ███████╗██████╗ ██╗         ██╗    ██╗██╗███╗   ██╗██████╗  ██████╗ ██╗    ██╗
  ██╔════╝██╔══██╗██║         ██║    ██║██║████╗  ██║██╔══██╗██╔═══██╗██║    ██║
  ███████╗██║  ██║██║         ██║ █╗ ██║██║██╔██╗ ██║██║  ██║██║   ██║██║ █╗ ██║
  ╚════██║██║  ██║██║         ██║███╗██║██║██║╚██╗██║██║  ██║██║   ██║██║███╗██║
  ███████║██████╔╝███████╗    ╚███╔███╔╝██║██║ ╚████║██████╔╝╚██████╔╝╚███╔███╔╝
  ╚══════╝╚═════╝ ╚══════╝     ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝  ╚══╝╚══╝
*/

SdlWindow::SdlWindow() {
  handle_ = null;
}

SdlWindow SdlWindow::def() {
  return SdlWindow();
}

SdlWindow::Handle* SdlWindow::create() {
#if IS_USING_SDL_1
  handle_ = SDL_SetVideoMode(640, 480, 0, 0);
  SDL_WM_SetCaption("Aban", null);
#elif IS_USING_SDL_2
  handle_ = SDL_CreateWindow(
    "Aban",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    0
  );
#elif IS_USING_SDL_3
  handle_ = SDL_CreateWindow("Aban", 800, 600, 0);
#endif
  return handle_;
}

// ReSharper disable once CppDFAConstantFunctionResult
SdlWindow::Handle* SdlWindow::destroy() {
#if IS_USING_SDL_1
  handle_ = null;
#elif  IS_USING_SDL_2 || IS_USING_SDL_3
  if (handle_ != null) { SDL_DestroyWindow(handle_); }
  handle_ = null;
#endif
  return handle_;
}

int SdlWindow::getVideoDriverCount() {
#if IS_USING_SDL_1
  return -1;
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  return SDL_GetNumVideoDrivers();
#endif
}

const char* SdlWindow::getVideoDriverName(const int index) {
#if IS_USING_SDL_1
  return null;
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  return SDL_GetVideoDriver(index);
#endif
}

#if IS_USING_SDL_1
static char current_video_driver_name_[255];
#endif

const char* SdlWindow::getCurrentVideoDriverName() {
#if IS_USING_SDL_1
  memset(current_video_driver_name_, 0, sizeof(current_video_driver_name_));
  SDL_VideoDriverName(current_video_driver_name_, sizeof(current_video_driver_name_));
  return current_video_driver_name_;
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  return SDL_GetCurrentVideoDriver();
#endif
}

bool SdlWindow::setTitle(const char* title) {
#if IS_USING_SDL_1
  SDL_WM_SetCaption(title, null);
  return true;
#elif  IS_USING_SDL_2
  SDL_SetWindowTitle(handle_, title);
  return true;
#elif  IS_USING_SDL_3
  return SDL_SetWindowTitle(handle_, title);
#endif
}




/*
  ██╗   ██╗██╗   ██╗██╗     ██╗  ██╗ █████╗ ███╗   ██╗
  ██║   ██║██║   ██║██║     ██║ ██╔╝██╔══██╗████╗  ██║
  ██║   ██║██║   ██║██║     █████╔╝ ███████║██╔██╗ ██║
  ╚██╗ ██╔╝██║   ██║██║     ██╔═██╗ ██╔══██║██║╚██╗██║
   ╚████╔╝ ╚██████╔╝███████╗██║  ██╗██║  ██║██║ ╚████║
    ╚═══╝   ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝
*/

#if AB_VULKAN
VulkanAppInfo::VulkanAppInfo() : VkApplicationInfo() {
  sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  pNext = null;
  pApplicationName = "Aban Editor";
  applicationVersion = VK_MAKE_VERSION(0, 1, 0);
  pEngineName = "Aban Engine";
  engineVersion = VK_MAKE_VERSION(AB_VERSION_MAJOR, AB_VERSION_MINOR, AB_VERSION_PATCH);
  apiVersion = VK_API_VERSION_1_0;
}
VulkanAppInfo VulkanAppInfo::def() {
  return VulkanAppInfo();
}
VkApplicationInfo VulkanAppInfo::castVkApplicationInfo() const {
  return *this;
}
VulkanAppInfo& VulkanAppInfo::setApplicationName(const char* c_str) {
  pApplicationName = c_str;
  return *this;
}
VulkanAppInfo& VulkanAppInfo::setApplicationVersion(const u8 major, const u8 minor, const u8 patch) {
  applicationVersion = VK_MAKE_VERSION(major, minor, patch);
  return *this;
}
VulkanAppInfo& VulkanAppInfo::setApiVersionTo1Point0() {
  apiVersion = VK_API_VERSION_1_0;
  return *this;
}
VulkanAppInfo& VulkanAppInfo::setApiVersionTo1Point1() {
  apiVersion = VK_API_VERSION_1_1;
  return *this;
}
VulkanAppInfo& VulkanAppInfo::setApiVersionTo1Point2() {
  apiVersion = VK_API_VERSION_1_2;
  return *this;
}
VulkanAppInfo& VulkanAppInfo::setApiVersionTo1Point3() {
  apiVersion = VK_API_VERSION_1_3;
  return *this;
}
VulkanAppInfo& VulkanAppInfo::setApiVersionTo1Point4() {
  apiVersion = VK_API_VERSION_1_4;
  return *this;
}
#endif /* AB_VULKAN */
