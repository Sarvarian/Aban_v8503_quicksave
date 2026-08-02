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

  ESysStatus unrecognizedEvent(const SDL_Event&); /* Unrecognized SDL Event */

  /* SDL1, SDL2, SDL3 Common Events Begin */
  ESysStatus quitEvent(const SDL_QuitEvent& event);
  /* SDL1, SDL2, SDL3 Common Events End */

#if IS_USING_SDL_1 || IS_USING_SDL_2
  /** SDL1, SDL2 SysWM Event */
  ESysStatus sysWmEvent(const SDL_SysWMEvent& event);
#endif

  /* SDL1, SDL2, SDL3 Common Events Begin */
  ESysStatus keyboardKeyDown(const SDL_KeyboardEvent& event); /**< Keyboard Key Down */
  ESysStatus keyboardKeyUp(const SDL_KeyboardEvent& event); /**< Keyboard Key Up */
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

#if IS_USING_SDL_1
  ESysStatus windowExposed(); /**< Window Exposed, Need Redraw */
  ESysStatus windowResized(const int w, const int h); /**< Window Resized */
  ESysStatus windowMinimized(); /**< Window Minimized */
  ESysStatus windowRestored(); /**< Window Restored */
  ESysStatus windowMouseEnter(); /**< Window Gained Mouse Focus */
  ESysStatus windowMouseLeave(); /**< Window Lost Mouse Focus */
  ESysStatus windowFocusGained(); /**< Window Gained Keyboard Focus */
  ESysStatus windowFocusLost(); /**< Window Lost Keyboard Focus */
#else
  ESysStatus windowExposed(const SDL_WindowEvent&); /**< Window Exposed, Need Redraw */
  ESysStatus windowResized(const SDL_WindowEvent&); /**< Window Resized */
  ESysStatus windowMinimized(const SDL_WindowEvent&); /**< Window Minimized */
  ESysStatus windowRestored(const SDL_WindowEvent&); /**< Window Restored */
  ESysStatus windowMouseEnter(const SDL_WindowEvent&); /**< Window Gained Mouse Focus */
  ESysStatus windowMouseLeave(const SDL_WindowEvent&); /**< Window Lost Mouse Focus */
  ESysStatus windowFocusGained(const SDL_WindowEvent&); /**< Window Gained Keyboard Focus */
  ESysStatus windowFocusLost(const SDL_WindowEvent&); /**< Window Lost Keyboard Focus */
#endif

#if IS_USING_SDL_2
  /** Extended Keyboard Text Composition Edition.
      `text` will be freed after calling this.
      So, make a hard copy of `text` if you need it.
   */
  ESysStatus textEditingExt(const SDL_TextEditingExtEvent&);
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  /* SDL2 Only and SDL3 Only Events Begin */
  ESysStatus terminating(const SDL_CommonEvent&); /**< App Terminating */
  ESysStatus lowMemory(const SDL_CommonEvent&); /**< App Low Memory */
  ESysStatus willEnterBackground(const SDL_CommonEvent&); /**< Will Enter Background */
  ESysStatus didEnterBackground(const SDL_CommonEvent&); /**< Did Enter Background */
  ESysStatus willEnterForeground(const SDL_CommonEvent&); /**< Will Enter Foreground */
  ESysStatus didEnterForeground(const SDL_CommonEvent&); /**< Did Enter Foreground */
  ESysStatus localeChanged(const SDL_CommonEvent&); /**< User Locale Changed */
  ESysStatus orientationUnknown(const SDL_DisplayEvent&); /**< Display Orientation Changed, Unknown */
  ESysStatus orientationLandscape(const SDL_DisplayEvent&); /**< Display Orientation Changed, Landscape */
  ESysStatus orientationLandscapeFlipped(const SDL_DisplayEvent&); /**< Display Orientation Changed, Landscape Flipped */
  ESysStatus orientationPortrait(const SDL_DisplayEvent&); /**< Display Orientation Changed, Portrait */
  ESysStatus orientationPortraitFlipped(const SDL_DisplayEvent&); /**< Display Orientation Changed, Portrait Flipped */
  ESysStatus displayAdded(const SDL_DisplayEvent&); /**< System Display Added */
  ESysStatus displayRemoved(const SDL_DisplayEvent&); /**< System Display Removed */
  ESysStatus displayMoved(const SDL_DisplayEvent&); /**< System Display Position Changed */
  ESysStatus windowShown(const SDL_WindowEvent&); /**< Window Shown */
  ESysStatus windowHidden(const SDL_WindowEvent&); /**< Window Hidden */
  ESysStatus windowMoved(const SDL_WindowEvent&); /**< Window Moved */
  ESysStatus windowSizeChanged(const SDL_WindowEvent&); /**< Window Size Changed */
  ESysStatus windowMaximized(const SDL_WindowEvent&); /**< Window Maximized */
  ESysStatus windowCloseRequest(const SDL_WindowEvent&); /**< Window Requested For Close */
  ESysStatus windowTakeFocus(const SDL_WindowEvent&); /**< Window Offered Focus */
  ESysStatus windowHitTest(const SDL_WindowEvent&); /**< Window Had Hit Test, That Wasn't SDL_HITTEST_NORMAL */
  ESysStatus windowIccChanged(const SDL_WindowEvent&); /**< Window's Display ICC Profile Changed */
  ESysStatus windowDisplayChanged(const SDL_WindowEvent&); /**< Window Moved Display */
  ESysStatus textEditing(const SDL_TextEditingEvent&); /**< Keyboard Text Composition Editing */
  ESysStatus textInput(const SDL_TextInputEvent&); /**< Keyboard Text Input */
  ESysStatus keymapChanged(const SDL_CommonEvent&); /**< System Keyboard Layout Changed */
  ESysStatus mouseWheel(const SDL_MouseWheelEvent&); /**< Mouse Wheel Motion */
  /* SDL2 Only and SDL3 Only Events End */
#endif

};


#endif /* AB_INPUT_EVENT_PORT_HPP */
