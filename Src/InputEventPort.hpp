#pragma once

#ifndef AB_INPUT_EVENT_PORT_HPP
#define AB_INPUT_EVENT_PORT_HPP

#include "Main.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL_events.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL_events.h>
#elif IS_USING_SDL_1
  #include <SDL/SDL_events.h>
#endif

class EventReceiver {
public:
  static EventReceiver def();
  ESysStatus receiveSdlInputEvent(const SDL_Event& event);

#if IS_USING_SDL_2 || IS_USING_SDL_3
  static int sdlEventFilter(void* self, SDL_Event* event);
#endif

private:
  EventReceiver();

#if IS_USING_SDL_2 || IS_USING_SDL_3
  int sdlEventFilter(SDL_Event& event);
#endif

  ESysStatus unrecognized(const SDL_Event&); /* Unrecognized SDL Event */

  /* SDL1, SDL2, SDL3 Common Events Begin */
  ESysStatus quit(const SDL_QuitEvent& event);
  /* SDL1, SDL2, SDL3 Common Events End */

#if IS_USING_SDL_1 || IS_USING_SDL_2
  /** SDL1, SDL2 SysWM Event */
  ESysStatus sys(const SDL_SysWMEvent& event);
#endif

  /* SDL1, SDL2, SDL3 Common Events Begin */
  ESysStatus keyDown(const SDL_KeyboardEvent& event); /**< Keyboard Key Down */
  ESysStatus keyUp(const SDL_KeyboardEvent& event); /**< Keyboard Key Up */
  ESysStatus motion(const SDL_MouseMotionEvent& event); /**< Mouse Motion */
  ESysStatus buttonDown(const SDL_MouseButtonEvent& event); /**< Mouse Button Down */
  ESysStatus buttonUp(const SDL_MouseButtonEvent& event); /**< Mouse Button Up */
  ESysStatus axis(const SDL_JoyAxisEvent& event); /**< Joystick Axis Motion */
  ESysStatus ball(const SDL_JoyBallEvent& event); /**< Joystick Ball Motion */
  ESysStatus hat(const SDL_JoyHatEvent& event); /**< Joystick Hat Motion */
  ESysStatus joyDown(const SDL_JoyButtonEvent& event); /**< Joystick Button Down */
  ESysStatus joyUp(const SDL_JoyButtonEvent& event); /**< Joystick Button Up */
  ESysStatus user(const SDL_UserEvent& event); /**< "User" Custom Event */
  /* SDL1, SDL2, SDL3 Common Events End */

#if IS_USING_SDL_1
  ESysStatus exposed(); /**< Window Exposed, Need Redraw */
  ESysStatus resized(const int w, const int h); /**< Window Resized */
  ESysStatus minimized(); /**< Window Minimized */
  ESysStatus restored(); /**< Window Restored */
  ESysStatus enter(); /**< Window Gained Mouse Focus */
  ESysStatus leave(); /**< Window Lost Mouse Focsus */
  ESysStatus writable(); /**< Window Gained Keyboard Focus */
  ESysStatus unwritable(); /**< Window Lost Keyboard Focus */
#else
  ESysStatus exposed(const SDL_WindowEvent&); /**< Window Exposed, Need Redraw */
  ESysStatus resized(const SDL_WindowEvent&); /**< Window Resized */
  ESysStatus minimized(const SDL_WindowEvent&); /**< Window Minimized */
  ESysStatus restored(const SDL_WindowEvent&); /**< Window Restored */
  ESysStatus enter(const SDL_WindowEvent&); /**< Window Gained Mouse Focus */
  ESysStatus leave(const SDL_WindowEvent&); /**< Window Lost Mouse Focsus */
  ESysStatus writable(const SDL_WindowEvent&); /**< Window Gained Keyboard Focus */
  ESysStatus unwritable(const SDL_WindowEvent&); /**< Window Lost Keyboard Focus */
#endif

#if IS_USING_SDL_2
  /** Extended Keyboard Text Composition Edition.
      `text` will be freed after calling this.
      So, make a hard copy of `text` if you need it.
   */
  ESysStatus writer(const SDL_TextEditingExtEvent&);
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  /* SDL2 Only and SDL3 Only Events Begin */
  ESysStatus terminating(const SDL_CommonEvent&); /**< App Terminating */
  ESysStatus low(const SDL_CommonEvent&); /**< App Low Memory */
  ESysStatus backWill(const SDL_CommonEvent&); /**< Will Enter Background */
  ESysStatus backDid(const SDL_CommonEvent&); /**< Did Enter Background */
  ESysStatus foreWill(const SDL_CommonEvent&); /**< Will Enter Foreground */
  ESysStatus foreDid(const SDL_CommonEvent&); /**< Did Enter Foreground */
  ESysStatus locale(const SDL_CommonEvent&); /**< User Locale Changed */
  ESysStatus disoriented(const SDL_DisplayEvent&); /**< Display Orientation Changed, Unknown */
  ESysStatus landscape(const SDL_DisplayEvent&); /**< Display Orientation Changed, Landscape */
  ESysStatus landscapeFlipped(const SDL_DisplayEvent&); /**< Display Orientation Changed, Landscape Flipped */
  ESysStatus portrait(const SDL_DisplayEvent&); /**< Display Orientation Changed, Portrait */
  ESysStatus portraitFlipped(const SDL_DisplayEvent&); /**< Display Orientation Changed, Portrait Flipped */
  ESysStatus on(const SDL_DisplayEvent&); /**< System Display Added */
  ESysStatus off(const SDL_DisplayEvent&); /**< System Display Removed */
  ESysStatus replace(const SDL_DisplayEvent&); /**< System Display Position Changed */
  ESysStatus shown(const SDL_WindowEvent&); /**< Window Shown */
  ESysStatus hidden(const SDL_WindowEvent&); /**< Window Hidden */
  ESysStatus reposition(const SDL_WindowEvent&); /**< Window Moved */
  ESysStatus sized(const SDL_WindowEvent&); /**< Window Size Changed */
  ESysStatus maximized(const SDL_WindowEvent&); /**< Window Maximized */
  ESysStatus close(const SDL_WindowEvent&); /**< Window Requested For Close */
  ESysStatus take(const SDL_WindowEvent&); /**< Window Offered Focus */
  ESysStatus hit(const SDL_WindowEvent&); /**< Window Had Hit Test, That Wasn't SDL_HITTEST_NORMAL */
  ESysStatus icc(const SDL_WindowEvent&); /**< Window's Display ICC Profile Changed */
  ESysStatus relocate(const SDL_WindowEvent&); /**< Window Moved Display */
  ESysStatus writing(const SDL_TextEditingEvent&); /**< Keyboard Text Composition Editing */
  ESysStatus text(const SDL_TextInputEvent&); /**< Keyboard Text Input */
  ESysStatus layout(const SDL_CommonEvent&); /**< System Keyboard Layout Changed */
  /* SDL2 Only and SDL3 Only Events End */
#endif

};


#endif /* AB_INPUT_EVENT_PORT_HPP */
