/* ReSharper disable CppMemberFunctionMayBeStatic */
#include "Aid.hpp"

SdlEventDispatcher::SdlEventDispatcher() { /* Empty */ }

/*
  ███████╗██╗   ██╗███████╗███╗   ██╗████████╗███████╗
  ██╔════╝██║   ██║██╔════╝████╗  ██║╚══██╔══╝██╔════╝
  █████╗  ██║   ██║█████╗  ██╔██╗ ██║   ██║   ███████╗
  ██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ╚════██║
  ███████╗ ╚████╔╝ ███████╗██║ ╚████║   ██║   ███████║
  ╚══════╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
*/

ESysStatus SdlEventDispatcher::on_unrecognized_event(const SDL_Event& event) { // NOLINT(*-convert-member-functions-to-static)
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

ESysStatus SdlEventDispatcher::on_quit(const SDL_QuitEvent& quit) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_QUIT;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_terminating(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_low_memory(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_will_enter_background(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_did_enter_background(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_will_enter_foreground(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_did_enter_foreground(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_locale_changed(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_system_theme_changed(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_orientation_unknown(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_orientation_landscape(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_orientation_landscape_flipped(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_orientation_portrait(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_orientation_portrait_flipped(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_display_added(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_display_removed(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_display_moved(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_display_desktop_mode_changed(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_display_current_mode_changed(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_display_content_scale_changed(const SDL_DisplayEvent& display) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_window_exposed() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_exposed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus SdlEventDispatcher::on_window_resized(const int w, const int h) {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_resized(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus SdlEventDispatcher::on_window_minimized() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_minimized(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus SdlEventDispatcher::on_window_restored() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_restored(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus SdlEventDispatcher::on_window_mouse_enter() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_mouse_enter(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus SdlEventDispatcher::on_window_mouse_leave() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_mouse_leave(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus SdlEventDispatcher::on_window_focus_gained() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_focus_gained(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus SdlEventDispatcher::on_window_focus_lost() {
#elif IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_focus_lost(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_window_shown(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_hidden(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_moved(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_pixel_size_changed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_metal_view_resized(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_size_changed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_maximized(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_close_request(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_take_focus(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_hit_test(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_icc_changed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_display_changed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_display_scale_changed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_safe_area_changed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_occluded(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_enter_fullscreen(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_leave_fullscreen(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_destroyed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_window_hdr_state_changed(const SDL_WindowEvent& window) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_1 || IS_USING_SDL_2
ESysStatus SdlEventDispatcher::on_sys_wm(const SDL_SysWMEvent& syswm) { // NOLINT(*-convert-member-functions-to-static)
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

ESysStatus SdlEventDispatcher::on_keyboard_key_down(const SDL_KeyboardEvent& key) {
  switch (Sdl::checkKey(key)) {
  case Sdl::NUM_0: target_delta_ms = 0; break;
  case Sdl::NUM_1: target_delta_ms = (MSPS / 30); break;
  case Sdl::NUM_2: target_delta_ms = (MSPS / 60); break;
  case Sdl::NUM_3: target_delta_ms = (MSPS / 120); break;
  default: break;
  }
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_keyboard_key_up(const SDL_KeyboardEvent& key) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_text_editing(const SDL_TextEditingEvent& edit) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_text_input(const SDL_TextInputEvent& text) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_keyboard_keymap_changed(const SDL_CommonEvent& common) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_2
ESysStatus SdlEventDispatcher::on_text_editing_ext(const SDL_TextEditingExtEvent& editExt) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_keyboard_added(const SDL_KeyboardDeviceEvent& kdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_keyboard_removed(const SDL_KeyboardDeviceEvent& kdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_text_editing_candidates(const SDL_TextEditingCandidatesEvent& edit_candidates) { // NOLINT(*-convert-member-functions-to-static)
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

ESysStatus SdlEventDispatcher::on_mouse_motion(const SDL_MouseMotionEvent& motion) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_mouse_button_down(const SDL_MouseButtonEvent& button) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_mouse_button_up(const SDL_MouseButtonEvent& button) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_mouse_wheel(const SDL_MouseWheelEvent& wheel) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_mouse_added(const SDL_MouseDeviceEvent& mdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_mouse_removed(const SDL_MouseDeviceEvent& mdevice) { // NOLINT(*-convert-member-functions-to-static)
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

ESysStatus SdlEventDispatcher::on_joystick_axis_motion(const SDL_JoyAxisEvent& jaxis) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_joystick_ball_motion(const SDL_JoyBallEvent& jball) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_joystick_hat_motion(const SDL_JoyHatEvent& jhat) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_joystick_button_down(const SDL_JoyButtonEvent& jbutton) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_joystick_button_up(const SDL_JoyButtonEvent& jbutton) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus SdlEventDispatcher::on_joystick_added(const SDL_JoyDeviceEvent& jdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_joystick_removed(const SDL_JoyDeviceEvent& jdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_joystick_battery_updated(const SDL_JoyBatteryEvent& jbattery) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_joystick_update_complete(const SDL_JoyDeviceEvent& jdevice) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_gamepad_axis_motion(const SDL_GamepadAxisEvent& gaxis) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_button_down(const SDL_GamepadButtonEvent& gbutton) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_button_up(const SDL_GamepadButtonEvent& gbutton) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_added(const SDL_GamepadDeviceEvent& gdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_removed(const SDL_GamepadDeviceEvent& gdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_remapped(const SDL_GamepadDeviceEvent& gdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_touchpad_down(const SDL_GamepadTouchpadEvent& gtouchpad) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_touchpad_motion(const SDL_GamepadTouchpadEvent& gtouchpad) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_touchpad_up(const SDL_GamepadTouchpadEvent& gtouchpad) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_sensor_update(const SDL_GamepadSensorEvent& gsensor) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_update_complete(const SDL_GamepadDeviceEvent& gdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_gamepad_steam_handle_updated(const SDL_GamepadDeviceEvent& gdevice) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_finger_down(const SDL_TouchFingerEvent& tfinger) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_finger_up(const SDL_TouchFingerEvent& tfinger) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_finger_motion(const SDL_TouchFingerEvent& tfinger) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_finger_canceled(const SDL_TouchFingerEvent& tfinger) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_dollar_gesture(const SDL_DollarGestureEvent& dgesture) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_dollar_record(const SDL_DollarGestureEvent& dgesture) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_multi_gesture(const SDL_MultiGestureEvent& mgesture) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_clipboard_update(const SDL_ClipboardEvent& clipboard) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_drop_file(const SDL_DropEvent& drop) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_drop_text(const SDL_DropEvent& drop) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_drop_begin(const SDL_DropEvent& drop) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_drop_complete(const SDL_DropEvent& drop) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_drop_position(const SDL_DropEvent& drop) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_audio_device_added(const SDL_AudioDeviceEvent& adevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_audio_device_removed(const SDL_AudioDeviceEvent& adevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_audio_device_format_changed(const SDL_AudioDeviceEvent& adevice) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_sensor_update(const SDL_SensorEvent& sensor) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_pen_proximity_in(const SDL_PenProximityEvent& pproximity) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_pen_proximity_out(const SDL_PenProximityEvent& pproximity) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_pen_down(const SDL_PenTouchEvent& ptouch) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_pen_up(const SDL_PenTouchEvent& ptouch) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_pen_button_down(const SDL_PenButtonEvent& pbutton) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_pen_button_up(const SDL_PenButtonEvent& pbutton) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_pen_motion(const SDL_PenMotionEvent& pmotion) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_pen_axis(const SDL_PenAxisEvent& paxis) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_camera_device_added(const SDL_CameraDeviceEvent& cdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_camera_device_removed(const SDL_CameraDeviceEvent& cdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_camera_device_approved(const SDL_CameraDeviceEvent& cdevice) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_camera_device_denied(const SDL_CameraDeviceEvent& cdevice) { // NOLINT(*-convert-member-functions-to-static)
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
ESysStatus SdlEventDispatcher::on_render_targets_reset(const SDL_RenderEvent& render) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_render_device_reset(const SDL_RenderEvent& render) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus SdlEventDispatcher::on_render_device_lost(const SDL_RenderEvent& render) { // NOLINT(*-convert-member-functions-to-static)
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

ESysStatus SdlEventDispatcher::on_user_event(const SDL_UserEvent& event) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus SdlEventDispatcher::eventSdl(const SDL_Event& event) {
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
ESysStatus SdlEventDispatcher::eventSdl(const SDL_Event& event) {
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

bool SdlEventDispatcher::sdlEventFilter(const SDL_Event& event) {
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
ESysStatus SdlEventDispatcher::eventSdl(const SDL_Event& event) {
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

bool SdlEventDispatcher::sdlEventFilter(const SDL_Event& event) { // NOLINT(*-convert-member-functions-to-static)
  switch (event.type) {
  /* These application events have special meaning on iOS and Android, see SDL3 README-ios.md and SDL3 README-android.md for details */
  case SDL_EVENT_TERMINATING: on_terminating(event.common); return false;
  case SDL_EVENT_LOW_MEMORY: on_low_memory(event.common); return false;
  case SDL_EVENT_WILL_ENTER_BACKGROUND: on_will_enter_background(event.common); return false;
  case SDL_EVENT_DID_ENTER_BACKGROUND: on_did_enter_background(event.common); return false;
  default: break;
  }
  return true;
}
#endif

#if IS_USING_SDL_2
// ReSharper disable once CppParameterMayBeConstPtrOrRef
int SdlEventDispatcher::sdlEventFilter(void* self, SDL_Event* event) {
  return static_cast<SdlEventDispatcher*>(self)->sdlEventFilter(*event) ? 1 : 0;
}
#elif IS_USING_SDL_3
// ReSharper disable once CppParameterMayBeConstPtrOrRef
bool SdlEventDispatcher::sdlEventFilter(void* self, SDL_Event* event) {
  return static_cast<SdlEventDispatcher*>(self)->sdlEventFilter(*event);
}
#endif
