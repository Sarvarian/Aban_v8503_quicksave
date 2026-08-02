#pragma once

#ifndef AB_ENGINE_HPP
#define AB_ENGINE_HPP

#include "Main.hpp"
#include "Memory.hpp"
#include "Sdl.hpp"

struct Step {
public:
  u8 just_continue : 1;
  u8 calculate_delta_time : 1;
  u8 window_check : 1;
  u8 window_undef : 1;
  u8 window_def : 1;
  u8 _pad03_ : 1;
  u8 _pad02_ : 1;
  u8 _pad01_ : 1;
  u8 _pad00_[mmBufferSize(0) - 1];
};
staticAssert(sizeof(Step) == sizeof(Buffer0), Step_FIT_INTO_ONE_BUFFER0)

class Engine : public virtual IEngine {
public:
  ESysStatus preSdlInit(int, char**);
  ESysStatus initSdl(int, char**);
  ESysStatus initEngine(int, char**);
  ESysStatus eventSdl(const SDL_Event*);
  ESysStatus stepEngine();
  void       shutEngine();
  void       shutSdl();

protected:
  SdlWindow window_;
  struct DebugData* db_;
  struct Bootstrapper* boot_;
  Step* current_;
  Step* next_;

  Engine();

public:
  static Engine def();

/*
  ███████╗██╗   ██╗███████╗███╗   ██╗████████╗███████╗
  ██╔════╝██║   ██║██╔════╝████╗  ██║╚══██╔══╝██╔════╝
  █████╗  ██║   ██║█████╗  ██╔██╗ ██║   ██║   ███████╗
  ██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ╚════██║
  ███████╗ ╚████╔╝ ███████╗██║ ╚████║   ██║   ███████║
  ╚══════╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝
*/

  ESysStatus unrecognizedEvent(const SDL_Event&); /* Unrecognized SDL Event */

/*
   █████╗ ██████╗ ██████╗
  ██╔══██╗██╔══██╗██╔══██╗
  ███████║██████╔╝██████╔╝
  ██╔══██║██╔═══╝ ██╔═══╝
  ██║  ██║██║     ██║
  ╚═╝  ╚═╝╚═╝     ╚═╝
*/

