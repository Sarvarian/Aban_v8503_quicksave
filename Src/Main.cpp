#include "Main.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL.h>
  #include <SDL3/SDL_main.h>
  #include <SDL3/SDL_init.h>
  #include <SDL3/SDL_events.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_main.h>
  #include <SDL2/SDL_events.h>
#elif IS_USING_SDL_1
  #include <SDL/SDL.h>
  #include <SDL/SDL_main.h>
  #include <SDL/SDL_events.h>
#endif

#include "Memory.hpp"
#include "Journal.hpp"




/*
  ███████╗████████╗██████╗ ██╗   ██╗ ██████╗████████╗
  ██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝╚══██╔══╝
  ███████╗   ██║   ██████╔╝██║   ██║██║        ██║
  ╚════██║   ██║   ██╔══██╗██║   ██║██║        ██║
  ███████║   ██║   ██║  ██║╚██████╔╝╚██████╗   ██║
  ╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝  ╚═════╝   ╚═╝
*/

struct Step {
public:
  u8 just_continue : 1;
  u8 calculate_delta_time : 1;
  u8 window_check : 1;
  u8 window_undef : 1;
  u8 window_def : 1;
  u8 _pad03_ : 1;
  u8 _pad02_ : 1;
  u8 _pad01_ : 1;
  u8 _pad00_[mmBufferSize(0) - 1];
};
staticAssert(sizeof(Step) == sizeof(Buffer0), Step_FIT_INTO_ONE_Buffer0)

struct Bootstrapper {
  Pool4* pools_[sizeof(Buffer0) / sizeof(Pool4*)];
  Step step_a;
  Step step_b;
  Buffer0 _pad_[125];
  Bootstrapper() : pools_(), step_a(), step_b() {}
  Bootstrapper* undef() {
    for (int i = 1; pools_[i] != null; i++) {
      pools_[i] = pools_[i]->undef();
    }
    pools_[0]->undef();
    return null;
  }
};
staticAssert(sizeof(Bootstrapper) == sizeof(Block0), BOOTSTRAPPER_FIT_INTO_ONE_BLOCK0)

struct DebugData {
  u64 frequency;
  u64 past;
private:
  DebugData() : frequency(clockFrequencyU64() / MSPS), past(clockU64()) {}
public:
  static DebugData* def() { return new DebugData(); }
  DebugData* undef() const { delete this; return null; }
};

class Engine {
public:
  static Engine def();

  ESysStatus preSdlInit(int, char**);
  ESysStatus initSdl(int, char**);
  ESysStatus initEngine(int, char**);
  ESysStatus eventSdl(const SDL_Event&);
  ESysStatus stepEngine();
  void       shutEngine();
  void       shutSdl();

  /* Target milliseconds per step.
     Should be sub second.
     Set to zero for uncapped step frequency.
     To calculate this you can use following formula:
       (millisecond_per_seconds / target_frequency) example: (1000 / 260)
       Also, there is a macro name `MSPS` in `Main.hpp`
       which is a constant for 'millisecond per seconds'.
   */
  u32 target_delta_ms;

  int exit_code;

private:
  Engine();

  SdlWindow window_;
  DebugData* db_;
  Bootstrapper* boot_;
  Step* current_;
  Step* next_;
  void calculateDeltaTime(DebugData& db);

/*
  ███████╗██╗   ██╗███████╗███╗   ██╗████████╗███████╗
  ██╔════╝██║   ██║██╔════╝████╗  ██║╚══██╔══╝██╔════╝
  █████╗  ██║   ██║█████╗  ██╔██╗ ██║   ██║   ███████╗
  ██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ╚════██║
  ███████╗ ╚████╔╝ ███████╗██║ ╚████║   ██║   ███████║
  ╚══════╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
*/

#if IS_USING_SDL_2
  static int sdlEventFilter(void* self, SDL_Event* event);
#elif IS_USING_SDL_3
  static bool sdlEventFilter(void* self, SDL_Event* event);
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  bool sdlEventFilter(const SDL_Event& event);
#endif

  ESysStatus on_unrecognized_event(const SDL_Event& event); /* Unrecognized SDL Event */

/*
   █████╗ ██████╗ ██████╗
  ██╔══██╗██╔══██╗██╔══██╗
  ███████║██████╔╝██████╔╝
  ██╔══██║██╔═══╝ ██╔═══╝
  ██║  ██║██║     ██║
  ╚═╝  ╚═╝╚═╝     ╚═╝
*/

