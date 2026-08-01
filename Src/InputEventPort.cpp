#include "InputEventPort.hpp"

EventReceiver::EventReceiver() {}

EventReceiver EventReceiver::def() {
  return EventReceiver();
}

ESysStatus EventReceiver::unrecognized(const SDL_Event &event) {
  /* I don't think `default` should be reachable. */
  /* I put a debugBreak so if it ever happened,   */
  /*     I get a change to investigate it.        */
  debugBreak;
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::unrecognizedOrientationEvent(const SDL_DisplayEvent &event) {
  /* I don't think `default` should be reachable. */
  /* I put a debugBreak so if it ever happened,   */
  /*     I get a change to investigate it.        */
  debugBreak;
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::unrecognizedDisplayEvent(const SDL_DisplayEvent &event) {
  /* I don't think `default` should be reachable. */
  /* I put a debugBreak so if it ever happened,   */
  /*     I get a change to investigate it.        */
  debugBreak;
  return E_SYS_CONTINUE;
}

int EventReceiver::sdlEventFilter(void* self, SDL_Event* event) {
  return static_cast<EventReceiver*>(self)->sdlEventFilter(*event);
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::active(const SDL_ActiveEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::resize(const SDL_ResizeEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::expose(const SDL_ExposeEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

ESysStatus EventReceiver::quit(const SDL_QuitEvent& event) {
  return E_SYS_QUIT;
}

#if IS_USING_SDL_1 || IS_USING_SDL_2
ESysStatus EventReceiver::sysWM(const SDL_SysWMEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

ESysStatus EventReceiver::keyDown(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::keyUp(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::motion(const SDL_MouseMotionEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::buttonDown(const SDL_MouseButtonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::buttonUp(const SDL_MouseButtonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::axis(const SDL_JoyAxisEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::ball(const SDL_JoyBallEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::hat(const SDL_JoyHatEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::joyDown(const SDL_JoyButtonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::joyUp(const SDL_JoyButtonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::user(const SDL_UserEvent& event) {
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus EventReceiver::terminating(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::low(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::backWill(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::backDid(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::foreWill(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::foreDid(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::locale(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::disoriented(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::landscape(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::landscapeFlipped(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::portrait(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::portraitFlipped(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::on(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::off(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::reposition(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_1
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
    case SDL_ACTIVEEVENT: return active(event.active);
    case SDL_KEYDOWN: return keyDown(event.key);
    case SDL_KEYUP: return keyUp(event.key);
    case SDL_MOUSEMOTION: return motion(event.motion);
    case SDL_MOUSEBUTTONDOWN: return buttonDown(event.button);
    case SDL_MOUSEBUTTONUP: return buttonUp(event.button);
    case SDL_JOYAXISMOTION: return axis(event.jaxis);
    case SDL_JOYBALLMOTION: return ball(event.jball);
    case SDL_JOYHATMOTION: return hat(event.jhat);
    case SDL_JOYBUTTONDOWN: return joyDown(event.jbutton);
    case SDL_JOYBUTTONUP: return joyUp(event.jbutton);
    case SDL_QUIT: return quit(event.quit);
    case SDL_SYSWMEVENT: return sysWM(event.syswm);
    case SDL_VIDEORESIZE: return resize(event.resize);
    case SDL_VIDEOEXPOSE: return expose(event.expose);
    case SDL_USEREVENT: return user(event.user);
    default: return unrecognized(event);
  }
  return unrecognized(event);
}
#elif IS_USING_SDL_2
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
    /* Application events */
    case SDL_QUIT: return quit(event.quit);
    /* These application events have special meaning on iOS, see SDL2 README-ios.md for details */
    case SDL_APP_TERMINATING: return terminating(event.common);
    case SDL_APP_LOWMEMORY: return low(event.common);
    case SDL_APP_WILLENTERBACKGROUND: return backWill(event.common);
    case SDL_APP_DIDENTERBACKGROUND: return backDid(event.common);
    case SDL_APP_WILLENTERFOREGROUND: return foreWill(event.common);
    case SDL_APP_DIDENTERFOREGROUND: return foreDid(event.common);
    case SDL_LOCALECHANGED: return locale(event.common);
    /* Display events */
    case SDL_DISPLAYEVENT:
      switch (event.display.event) {
        case SDL_DISPLAYEVENT_ORIENTATION:
          switch (event.display.data1) {
            case SDL_ORIENTATION_UNKNOWN: return disoriented(event.display);
            case SDL_ORIENTATION_LANDSCAPE: return landscape(event.display);
            case SDL_ORIENTATION_LANDSCAPE_FLIPPED: return landscapeFlipped(event.display);
            case SDL_ORIENTATION_PORTRAIT: return portrait(event.display);
            case SDL_ORIENTATION_PORTRAIT_FLIPPED: return portraitFlipped(event.display);
            default: return unrecognizedOrientationEvent(event.display);
          }
        case SDL_DISPLAYEVENT_CONNECTED: return on(event.display);
        case SDL_DISPLAYEVENT_DISCONNECTED: return off(event.display);
        case SDL_DISPLAYEVENT_MOVED: reposition(event.display);
        default: return unrecognizedDisplayEvent(event.display);
      }
    default: return unrecognized(event);
  }
  return unrecognized(event);
}

int EventReceiver::sdlEventFilter(SDL_Event& event) {
  return 1;
}
#elif IS_USING_SDL_3
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
    /* Application events */
    case SDL_EVENT_QUIT: return quit(event.quit);
    /* These application events have special meaning on iOS and Android, see README-ios.md and README-android.md for details */
    default: return unrecognized(event);
  }
  return unrecognized(event);
}

int EventReceiver::sdlEventFilter(SDL_Event& event) {
  return 1;
}
#endif

