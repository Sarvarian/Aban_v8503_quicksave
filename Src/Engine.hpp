#pragma once

#ifndef AB_ENGINE_HPP
#define AB_ENGINE_HPP

#include "Main.hpp"
#include "Memory.hpp"
#include "Sdl.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL_events.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL_events.h>
#elif IS_USING_SDL_1
  #include <SDL/SDL_events.h>
#endif

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
  struct DebugData* db_;
  struct Bootstrapper* boot_;
  struct Step* current_;
  struct Step* next_;
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


#endif /* AB_ENGINE_HPP */