  ESysStatus on_quit(const SDL_QuitEvent& quit);

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_terminating(const SDL_CommonEvent& common); /**< App Terminating */
  ESysStatus on_low_memory(const SDL_CommonEvent& common); /**< App Low Memory */
  ESysStatus on_will_enter_background(const SDL_CommonEvent& common); /**< Will Enter Background */
  ESysStatus on_did_enter_background(const SDL_CommonEvent& common); /**< Did Enter Background */
  ESysStatus on_will_enter_foreground(const SDL_CommonEvent& common); /**< Will Enter Foreground */
  ESysStatus on_did_enter_foreground(const SDL_CommonEvent& common); /**< Did Enter Foreground */
  ESysStatus on_locale_changed(const SDL_CommonEvent& common); /**< User Locale Changed */
  ESysStatus on_system_theme_changed(const SDL_CommonEvent& common); /**< System Theme Changed */
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
  ESysStatus on_orientation_unknown(const SDL_DisplayEvent& display); /**< Display Orientation Changed, Unknown */
  ESysStatus on_orientation_landscape(const SDL_DisplayEvent& display); /**< Display Orientation Changed, Landscape */
  ESysStatus on_orientation_landscape_flipped(const SDL_DisplayEvent& display); /**< Display Orientation Changed, Landscape Flipped */
  ESysStatus on_orientation_portrait(const SDL_DisplayEvent& display); /**< Display Orientation Changed, Portrait */
  ESysStatus on_orientation_portrait_flipped(const SDL_DisplayEvent& display); /**< Display Orientation Changed, Portrait Flipped */
  ESysStatus on_display_added(const SDL_DisplayEvent& display); /**< System Display Added */
  ESysStatus on_display_removed(const SDL_DisplayEvent& display); /**< System Display Removed */
  ESysStatus on_display_moved(const SDL_DisplayEvent& display); /**< System Display Position Changed */
  ESysStatus on_display_desktop_mode_changed(const SDL_DisplayEvent& display);
  ESysStatus on_display_current_mode_changed(const SDL_DisplayEvent& display);
  ESysStatus on_display_content_scale_changed(const SDL_DisplayEvent& display);
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
  ESysStatus on_window_exposed(); /**< Window Exposed, Need Redraw */
  ESysStatus on_window_resized(const int w, const int h); /**< Window Resized */
  ESysStatus on_window_minimized(); /**< Window Minimized */
  ESysStatus on_window_restored(); /**< Window Restored */
  ESysStatus on_window_mouse_enter(); /**< Window Gained Mouse Focus */
  ESysStatus on_window_mouse_leave(); /**< Window Lost Mouse Focus */
  ESysStatus on_window_focus_gained(); /**< Window Gained Keyboard Focus */
  ESysStatus on_window_focus_lost(); /**< Window Lost Keyboard Focus */
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_window_exposed(const SDL_WindowEvent& window); /**< Window Exposed, Need Redraw */
  ESysStatus on_window_resized(const SDL_WindowEvent& window); /**< Window Resized */
  ESysStatus on_window_minimized(const SDL_WindowEvent& window); /**< Window Minimized */
  ESysStatus on_window_restored(const SDL_WindowEvent& window); /**< Window Restored */
  ESysStatus on_window_mouse_enter(const SDL_WindowEvent& window); /**< Window Gained Mouse Focus */
  ESysStatus on_window_mouse_leave(const SDL_WindowEvent& window); /**< Window Lost Mouse Focus */
  ESysStatus on_window_focus_gained(const SDL_WindowEvent& window); /**< Window Gained Keyboard Focus */
  ESysStatus on_window_focus_lost(const SDL_WindowEvent& window); /**< Window Lost Keyboard Focus */
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_window_shown(const SDL_WindowEvent& window); /**< Window Shown */
  ESysStatus on_window_hidden(const SDL_WindowEvent& window); /**< Window Hidden */
  ESysStatus on_window_moved(const SDL_WindowEvent& window); /**< Window Moved */
  ESysStatus on_window_pixel_size_changed(const SDL_WindowEvent& window);
  ESysStatus on_window_metal_view_resized(const SDL_WindowEvent& window);
  ESysStatus on_window_size_changed(const SDL_WindowEvent& window); /**< Window Size Changed */
  ESysStatus on_window_maximized(const SDL_WindowEvent& window); /**< Window Maximized */
  ESysStatus on_window_close_request(const SDL_WindowEvent& window); /**< Window Requested For Close */
  ESysStatus on_window_take_focus(const SDL_WindowEvent& window); /**< Window Offered Focus */
  ESysStatus on_window_hit_test(const SDL_WindowEvent& window); /**< Window Had Hit Test, That Wasn't SDL_HITTEST_NORMAL */
  ESysStatus on_window_icc_changed(const SDL_WindowEvent& window); /**< Window's Display ICC Profile Changed */
  ESysStatus on_window_display_changed(const SDL_WindowEvent& window); /**< Window Moved Display */
  ESysStatus on_window_display_scale_changed(const SDL_WindowEvent& window);
  ESysStatus on_window_safe_area_changed(const SDL_WindowEvent& window);
  ESysStatus on_window_occluded(const SDL_WindowEvent& window);
  ESysStatus on_window_enter_fullscreen(const SDL_WindowEvent& window);
  ESysStatus on_window_leave_fullscreen(const SDL_WindowEvent& window);
  ESysStatus on_window_destroyed(const SDL_WindowEvent& window);
  ESysStatus on_window_hdr_state_changed(const SDL_WindowEvent& window);
#endif

#if IS_USING_SDL_1 || IS_USING_SDL_2
  /** SDL1, SDL2 SysWM Event */
  ESysStatus on_sys_wm(const SDL_SysWMEvent& syswm);
#endif

/*
  ██╗  ██╗███████╗██╗   ██╗██████╗  ██████╗  █████╗ ██████╗ ██████╗
  ██║ ██╔╝██╔════╝╚██╗ ██╔╝██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔══██╗
  █████╔╝ █████╗   ╚████╔╝ ██████╔╝██║   ██║███████║██████╔╝██║  ██║
  ██╔═██╗ ██╔══╝    ╚██╔╝  ██╔══██╗██║   ██║██╔══██║██╔══██╗██║  ██║
  ██║  ██╗███████╗   ██║   ██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝
  ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/

  ESysStatus on_keyboard_key_down(const SDL_KeyboardEvent& key); /**< Keyboard Key Down */
  ESysStatus on_keyboard_key_up(const SDL_KeyboardEvent& key); /**< Keyboard Key Up */

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_text_editing(const SDL_TextEditingEvent& edit); /**< Keyboard Text Composition Editing */
  ESysStatus on_text_input(const SDL_TextInputEvent& text); /**< Keyboard Text Input */
  ESysStatus on_keyboard_keymap_changed(const SDL_CommonEvent& common); /**< System Keyboard Layout Changed */
#endif

#if IS_USING_SDL_2
  /** Keyboard Text Composition Editing, Extended.
      `text` will be freed after calling this.
      So, make a hard copy of `text` if you need it.
   */
  ESysStatus on_text_editing_ext(const SDL_TextEditingExtEvent& editExt);
#endif

#if IS_USING_SDL_3
  ESysStatus on_keyboard_added(const SDL_KeyboardDeviceEvent& kdevice);
  ESysStatus on_keyboard_removed(const SDL_KeyboardDeviceEvent& kdevice);
  ESysStatus on_text_editing_candidates(const SDL_TextEditingCandidatesEvent& edit_candidates);
#endif

/*
  ███╗   ███╗ ██████╗ ██╗   ██╗███████╗███████╗
  ████╗ ████║██╔═══██╗██║   ██║██╔════╝██╔════╝
  ██╔████╔██║██║   ██║██║   ██║███████╗█████╗
  ██║╚██╔╝██║██║   ██║██║   ██║╚════██║██╔══╝
  ██║ ╚═╝ ██║╚██████╔╝╚██████╔╝███████║███████╗
  ╚═╝     ╚═╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝
*/

