#include "Engine.hpp"

#include "Journal.hpp"
#include "InputEventPort.hpp"

ESysStatus Engine::preSdlInit(int, char**) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::initSdl(int, char**) {
  /*
  SDL_Init(0
    | SDL_INIT_TIMER
    | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD
    | SDL_INIT_VIDEO
  );
  */
  Sdl::def().timer().video().events().eventThread().init();
  return E_SYS_CONTINUE;
}

struct SdlWindowBuffer { SdlWindow buffer[sizeof(Buffer0) / sizeof(SdlWindow)]; };
staticAssert(sizeof(SdlWindowBuffer) == sizeof(Buffer0), SDL_WINDOW_BUFFER_FIT_INTO_ONE_BUFFER0)

struct NullField {
  u64 sdl_window;
  u64 _pad_[63];
};
staticAssert(sizeof(NullField) == sizeof(Buffer0), NULL_FIELD_FIT_INTO_ONE_BUFFER0)

struct Bootstrapper {
  Pool4* pools_[sizeof(Buffer0) / sizeof(Pool4*)];
  NullField null_field;
  Step step_a;
  Step step_b;
  Buffer0 _pad_[124];
  Bootstrapper()
    : pools_(), null_field(), step_a(), step_b()
  {}
  Bootstrapper* undef() {
    for (int i = 1; pools_[i] != null; i++) {
      pools_[i] = pools_[i]->undef();
    }
    pools_[0]->undef();
    return null;
  }
};
staticAssert(sizeof(Bootstrapper) == sizeof(Block0), BOOTSTRAPPER_FIT_INTO_ONE_BLOCK0)


ESysStatus Engine::initEngine(int, char**) {
#if IS_USING_SDL_2 || IS_USING_SDL_3
  SDL_SetEventFilter(EventReceiver::sdlEventFilter, null);
#endif

  // 1. Building the first memory data structure.
  // 2. Running the system.

  // Route: advance(); // May allocate more memory.
  // Route: shutdown(); // Rely on pre-allocated memory.

  // 1. Building the first memory data structure.
  Pool4* initial_pool = Pool4::def();
  if (initial_pool == null) {
    Journal::firstPoolAllocationFailed();
    exit_code = EXIT_FAILURE;
    return E_SYS_FATALITY;
  }
  const BlockIndex fi = BlockIndex(0);
  Block0* fb = fi.toBlock0(initial_pool);
  assert(static_cast<void*>(initial_pool) == static_cast<void*>(fb));
  boot_ = reinterpret_cast<Bootstrapper*>(fb);
  boot_->pools_[0] = initial_pool;
  current_ = &(boot_->step_a);
  next_ = &(boot_->step_b);
  next_->calculate_delta_time = true;

  if (window_.create() != SdlWindow::CREATION_SUCCEED) {
    return E_SYS_FATALITY;
  }
  return E_SYS_CONTINUE;
}

ESysStatus Engine::eventSdl(const SDL_Event* event) {
  EventReceiver receiver = EventReceiver::def();
  receiver.receiveSdlInputEvent(*event);
  /*
  if keyboard:
    SDL_Event_Key:
      storeKey(event.key);
  */

#if IS_USING_SDL_1
  switch (event->type) {
  case SDL_QUIT:  return E_SYS_QUIT;
  case SDL_KEYUP:
    // print("%d\n", event->key.keysym.scancode);
    if (event->key.keysym.scancode == 9) {
      return E_SYS_QUIT;
    } else if (event->key.keysym.scancode == 19) {
      target_delta_ms = 0;
      return E_SYS_CONTINUE;
    } else if (event->key.keysym.scancode == 10) {
      target_delta_ms = MSPS / 30;
      return E_SYS_CONTINUE;
    } else if (event->key.keysym.scancode == 11) {
      target_delta_ms = MSPS / 60;
      return E_SYS_CONTINUE;
    } else if (event->key.keysym.scancode == 12) {
      target_delta_ms = MSPS / 120;
      return E_SYS_CONTINUE;
    } else {
      return E_SYS_CONTINUE;
    }
  default: return E_SYS_CONTINUE;
  }
#endif

  return E_SYS_CONTINUE;
}

struct DebugData {
  u64 frequency;
  u64 past;
private:
  DebugData() :
    frequency(clockFrequencyU64() / MSPS), past(clockU64()) {}
public:
  static DebugData* def() { return new DebugData(); }
  DebugData* undef() const { delete this; return null; }
};

void calculateDeltaTime(DebugData& db) {
  /* Begin { Print Frame Time } */ {
    const u64 now = clockU64();
    const double delta = castDouble(now - db.past) / castDouble(db.frequency);
    const double fps = castDouble(MSPS) / delta;
    db.past = now;
    print("delta: %f\tfps: %f\n", delta, fps);
  } /* End { Print Frame Time } */
}

