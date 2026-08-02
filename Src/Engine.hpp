#pragma once

#ifndef AB_ENGINE_HPP
#define AB_ENGINE_HPP

#include "Main.hpp"
#include "Memory.hpp"
#include "Sdl.hpp"

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
staticAssert(sizeof(Step) == sizeof(Buffer0), Step_FIT_INTO_ONE_BUFFER0)

class Engine : public virtual IEngine {
public:
  ESysStatus preSdlInit(int, char**);
  ESysStatus initSdl(int, char**);
  ESysStatus initEngine(int, char**);
  ESysStatus eventSdl(const SDL_Event*);
  ESysStatus stepEngine();
  void       shutEngine();
  void       shutSdl();

protected:
  SdlWindow window_;
  struct DebugData* db_;
  struct Bootstrapper* boot_;
  Step* current_;
  Step* next_;

  Engine();

public:
  static Engine def();

/*
  ███████╗██╗   ██╗███████╗███╗   ██╗████████╗███████╗
  ██╔════╝██║   ██║██╔════╝████╗  ██║╚══██╔══╝██╔════╝
  █████╗  ██║   ██║█████╗  ██╔██╗ ██║   ██║   ███████╗
  ██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ╚════██║
  ███████╗ ╚████╔╝ ███████╗██║ ╚████║   ██║   ███████║
  ╚══════╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
*/

  ESysStatus on_unrecognized_event(const SDL_Event&); /* Unrecognized SDL Event */

/*
   █████╗ ██████╗ ██████╗
  ██╔══██╗██╔══██╗██╔══██╗
  ███████║██████╔╝██████╔╝
  ██╔══██║██╔═══╝ ██╔═══╝
  ██║  ██║██║     ██║
  ╚═╝  ╚═╝╚═╝     ╚═╝
*/