  ESysStatus on_mouse_motion(const SDL_MouseMotionEvent& motion); /**< Mouse Motion */
  ESysStatus on_mouse_button_down(const SDL_MouseButtonEvent& button); /**< Mouse Button Down */
  ESysStatus on_mouse_button_up(const SDL_MouseButtonEvent& button); /**< Mouse Button Up */

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_mouse_wheel(const SDL_MouseWheelEvent& wheel); /**< Mouse Wheel Motion */
#endif

#if IS_USING_SDL_3
  ESysStatus on_mouse_added(const SDL_MouseDeviceEvent& mdevice);
  ESysStatus on_mouse_removed(const SDL_MouseDeviceEvent& mdevice);
#endif

/*
       ██╗ ██████╗ ██╗   ██╗███████╗████████╗██╗ ██████╗██╗  ██╗
       ██║██╔═══██╗╚██╗ ██╔╝██╔════╝╚══██╔══╝██║██╔════╝██║ ██╔╝
       ██║██║   ██║ ╚████╔╝ ███████╗   ██║   ██║██║     █████╔╝
  ██   ██║██║   ██║  ╚██╔╝  ╚════██║   ██║   ██║██║     ██╔═██╗
  ╚█████╔╝╚██████╔╝   ██║   ███████║   ██║   ██║╚██████╗██║  ██╗
   ╚════╝  ╚═════╝    ╚═╝   ╚══════╝   ╚═╝   ╚═╝ ╚═════╝╚═╝  ╚═╝
*/

  ESysStatus on_joystick_axis_motion(const SDL_JoyAxisEvent& jaxis); /**< Joystick Axis Motion */
  ESysStatus on_joystick_ball_motion(const SDL_JoyBallEvent& jball); /**< Joystick Ball Motion */
  ESysStatus on_joystick_hat_motion(const SDL_JoyHatEvent& jhat); /**< Joystick Hat Motion */
  ESysStatus on_joystick_button_down(const SDL_JoyButtonEvent& jbutton); /**< Joystick Button Down */
  ESysStatus on_joystick_button_up(const SDL_JoyButtonEvent& jbutton); /**< Joystick Button Up */

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_joystick_added(const SDL_JoyDeviceEvent& jdevice);
  ESysStatus on_joystick_removed(const SDL_JoyDeviceEvent& jdevice);
  ESysStatus on_joystick_battery_updated(const SDL_JoyBatteryEvent& jbattery);
  ESysStatus on_joystick_update_complete(const SDL_JoyDeviceEvent& jdevice);
#endif

/*
   ██████╗  █████╗ ███╗   ███╗███████╗██████╗  █████╗ ██████╗
  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝██╔══██╗██╔══██╗██╔══██╗
  ██║  ███╗███████║██╔████╔██║█████╗  ██████╔╝███████║██║  ██║
  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ██╔═══╝ ██╔══██║██║  ██║
  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗██║     ██║  ██║██████╔╝
   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═════╝
*/

#if IS_USING_SDL_2
  typedef SDL_ControllerAxisEvent SDL_GamepadAxisEvent;
  typedef SDL_ControllerButtonEvent SDL_GamepadButtonEvent;
  typedef SDL_ControllerDeviceEvent SDL_GamepadDeviceEvent;
  typedef SDL_ControllerTouchpadEvent SDL_GamepadTouchpadEvent;
  typedef SDL_ControllerSensorEvent SDL_GamepadSensorEvent;
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_gamepad_axis_motion(const SDL_GamepadAxisEvent& gaxis);
  ESysStatus on_gamepad_button_down(const SDL_GamepadButtonEvent& gbutton);
  ESysStatus on_gamepad_button_up(const SDL_GamepadButtonEvent& gbutton);
  ESysStatus on_gamepad_added(const SDL_GamepadDeviceEvent& gdevice);
  ESysStatus on_gamepad_removed(const SDL_GamepadDeviceEvent& gdevice);
  ESysStatus on_gamepad_remapped(const SDL_GamepadDeviceEvent& gdevice);
  ESysStatus on_gamepad_touchpad_down(const SDL_GamepadTouchpadEvent& gtouchpad);
  ESysStatus on_gamepad_touchpad_motion(const SDL_GamepadTouchpadEvent& gtouchpad);
  ESysStatus on_gamepad_touchpad_up(const SDL_GamepadTouchpadEvent& gtouchpad);
  ESysStatus on_gamepad_sensor_update(const SDL_GamepadSensorEvent& gsensor);
  ESysStatus on_gamepad_update_complete(const SDL_GamepadDeviceEvent& gdevice);
  ESysStatus on_gamepad_steam_handle_updated(const SDL_GamepadDeviceEvent& gdevice);
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
  ESysStatus on_finger_down(const SDL_TouchFingerEvent& tfinger);
  ESysStatus on_finger_up(const SDL_TouchFingerEvent& tfinger);
  ESysStatus on_finger_motion(const SDL_TouchFingerEvent& tfinger);
  ESysStatus on_finger_canceled(const SDL_TouchFingerEvent& tfinger);
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
  ESysStatus on_dollar_gesture(const SDL_DollarGestureEvent& dgesture);
  ESysStatus on_dollar_record(const SDL_DollarGestureEvent& dgesture);
  ESysStatus on_multi_gesture(const SDL_MultiGestureEvent& mgesture);
#endif


/*
   ██████╗██╗     ██╗██████╗ ██████╗  ██████╗  █████╗ ██████╗ ██████╗
  ██╔════╝██║     ██║██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔══██╗
  ██║     ██║     ██║██████╔╝██████╔╝██║   ██║███████║██████╔╝██║  ██║
  ██║     ██║     ██║██╔═══╝ ██╔══██╗██║   ██║██╔══██║██╔══██╗██║  ██║
  ╚██████╗███████╗██║██║     ██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝
   ╚═════╝╚══════╝╚═╝╚═╝     ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/

#if IS_USING_SDL_2
  typedef SDL_CommonEvent SDL_ClipboardEvent;
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_clipboard_update(const SDL_ClipboardEvent& clipboard);
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
  ESysStatus on_drop_file(const SDL_DropEvent& drop);
  ESysStatus on_drop_text(const SDL_DropEvent& drop);
  ESysStatus on_drop_begin(const SDL_DropEvent& drop);
  ESysStatus on_drop_complete(const SDL_DropEvent& drop);
  ESysStatus on_drop_position(const SDL_DropEvent& drop);
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
  ESysStatus on_audio_device_added(const SDL_AudioDeviceEvent& adevice);
  ESysStatus on_audio_device_removed(const SDL_AudioDeviceEvent& adevice);
  ESysStatus on_audio_device_format_changed(const SDL_AudioDeviceEvent& adevice);
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
  ESysStatus on_sensor_update(const SDL_SensorEvent& sensor);
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
  ESysStatus on_pen_proximity_in(const SDL_PenProximityEvent& pproximity);
  ESysStatus on_pen_proximity_out(const SDL_PenProximityEvent& pproximity);
  ESysStatus on_pen_down(const SDL_PenTouchEvent& ptouch);
  ESysStatus on_pen_up(const SDL_PenTouchEvent& ptouch);
  ESysStatus on_pen_button_down(const SDL_PenButtonEvent& pbutton);
  ESysStatus on_pen_button_up(const SDL_PenButtonEvent& pbutton);
  ESysStatus on_pen_motion(const SDL_PenMotionEvent& pmotion);
  ESysStatus on_pen_axis(const SDL_PenAxisEvent& paxis);
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
  ESysStatus on_camera_device_added(const SDL_CameraDeviceEvent& cdevice);
  ESysStatus on_camera_device_removed(const SDL_CameraDeviceEvent& cdevice);
  ESysStatus on_camera_device_approved(const SDL_CameraDeviceEvent& cdevice);
  ESysStatus on_camera_device_denied(const SDL_CameraDeviceEvent& cdevice);
#endif

/*
  ██████╗ ███████╗███╗   ██╗██████╗ ███████╗██████╗
  ██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝██╔══██╗
  ██████╔╝█████╗  ██╔██╗ ██║██║  ██║█████╗  ██████╔╝
  ██╔══██╗██╔══╝  ██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗
  ██║  ██║███████╗██║ ╚████║██████╔╝███████╗██║  ██║
  ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝
*/

#if IS_USING_SDL_2
  typedef SDL_CommonEvent SDL_RenderEvent;
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_render_targets_reset(const SDL_RenderEvent& render);
  ESysStatus on_render_device_reset(const SDL_RenderEvent& render);
  ESysStatus on_render_device_lost(const SDL_RenderEvent& render);
#endif

/*
  ██╗   ██╗███████╗███████╗██████╗
  ██║   ██║██╔════╝██╔════╝██╔══██╗
  ██║   ██║███████╗█████╗  ██████╔╝
  ██║   ██║╚════██║██╔══╝  ██╔══██╗
  ╚██████╔╝███████║███████╗██║  ██║
   ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝
*/

