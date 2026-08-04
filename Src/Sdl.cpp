#include "Sdl.hpp"

#include "Main.hpp"



#if IS_USING_SDL_1

#include "SDL/SDL.h"

static char current_video_driver_name_[255];

Sdl::Sdl() {
  subsystem_flags_ = 0;
}

Sdl Sdl::def() {
  return Sdl();
}

Sdl::Status Sdl::init() {
#if !AB_SANITIZE
  atexit(SDL_Quit);
#endif
  const int res = SDL_Init(subsystem_flags_);
  return res == 0 ? INIT_SUCCEED : INIT_FAILED;
}

void Sdl::quit() {
  SDL_Quit();
}

Sdl& Sdl::timer() {
  subsystem_flags_ |= SDL_INIT_TIMER;
  return *this;
}

Sdl & Sdl::audio() {
  subsystem_flags_ |= SDL_INIT_AUDIO;
  return *this;
}

Sdl& Sdl::video() {
  subsystem_flags_ |= SDL_INIT_VIDEO;
  return *this;
}

Sdl& Sdl::joystick() {
  subsystem_flags_ |= SDL_INIT_JOYSTICK;
  return *this;
}

Sdl& Sdl::haptic() {
  /* No Such Init For SDL1 */
  return *this;
}

Sdl& Sdl::gamepad() {
  /* No Such Init For SDL1 */
  return *this;
}

Sdl& Sdl::events() {
  /* No Such Init For SDL1 */
  return *this;
}

Sdl& Sdl::sensor() {
  /* No Such Init For SDL1 */
  return *this;
}

Sdl& Sdl::camera() {
  /* No Such Init For SDL1 */
  return *this;
}

Sdl& Sdl::eventThread() {
  subsystem_flags_ |= SDL_INIT_EVENTTHREAD;
  return *this;
}

SdlWindow::SdlWindow() {
  handle_ = null;
}

SdlWindow SdlWindow::def() {
  return SdlWindow();
}

SdlWindow::Status SdlWindow::create() {
  handle_ = SDL_SetVideoMode(640, 480, 0, 0);
  SDL_WM_SetCaption("Aban", null);
  return handle_ == null ? CREATION_FAILED : CREATION_SUCCEED;
}

void SdlWindow::destroy() {
  handle_ = null;
}

bool SdlWindow::isMultiWindowSupported() {
  return false;
}

int SdlWindow::getVideoDriverCount() {
  return -1;
}

const char* SdlWindow::getVideoDriverName(const int index) {
  return null;
}

const char* SdlWindow::getCurrentVideoDriverName() {
  memset(current_video_driver_name_, 0, sizeof(current_video_driver_name_));
  SDL_VideoDriverName(current_video_driver_name_, sizeof(current_video_driver_name_));
  return current_video_driver_name_;
}

#elif IS_USING_SDL_2

#include "SDL2/SDL.h"

Sdl::Sdl() {
  subsystem_flags_ = 0;
}

Sdl Sdl::def() {
  return Sdl();
}

Sdl::Status Sdl::init() {
#if !AB_SANITIZE
  atexit(SDL_Quit);
#endif
  const int res = SDL_Init(subsystem_flags_);
  return res == 0 ? INIT_SUCCEED : INIT_FAILED;
}

void Sdl::quit() {
  SDL_Quit();
}

Sdl& Sdl::timer() {
  subsystem_flags_ |= SDL_INIT_TIMER;
  return *this;
}

Sdl& Sdl::audio() {
  subsystem_flags_ |= SDL_INIT_AUDIO;
  return *this;
}

Sdl& Sdl::video() {
  subsystem_flags_ |= SDL_INIT_VIDEO;
  return *this;
}

Sdl& Sdl::joystick() {
  subsystem_flags_ |= SDL_INIT_JOYSTICK;
  return *this;
}

Sdl& Sdl::haptic() {
  subsystem_flags_ |= SDL_INIT_HAPTIC;
  return *this;
}

Sdl& Sdl::gamepad() {
  subsystem_flags_ |= SDL_INIT_GAMECONTROLLER;
  return *this;
}

Sdl& Sdl::events() {
  subsystem_flags_ |= SDL_INIT_EVENTS;
  return *this;
}

