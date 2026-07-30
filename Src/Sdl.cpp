#include "Sdl.hpp"

#include "Main.hpp"
#include "SDL3/SDL_init.h"

Sdl::Sdl() {
  subsystem_flags_ = 0;
}

Sdl::Status Sdl::init() {
  const bool res = SDL_Init(subsystem_flags_);
  return res == true ? INIT_SUCCEED : INIT_FAILED;
}

void Sdl::quit() {
  SDL_Quit();
}

Sdl& Sdl::video() {
  subsystem_flags_ |= SDL_INIT_VIDEO;
  return *this;
}
