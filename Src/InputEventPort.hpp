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

#if IS_USING_SDL_2
  static int sdlEventFilter(void* self, SDL_Event* event);
#elif IS_USING_SDL_3
  static bool sdlEventFilter(void* self, SDL_Event* event);
#endif

private:
  EventReceiver();

#if IS_USING_SDL_2 || IS_USING_SDL_3
  bool sdlEventFilter(SDL_Event& event);
#endif



#if IS_USING_SDL_1 || IS_USING_SDL_2
  /** SDL1, SDL2 SysWM Event */
  ESysStatus sysWmEvent(const SDL_SysWMEvent& event);
#endif

  /* SDL1, SDL2, SDL3 Common Events Begin */
  ESysStatus mouseMotion(const SDL_MouseMotionEvent& event); /**< Mouse Motion */
  ESysStatus mouseButtonDown(const SDL_MouseButtonEvent& event); /**< Mouse Button Down */
  ESysStatus mouseButtonUp(const SDL_MouseButtonEvent& event); /**< Mouse Button Up */
  ESysStatus joystickAxisMotion(const SDL_JoyAxisEvent& event); /**< Joystick Axis Motion */
  ESysStatus joystickBallMotion(const SDL_JoyBallEvent& event); /**< Joystick Ball Motion */
  ESysStatus joystickHatMotion(const SDL_JoyHatEvent& event); /**< Joystick Hat Motion */
  ESysStatus joystickButtonDown(const SDL_JoyButtonEvent& event); /**< Joystick Button Down */
  ESysStatus joystickButtonUp(const SDL_JoyButtonEvent& event); /**< Joystick Button Up */
  ESysStatus userEvent(const SDL_UserEvent& event); /**< "User" Custom Event */
  /* SDL1, SDL2, SDL3 Common Events End */



#if IS_USING_SDL_2 || IS_USING_SDL_3
  /* SDL2 Only and SDL3 Only Events Begin */
  ESysStatus mouseWheel(const SDL_MouseWheelEvent&); /**< Mouse Wheel Motion */
  /* SDL2 Only and SDL3 Only Events End */
#endif

};


#endif /* AB_INPUT_EVENT_PORT_HPP */