Sdl & Sdl::sensor() {
  subsystem_flags_ |= SDL_INIT_SENSOR;
  return *this;
}

Sdl & Sdl::camera() {
  /* No Such Init For SDL2 */
  return *this;
}

Sdl& Sdl::eventThread() {
  /* SDL1 Feature Only. */
  return *this;
}

SdlWindow::SdlWindow() {
  handle_ = null;
}

SdlWindow SdlWindow::def() {
  return SdlWindow();
}

SdlWindow::Status SdlWindow::create() {
  handle_ = SDL_CreateWindow(
    "Aban",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    0
  );
  return handle_ == null ? CREATION_FAILED : CREATION_SUCCEED;
}

void SdlWindow::destroy() {
  if (handle_ != null) {
    SDL_DestroyWindow(static_cast<SDL_Window*>(handle_));
  }
  handle_ = null;
}

bool SdlWindow::isMultiWindowSupported() {
#if IS_OS_LINUX
  return true;
#endif
}

int SdlWindow::getVideoDriverCount() {
  return SDL_GetNumVideoDrivers();
}

const char * SdlWindow::getVideoDriverName(const int index) {
  return SDL_GetVideoDriver(index);
}

const char * SdlWindow::getCurrentVideoDriverName() {
  return SDL_GetCurrentVideoDriver();
}


#elif IS_USING_SDL_3

#include "SDL3/SDL_init.h"

Sdl::Sdl() {
  subsystem_flags_ = 0;
}

Sdl Sdl::def() {
  return Sdl();
}

Sdl::Status Sdl::init() {
#if !AB_SANITIZE
  atexit(SDL_Quit);
#endif
  const bool res = SDL_Init(subsystem_flags_);
  return res == true ? INIT_SUCCEED : INIT_FAILED;
}

void Sdl::quit() {
  SDL_Quit();
}

Sdl& Sdl::timer() {
  /* No Such Init For SDL3 */
  return *this;
}

Sdl& Sdl::audio() {
  subsystem_flags_ |= SDL_INIT_AUDIO;
  return *this;
}

Sdl& Sdl::video() {
  subsystem_flags_ |= SDL_INIT_VIDEO;
  return *this;
}

Sdl& Sdl::joystick() {
  subsystem_flags_ |= SDL_INIT_JOYSTICK;
  return *this;
}

Sdl& Sdl::haptic() {
  subsystem_flags_ |= SDL_INIT_HAPTIC;
  return *this;
}

Sdl& Sdl::gamepad() {
  subsystem_flags_ |= SDL_INIT_GAMEPAD;
  return *this;
}

Sdl& Sdl::events() {
  subsystem_flags_ |= SDL_INIT_EVENTS;
  return *this;
}

Sdl& Sdl::sensor() {
  subsystem_flags_ |= SDL_INIT_SENSOR;
  return *this;
}

Sdl & Sdl::camera() {
  subsystem_flags_ |= SDL_INIT_CAMERA;
  return *this;
}

Sdl& Sdl::eventThread() {
  /* SDL1 Feature Only. */
  return *this;
}

SdlWindow::SdlWindow() {
  handle_ = null;
}

SdlWindow SdlWindow::def() {
  return SdlWindow();
}

SdlWindow::Status SdlWindow::create() {
  handle_ = SDL_CreateWindow("Aban", 800, 600, 0);
  return handle_ == null ? CREATION_FAILED : CREATION_SUCCEED;
}

void SdlWindow::destroy() {
  if (handle_ != null) {
    SDL_DestroyWindow(static_cast<SDL_Window*>(handle_));
  }
  handle_ = null;
}

bool SdlWindow::isMultiWindowSupported() {
#if IS_OS_LINUX
  return true;
#endif
}

int SdlWindow::getVideoDriverCount() {
  return SDL_GetNumVideoDrivers();
}

const char * SdlWindow::getVideoDriverName(const int index) {
  return SDL_GetVideoDriver(index);
}

const char * SdlWindow::getCurrentVideoDriverName() {
  return SDL_GetCurrentVideoDriver();
}

#else
  #error "Failed to detect SDL version."
#endif
