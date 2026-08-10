#include "Video.hpp"

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

// ReSharper disable once CppDFAConstantFunctionResult
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

Video::Video() {
}

Video* Video::def() {
  return null;
}

Video* Video::undef() {
  return null;
}
