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

ESysStatus EventReceiver::unrecognized(const SDL_Event& event) {
  /* I don't think `default` should be reachable. */
  /* I put a debugBreak so if it ever happened,   */
  /*     I get a change to investigate it.        */
  debugBreak;
  return E_SYS_CONTINUE;
}


ESysStatus EventReceiver::quit(const SDL_QuitEvent& event) {
  return E_SYS_QUIT;
}

#if IS_USING_SDL_1 || IS_USING_SDL_2
ESysStatus EventReceiver::sys(const SDL_SysWMEvent& event) {
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

#if IS_USING_SDL_1
ESysStatus EventReceiver::exposed() {
#else
ESysStatus EventReceiver::exposed(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::resized(const int w, const int h) {
#else
ESysStatus EventReceiver::resized(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::minimized() {
#else
ESysStatus EventReceiver::minimized(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::restored() {
#else
ESysStatus EventReceiver::restored(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::enter() {
#else
ESysStatus EventReceiver::enter(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::leave() {
#else
ESysStatus EventReceiver::leave(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::writable() {
#else
ESysStatus EventReceiver::writable(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::unwritable() {
#else
ESysStatus EventReceiver::unwritable(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2
ESysStatus EventReceiver::writer(const SDL_TextEditingExtEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

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

ESysStatus EventReceiver::replace(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::shown(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::hidden(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::reposition(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::sized(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::maximized(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::close(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::take(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::hit(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::icc(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::relocate(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::writing(const SDL_TextEditingEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::text(const SDL_TextInputEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::layout(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::wheel(const SDL_MouseWheelEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_1
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
    case SDL_ACTIVEEVENT:
      switch (event.active.type) {
      case SDL_APPACTIVE: return event.active.gain ? restored() : minimized();
      case SDL_APPMOUSEFOCUS: return event.active.gain ? enter() : leave();
      case SDL_APPINPUTFOCUS: return event.active.gain ? writable() : unwritable();
      default: break;
      }
      break;
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
    case SDL_SYSWMEVENT: return sys(event.syswm);
    case SDL_VIDEORESIZE: return resized(event.resize.w, event.resize.h);
    case SDL_VIDEOEXPOSE: return exposed();
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
      default: break;
      }
      break;
    case SDL_DISPLAYEVENT_CONNECTED: return on(event.display);
    case SDL_DISPLAYEVENT_DISCONNECTED: return off(event.display);
    case SDL_DISPLAYEVENT_MOVED: return replace(event.display);
    default: break;
    }
    break;
  case SDL_WINDOWEVENT:
    switch (event.window.event) {
    case SDL_WINDOWEVENT_SHOWN: return shown(event.window);
    case SDL_WINDOWEVENT_HIDDEN: return hidden(event.window);
    case SDL_WINDOWEVENT_EXPOSED: return exposed(event.window);
    case SDL_WINDOWEVENT_MOVED: return reposition(event.window);
    case SDL_WINDOWEVENT_RESIZED: return resized(event.window);
    case SDL_WINDOWEVENT_SIZE_CHANGED: return sized(event.window);
    case SDL_WINDOWEVENT_MINIMIZED: return minimized(event.window);
    case SDL_WINDOWEVENT_MAXIMIZED: return maximized(event.window);
    case SDL_WINDOWEVENT_RESTORED: return restored(event.window);
    case SDL_WINDOWEVENT_ENTER: return enter(event.window);
    case SDL_WINDOWEVENT_LEAVE: return leave(event.window);
    case SDL_WINDOWEVENT_FOCUS_GAINED: return writable(event.window);
    case SDL_WINDOWEVENT_FOCUS_LOST: return unwritable(event.window);
    case SDL_WINDOWEVENT_CLOSE: return close(event.window);
    case SDL_WINDOWEVENT_TAKE_FOCUS: return take(event.window);
    case SDL_WINDOWEVENT_HIT_TEST: return hit(event.window);
    case SDL_WINDOWEVENT_ICCPROF_CHANGED: return icc(event.window);
    case SDL_WINDOWEVENT_DISPLAY_CHANGED: return relocate(event.window);
    default: break;
    }
    break;
  case SDL_SYSWMEVENT: return sys(event.syswm);
  /* Keyboard events */
  case SDL_KEYDOWN: return keyDown(event.key);
  case SDL_KEYUP: return keyUp(event.key);
  case SDL_TEXTEDITING: return writing(event.edit);
  case SDL_TEXTINPUT: return text(event.text);
  case SDL_KEYMAPCHANGED: return layout(event.common);
  case SDL_TEXTEDITING_EXT: {
    const ESysStatus res = writer(event.editExt);
    SDL_free(event.editExt.text);
    return res;
  }
  /* Mouse events */
  case SDL_MOUSEMOTION: return motion(event.motion);
  case SDL_MOUSEBUTTONDOWN: return buttonDown(event.button);
  case SDL_MOUSEBUTTONUP: return buttonUp(event.button);
  case SDL_MOUSEWHEEL: return wheel(event.wheel);
  default: return unrecognized(event);
  }
  return unrecognized(event);
}

bool EventReceiver::sdlEventFilter(SDL_Event& event) {
  return true;
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

bool EventReceiver::sdlEventFilter(SDL_Event& event) {
  return true;
}
#endif

