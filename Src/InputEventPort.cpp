#include "InputEventPort.hpp"

EventReceiver::EventReceiver() {}

EventReceiver EventReceiver::def() {
  return EventReceiver();
}

#if IS_USING_SDL_2
int EventReceiver::sdlEventFilter(void* self, SDL_Event* event) {
  return static_cast<EventReceiver*>(self)->sdlEventFilter(*event) ? 1 : 0;
}
#elif IS_USING_SDL_3
bool EventReceiver::sdlEventFilter(void* self, SDL_Event* event) {
  return static_cast<EventReceiver*>(self)->sdlEventFilter(*event);
}
#endif


