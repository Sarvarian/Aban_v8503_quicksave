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



#endif /* AB_SDL_INIT_HPP */
