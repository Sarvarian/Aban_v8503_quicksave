#pragma once

#ifndef AB_INPUT_EVENT_PORT_HPP
#define AB_INPUT_EVENT_PORT_HPP

#include "Main.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL_events.h>
  struct SDL_ActiveEvent;
#elif IS_USING_SDL_2
  #include <SDL2/SDL_events.h>
  struct SDL_ActiveEvent;
#elif IS_USING_SDL_1
  #include <SDL/SDL_events.h>
#endif

class EventReceiver {
public:
  static EventReceiver def();
  ESysStatus receiveSdlInputEvent(const SDL_Event& event);

private:
  EventReceiver();

  /** SDL1 Active Event */
  ESysStatus active(const SDL_ActiveEvent& event);

};


#endif /* AB_INPUT_EVENT_PORT_HPP */