ESysStatus Engine::stepEngine() {

  /* Begin { Memory Allocation } * / {
    Pool2* pool = Pool2::def();
    assert(pool != null);
    Pool2::BlockAllocator allocator = pool->defBlockAllocator();
    BlockIndex index = allocator.pushBlock0();
    assert(index.isValid());
    Block0* block = allocator.pushBlock0().toBlock0(pool);
    assert(block->isValid(pool));
    Buffer0* buffer = block->operator[](0);
    printf("pool: %p\n", static_cast<void*>(pool));
    pool = pool->undef(); } /* End { Memory Allocation } */

  /** /
  const usize total = Memory::totalRawMemory();
  const usize safe = (total / 4) * 3; // 1/4 of system memory.
  printf("total memory: %lu\tsafe memory: %lu\n", total, safe);
  if (safe > tttUSize(BINLOG_2147483648)) {
    printf("2G pool allocation.\n");
  } else if (safe > tttUSize(BINLOG_1073741824)) {
    printf("1G pool allocation.\n");
  } else if (safe > tttUSize(BINLOG_536870912)) {
    printf("512MB pool allocation.\n");
  } else if (safe > tttUSize(BINLOG_268435456)) {
    printf("256MB pool allocation.\n");
  } else if (safe > tttUSize(BINLOG_134217728)) {
    printf("128MB pool allocation.\n");
  } else {
    printf("Not enough memory.\n");
  }
  /**/

  /* Step Dispatch */
  if (current_->just_continue) {}
  if (current_->calculate_delta_time) {
    current_->calculate_delta_time = false;
    calculateDeltaTime(*db_);
    next_->calculate_delta_time = true;
  }
  if (current_->window_check) {}
  if (current_->window_undef) {}
  if (current_->window_def) {}

  Step* t = current_;
  current_ = next_;
  next_ = t;

  return E_SYS_CONTINUE;
}

void Engine::shutEngine() {
  window_.destroy();
  db_ = db_->undef();
  next_ = null;
  current_ = null;
  boot_ = boot_->undef();
}

void Engine::shutSdl() {
#ifndef SANITIZE
  Sdl::quit();
#endif
}

Engine::Engine()
  : window_(SdlWindow::def())
{
  /* FFF: F&^k Fixed Frequency */
  /* target_delta_ms = 0;      */
  target_delta_ms = (MSPS / 60);
  exit_code = EXIT_SUCCESS;
  db_ = DebugData::def();
  boot_ = null;
  current_ = null;
  next_ = null;
}

Engine Engine::def() {
  return Engine();
}

/*
  ███████╗██╗   ██╗███████╗███╗   ██╗████████╗███████╗
  ██╔════╝██║   ██║██╔════╝████╗  ██║╚══██╔══╝██╔════╝
  █████╗  ██║   ██║█████╗  ██╔██╗ ██║   ██║   ███████╗
  ██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ╚════██║
  ███████╗ ╚████╔╝ ███████╗██║ ╚████║   ██║   ███████║
  ╚══════╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
*/

ESysStatus Engine::unrecognizedEvent(const SDL_Event& event) {
  /* I don't think `default` should be reachable. */
  /* I put a debugBreak so if it ever happened,   */
  /*     I get a change to investigate it.        */
  debugBreak;
  return E_SYS_CONTINUE;
}

/*
   █████╗ ██████╗ ██████╗
  ██╔══██╗██╔══██╗██╔══██╗
  ███████║██████╔╝██████╔╝
  ██╔══██║██╔═══╝ ██╔═══╝
  ██║  ██║██║     ██║
  ╚═╝  ╚═╝╚═╝     ╚═╝
*/

ESysStatus Engine::quitEvent(const SDL_QuitEvent& event) {
  return E_SYS_QUIT;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::terminating(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::lowMemory(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::willEnterBackground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::didEnterBackground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::willEnterForeground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::didEnterForeground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::localeChanged(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::systemThemeChanged(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ██████╗ ██╗███████╗██████╗ ██╗      █████╗ ██╗   ██╗
  ██╔══██╗██║██╔════╝██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝
  ██║  ██║██║███████╗██████╔╝██║     ███████║ ╚████╔╝
  ██║  ██║██║╚════██║██╔═══╝ ██║     ██╔══██║  ╚██╔╝
  ██████╔╝██║███████║██║     ███████╗██║  ██║   ██║
  ╚═════╝ ╚═╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝
*/

ESysStatus Engine::orientationUnknown(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::orientationLandscape(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::orientationLandscapeFlipped(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::orientationPortrait(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::orientationPortraitFlipped(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::displayAdded(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::displayRemoved(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::displayMoved(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::displayDesktopModeChanged(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::displayCurrentModeChanged(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::displayContentScaleChanged(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

/*
  ██╗    ██╗██╗███╗   ██╗██████╗  ██████╗ ██╗    ██╗
  ██║    ██║██║████╗  ██║██╔══██╗██╔═══██╗██║    ██║
  ██║ █╗ ██║██║██╔██╗ ██║██║  ██║██║   ██║██║ █╗ ██║
  ██║███╗██║██║██║╚██╗██║██║  ██║██║   ██║██║███╗██║
  ╚███╔███╔╝██║██║ ╚████║██████╔╝╚██████╔╝╚███╔███╔╝
   ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝  ╚══╝╚══╝
*/

#if IS_USING_SDL_1
ESysStatus Engine::windowExposed() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowExposed(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::windowResized(const int w, const int h) {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowResized(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::windowMinimized() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowMinimized(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::windowRestored() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowRestored(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::windowMouseEnter() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowMouseEnter(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::windowMouseLeave() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowMouseLeave(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::windowFocusGained() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowFocusGained(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::windowFocusLost() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowFocusLost(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::windowShown(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowHidden(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowMoved(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowPixelSizeChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowMetalViewResized(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowSizeChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowMaximized(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowCloseRequest(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowTakeFocus(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowHitTest(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowIccChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowDisplayChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowDisplayScaleChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowSafeAreaChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowOccluded(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowEnterFullscreen(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowLeaveFullscreen(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowDestroyed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::windowHdrStateChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}
#endif
