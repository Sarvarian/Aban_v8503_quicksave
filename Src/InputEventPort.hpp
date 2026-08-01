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

  ESysStatus unrecognized(const SDL_Event& event); /* Unrecognized SDL Event */
  ESysStatus unrecognizedOrientationEvent(const SDL_DisplayEvent& event); /* Unrecognized Display Orientation Event */
  ESysStatus unrecognizedDisplayEvent(const SDL_DisplayEvent& event); /* Unrecognized Display Event */

#if IS_USING_SDL_1
  /** SDL1 Active Event */
  ESysStatus active(const SDL_ActiveEvent& event);
  /** SDL1 Resize Event */
  ESysStatus resize(const SDL_ResizeEvent& event);
  /** SDL1 Expose Event */
  ESysStatus expose(const SDL_ExposeEvent& event);
#endif

  /* SDL1, SDL2, SDL3 Common Events Begin */
  ESysStatus quit(const SDL_QuitEvent& event);
  /* SDL1, SDL2, SDL3 Common Events End */

#if IS_USING_SDL_1 || IS_USING_SDL_2
  /** SDL1, SDL2 SysWM Event */
  ESysStatus sysWM(const SDL_SysWMEvent& event);
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

#if IS_USING_SDL_2 || IS_USING_SDL_3
  /* SDL2 Only and SDL3 Only Events Begin */
  ESysStatus terminating(const SDL_CommonEvent& event); /**< App Terminating */
  ESysStatus low(const SDL_CommonEvent& event); /**< App Low Memory */
  ESysStatus backWill(const SDL_CommonEvent& event); /**< Will Enter Background */
  ESysStatus backDid(const SDL_CommonEvent& event); /**< Did Enter Background */
  ESysStatus foreWill(const SDL_CommonEvent& event); /**< Will Enter Foreground */
  ESysStatus foreDid(const SDL_CommonEvent& event); /**< Did Enter Foreground */
  ESysStatus locale(const SDL_CommonEvent& event); /**< User Locale Changed */
  ESysStatus disoriented(const SDL_DisplayEvent& event); /**< Display Orientation Changed, Unknown */
  ESysStatus landscape(const SDL_DisplayEvent& event); /**< Display Orientation Changed, Landscape */
  ESysStatus landscapeFlipped(const SDL_DisplayEvent& event); /**< Display Orientation Changed, Landscape Flipped */
  ESysStatus portrait(const SDL_DisplayEvent& event); /**< Display Orientation Changed, Portrait */
  ESysStatus portraitFlipped(const SDL_DisplayEvent& event); /**< Display Orientation Changed, Portrait Flipped */
  ESysStatus on(const SDL_DisplayEvent& event); /**< System Display Added */
  ESysStatus off(const SDL_DisplayEvent& event); /**< System Display Removed */
  ESysStatus relocation(const SDL_DisplayEvent& event); /**< System Display Position Changed */
  /* SDL2 Only and SDL3 Only Events End */
#endif

};


#endif /* AB_INPUT_EVENT_PORT_HPP */