  ESysStatus quitEvent(const SDL_QuitEvent& event);

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus terminating(const SDL_CommonEvent&); /**< App Terminating */
  ESysStatus lowMemory(const SDL_CommonEvent&); /**< App Low Memory */
  ESysStatus willEnterBackground(const SDL_CommonEvent&); /**< Will Enter Background */
  ESysStatus didEnterBackground(const SDL_CommonEvent&); /**< Did Enter Background */
  ESysStatus willEnterForeground(const SDL_CommonEvent&); /**< Will Enter Foreground */
  ESysStatus didEnterForeground(const SDL_CommonEvent&); /**< Did Enter Foreground */
  ESysStatus localeChanged(const SDL_CommonEvent&); /**< User Locale Changed */
  ESysStatus systemThemeChanged(const SDL_CommonEvent&); /**< System Theme Changed */
#endif

/*
  ██████╗ ██╗███████╗██████╗ ██╗      █████╗ ██╗   ██╗
  ██╔══██╗██║██╔════╝██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝
  ██║  ██║██║███████╗██████╔╝██║     ███████║ ╚████╔╝
  ██║  ██║██║╚════██║██╔═══╝ ██║     ██╔══██║  ╚██╔╝
  ██████╔╝██║███████║██║     ███████╗██║  ██║   ██║
  ╚═════╝ ╚═╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝
*/

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus orientationUnknown(const SDL_DisplayEvent&); /**< Display Orientation Changed, Unknown */
  ESysStatus orientationLandscape(const SDL_DisplayEvent&); /**< Display Orientation Changed, Landscape */
  ESysStatus orientationLandscapeFlipped(const SDL_DisplayEvent&); /**< Display Orientation Changed, Landscape Flipped */
  ESysStatus orientationPortrait(const SDL_DisplayEvent&); /**< Display Orientation Changed, Portrait */
  ESysStatus orientationPortraitFlipped(const SDL_DisplayEvent&); /**< Display Orientation Changed, Portrait Flipped */
  ESysStatus displayAdded(const SDL_DisplayEvent&); /**< System Display Added */
  ESysStatus displayRemoved(const SDL_DisplayEvent&); /**< System Display Removed */
  ESysStatus displayMoved(const SDL_DisplayEvent&); /**< System Display Position Changed */
  ESysStatus displayDesktopModeChanged(const SDL_DisplayEvent&);
  ESysStatus displayCurrentModeChanged(const SDL_DisplayEvent&);
  ESysStatus displayContentScaleChanged(const SDL_DisplayEvent&);
#endif

/*
  ██╗    ██╗██╗███╗   ██╗██████╗  ██████╗ ██╗    ██╗
  ██║    ██║██║████╗  ██║██╔══██╗██╔═══██╗██║    ██║
  ██║ █╗ ██║██║██╔██╗ ██║██║  ██║██║   ██║██║ █╗ ██║
  ██║███╗██║██║██║╚██╗██║██║  ██║██║   ██║██║███╗██║
  ╚███╔███╔╝██║██║ ╚████║██████╔╝╚██████╔╝╚███╔███╔╝
   ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝  ╚══╝╚══╝
*/


#if IS_USING_SDL_1
  ESysStatus windowExposed(); /**< Window Exposed, Need Redraw */
  ESysStatus windowResized(const int w, const int h); /**< Window Resized */
  ESysStatus windowMinimized(); /**< Window Minimized */
  ESysStatus windowRestored(); /**< Window Restored */
  ESysStatus windowMouseEnter(); /**< Window Gained Mouse Focus */
  ESysStatus windowMouseLeave(); /**< Window Lost Mouse Focus */
  ESysStatus windowFocusGained(); /**< Window Gained Keyboard Focus */
  ESysStatus windowFocusLost(); /**< Window Lost Keyboard Focus */
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus windowExposed(const SDL_WindowEvent&); /**< Window Exposed, Need Redraw */
  ESysStatus windowResized(const SDL_WindowEvent&); /**< Window Resized */
  ESysStatus windowMinimized(const SDL_WindowEvent&); /**< Window Minimized */
  ESysStatus windowRestored(const SDL_WindowEvent&); /**< Window Restored */
  ESysStatus windowMouseEnter(const SDL_WindowEvent&); /**< Window Gained Mouse Focus */
  ESysStatus windowMouseLeave(const SDL_WindowEvent&); /**< Window Lost Mouse Focus */
  ESysStatus windowFocusGained(const SDL_WindowEvent&); /**< Window Gained Keyboard Focus */
  ESysStatus windowFocusLost(const SDL_WindowEvent&); /**< Window Lost Keyboard Focus */
#endif

#if IS_USING_SDL_2 || IS_USING_SDL_3
  ESysStatus windowShown(const SDL_WindowEvent&); /**< Window Shown */
  ESysStatus windowHidden(const SDL_WindowEvent&); /**< Window Hidden */
  ESysStatus windowMoved(const SDL_WindowEvent&); /**< Window Moved */
  ESysStatus windowPixelSizeChanged(const SDL_WindowEvent&);
  ESysStatus windowMetalViewResized(const SDL_WindowEvent&);
  ESysStatus windowSizeChanged(const SDL_WindowEvent&); /**< Window Size Changed */
  ESysStatus windowMaximized(const SDL_WindowEvent&); /**< Window Maximized */
  ESysStatus windowCloseRequest(const SDL_WindowEvent&); /**< Window Requested For Close */
  ESysStatus windowTakeFocus(const SDL_WindowEvent&); /**< Window Offered Focus */
  ESysStatus windowHitTest(const SDL_WindowEvent&); /**< Window Had Hit Test, That Wasn't SDL_HITTEST_NORMAL */
  ESysStatus windowIccChanged(const SDL_WindowEvent&); /**< Window's Display ICC Profile Changed */
  ESysStatus windowDisplayChanged(const SDL_WindowEvent&); /**< Window Moved Display */
  ESysStatus windowDisplayScaleChanged(const SDL_WindowEvent&);
  ESysStatus windowSafeAreaChanged(const SDL_WindowEvent&);
  ESysStatus windowOccluded(const SDL_WindowEvent&);
  ESysStatus windowEnterFullscreen(const SDL_WindowEvent&);
  ESysStatus windowLeaveFullscreen(const SDL_WindowEvent&);
  ESysStatus windowDestroyed(const SDL_WindowEvent&);
  ESysStatus windowHdrStateChanged(const SDL_WindowEvent&);
#endif

};


#endif /* AB_ENGINE_HPP */