  ESysStatus on_user_event(const SDL_UserEvent& event); /**< "User" Custom Event */

};




/*
  ███████╗███╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗
  ██╔════╝████╗  ██║██╔════╝ ██║████╗  ██║██╔════╝
  █████╗  ██╔██╗ ██║██║  ███╗██║██╔██╗ ██║█████╗
  ██╔══╝  ██║╚██╗██║██║   ██║██║██║╚██╗██║██╔══╝
  ███████╗██║ ╚████║╚██████╔╝██║██║ ╚████║███████╗
  ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝
*/

ESysStatus Engine::preSdlInit(int, char**) {
  return E_SYS_CONTINUE;
}

ESysStatus Engine::initSdl(int, char**) {
  const Sdl::Status res = Sdl::def().timer().video().events().eventThread().init();
  if (res != Sdl::INIT_SUCCEED) {
    Journal::sdlInitFailed();
    exit_code = EXIT_FAILURE;
    debugBreak;
    return E_SYS_FATALITY;
  } else {
    return E_SYS_CONTINUE;
  }
}

ESysStatus Engine::initEngine(int, char**) {
#if IS_USING_SDL_2 || IS_USING_SDL_3
  SDL_SetEventFilter(sdlEventFilter, null);
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
    debugBreak;
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

  if (window_.create() == null) {
    exit_code = EXIT_FAILURE;
    debugBreak;
    return E_SYS_FATALITY;
  }

  print("Current video driver: %s\n", SdlWindow::getCurrentVideoDriverName());
#if IS_USING_SDL_2 || IS_USING_SDL_3
  const int video_count = SdlWindow::getVideoDriverCount();
  if (video_count < 1) {
    exit_code = EXIT_FAILURE;
    debugBreak;
    return E_SYS_FATALITY;
  }
  print("Found %d video drivers.\n", video_count);
  for (int i = 0; i < video_count; i++) {
    const char* name = SdlWindow::getVideoDriverName(i);
    print("Video driver %d: %s\n", i, name);
  }
#endif
  print("Current video driver: %s\n", SdlWindow::getCurrentVideoDriverName());

  return E_SYS_CONTINUE;
}

