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

ESysStatus Engine::on_unrecognized_event(const SDL_Event& event) {
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

ESysStatus Engine::on_quit(const SDL_QuitEvent& event) {
  return E_SYS_QUIT;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_terminating(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_low_memory(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_will_enter_background(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_did_enter_background(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_will_enter_foreground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_did_enter_foreground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_locale_changed(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_system_theme_changed(const SDL_CommonEvent& event) {
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

ESysStatus Engine::on_orientation_unknown(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_orientation_landscape(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_orientation_landscape_flipped(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_orientation_portrait(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_orientation_portrait_flipped(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_added(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_removed(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_moved(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_desktop_mode_changed(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_current_mode_changed(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_content_scale_changed(const SDL_DisplayEvent& event) {
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
ESysStatus Engine::on_window_exposed() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_exposed(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_resized(const int w, const int h) {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_resized(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_minimized() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_minimized(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_restored() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_restored(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_mouse_enter() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_mouse_enter(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_mouse_leave() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_mouse_leave(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_focus_gained() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_focus_gained(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_focus_lost() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_focus_lost(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_shown(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_hidden(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_moved(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_pixel_size_changed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_metal_view_resized(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_size_changed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_maximized(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_close_request(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_take_focus(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_hit_test(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_icc_changed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_display_changed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_display_scale_changed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_safe_area_changed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_occluded(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_enter_fullscreen(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_leave_fullscreen(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_destroyed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_hdr_state_changed(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_1 || IS_USING_SDL_2
ESysStatus Engine::on_sys_wm(const SDL_SysWMEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ██╗  ██╗███████╗██╗   ██╗██████╗  ██████╗  █████╗ ██████╗ ██████╗
  ██║ ██╔╝██╔════╝╚██╗ ██╔╝██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔══██╗
  █████╔╝ █████╗   ╚████╔╝ ██████╔╝██║   ██║███████║██████╔╝██║  ██║
  ██╔═██╗ ██╔══╝    ╚██╔╝  ██╔══██╗██║   ██║██╔══██║██╔══██╗██║  ██║
  ██║  ██╗███████╗   ██║   ██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝
  ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/

ESysStatus Engine::on_keyboard_key_down(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_keyboard_key_up(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_text_editing(const SDL_TextEditingEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_text_input(const SDL_TextInputEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_keymap_changed(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_2
ESysStatus Engine::on_text_editing_ext(const SDL_TextEditingExtEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_keyboard_added(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_keyboard_removed(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_text_editing_candidates(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ███╗   ███╗ ██████╗ ██╗   ██╗███████╗███████╗
  ████╗ ████║██╔═══██╗██║   ██║██╔════╝██╔════╝
  ██╔████╔██║██║   ██║██║   ██║███████╗█████╗
  ██║╚██╔╝██║██║   ██║██║   ██║╚════██║██╔══╝
  ██║ ╚═╝ ██║╚██████╔╝╚██████╔╝███████║███████╗
  ╚═╝     ╚═╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝
*/

/*
       ██╗ ██████╗ ██╗   ██╗███████╗████████╗██╗ ██████╗██╗  ██╗
       ██║██╔═══██╗╚██╗ ██╔╝██╔════╝╚══██╔══╝██║██╔════╝██║ ██╔╝
       ██║██║   ██║ ╚████╔╝ ███████╗   ██║   ██║██║     █████╔╝
  ██   ██║██║   ██║  ╚██╔╝  ╚════██║   ██║   ██║██║     ██╔═██╗
  ╚█████╔╝╚██████╔╝   ██║   ███████║   ██║   ██║╚██████╗██║  ██╗
   ╚════╝  ╚═════╝    ╚═╝   ╚══════╝   ╚═╝   ╚═╝ ╚═════╝╚═╝  ╚═╝
*/

/*
   ██████╗  █████╗ ███╗   ███╗███████╗██████╗  █████╗ ██████╗
  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝██╔══██╗██╔══██╗██╔══██╗
  ██║  ███╗███████║██╔████╔██║█████╗  ██████╔╝███████║██║  ██║
  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ██╔═══╝ ██╔══██║██║  ██║
  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗██║     ██║  ██║██████╔╝
   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═════╝
*/

/*
  ████████╗ ██████╗ ██╗   ██╗ ██████╗██╗  ██╗
  ╚══██╔══╝██╔═══██╗██║   ██║██╔════╝██║  ██║
     ██║   ██║   ██║██║   ██║██║     ███████║
     ██║   ██║   ██║██║   ██║██║     ██╔══██║
     ██║   ╚██████╔╝╚██████╔╝╚██████╗██║  ██║
     ╚═╝    ╚═════╝  ╚═════╝  ╚═════╝╚═╝  ╚═╝
*/

/*
   ██████╗ ███████╗███████╗████████╗██╗   ██╗██████╗ ███████╗
  ██╔════╝ ██╔════╝██╔════╝╚══██╔══╝██║   ██║██╔══██╗██╔════╝
  ██║  ███╗█████╗  ███████╗   ██║   ██║   ██║██████╔╝█████╗
  ██║   ██║██╔══╝  ╚════██║   ██║   ██║   ██║██╔══██╗██╔══╝
  ╚██████╔╝███████╗███████║   ██║   ╚██████╔╝██║  ██║███████╗
   ╚═════╝ ╚══════╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝
*/

/*
   ██████╗██╗     ██╗██████╗ ██████╗  ██████╗  █████╗ ██████╗ ██████╗
  ██╔════╝██║     ██║██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔══██╗
  ██║     ██║     ██║██████╔╝██████╔╝██║   ██║███████║██████╔╝██║  ██║
  ██║     ██║     ██║██╔═══╝ ██╔══██╗██║   ██║██╔══██║██╔══██╗██║  ██║
  ╚██████╗███████╗██║██║     ██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝
   ╚═════╝╚══════╝╚═╝╚═╝     ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/

/*
  ██████╗ ██████╗  █████╗  ██████╗
  ██╔══██╗██╔══██╗██╔══██╗██╔════╝
  ██║  ██║██████╔╝███████║██║  ███╗
  ██║  ██║██╔══██╗██╔══██║██║   ██║
  ██████╔╝██║  ██║██║  ██║╚██████╔╝
  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝
*/

/*
   █████╗ ██╗   ██╗██████╗ ██╗ ██████╗
  ██╔══██╗██║   ██║██╔══██╗██║██╔═══██╗
  ███████║██║   ██║██║  ██║██║██║   ██║
  ██╔══██║██║   ██║██║  ██║██║██║   ██║
  ██║  ██║╚██████╔╝██████╔╝██║╚██████╔╝
  ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝ ╚═════╝
*/

/*
  ███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗
  ██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗
  ███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝
  ╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗
  ███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║
  ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝
*/

/*
  ██████╗ ███████╗███╗   ██╗
  ██╔══██╗██╔════╝████╗  ██║
  ██████╔╝█████╗  ██╔██╗ ██║
  ██╔═══╝ ██╔══╝  ██║╚██╗██║
  ██║     ███████╗██║ ╚████║
  ╚═╝     ╚══════╝╚═╝  ╚═══╝
*/

/*
   ██████╗ █████╗ ███╗   ███╗███████╗██████╗  █████╗
  ██╔════╝██╔══██╗████╗ ████║██╔════╝██╔══██╗██╔══██╗
  ██║     ███████║██╔████╔██║█████╗  ██████╔╝███████║
  ██║     ██╔══██║██║╚██╔╝██║██╔══╝  ██╔══██╗██╔══██║
  ╚██████╗██║  ██║██║ ╚═╝ ██║███████╗██║  ██║██║  ██║
   ╚═════╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝
*/

/*
  ██████╗ ███████╗███╗   ██╗██████╗ ███████╗██████╗
  ██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝██╔══██╗
  ██████╔╝█████╗  ██╔██╗ ██║██║  ██║█████╗  ██████╔╝
  ██╔══██╗██╔══╝  ██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗
  ██║  ██║███████╗██║ ╚████║██████╔╝███████╗██║  ██║
  ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝
*/

/*
  ██╗   ██╗███████╗███████╗██████╗
  ██║   ██║██╔════╝██╔════╝██╔══██╗
  ██║   ██║███████╗█████╗  ██████╔╝
  ██║   ██║╚════██║██╔══╝  ██╔══██╗
  ╚██████╔╝███████║███████╗██║  ██║
   ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝
*/