  ESysStatus on_quit(const SDL_QuitEvent& event);

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_terminating(const SDL_CommonEvent&); /**< App Terminating */
  ESysStatus on_low_memory(const SDL_CommonEvent&); /**< App Low Memory */
  ESysStatus on_will_enter_background(const SDL_CommonEvent&); /**< Will Enter Background */
  ESysStatus on_did_enter_background(const SDL_CommonEvent&); /**< Did Enter Background */
  ESysStatus on_will_enter_foreground(const SDL_CommonEvent&); /**< Will Enter Foreground */
  ESysStatus on_did_enter_foreground(const SDL_CommonEvent&); /**< Did Enter Foreground */
  ESysStatus on_locale_changed(const SDL_CommonEvent&); /**< User Locale Changed */
  ESysStatus on_system_theme_changed(const SDL_CommonEvent&); /**< System Theme Changed */
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
  ESysStatus on_orientation_unknown(const SDL_DisplayEvent&); /**< Display Orientation Changed, Unknown */
  ESysStatus on_orientation_landscape(const SDL_DisplayEvent&); /**< Display Orientation Changed, Landscape */
  ESysStatus on_orientation_landscape_flipped(const SDL_DisplayEvent&); /**< Display Orientation Changed, Landscape Flipped */
  ESysStatus on_orientation_portrait(const SDL_DisplayEvent&); /**< Display Orientation Changed, Portrait */
  ESysStatus on_orientation_portrait_flipped(const SDL_DisplayEvent&); /**< Display Orientation Changed, Portrait Flipped */
  ESysStatus on_display_added(const SDL_DisplayEvent&); /**< System Display Added */
  ESysStatus on_display_removed(const SDL_DisplayEvent&); /**< System Display Removed */
  ESysStatus on_display_moved(const SDL_DisplayEvent&); /**< System Display Position Changed */
  ESysStatus on_display_desktop_mode_changed(const SDL_DisplayEvent&);
  ESysStatus on_display_current_mode_changed(const SDL_DisplayEvent&);
  ESysStatus on_display_content_scale_changed(const SDL_DisplayEvent&);
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
  ESysStatus on_window_exposed(const SDL_WindowEvent&); /**< Window Exposed, Need Redraw */
  ESysStatus on_window_resized(const SDL_WindowEvent&); /**< Window Resized */
  ESysStatus on_window_minimized(const SDL_WindowEvent&); /**< Window Minimized */
  ESysStatus on_window_restored(const SDL_WindowEvent&); /**< Window Restored */
  ESysStatus on_window_mouse_enter(const SDL_WindowEvent&); /**< Window Gained Mouse Focus */
  ESysStatus on_window_mouse_leave(const SDL_WindowEvent&); /**< Window Lost Mouse Focus */
  ESysStatus on_window_focus_gained(const SDL_WindowEvent&); /**< Window Gained Keyboard Focus */
  ESysStatus on_window_focus_lost(const SDL_WindowEvent&); /**< Window Lost Keyboard Focus */
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_window_shown(const SDL_WindowEvent&); /**< Window Shown */
  ESysStatus on_window_hidden(const SDL_WindowEvent&); /**< Window Hidden */
  ESysStatus on_window_moved(const SDL_WindowEvent&); /**< Window Moved */
  ESysStatus on_window_pixel_size_changed(const SDL_WindowEvent&);
  ESysStatus on_window_metal_view_resized(const SDL_WindowEvent&);
  ESysStatus on_window_size_changed(const SDL_WindowEvent&); /**< Window Size Changed */
  ESysStatus on_window_maximized(const SDL_WindowEvent&); /**< Window Maximized */
  ESysStatus on_window_close_request(const SDL_WindowEvent&); /**< Window Requested For Close */
  ESysStatus on_window_take_focus(const SDL_WindowEvent&); /**< Window Offered Focus */
  ESysStatus on_window_hit_test(const SDL_WindowEvent&); /**< Window Had Hit Test, That Wasn't SDL_HITTEST_NORMAL */
  ESysStatus on_window_icc_changed(const SDL_WindowEvent&); /**< Window's Display ICC Profile Changed */
  ESysStatus on_window_display_changed(const SDL_WindowEvent&); /**< Window Moved Display */
  ESysStatus on_window_display_scale_changed(const SDL_WindowEvent&);
  ESysStatus on_window_safe_area_changed(const SDL_WindowEvent&);
  ESysStatus on_window_occluded(const SDL_WindowEvent&);
  ESysStatus on_window_enter_fullscreen(const SDL_WindowEvent&);
  ESysStatus on_window_leave_fullscreen(const SDL_WindowEvent&);
  ESysStatus on_window_destroyed(const SDL_WindowEvent&);
  ESysStatus on_window_hdr_state_changed(const SDL_WindowEvent&);
#endif

#if IS_USING_SDL_1 || IS_USING_SDL_2
  /** SDL1, SDL2 SysWM Event */
  ESysStatus on_sys_wm(const SDL_SysWMEvent& event);
#endif

/*
  ██╗  ██╗███████╗██╗   ██╗██████╗  ██████╗  █████╗ ██████╗ ██████╗
  ██║ ██╔╝██╔════╝╚██╗ ██╔╝██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔══██╗
  █████╔╝ █████╗   ╚████╔╝ ██████╔╝██║   ██║███████║██████╔╝██║  ██║
  ██╔═██╗ ██╔══╝    ╚██╔╝  ██╔══██╗██║   ██║██╔══██║██╔══██╗██║  ██║
  ██║  ██╗███████╗   ██║   ██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝
  ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/

  ESysStatus on_keyboard_key_down(const SDL_KeyboardEvent& event); /**< Keyboard Key Down */
  ESysStatus on_keyboard_key_up(const SDL_KeyboardEvent& event); /**< Keyboard Key Up */

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_text_editing(const SDL_TextEditingEvent&); /**< Keyboard Text Composition Editing */
  ESysStatus on_text_input(const SDL_TextInputEvent&); /**< Keyboard Text Input */
  ESysStatus on_keymap_changed(const SDL_CommonEvent&); /**< System Keyboard Layout Changed */
#endif

#if IS_USING_SDL_2
  /** Keyboard Text Composition Editing, Extended.
      `text` will be freed after calling this.
      So, make a hard copy of `text` if you need it.
   */
  ESysStatus on_text_editing_ext(const SDL_TextEditingExtEvent&);
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus on_keyboard_added(const SDL_TextEditingExtEvent&);
  ESysStatus on_keyboard_removed(const SDL_TextEditingExtEvent&);
  ESysStatus on_text_editing_candidates(const SDL_TextEditingExtEvent&);
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

};


#endif /* AB_ENGINE_HPP */
