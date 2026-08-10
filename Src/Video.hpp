#pragma once

#ifndef AB_VIDEO_DEVICE_HPP
#define AB_VIDEO_DEVICE_HPP

#if IS_USING_SDL_1
  #include <SDL/SDL_video.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL_video.h>
#elif IS_USING_SDL_3
  #include <SDL3/SDL_video.h>
#endif

/** SDL Window Handle Manager */
class SdlWindow {
public:

  static SdlWindow def();

#if IS_USING_SDL_1
  typedef SDL_Surface Handle;
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  typedef SDL_Window Handle;
#endif

  /** Returns null in case of failure. Call SDL_GetError() for more information. */
  Handle* create();
  /** Always returns null.*/
  Handle* destroy();

  /** Wrapper around `SDL_GetNumVideoDrivers`
   *  - SDL1: Will always return -1
   */
  static int getVideoDriverCount();

  /** Wrapper around `SDL_GetVideoDriver`
   *  - SDL1: Will always return null
   */
  static const char* getVideoDriverName(const int index);

  /** Wrapper around `SDL_GetCurrentVideoDriver`
   *  - SDL1: Will return result of `SDL_VideoDriverName`
   *  - SDL1: Returns null if video has not been initialized with SDL_Init
   */
  static const char* getCurrentVideoDriverName();

  /** \returns true on success or false on failure; call SDL_GetError() for more information. */
  bool setTitle(const char* title);

private:
  SdlWindow();

  /** On SDL1 this will be `SDL_Surface`
   *  while in SDl2 and SDL3 this will be `SDL_Window` */
  Handle* handle_;
};
staticAssert(sizeof(SdlWindow) == sizeof(void*), SdlWindow_IS_JUST_A_CONTAINER_FOR_ITS_HANDLE)

class Video {
public:
  static Video* def();

  /** \return Always returns null */
  Video* undef();

private:
  Video();

};

#endif /* AB_VIDEO_DEVICE_HPP */