void Engine::calculateDeltaTime(DebugData& db) {
  /* Begin { Print Frame Time } */ {
    const u64 now = clockU64();
    const double delta = castDouble(now - db.past) / castDouble(db.frequency);
    const double fps = castDouble(MSPS) / delta;
    db.past = now;
    // print("delta: %f\tfps: %f\n", delta, fps);
    char title[128] = {0};
    snprintf(title, sizeof(title), "delta: %.2f fps: %.2f", delta, fps);
    window_.setTitle(title);
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
#if !AB_SANITIZE
  Sdl::quit();
#endif
}

Engine::Engine()
  : window_(SdlWindow::def())
{
  /* FFF: F&^k Fixed Frequency */
  /* target_delta_ms = 0;      */
  target_delta_ms = (MSPS / 10);
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
  // debugBreak;
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
  switch (Sdl::checkKey(key)) {
  case Sdl::NUM_0: target_delta_ms = 0; break;
  case Sdl::NUM_1: target_delta_ms = (MSPS / 30); break;
  case Sdl::NUM_2: target_delta_ms = (MSPS / 60); break;
  case Sdl::NUM_3: target_delta_ms = (MSPS / 120); break;
  default: break;
  }
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

ESysStatus Engine::on_keyboard_keymap_changed(const SDL_CommonEvent& common) {
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

ESysStatus Engine::on_finger_canceled(const SDL_TouchFingerEvent& tfinger) {
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

ESysStatus Engine::on_dollar_record(const SDL_DollarGestureEvent& dgesture) {
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
    case SDL_ACTIVEEVENT: {
      if (event.active.state & SDL_APPMOUSEFOCUS) { event.active.gain ? on_window_mouse_enter() : on_window_mouse_leave(); }
      if (event.active.state & SDL_APPINPUTFOCUS) { event.active.gain ? on_window_focus_gained() : on_window_focus_lost(); }
      if (event.active.state & SDL_APPACTIVE) { event.active.gain ? on_window_restored() : on_window_minimized(); }
      return E_SYS_CONTINUE;
    }
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
ESysStatus Engine::eventSdl(const SDL_Event& event) {
  switch (event.type) {
  /* Application events */
  case SDL_QUIT: return on_quit(event.quit);
  /* These application events have special meaning on iOS, see SDL2 README-ios.md for details */
  case SDL_APP_TERMINATING: return on_terminating(event.common);
  case SDL_APP_LOWMEMORY: return on_low_memory(event.common);
  case SDL_APP_WILLENTERBACKGROUND: return on_will_enter_background(event.common);
  case SDL_APP_DIDENTERBACKGROUND: return on_did_enter_background(event.common);
  case SDL_APP_WILLENTERFOREGROUND: return on_will_enter_foreground(event.common);
  case SDL_APP_DIDENTERFOREGROUND: return on_did_enter_foreground(event.common);
  case SDL_LOCALECHANGED: return on_locale_changed(event.common);
  /* Display events */
  case SDL_DISPLAYEVENT:
    switch (event.display.event) {
    case SDL_DISPLAYEVENT_ORIENTATION:
      switch (event.display.data1) {
      case SDL_ORIENTATION_UNKNOWN: return on_orientation_unknown(event.display);
      case SDL_ORIENTATION_LANDSCAPE: return on_orientation_landscape(event.display);
      case SDL_ORIENTATION_LANDSCAPE_FLIPPED: return on_orientation_landscape_flipped(event.display);
      case SDL_ORIENTATION_PORTRAIT: return on_orientation_portrait(event.display);
      case SDL_ORIENTATION_PORTRAIT_FLIPPED: return on_orientation_portrait_flipped(event.display);
      default: break;
      }
      break;
    case SDL_DISPLAYEVENT_CONNECTED: return on_display_added(event.display);
    case SDL_DISPLAYEVENT_DISCONNECTED: return on_display_removed(event.display);
    case SDL_DISPLAYEVENT_MOVED: return on_display_moved(event.display);
    default: break;
    }
    break;
  case SDL_WINDOWEVENT:
    switch (event.window.event) {
    case SDL_WINDOWEVENT_SHOWN: return on_window_shown(event.window);
    case SDL_WINDOWEVENT_HIDDEN: return on_window_hidden(event.window);
    case SDL_WINDOWEVENT_EXPOSED: return on_window_exposed(event.window);
    case SDL_WINDOWEVENT_MOVED: return on_window_moved(event.window);
    case SDL_WINDOWEVENT_RESIZED: return on_window_resized(event.window);
    case SDL_WINDOWEVENT_SIZE_CHANGED: return on_window_size_changed(event.window);
    case SDL_WINDOWEVENT_MINIMIZED: return on_window_minimized(event.window);
    case SDL_WINDOWEVENT_MAXIMIZED: return on_window_maximized(event.window);
    case SDL_WINDOWEVENT_RESTORED: return on_window_restored(event.window);
    case SDL_WINDOWEVENT_ENTER: return on_window_mouse_enter(event.window);
    case SDL_WINDOWEVENT_LEAVE: return on_window_mouse_leave(event.window);
    case SDL_WINDOWEVENT_FOCUS_GAINED: return on_window_focus_gained(event.window);
    case SDL_WINDOWEVENT_FOCUS_LOST: return on_window_focus_lost(event.window);
    case SDL_WINDOWEVENT_CLOSE: return on_window_close_request(event.window);
    case SDL_WINDOWEVENT_TAKE_FOCUS: return on_window_take_focus(event.window);
    case SDL_WINDOWEVENT_HIT_TEST: return on_window_hit_test(event.window);
    case SDL_WINDOWEVENT_ICCPROF_CHANGED: return on_window_icc_changed(event.window);
    case SDL_WINDOWEVENT_DISPLAY_CHANGED: return on_window_display_changed(event.window);
    default: break;
    }
    break;
  case SDL_SYSWMEVENT: return on_sys_wm(event.syswm);
  /* Keyboard events */
  case SDL_KEYDOWN: return on_keyboard_key_down(event.key);
  case SDL_KEYUP: return on_keyboard_key_up(event.key);
  case SDL_TEXTEDITING: return on_text_editing(event.edit);
  case SDL_TEXTINPUT: return on_text_input(event.text);
  case SDL_KEYMAPCHANGED: return on_keyboard_keymap_changed(event.common);
  case SDL_TEXTEDITING_EXT: {
    const ESysStatus res = on_text_editing_ext(event.editExt);
    SDL_free(event.editExt.text);
    return res;
  }
  /* Mouse events */
  case SDL_MOUSEMOTION: return on_mouse_motion(event.motion);
  case SDL_MOUSEBUTTONDOWN: return on_mouse_button_down(event.button);
  case SDL_MOUSEBUTTONUP: return on_mouse_button_up(event.button);
  case SDL_MOUSEWHEEL: return on_mouse_wheel(event.wheel);
  /* Joystick events */
  case SDL_JOYAXISMOTION: return on_joystick_axis_motion(event.jaxis);
  case SDL_JOYBALLMOTION: return on_joystick_ball_motion(event.jball);
  case SDL_JOYHATMOTION: return on_joystick_hat_motion(event.jhat);
  case SDL_JOYBUTTONDOWN: return on_joystick_button_down(event.jbutton);
  case SDL_JOYBUTTONUP: return on_joystick_button_up(event.jbutton);
  case SDL_JOYDEVICEADDED: return on_joystick_added(event.jdevice);
  case SDL_JOYDEVICEREMOVED: return on_joystick_removed(event.jdevice);
  case SDL_JOYBATTERYUPDATED: return on_joystick_battery_updated(event.jbattery);
  /* Game controller events */
  case SDL_CONTROLLERAXISMOTION: return on_gamepad_axis_motion(event.caxis);
  case SDL_CONTROLLERBUTTONDOWN: return on_gamepad_button_down(event.cbutton);
  case SDL_CONTROLLERBUTTONUP: return on_gamepad_button_up(event.cbutton);
  case SDL_CONTROLLERDEVICEADDED: return on_gamepad_added(event.cdevice);
  case SDL_CONTROLLERDEVICEREMOVED: return on_gamepad_removed(event.cdevice);
  case SDL_CONTROLLERDEVICEREMAPPED: return on_gamepad_remapped(event.cdevice);
  case SDL_CONTROLLERTOUCHPADDOWN: return on_gamepad_touchpad_down(event.ctouchpad);
  case SDL_CONTROLLERTOUCHPADMOTION: return on_gamepad_touchpad_motion(event.ctouchpad);
  case SDL_CONTROLLERTOUCHPADUP: return on_gamepad_touchpad_up(event.ctouchpad);
  case SDL_CONTROLLERSENSORUPDATE: return on_gamepad_sensor_update(event.csensor);
  case SDL_CONTROLLERSTEAMHANDLEUPDATED: return on_gamepad_steam_handle_updated(event.cdevice);
  /* Touch events */
  case SDL_FINGERDOWN: return on_finger_down(event.tfinger);
  case SDL_FINGERUP: return on_finger_up(event.tfinger);
  case SDL_FINGERMOTION: return on_finger_motion(event.tfinger);
  /* Gesture events */
  case SDL_DOLLARGESTURE: return on_dollar_gesture(event.dgesture);
  case SDL_DOLLARRECORD : return on_dollar_record(event.dgesture);
  case SDL_MULTIGESTURE: return on_multi_gesture(event.mgesture);
  /* Clipboard events */
  case SDL_CLIPBOARDUPDATE: return on_clipboard_update(event.common);
  /* Drag and drop events */
  case SDL_DROPFILE: return on_drop_file(event.drop);
  case SDL_DROPTEXT: return on_drop_text(event.drop);
  case SDL_DROPBEGIN: return on_drop_begin(event.drop);
  case SDL_DROPCOMPLETE: return on_drop_complete(event.drop);
  /* Audio hotplug events */
  case SDL_AUDIODEVICEADDED: return on_audio_device_added(event.adevice);
  case SDL_AUDIODEVICEREMOVED: return on_audio_device_removed(event.adevice);
  /* Sensor events */
  case SDL_SENSORUPDATE: return on_sensor_update(event.sensor);
  /* Render events */
  case SDL_RENDER_TARGETS_RESET: return on_render_targets_reset(event.common);
  case SDL_RENDER_DEVICE_RESET: return on_render_device_reset(event.common);
  /* User events */
  case SDL_USEREVENT: return on_user_event(event.user);
  default: break;
  }
  return on_unrecognized_event(event);
}

bool Engine::sdlEventFilter(const SDL_Event& event) {
  /* Application events */
  /* These application events have special meaning on iOS, see SDL2 README-ios.md for details */
  switch (event.type) {
  case SDL_APP_TERMINATING: on_terminating(event.common); return false;
  case SDL_APP_LOWMEMORY: on_low_memory(event.common); return false;
  case SDL_APP_WILLENTERBACKGROUND: on_will_enter_background(event.common); return false;
  case SDL_APP_DIDENTERBACKGROUND: on_did_enter_background(event.common); return false;
  default: break;
  }
  return true;
}
#elif IS_USING_SDL_3
ESysStatus Engine::eventSdl(const SDL_Event& event) {
  switch (event.type) {
  /* Application events */
  case SDL_EVENT_QUIT: return on_quit(event.quit);
  /* These application events have special meaning on iOS and Android, see SDL3 README-ios.md and SDL3 README-android.md for details */
  case SDL_EVENT_TERMINATING: return on_terminating(event.common);
  case SDL_EVENT_LOW_MEMORY: return on_low_memory(event.common);
  case SDL_EVENT_WILL_ENTER_BACKGROUND: return on_will_enter_background(event.common);
  case SDL_EVENT_DID_ENTER_BACKGROUND: return on_did_enter_background(event.common);
  case SDL_EVENT_WILL_ENTER_FOREGROUND: return on_will_enter_foreground(event.common);
  case SDL_EVENT_DID_ENTER_FOREGROUND: return on_did_enter_foreground(event.common);
  case SDL_EVENT_LOCALE_CHANGED: return on_locale_changed(event.common);
  case SDL_EVENT_SYSTEM_THEME_CHANGED: return on_system_theme_changed(event.common);
  /* Display events */
  case SDL_EVENT_DISPLAY_ORIENTATION:
    switch (event.display.data1) {
    case SDL_ORIENTATION_UNKNOWN: return on_orientation_unknown(event.display);
    case SDL_ORIENTATION_LANDSCAPE: return on_orientation_landscape(event.display);
    case SDL_ORIENTATION_LANDSCAPE_FLIPPED: return on_orientation_landscape_flipped(event.display);
    case SDL_ORIENTATION_PORTRAIT: return on_orientation_portrait(event.display);
    case SDL_ORIENTATION_PORTRAIT_FLIPPED: return on_orientation_portrait_flipped(event.display);
    default: break;
    }
    break;
  case SDL_EVENT_DISPLAY_ADDED: return on_display_added(event.display);
  case SDL_EVENT_DISPLAY_REMOVED: return on_display_removed(event.display);
  case SDL_EVENT_DISPLAY_MOVED: return on_display_moved(event.display);
  case SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED: return on_display_desktop_mode_changed(event.display);
  case SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED: return on_display_current_mode_changed(event.display);
  case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED: return on_display_content_scale_changed(event.display);
  /* Window events */
  case SDL_EVENT_WINDOW_SHOWN: return on_window_shown(event.window);
  case SDL_EVENT_WINDOW_HIDDEN: return on_window_hidden(event.window);
  case SDL_EVENT_WINDOW_EXPOSED: return on_window_exposed(event.window);
  case SDL_EVENT_WINDOW_MOVED: return on_window_moved(event.window);
  case SDL_EVENT_WINDOW_RESIZED: return on_window_resized(event.window);
  case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: return on_window_pixel_size_changed(event.window);
  case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED: return on_window_metal_view_resized(event.window);
  case SDL_EVENT_WINDOW_MINIMIZED: return on_window_minimized(event.window);
  case SDL_EVENT_WINDOW_MAXIMIZED: return on_window_maximized(event.window);
  case SDL_EVENT_WINDOW_RESTORED: return on_window_restored(event.window);
  case SDL_EVENT_WINDOW_MOUSE_ENTER: return on_window_mouse_enter(event.window);
  case SDL_EVENT_WINDOW_MOUSE_LEAVE: return on_window_mouse_leave(event.window);
  case SDL_EVENT_WINDOW_FOCUS_GAINED: return on_window_focus_gained(event.window);
  case SDL_EVENT_WINDOW_FOCUS_LOST: return on_window_focus_lost(event.window);
  case SDL_EVENT_WINDOW_CLOSE_REQUESTED: return on_window_close_request(event.window);
  case SDL_EVENT_WINDOW_HIT_TEST: return on_window_hit_test(event.window);
  case SDL_EVENT_WINDOW_ICCPROF_CHANGED: return on_window_icc_changed(event.window);
  case SDL_EVENT_WINDOW_DISPLAY_CHANGED: return on_window_display_changed(event.window);
  case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED: return on_window_display_scale_changed(event.window);
  case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED: return on_window_safe_area_changed(event.window);
  case SDL_EVENT_WINDOW_OCCLUDED: return on_window_occluded(event.window);
  case SDL_EVENT_WINDOW_ENTER_FULLSCREEN: return on_window_enter_fullscreen(event.window);
  case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN: return on_window_leave_fullscreen(event.window);
  case SDL_EVENT_WINDOW_DESTROYED: return on_window_destroyed(event.window);
  case SDL_EVENT_WINDOW_HDR_STATE_CHANGED: return on_window_hdr_state_changed(event.window);
  /* Keyboard events */
  case SDL_EVENT_KEY_DOWN: return on_keyboard_key_down(event.key);
  case SDL_EVENT_KEY_UP: return on_keyboard_key_up(event.key);
  case SDL_EVENT_TEXT_EDITING: return on_text_editing(event.edit);
  case SDL_EVENT_TEXT_INPUT: return on_text_input(event.text);
  case SDL_EVENT_KEYMAP_CHANGED: return on_keyboard_keymap_changed(event.common);
  case SDL_EVENT_KEYBOARD_ADDED: return on_keyboard_added(event.kdevice);
  case SDL_EVENT_KEYBOARD_REMOVED: return on_keyboard_removed(event.kdevice);
  case SDL_EVENT_TEXT_EDITING_CANDIDATES: return on_text_editing_candidates(event.edit_candidates);
  /* Mouse events */
  case SDL_EVENT_MOUSE_MOTION: return on_mouse_motion(event.motion);
  case SDL_EVENT_MOUSE_BUTTON_DOWN: return on_mouse_button_down(event.button);
  case SDL_EVENT_MOUSE_BUTTON_UP: return on_mouse_button_up(event.button);
  case SDL_EVENT_MOUSE_WHEEL: return on_mouse_wheel(event.wheel);
  case SDL_EVENT_MOUSE_ADDED: return on_mouse_added(event.mdevice);
  case SDL_EVENT_MOUSE_REMOVED: return on_mouse_removed(event.mdevice);
  /* Joystick events */
  case SDL_EVENT_JOYSTICK_AXIS_MOTION: return on_joystick_axis_motion(event.jaxis);
  case SDL_EVENT_JOYSTICK_BALL_MOTION: return on_joystick_ball_motion(event.jball);
  case SDL_EVENT_JOYSTICK_HAT_MOTION: return on_joystick_hat_motion(event.jhat);
  case SDL_EVENT_JOYSTICK_BUTTON_DOWN: return on_joystick_button_down(event.jbutton);
  case SDL_EVENT_JOYSTICK_BUTTON_UP: return on_joystick_button_up(event.jbutton);
  case SDL_EVENT_JOYSTICK_ADDED: return on_joystick_added(event.jdevice);
  case SDL_EVENT_JOYSTICK_REMOVED: return on_joystick_removed(event.jdevice);
  case SDL_EVENT_JOYSTICK_BATTERY_UPDATED: return on_joystick_battery_updated(event.jbattery);
  case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE: return on_joystick_update_complete(event.jdevice);
  /* Gamepad events (renamed from "Game controller" / CONTROLLER in SDL2) */
  case SDL_EVENT_GAMEPAD_AXIS_MOTION: return on_gamepad_axis_motion(event.gaxis);
  case SDL_EVENT_GAMEPAD_BUTTON_DOWN: return on_gamepad_button_down(event.gbutton);
  case SDL_EVENT_GAMEPAD_BUTTON_UP: return on_gamepad_button_up(event.gbutton);
  case SDL_EVENT_GAMEPAD_ADDED: return on_gamepad_added(event.gdevice);
  case SDL_EVENT_GAMEPAD_REMOVED: return on_gamepad_removed(event.gdevice);
  case SDL_EVENT_GAMEPAD_REMAPPED: return on_gamepad_remapped(event.gdevice);
  case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN: return on_gamepad_touchpad_down(event.gtouchpad);
  case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION: return on_gamepad_touchpad_motion(event.gtouchpad);
  case SDL_EVENT_GAMEPAD_TOUCHPAD_UP: return on_gamepad_touchpad_up(event.gtouchpad);
  case SDL_EVENT_GAMEPAD_SENSOR_UPDATE: return on_gamepad_sensor_update(event.gsensor);
  case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE: return on_gamepad_update_complete(event.gdevice);
  case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED: return on_gamepad_steam_handle_updated(event.gdevice);
  /* Touch events */
  case SDL_EVENT_FINGER_DOWN: return on_finger_down(event.tfinger);
  case SDL_EVENT_FINGER_UP: return on_finger_up(event.tfinger);
  case SDL_EVENT_FINGER_MOTION: return on_finger_motion(event.tfinger);
  case SDL_EVENT_FINGER_CANCELED: return on_finger_canceled(event.tfinger);
  /* Clipboard events */
  case SDL_EVENT_CLIPBOARD_UPDATE: return on_clipboard_update(event.clipboard);
  /* Drag and drop events */
  case SDL_EVENT_DROP_FILE: return on_drop_file(event.drop);
  case SDL_EVENT_DROP_TEXT: return on_drop_text(event.drop);
  case SDL_EVENT_DROP_BEGIN: return on_drop_begin(event.drop);
  case SDL_EVENT_DROP_COMPLETE: return on_drop_complete(event.drop);
  case SDL_EVENT_DROP_POSITION: return on_drop_position(event.drop);
  /* Audio hotplug events */
  case SDL_EVENT_AUDIO_DEVICE_ADDED: return on_audio_device_added(event.adevice);
  case SDL_EVENT_AUDIO_DEVICE_REMOVED: return on_audio_device_removed(event.adevice);
  case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED: return on_audio_device_format_changed(event.adevice);
  /* Sensor events */
  case SDL_EVENT_SENSOR_UPDATE: return on_sensor_update(event.sensor);
  /* Pressure-sensitive pen events */
  case SDL_EVENT_PEN_PROXIMITY_IN: return on_pen_proximity_in(event.pproximity);
  case SDL_EVENT_PEN_PROXIMITY_OUT: return on_pen_proximity_out(event.pproximity);
  case SDL_EVENT_PEN_DOWN: return on_pen_down(event.ptouch);
  case SDL_EVENT_PEN_UP: return on_pen_up(event.ptouch);
  case SDL_EVENT_PEN_BUTTON_DOWN: return on_pen_button_down(event.pbutton);
  case SDL_EVENT_PEN_BUTTON_UP: return on_pen_button_up(event.pbutton);
  case SDL_EVENT_PEN_MOTION: return on_pen_motion(event.pmotion);
  case SDL_EVENT_PEN_AXIS: return on_pen_axis(event.paxis);
  /* Camera hotplug events */
  case SDL_EVENT_CAMERA_DEVICE_ADDED: return on_camera_device_added(event.cdevice);
  case SDL_EVENT_CAMERA_DEVICE_REMOVED: return on_camera_device_removed(event.cdevice);
  case SDL_EVENT_CAMERA_DEVICE_APPROVED: return on_camera_device_approved(event.cdevice);
  case SDL_EVENT_CAMERA_DEVICE_DENIED: return on_camera_device_denied(event.cdevice);
  /* Render events */
  case SDL_EVENT_RENDER_TARGETS_RESET: return on_render_targets_reset(event.render);
  case SDL_EVENT_RENDER_DEVICE_RESET: return on_render_device_reset(event.render);
  case SDL_EVENT_RENDER_DEVICE_LOST: return on_render_device_lost(event.render);
  /* User events */
  case SDL_EVENT_USER: return on_user_event(event.user);
  default: break;
  }
  return on_unrecognized_event(event);
}

bool Engine::sdlEventFilter(const SDL_Event& event) {
  return true;
}
#endif

#if IS_USING_SDL_2
int Engine::sdlEventFilter(void* self, SDL_Event* event) {
  return static_cast<Engine*>(self)->sdlEventFilter(*event) ? 1 : 0;
}
#elif IS_USING_SDL_3
bool Engine::sdlEventFilter(void* self, SDL_Event* event) {
  return static_cast<Engine*>(self)->sdlEventFilter(*event);
}
#endif




/*
  ███╗   ███╗ █████╗ ██╗███╗   ██╗
  ████╗ ████║██╔══██╗██║████╗  ██║
  ██╔████╔██║███████║██║██╔██╗ ██║
  ██║╚██╔╝██║██╔══██║██║██║╚██╗██║
  ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝
*/

struct Timing {
private:
  const u64 frequency_; /* Clock frequency in millisecond. */
  u64 post_; /* Post delay clock. */
  u32 delay_; /* Calculated milliseconds of last delay. */
  Timing()
  : frequency_(clockFrequencyU64() / MSPS)
  , post_(clockU64())
  , delay_(0)
  {}
public:
  void frameEnd(const u32 target_delta_ms) {
    const u64 now = clockU64();
    const u64 past = post_;
    const u64 delta = (now - past) / frequency_;
    delay_ = target_delta_ms > delta ? target_delta_ms - delta : 0 ;
    SDL_Delay(delay_);
    post_ = clockU64();
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
repeat_step:
    switch (engine.stepEngine()) {
      case E_SYS_REPEAT: goto repeat_step;
      case E_SYS_CONTINUE: break;
      default: return shutdown(engine);
    }
    timing.frameEnd(engine.target_delta_ms);
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

Sdl::Status Sdl::init() {
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

