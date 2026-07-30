#pragma once

#ifndef AB_SDL_INIT_HPP
#define AB_SDL_INIT_HPP


/** SDL Initializer */
class Sdl {
public:

  enum Status {
    INIT_FAILED = false,
    INIT_SUCCEED = true
  };

  Sdl();
  Status init();
  static void quit();

  /** Add video subsystem to init flags. */
  Sdl& video();

private:
  unsigned int subsystem_flags_;
};

/** SDL Window Handle Manager */
class SdlWindow {
public:

  enum Status {
    CREATION_FAILED = 0,
    CREATION_SUCCEED = 1
  };

  SdlWindow();
  Status create();
  void destroy();

  /** Can the window subsystem handle and
   *    provide multiple windows simultaneously.
   *  Or the system only works with one main
   *    Window alone?
   */
  static bool isMultiWindowSupported();

  /** Wrapper around `SDL_GetNumVideoDrivers`
   *  - SDL1: Will always return -1
   *  - Thread Safety: This function should only be called on the main thread.
   */
  static int getVideoDriverCount();

  /** Wrapper around `SDL_GetVideoDriver`
   *  - SDL1: Will always return null
   *  - Thread Safety: This function should only be called on the main thread.
   */
  static const char* getVideoDriverName(const int index);

  /** Wrapper around `SDL_GetCurrentVideoDriver`
   *  - SDL1: Will return result of `SDL_VideoDriverName`
   *  - SDL1: Returns null if video has not been initialized with SDL_Init
   *  - Thread Safety: This function should only be called on the main thread.
   */
  static const char* getCurrentVideoDriverName();


private:
  /** On SDL1 this will be `SDL_Surface`
   *  while in SDl2 and SDL3 this will be
   *  `SDL_Window`
   */
  void* handle_;
};



#endif /* AB_SDL_INIT_HPP */
