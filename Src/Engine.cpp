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

/*
ESysStatus Engine::eventSdl(const SDL_Event* event) {
  EventReceiver receiver = EventReceiver::def();
  receiver.receiveSdlInputEvent(*event);
  if keyboard:
    SDL_Event_Key:
      storeKey(event.key);

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
*/

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

ESysStatus Engine::on_quit(const SDL_QuitEvent& quit) {
  return E_SYS_QUIT;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_terminating(const SDL_CommonEvent& common) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_low_memory(const SDL_CommonEvent& common) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_will_enter_background(const SDL_CommonEvent& common) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_did_enter_background(const SDL_CommonEvent& common) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_will_enter_foreground(const SDL_CommonEvent& common) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_did_enter_foreground(const SDL_CommonEvent& common) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_locale_changed(const SDL_CommonEvent& common) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_system_theme_changed(const SDL_CommonEvent& common) {
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

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_orientation_unknown(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_orientation_landscape(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_orientation_landscape_flipped(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_orientation_portrait(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_orientation_portrait_flipped(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_added(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_removed(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_moved(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_desktop_mode_changed(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_current_mode_changed(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_display_content_scale_changed(const SDL_DisplayEvent& display) {
  return E_SYS_CONTINUE;
}
#endif

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
ESysStatus Engine::on_window_exposed(const SDL_WindowEvent& window) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_resized(const int w, const int h) {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_resized(const SDL_WindowEvent& window) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_minimized() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_minimized(const SDL_WindowEvent& window) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_restored() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_restored(const SDL_WindowEvent& window) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_mouse_enter() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_mouse_enter(const SDL_WindowEvent& window) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_mouse_leave() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_mouse_leave(const SDL_WindowEvent& window) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_focus_gained() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_focus_gained(const SDL_WindowEvent& window) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus Engine::on_window_focus_lost() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_focus_lost(const SDL_WindowEvent& window) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_window_shown(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_hidden(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_moved(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_pixel_size_changed(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_metal_view_resized(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_size_changed(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_maximized(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_close_request(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_take_focus(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_hit_test(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_icc_changed(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_display_changed(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_display_scale_changed(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_safe_area_changed(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_occluded(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_enter_fullscreen(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_leave_fullscreen(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_destroyed(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_window_hdr_state_changed(const SDL_WindowEvent& window) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_1 || IS_USING_SDL_2
ESysStatus Engine::on_sys_wm(const SDL_SysWMEvent& syswm) {
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

ESysStatus Engine::on_keyboard_key_down(const SDL_KeyboardEvent& key) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_keyboard_key_up(const SDL_KeyboardEvent& key) {
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_text_editing(const SDL_TextEditingEvent& edit) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_text_input(const SDL_TextInputEvent& text) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_keymap_changed(const SDL_CommonEvent& common) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_2
ESysStatus Engine::on_text_editing_ext(const SDL_TextEditingExtEvent& editExt) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_3
ESysStatus Engine::on_keyboard_added(const SDL_KeyboardDeviceEvent& kdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_keyboard_removed(const SDL_KeyboardDeviceEvent& kdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_text_editing_candidates(const SDL_TextEditingCandidatesEvent& edit_candidates) {
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

ESysStatus Engine::on_mouse_motion(const SDL_MouseMotionEvent& motion) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_mouse_button_down(const SDL_MouseButtonEvent& button) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_mouse_button_up(const SDL_MouseButtonEvent& button) {
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_mouse_wheel(const SDL_MouseWheelEvent& wheel) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_3
ESysStatus Engine::on_mouse_added(const SDL_MouseDeviceEvent& mdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_mouse_removed(const SDL_MouseDeviceEvent& mdevice) {
  return E_SYS_CONTINUE;
}
#endif

/*
       ██╗ ██████╗ ██╗   ██╗███████╗████████╗██╗ ██████╗██╗  ██╗
       ██║██╔═══██╗╚██╗ ██╔╝██╔════╝╚══██╔══╝██║██╔════╝██║ ██╔╝
       ██║██║   ██║ ╚████╔╝ ███████╗   ██║   ██║██║     █████╔╝
  ██   ██║██║   ██║  ╚██╔╝  ╚════██║   ██║   ██║██║     ██╔═██╗
  ╚█████╔╝╚██████╔╝   ██║   ███████║   ██║   ██║╚██████╗██║  ██╗
   ╚════╝  ╚═════╝    ╚═╝   ╚══════╝   ╚═╝   ╚═╝ ╚═════╝╚═╝  ╚═╝
*/

ESysStatus Engine::on_joystick_axis_motion(const SDL_JoyAxisEvent& jaxis) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_joystick_ball_motion(const SDL_JoyBallEvent& jball) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_joystick_hat_motion(const SDL_JoyHatEvent& jhat) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_joystick_button_down(const SDL_JoyButtonEvent& jbutton) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_joystick_button_up(const SDL_JoyButtonEvent& jbutton) {
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_joystick_added(const SDL_JoyDeviceEvent& jdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_joystick_removed(const SDL_JoyDeviceEvent& jdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_joystick_battery_updated(const SDL_JoyBatteryEvent& jbattery) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_joystick_update_complete(const SDL_JoyDeviceEvent& jdevice) {
  return E_SYS_CONTINUE;
}
#endif

/*
   ██████╗  █████╗ ███╗   ███╗███████╗██████╗  █████╗ ██████╗
  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝██╔══██╗██╔══██╗██╔══██╗
  ██║  ███╗███████║██╔████╔██║█████╗  ██████╔╝███████║██║  ██║
  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ██╔═══╝ ██╔══██║██║  ██║
  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗██║     ██║  ██║██████╔╝
   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═════╝
*/

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_gamepad_axis_motion(const SDL_GamepadAxisEvent& gaxis) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_button_down(const SDL_GamepadButtonEvent& gbutton) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_button_up(const SDL_GamepadButtonEvent& gbutton) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_added(const SDL_GamepadDeviceEvent& gdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_removed(const SDL_GamepadDeviceEvent& gdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_remapped(const SDL_GamepadDeviceEvent& gdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_touchpad_down(const SDL_GamepadTouchpadEvent& gtouchpad) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_touchpad_motion(const SDL_GamepadTouchpadEvent& gtouchpad) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_touchpad_up(const SDL_GamepadTouchpadEvent& gtouchpad) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_sensor_update(const SDL_GamepadSensorEvent& gsensor) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_update_complete(const SDL_GamepadDeviceEvent& gdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_gamepad_steam_handle_updated(const SDL_GamepadDeviceEvent& gdevice) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ████████╗ ██████╗ ██╗   ██╗ ██████╗██╗  ██╗
  ╚══██╔══╝██╔═══██╗██║   ██║██╔════╝██║  ██║
     ██║   ██║   ██║██║   ██║██║     ███████║
     ██║   ██║   ██║██║   ██║██║     ██╔══██║
     ██║   ╚██████╔╝╚██████╔╝╚██████╗██║  ██║
     ╚═╝    ╚═════╝  ╚═════╝  ╚═════╝╚═╝  ╚═╝
*/

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_finger_down(const SDL_TouchFingerEvent& tfinger) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_finger_up(const SDL_TouchFingerEvent& tfinger) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_finger_motion(const SDL_TouchFingerEvent& tfinger) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_finger_cancel(const SDL_TouchFingerEvent& tfinger) {
  return E_SYS_CONTINUE;
}
#endif

/*
   ██████╗ ███████╗███████╗████████╗██╗   ██╗██████╗ ███████╗
  ██╔════╝ ██╔════╝██╔════╝╚══██╔══╝██║   ██║██╔══██╗██╔════╝
  ██║  ███╗█████╗  ███████╗   ██║   ██║   ██║██████╔╝█████╗
  ██║   ██║██╔══╝  ╚════██║   ██║   ██║   ██║██╔══██╗██╔══╝
  ╚██████╔╝███████╗███████║   ██║   ╚██████╔╝██║  ██║███████╗
   ╚═════╝ ╚══════╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝
*/

#if IS_USING_SDL_2
ESysStatus Engine::on_dollar_gesture(const SDL_DollarGestureEvent& dgesture) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_dollar_cord(const SDL_DollarGestureEvent& dgesture) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_multi_gesture(const SDL_MultiGestureEvent& mgesture) {
  return E_SYS_CONTINUE;
}
#endif

/*
   ██████╗██╗     ██╗██████╗ ██████╗  ██████╗  █████╗ ██████╗ ██████╗
  ██╔════╝██║     ██║██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔══██╗
  ██║     ██║     ██║██████╔╝██████╔╝██║   ██║███████║██████╔╝██║  ██║
  ██║     ██║     ██║██╔═══╝ ██╔══██╗██║   ██║██╔══██║██╔══██╗██║  ██║
  ╚██████╗███████╗██║██║     ██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝
   ╚═════╝╚══════╝╚═╝╚═╝     ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_clipboard_update(const SDL_ClipboardEvent& clipboard) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ██████╗ ██████╗  ██████╗ ██████╗
  ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗
  ██║  ██║██████╔╝██║   ██║██████╔╝
  ██║  ██║██╔══██╗██║   ██║██╔═══╝
  ██████╔╝██║  ██║╚██████╔╝██║
  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝
*/

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_drop_file(const SDL_DropEvent& drop) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_drop_text(const SDL_DropEvent& drop) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_drop_begin(const SDL_DropEvent& drop) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_drop_complete(const SDL_DropEvent& drop) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_drop_position(const SDL_DropEvent& drop) {
  return E_SYS_CONTINUE;
}
#endif

/*
   █████╗ ██╗   ██╗██████╗ ██╗ ██████╗
  ██╔══██╗██║   ██║██╔══██╗██║██╔═══██╗
  ███████║██║   ██║██║  ██║██║██║   ██║
  ██╔══██║██║   ██║██║  ██║██║██║   ██║
  ██║  ██║╚██████╔╝██████╔╝██║╚██████╔╝
  ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝ ╚═════╝
*/

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_audio_device_added(const SDL_AudioDeviceEvent& adevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_audio_device_removed(const SDL_AudioDeviceEvent& adevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_audio_device_format_changed(const SDL_AudioDeviceEvent& adevice) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ███████╗███████╗███╗   ██╗███████╗ ██████╗ ██████╗
  ██╔════╝██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗
  ███████╗█████╗  ██╔██╗ ██║███████╗██║   ██║██████╔╝
  ╚════██║██╔══╝  ██║╚██╗██║╚════██║██║   ██║██╔══██╗
  ███████║███████╗██║ ╚████║███████║╚██████╔╝██║  ██║
  ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝
*/

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_sensor_update(const SDL_SensorEvent& sensor) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ██████╗ ███████╗███╗   ██╗
  ██╔══██╗██╔════╝████╗  ██║
  ██████╔╝█████╗  ██╔██╗ ██║
  ██╔═══╝ ██╔══╝  ██║╚██╗██║
  ██║     ███████╗██║ ╚████║
  ╚═╝     ╚══════╝╚═╝  ╚═══╝
*/

#if IS_USING_SDL_3
ESysStatus Engine::on_pen_proximity_in(const SDL_PenProximityEvent& pproximity) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_pen_proximity_out(const SDL_PenProximityEvent& pproximity) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_pen_down(const SDL_PenTouchEvent& ptouch) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_pen_up(const SDL_PenTouchEvent& ptouch) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_pen_button_down(const SDL_PenButtonEvent& pbutton) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_pen_button_up(const SDL_PenButtonEvent& pbutton) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_pen_motion(const SDL_PenMotionEvent& pmotion) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_pen_axis(const SDL_PenAxisEvent& paxis) {
  return E_SYS_CONTINUE;
}
#endif

/*
   ██████╗ █████╗ ███╗   ███╗███████╗██████╗  █████╗
  ██╔════╝██╔══██╗████╗ ████║██╔════╝██╔══██╗██╔══██╗
  ██║     ███████║██╔████╔██║█████╗  ██████╔╝███████║
  ██║     ██╔══██║██║╚██╔╝██║██╔══╝  ██╔══██╗██╔══██║
  ╚██████╗██║  ██║██║ ╚═╝ ██║███████╗██║  ██║██║  ██║
   ╚═════╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝
*/

#if IS_USING_SDL_3
ESysStatus Engine::on_camera_device_added(const SDL_CameraDeviceEvent& cdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_camera_device_removed(const SDL_CameraDeviceEvent& cdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_camera_device_approved(const SDL_CameraDeviceEvent& cdevice) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_camera_device_denied(const SDL_CameraDeviceEvent& cdevice) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ██████╗ ███████╗███╗   ██╗██████╗ ███████╗██████╗
  ██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝██╔══██╗
  ██████╔╝█████╗  ██╔██╗ ██║██║  ██║█████╗  ██████╔╝
  ██╔══██╗██╔══╝  ██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗
  ██║  ██║███████╗██║ ╚████║██████╔╝███████╗██║  ██║
  ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝
*/

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus Engine::on_render_targets_reset(const SDL_RenderEvent& render) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_render_device_reset(const SDL_RenderEvent& render) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::on_render_device_lost(const SDL_RenderEvent& render) {
  return E_SYS_CONTINUE;
}
#endif

/*
  ██╗   ██╗███████╗███████╗██████╗
  ██║   ██║██╔════╝██╔════╝██╔══██╗
  ██║   ██║███████╗█████╗  ██████╔╝
  ██║   ██║╚════██║██╔══╝  ██╔══██╗
  ╚██████╔╝███████║███████╗██║  ██║
   ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝
*/

ESysStatus Engine::on_user_event(const SDL_UserEvent& event) {
  return E_SYS_CONTINUE;
}




#if IS_USING_SDL_1
ESysStatus Engine::eventSdl(const SDL_Event& event) {
  switch (event.type) {
    case SDL_ACTIVEEVENT:
      switch (event.active.type) {
      case SDL_APPACTIVE: return event.active.gain ? on_window_restored() : on_window_minimized();
      case SDL_APPMOUSEFOCUS: return event.active.gain ? on_window_mouse_enter() : on_window_mouse_leave();
      case SDL_APPINPUTFOCUS: return event.active.gain ? on_window_focus_gained() : on_window_focus_lost();
      default: break;
      }
      break;
    case SDL_KEYDOWN: return on_keyboard_key_down(event.key);
    case SDL_KEYUP: return on_keyboard_key_up(event.key);
    case SDL_MOUSEMOTION: return on_mouse_motion(event.motion);
    case SDL_MOUSEBUTTONDOWN: return on_mouse_button_down(event.button);
    case SDL_MOUSEBUTTONUP: return on_mouse_button_up(event.button);
    case SDL_JOYAXISMOTION: return on_joystick_axis_motion(event.jaxis);
    case SDL_JOYBALLMOTION: return on_joystick_ball_motion(event.jball);
    case SDL_JOYHATMOTION: return on_joystick_hat_motion(event.jhat);
    case SDL_JOYBUTTONDOWN: return on_joystick_button_down(event.jbutton);
    case SDL_JOYBUTTONUP: return on_joystick_button_up(event.jbutton);
    case SDL_QUIT: return on_quit(event.quit);
    case SDL_SYSWMEVENT: return on_sys_wm(event.syswm);
    case SDL_VIDEORESIZE: return on_window_resized(event.resize.w, event.resize.h);
    case SDL_VIDEOEXPOSE: return on_window_exposed();
    case SDL_USEREVENT: return on_user_event(event.user);
    default: break;
  }
  return on_unrecognized_event(event);
}
#elif IS_USING_SDL_2
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
  /* Application events */
  case SDL_QUIT: return quitEvent(event.quit);
  /* These application events have special meaning on iOS, see SDL2 README-ios.md for details */
  case SDL_APP_TERMINATING: return terminating(event.common);
  case SDL_APP_LOWMEMORY: return lowMemory(event.common);
  case SDL_APP_WILLENTERBACKGROUND: return willEnterBackground(event.common);
  case SDL_APP_DIDENTERBACKGROUND: return didEnterBackground(event.common);
  case SDL_APP_WILLENTERFOREGROUND: return willEnterForeground(event.common);
  case SDL_APP_DIDENTERFOREGROUND: return didEnterForeground(event.common);
  case SDL_LOCALECHANGED: return localeChanged(event.common);
  /* Display events */
  case SDL_DISPLAYEVENT:
    switch (event.display.event) {
    case SDL_DISPLAYEVENT_ORIENTATION:
      switch (event.display.data1) {
      case SDL_ORIENTATION_UNKNOWN: return orientationUnknown(event.display);
      case SDL_ORIENTATION_LANDSCAPE: return orientationLandscape(event.display);
      case SDL_ORIENTATION_LANDSCAPE_FLIPPED: return orientationLandscapeFlipped(event.display);
      case SDL_ORIENTATION_PORTRAIT: return orientationPortrait(event.display);
      case SDL_ORIENTATION_PORTRAIT_FLIPPED: return orientationPortraitFlipped(event.display);
      default: break;
      }
      break;
    case SDL_DISPLAYEVENT_CONNECTED: return displayAdded(event.display);
    case SDL_DISPLAYEVENT_DISCONNECTED: return displayRemoved(event.display);
    case SDL_DISPLAYEVENT_MOVED: return displayMoved(event.display);
    default: break;
    }
    break;
  case SDL_WINDOWEVENT:
    switch (event.window.event) {
    case SDL_WINDOWEVENT_SHOWN: return windowShown(event.window);
    case SDL_WINDOWEVENT_HIDDEN: return windowHidden(event.window);
    case SDL_WINDOWEVENT_EXPOSED: return windowExposed(event.window);
    case SDL_WINDOWEVENT_MOVED: return windowMoved(event.window);
    case SDL_WINDOWEVENT_RESIZED: return windowResized(event.window);
    case SDL_WINDOWEVENT_SIZE_CHANGED: return windowSizeChanged(event.window);
    case SDL_WINDOWEVENT_MINIMIZED: return windowMinimized(event.window);
    case SDL_WINDOWEVENT_MAXIMIZED: return windowMaximized(event.window);
    case SDL_WINDOWEVENT_RESTORED: return windowRestored(event.window);
    case SDL_WINDOWEVENT_ENTER: return windowMouseEnter(event.window);
    case SDL_WINDOWEVENT_LEAVE: return windowMouseLeave(event.window);
    case SDL_WINDOWEVENT_FOCUS_GAINED: return windowFocusGained(event.window);
    case SDL_WINDOWEVENT_FOCUS_LOST: return windowFocusLost(event.window);
    case SDL_WINDOWEVENT_CLOSE: return windowCloseRequest(event.window);
    case SDL_WINDOWEVENT_TAKE_FOCUS: return windowTakeFocus(event.window);
    case SDL_WINDOWEVENT_HIT_TEST: return windowHitTest(event.window);
    case SDL_WINDOWEVENT_ICCPROF_CHANGED: return windowIccChanged(event.window);
    case SDL_WINDOWEVENT_DISPLAY_CHANGED: return windowDisplayChanged(event.window);
    default: break;
    }
    break;
  case SDL_SYSWMEVENT: return sysWmEvent(event.syswm);
  /* Keyboard events */
  case SDL_KEYDOWN: return keyboardKeyDown(event.key);
  case SDL_KEYUP: return keyboardKeyUp(event.key);
  case SDL_TEXTEDITING: return textEditing(event.edit);
  case SDL_TEXTINPUT: return textInput(event.text);
  case SDL_KEYMAPCHANGED: return keymapChanged(event.common);
  case SDL_TEXTEDITING_EXT: {
    const ESysStatus res = textEditingExt(event.editExt);
    SDL_free(event.editExt.text);
    return res;
  }
  /* Mouse events */
  case SDL_MOUSEMOTION: return mouseMotion(event.motion);
  case SDL_MOUSEBUTTONDOWN: return mouseButtonDown(event.button);
  case SDL_MOUSEBUTTONUP: return mouseButtonUp(event.button);
  case SDL_MOUSEWHEEL: return mouseWheel(event.wheel);
  /* Joystick events */
  case SDL_JOYAXISMOTION:
  case SDL_JOYBALLMOTION:
  case SDL_JOYHATMOTION:
  case SDL_JOYBUTTONDOWN:
  case SDL_JOYBUTTONUP:
  case SDL_JOYDEVICEADDED:
  case SDL_JOYDEVICEREMOVED:
  case SDL_JOYBATTERYUPDATED:
  /* Game controller events */
  case SDL_CONTROLLERAXISMOTION:
  case SDL_CONTROLLERBUTTONDOWN:
  case SDL_CONTROLLERBUTTONUP:
  case SDL_CONTROLLERDEVICEADDED:
  case SDL_CONTROLLERDEVICEREMOVED:
  case SDL_CONTROLLERDEVICEREMAPPED:
  case SDL_CONTROLLERTOUCHPADDOWN:
  case SDL_CONTROLLERTOUCHPADMOTION:
  case SDL_CONTROLLERTOUCHPADUP:
  case SDL_CONTROLLERSENSORUPDATE:
  case SDL_CONTROLLERSTEAMHANDLEUPDATED:
  default: return unrecognizedEvent(event);
  }
  return unrecognizedEvent(event);
}

bool EventReceiver::sdlEventFilter(SDL_Event& event) {
  return true;
}
#elif IS_USING_SDL_3
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
    /* Application events */
    case SDL_EVENT_QUIT: return quitEvent(event.quit);
    /* These application events have special meaning on iOS and Android, see README-ios.md and README-android.md for details */
    default: return unrecognizedEvent(event);
  }
  return unrecognizedEvent(event);
}

bool EventReceiver::sdlEventFilter(SDL_Event& event) {
  return true;
}
#endif

