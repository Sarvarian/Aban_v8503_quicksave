#pragma once

#ifndef AB_ADO_HPP
#define AB_ADO_HPP

/* Aban Device Order */

#include "Main.hpp"

#if IS_USING_SDL_1
  #include <SDL/SDL_video.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL_video.h>
#elif IS_USING_SDL_3
  #include <SDL3/SDL_video.h>
#endif

#if AB_VULKAN
  #include <volk.h>
#endif




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
Condvar* condvarCreate(void); /* NOLINT(*-redundant-void-arg) */

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
EMutexResult condvarWaitTimeout(Condvar*, Mutex*, const i32 timeoutMS); /* NOLINT(*-avoid-const-params-in-decls) */

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
Semaphore* semaphoreCreate(const u32 initial_value); /* NOLINT(*-avoid-const-params-in-decls) */

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
EMutexResult semaphoreWaitTimeout(Semaphore*, const i32 timeoutMS); /* NOLINT(*-avoid-const-params-in-decls) */

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_TIMED_OUT` on timeout,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult semaphoreTryWait(Semaphore*);

/** @return `E_MUTEX_SUCCEEDED` on success,
 *          `E_MUTEX_FAILED` on failure.
 */
EMutexResult semaphoreSignal(Semaphore*);

ThreadID getCurrentThreadID(void); /* NOLINT(*-redundant-void-arg) */

ThreadID getThreadID(Thread*);

#endif /* AB_CONCUR */




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
  /** Add No Parachute to init flags. */
  Sdl& noParachute();
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




/*
  ███████╗██████╗ ██╗         ██╗    ██╗██╗███╗   ██╗██████╗  ██████╗ ██╗    ██╗
  ██╔════╝██╔══██╗██║         ██║    ██║██║████╗  ██║██╔══██╗██╔═══██╗██║    ██║
  ███████╗██║  ██║██║         ██║ █╗ ██║██║██╔██╗ ██║██║  ██║██║   ██║██║ █╗ ██║
  ╚════██║██║  ██║██║         ██║███╗██║██║██║╚██╗██║██║  ██║██║   ██║██║███╗██║
  ███████║██████╔╝███████╗    ╚███╔███╔╝██║██║ ╚████║██████╔╝╚██████╔╝╚███╔███╔╝
  ╚══════╝╚═════╝ ╚══════╝     ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝  ╚══╝╚══╝
*/

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
  static const char* getVideoDriverName(const int index); // NOLINT(*-avoid-const-params-in-decls)

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




/*
  ██╗   ██╗██╗   ██╗██╗     ██╗  ██╗ █████╗ ███╗   ██╗
  ██║   ██║██║   ██║██║     ██║ ██╔╝██╔══██╗████╗  ██║
  ██║   ██║██║   ██║██║     █████╔╝ ███████║██╔██╗ ██║
  ╚██╗ ██╔╝██║   ██║██║     ██╔═██╗ ██╔══██║██║╚██╗██║
   ╚████╔╝ ╚██████╔╝███████╗██║  ██╗██║  ██║██║ ╚████║
    ╚═══╝   ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝
*/

#if AB_VULKAN
class VulkanAppInfo : private VkApplicationInfo {
public:
  static VulkanAppInfo def();
  VkApplicationInfo castVkApplicationInfo() const;
  VulkanAppInfo& setApplicationName(const char* c_str);
  VulkanAppInfo& setApplicationVersion(const u8 major, const u8 minor, const u8 patch); // NOLINT(*-avoid-const-params-in-decls)
  VulkanAppInfo& setApiVersionTo1Point0();
  VulkanAppInfo& setApiVersionTo1Point1();
  VulkanAppInfo& setApiVersionTo1Point2();
  VulkanAppInfo& setApiVersionTo1Point3();
  VulkanAppInfo& setApiVersionTo1Point4();
private:
  VulkanAppInfo();
};
staticAssert(sizeof(VulkanAppInfo) == sizeof(VkApplicationInfo), VulkanAppInfor_IS_JUST_A_THIN_WRAPPER_OVER_VkApplicationInfo)
#endif /* AB_VULKAN */

#endif /* AB_ADO_HPP */
