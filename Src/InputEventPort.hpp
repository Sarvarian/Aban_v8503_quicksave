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

private:
  EventReceiver();

  ESysStatus unrecognized(const SDL_Event& event); /* Unrecognized SDL Event */

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

};


#endif /* AB_INPUT_EVENT_PORT_HPP */
