#include "InputEventPort.hpp"

#include "Main.hpp"

#if IS_USING_SDL_1
void ReceiveSdlInputEvent(const union SDL_Event& event, class EventReciever& receiver) {
}
#elif IS_USING_SDL_2
void ReceiveSdlInputEvent(const union SDL_Event& event, class EventReciever& receiver) {
}
#elif IS_USING_SDL_3
#include <SDL3/SDL_events.h>
void ReceiveSdlInputEvent(const union SDL_Event& event, class EventReciever& receiver) {
  switch (event.type) {

  }
}
#endif




EventReceiver::EventReceiver() {
}

EventReceiver EventReceiver::def() {
  return EventReceiver();
}

