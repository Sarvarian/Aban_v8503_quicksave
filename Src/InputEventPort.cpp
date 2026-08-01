#include "InputEventPort.hpp"

EventReceiver::EventReceiver() {}

EventReceiver EventReceiver::def() {
  return EventReceiver();
}

ESysStatus EventReceiver::active(const SDL_ActiveEvent &event) {
  return E_SYS_CONTINUE;
}


#if IS_USING_SDL_1
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event &event) {
  switch (event.type) {
    case SDL_ACTIVEEVENT: return active(event.active);
    case SDL_KEYDOWN: break;
    case SDL_KEYUP: break;
    case SDL_MOUSEMOTION: break;
    case SDL_MOUSEBUTTONDOWN: break;
    case SDL_MOUSEBUTTONUP: break;
    case SDL_JOYAXISMOTION: break;
    case SDL_JOYBALLMOTION: break;
    case SDL_JOYHATMOTION: break;
    case SDL_JOYBUTTONDOWN: break;
    case SDL_JOYBUTTONUP: break;
    case SDL_QUIT: break;
    case SDL_SYSWMEVENT: break;
    case SDL_VIDEORESIZE: break;
    case SDL_VIDEOEXPOSE: break;
    case SDL_USEREVENT: break;
    default: break;
  }
  return E_SYS_CONTINUE;
}
#elif IS_USING_SDL_2
void receiveSdlInputEvent(const SDL_Event& event, EventReciever& receiver) {
  switch (event.type) {
    case SDL_ACTIVEEVENT: break;
    case SDL_KEYDOWN: break;
    case SDL_KEYUP: break;
    case SDL_MOUSEMOTION: break;
    case SDL_MOUSEBUTTONDOWN: break;
    case SDL_MOUSEBUTTONUP: break;
    case SDL_JOYAXISMOTION: break;
    case SDL_JOYBALLMOTION: break;
    case SDL_JOYHATMOTION: break;
    case SDL_JOYBUTTONDOWN: break;
    case SDL_JOYBUTTONUP: break;
    case SDL_QUIT: break;
    case SDL_SYSWMEVENT: break;
    case SDL_VIDEORESIZE: break;
    case SDL_VIDEOEXPOSE: break;
    case SDL_USEREVENT: break;
    default: break;
  }
}
#elif IS_USING_SDL_3
void receiveSdlInputEvent(const SDL_Event& event, EventReciever& receiver) {
  switch (event.type) {
    case SDL_EVENT_ACTIVEEVENT: break;
    case SDL_EVENT_KEY_DOWN: break;
    case SDL_EVENT_KEY_UP: break;
    case SDL_EVENT_MOUSE_MOTION: break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN: break;
    case SDL_EVENT_MOUSE_BUTTON_UP: break;
    case SDL_EVENT_JOYSTICK_AXIS_MOTION: break;
    case SDL_EVENT_JOYSTICK_BALL_MOTION: break;
    case SDL_EVENT_JOYSTICK_HAT_MOTION: break;
    case SDL_EVENT_JOYSTICK_BUTTON_DOWN: break;
    case SDL_EVENT_JOYSTICK_BUTTON_UP: break;
    case SDL_EVENT_QUIT: break;
    case SDL_EVENT_SYSWMEVENT: break;
    case SDL_EVENT_VIDEORESIZE: break;
    case SDL_EVENT_VIDEOEXPOSE: break;
    case SDL_EVENT_USER: break;
    default: break;
  }
}
#endif

