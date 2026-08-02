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

ESysStatus EventReceiver::unrecognizedEvent(const SDL_Event& event) {
  /* I don't think `default` should be reachable. */
  /* I put a debugBreak so if it ever happened,   */
  /*     I get a change to investigate it.        */
  debugBreak;
  return E_SYS_CONTINUE;
}


ESysStatus EventReceiver::quitEvent(const SDL_QuitEvent& event) {
  return E_SYS_QUIT;
}

#if IS_USING_SDL_1 || IS_USING_SDL_2
ESysStatus EventReceiver::sysWmEvent(const SDL_SysWMEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

ESysStatus EventReceiver::keyboardKeyDown(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::keyboardKeyUp(const SDL_KeyboardEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::mouseMotion(const SDL_MouseMotionEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::mouseButtonDown(const SDL_MouseButtonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::mouseButtonUp(const SDL_MouseButtonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::joystickAxisMotion(const SDL_JoyAxisEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::joystickBallMotion(const SDL_JoyBallEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::joystickHatMotion(const SDL_JoyHatEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::joystickButtonDown(const SDL_JoyButtonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::joystickButtonUp(const SDL_JoyButtonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::userEvent(const SDL_UserEvent& event) {
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::windowExposed() {
#else
ESysStatus EventReceiver::windowExposed(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::windowResized(const int w, const int h) {
#else
ESysStatus EventReceiver::windowResized(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::windowMinimized() {
#else
ESysStatus EventReceiver::windowMinimized(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::windowRestored() {
#else
ESysStatus EventReceiver::windowRestored(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::windowMouseEnter() {
#else
ESysStatus EventReceiver::windowMouseEnter(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::windowMouseLeave() {
#else
ESysStatus EventReceiver::windowMouseLeave(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::windowFocusGained() {
#else
ESysStatus EventReceiver::windowFocusGained(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_1
ESysStatus EventReceiver::windowFocusLost() {
#else
ESysStatus EventReceiver::windowFocusLost(const SDL_WindowEvent& event) {
#endif
  return E_SYS_CONTINUE;
}

#if IS_USING_SDL_2
ESysStatus EventReceiver::textEditingExt(const SDL_TextEditingExtEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
ESysStatus EventReceiver::terminating(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::lowMemory(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::willEnterBackground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::didEnterBackground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::willEnterForeground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::didEnterForeground(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::localeChanged(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::orientationUnknown(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::orientationLandscape(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::orientationLandscapeFlipped(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::orientationPortrait(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::orientationPortraitFlipped(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::displayAdded(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::displayRemoved(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::displayMoved(const SDL_DisplayEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowShown(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowHidden(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowMoved(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowSizeChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowMaximized(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowCloseRequest(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowTakeFocus(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowHitTest(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowIccChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::windowDisplayChanged(const SDL_WindowEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::textEditing(const SDL_TextEditingEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::textInput(const SDL_TextInputEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::keymapChanged(const SDL_CommonEvent& event) {
  return E_SYS_CONTINUE;
}

ESysStatus EventReceiver::mouseWheel(const SDL_MouseWheelEvent& event) {
  return E_SYS_CONTINUE;
}
#endif

#if IS_USING_SDL_1
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
    case SDL_ACTIVEEVENT:
      switch (event.active.type) {
      case SDL_APPACTIVE: return event.active.gain ? windowRestored() : windowMinimized();
      case SDL_APPMOUSEFOCUS: return event.active.gain ? windowMouseEnter() : windowMouseLeave();
      case SDL_APPINPUTFOCUS: return event.active.gain ? windowFocusGained() : windowFocusLost();
      default: break;
      }
      break;
    case SDL_KEYDOWN: return keyboardKeyDown(event.key);
    case SDL_KEYUP: return keyboardKeyUp(event.key);
    case SDL_MOUSEMOTION: return mouseMotion(event.motion);
    case SDL_MOUSEBUTTONDOWN: return mouseButtonDown(event.button);
    case SDL_MOUSEBUTTONUP: return mouseButtonUp(event.button);
    case SDL_JOYAXISMOTION: return joystickAxisMotion(event.jaxis);
    case SDL_JOYBALLMOTION: return joystickBallMotion(event.jball);
    case SDL_JOYHATMOTION: return joystickHatMotion(event.jhat);
    case SDL_JOYBUTTONDOWN: return joystickButtonDown(event.jbutton);
    case SDL_JOYBUTTONUP: return joystickButtonUp(event.jbutton);
    case SDL_QUIT: return quitEvent(event.quit);
    case SDL_SYSWMEVENT: return sysWmEvent(event.syswm);
    case SDL_VIDEORESIZE: return windowResized(event.resize.w, event.resize.h);
    case SDL_VIDEOEXPOSE: return windowExposed();
    case SDL_USEREVENT: return userEvent(event.user);
    default: return unrecognizedEvent(event);
  }
  return unrecognizedEvent(event);
}
#elif IS_USING_SDL_2
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
  /* Application events */
  case SDL_QUIT: return quitEvent(event.quit);
  /* These application events have special meaning on iOS, see SDL2 README-ios.md for details */
  case SDL_APP_TERMINATING: return terminating(event.common);
  case SDL_APP_LOWMEMORY: return lowMemory(event.common);
  case SDL_APP_WILLENTERBACKGROUND: return willEnterBackground(event.common);
  case SDL_APP_DIDENTERBACKGROUND: return didEnterBackground(event.common);
  case SDL_APP_WILLENTERFOREGROUND: return willEnterForeground(event.common);
  case SDL_APP_DIDENTERFOREGROUND: return didEnterForeground(event.common);
  case SDL_LOCALECHANGED: return localeChanged(event.common);
  /* Display events */
  case SDL_DISPLAYEVENT:
    switch (event.display.event) {
    case SDL_DISPLAYEVENT_ORIENTATION:
      switch (event.display.data1) {
      case SDL_ORIENTATION_UNKNOWN: return orientationUnknown(event.display);
      case SDL_ORIENTATION_LANDSCAPE: return orientationLandscape(event.display);
      case SDL_ORIENTATION_LANDSCAPE_FLIPPED: return orientationLandscapeFlipped(event.display);
      case SDL_ORIENTATION_PORTRAIT: return orientationPortrait(event.display);
      case SDL_ORIENTATION_PORTRAIT_FLIPPED: return orientationPortraitFlipped(event.display);
      default: break;
      }
      break;
    case SDL_DISPLAYEVENT_CONNECTED: return displayAdded(event.display);
    case SDL_DISPLAYEVENT_DISCONNECTED: return displayRemoved(event.display);
    case SDL_DISPLAYEVENT_MOVED: return displayMoved(event.display);
    default: break;
    }
    break;
  case SDL_WINDOWEVENT:
    switch (event.window.event) {
    case SDL_WINDOWEVENT_SHOWN: return windowShown(event.window);
    case SDL_WINDOWEVENT_HIDDEN: return windowHidden(event.window);
    case SDL_WINDOWEVENT_EXPOSED: return windowExposed(event.window);
    case SDL_WINDOWEVENT_MOVED: return windowMoved(event.window);
    case SDL_WINDOWEVENT_RESIZED: return windowResized(event.window);
    case SDL_WINDOWEVENT_SIZE_CHANGED: return windowSizeChanged(event.window);
    case SDL_WINDOWEVENT_MINIMIZED: return windowMinimized(event.window);
    case SDL_WINDOWEVENT_MAXIMIZED: return windowMaximized(event.window);
    case SDL_WINDOWEVENT_RESTORED: return windowRestored(event.window);
    case SDL_WINDOWEVENT_ENTER: return windowMouseEnter(event.window);
    case SDL_WINDOWEVENT_LEAVE: return windowMouseLeave(event.window);
    case SDL_WINDOWEVENT_FOCUS_GAINED: return windowFocusGained(event.window);
    case SDL_WINDOWEVENT_FOCUS_LOST: return windowFocusLost(event.window);
    case SDL_WINDOWEVENT_CLOSE: return windowCloseRequest(event.window);
    case SDL_WINDOWEVENT_TAKE_FOCUS: return windowTakeFocus(event.window);
    case SDL_WINDOWEVENT_HIT_TEST: return windowHitTest(event.window);
    case SDL_WINDOWEVENT_ICCPROF_CHANGED: return windowIccChanged(event.window);
    case SDL_WINDOWEVENT_DISPLAY_CHANGED: return windowDisplayChanged(event.window);
    default: break;
    }
    break;
  case SDL_SYSWMEVENT: return sysWmEvent(event.syswm);
  /* Keyboard events */
  case SDL_KEYDOWN: return keyboardKeyDown(event.key);
  case SDL_KEYUP: return keyboardKeyUp(event.key);
  case SDL_TEXTEDITING: return textEditing(event.edit);
  case SDL_TEXTINPUT: return textInput(event.text);
  case SDL_KEYMAPCHANGED: return keymapChanged(event.common);
  case SDL_TEXTEDITING_EXT: {
    const ESysStatus res = textEditingExt(event.editExt);
    SDL_free(event.editExt.text);
    return res;
  }
  /* Mouse events */
  case SDL_MOUSEMOTION: return mouseMotion(event.motion);
  case SDL_MOUSEBUTTONDOWN: return mouseButtonDown(event.button);
  case SDL_MOUSEBUTTONUP: return mouseButtonUp(event.button);
  case SDL_MOUSEWHEEL: return mouseWheel(event.wheel);
  /* Joystick events */
  case SDL_JOYAXISMOTION:
  case SDL_JOYBALLMOTION:
  case SDL_JOYHATMOTION:
  case SDL_JOYBUTTONDOWN:
  case SDL_JOYBUTTONUP:
  case SDL_JOYDEVICEADDED:
  case SDL_JOYDEVICEREMOVED:
  case SDL_JOYBATTERYUPDATED:
  /* Game controller events */
  case SDL_CONTROLLERAXISMOTION:
  case SDL_CONTROLLERBUTTONDOWN:
  case SDL_CONTROLLERBUTTONUP:
  case SDL_CONTROLLERDEVICEADDED:
  case SDL_CONTROLLERDEVICEREMOVED:
  case SDL_CONTROLLERDEVICEREMAPPED:
  case SDL_CONTROLLERTOUCHPADDOWN:
  case SDL_CONTROLLERTOUCHPADMOTION:
  case SDL_CONTROLLERTOUCHPADUP:
  case SDL_CONTROLLERSENSORUPDATE:
  case SDL_CONTROLLERSTEAMHANDLEUPDATED:
  default: return unrecognizedEvent(event);
  }
  return unrecognizedEvent(event);
}

bool EventReceiver::sdlEventFilter(SDL_Event& event) {
  return true;
}
#elif IS_USING_SDL_3
ESysStatus EventReceiver::receiveSdlInputEvent(const SDL_Event& event) {
  switch (event.type) {
    /* Application events */
    case SDL_EVENT_QUIT: return quitEvent(event.quit);
    /* These application events have special meaning on iOS and Android, see README-ios.md and README-android.md for details */
    default: return unrecognizedEvent(event);
  }
  return unrecognizedEvent(event);
}

bool EventReceiver::sdlEventFilter(SDL_Event& event) {
  return true;
}
#endif

