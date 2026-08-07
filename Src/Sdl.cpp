#include "Sdl.hpp"

#include "Main.hpp"

#if IS_USING_SDL_3
  #include "SDL3/SDL_init.h"
#elif IS_USING_SDL_2
  #include "SDL2/SDL.h"
#elif IS_USING_SDL_1
  #include "SDL/SDL.h"
#endif


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
#if IS_USING_SDL_1 || IS_USING_SDL_3
  const int res = SDL_Init(subsystem_flags_);
  return res == 0 ? INIT_SUCCEED : INIT_FAILED;
#elif IS_USING_SDL_3
  const bool res = SDL_Init(subsystem_flags_);
  return res == true ? INIT_SUCCEED : INIT_FAILED;
#endif
}

void Sdl::quit() {
  SDL_Quit();
}

Sdl& Sdl::timer() {
#if IS_USING_SDL_1 || IS_USING_SDL_2
  subsystem_flags_ |= SDL_INIT_TIMER;
#elif IS_USING_SDL_3
  /* No Such Init For SDL3 */
#endif
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
#if IS_USING_SDL_1
  /* No Such Init For SDL1 */
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_HAPTIC;
#endif
  return *this;
}

Sdl& Sdl::gamepad() {
#if IS_USING_SDL_1
  /* No Such Init For SDL1 */
#elif IS_USING_SDL_2
  subsystem_flags_ |= SDL_INIT_GAMECONTROLLER;
#elif IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_GAMEPAD;
#endif
  return *this;
}

Sdl& Sdl::events() {
#if IS_USING_SDL_1
  /* No Such Init For SDL1 */
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_EVENTS;
#endif
  return *this;
}

Sdl& Sdl::sensor() {
#if IS_USING_SDL_1
  /* No Such Init For SDL1 */
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_SENSOR;
#endif
  return *this;
}

Sdl& Sdl::camera() {
#if IS_USING_SDL_1 || IS_USING_SDL_2
  /* No Such Init For SDL1 */
  /* No Such Init For SDL2 */
#elif IS_USING_SDL_3
  subsystem_flags_ |= SDL_INIT_CAMERA;
#endif
  return *this;
}

Sdl& Sdl::eventThread() {
#if IS_USING_SDL_1
  subsystem_flags_ |= SDL_INIT_EVENTTHREAD;
#elif  IS_USING_SDL_2 || IS_USING_SDL_3
  /* SDL1 Feature Only. */
#endif
  return *this;
}

unsigned int Sdl::checkKey(const SDL_KeyboardEvent& key) {
#if IS_USING_SDL_1
  return key.keysym.sym;
#elif IS_USING_SDL_2
  return key.keysym.scancode;
#elif IS_USING_SDL_3
  return key.scancode;
#endif
}

SdlWindow::SdlWindow() {
  handle_ = null;
}

SdlWindow SdlWindow::def() {
  return SdlWindow();
}

SdlWindow::Handle* SdlWindow::create() {
#if IS_USING_SDL_1
  handle_ = SDL_SetVideoMode(640, 480, 0, 0);
  SDL_WM_SetCaption("Aban", null);
#elif IS_USING_SDL_2
  handle_ = SDL_CreateWindow(
    "Aban",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    0
  );
#elif IS_USING_SDL_3
  handle_ = SDL_CreateWindow("Aban", 800, 600, 0);
#endif
  return handle_;
}

SdlWindow::Handle* SdlWindow::destroy() {
#if IS_USING_SDL_1
  handle_ = null;
#elif  IS_USING_SDL_2 || IS_USING_SDL_3
  if (handle_ != null) { SDL_DestroyWindow(handle_); }
  handle_ = null;
#endif
  return handle_;
}

int SdlWindow::getVideoDriverCount() {
#if IS_USING_SDL_1
  return -1;
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  return SDL_GetNumVideoDrivers();
#endif
}

const char* SdlWindow::getVideoDriverName(const int index) {
#if IS_USING_SDL_1
  return null;
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  return SDL_GetVideoDriver(index);
#endif
}

#if IS_USING_SDL_1
static char current_video_driver_name_[255];
#endif

const char* SdlWindow::getCurrentVideoDriverName() {
#if IS_USING_SDL_1
  memset(current_video_driver_name_, 0, sizeof(current_video_driver_name_));
  SDL_VideoDriverName(current_video_driver_name_, sizeof(current_video_driver_name_));
  return current_video_driver_name_;
#elif IS_USING_SDL_2 || IS_USING_SDL_3
  return SDL_GetCurrentVideoDriver();
#endif
}

bool SdlWindow::setTitle(const char* title) {
#if IS_USING_SDL_1
  SDL_WM_SetCaption(title, null);
  return true;
#elif  IS_USING_SDL_2
  SDL_SetWindowTitle(handle_, title);
  return true;
#elif  IS_USING_SDL_3
  return SDL_SetWindowTitle(handle_, title);
#endif
}
