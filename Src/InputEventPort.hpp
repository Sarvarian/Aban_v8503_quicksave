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




  /* SDL1, SDL2, SDL3 Common Events Begin */
  ESysStatus userEvent(const SDL_UserEvent& event); /**< "User" Custom Event */
  /* SDL1, SDL2, SDL3 Common Events End */




};


#endif /* AB_INPUT_EVENT_PORT_HPP */
