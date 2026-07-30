
#include <cstdio>
#include "Main.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL.h>
  #include <SDL3/SDL_main.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL.h>
#elif IS_USING_SDL_1
  #include <SDL/SDL.h>
#else
  #error "Failed to detect SDL version."
#endif

#include "Sdl.hpp"

int main(int argc, char** argv) {
  int res = 0;
  SdlWindow window = SdlWindow();
  res = Sdl().video().init();
  if (res == Sdl::INIT_SUCCEED) {
    printf("SDL Init Successful!\n");
  } else {
    printf("SDL Init Failed!\nSDL: %s\n", SDL_GetError());
    goto exit;
  }
  if (window.create() == SdlWindow::CREATION_FAILED) {
    printf("SDL Window Creation Failed!\n");
    printf("%s\n", SDL_GetError());
    goto exit;
  }
  printf("Hello my dear friends!\n");
#if !IS_USING_SDL_1
  {
    const int video_count = SdlWindow::getVideoDriverCount();
    if (video_count < 1) {
      goto exit;
    }
    printf("Found %d video drivers.\n", video_count);
    for (int i = 0; i < video_count; i++) {
      const char* name = SdlWindow::getVideoDriverName(i);
      printf("Video driver %d: %s\n", i, name);
    }
  }
#endif
  printf("Current video driver: %s\n", SdlWindow::getCurrentVideoDriverName());
  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        goto exit;
      }
    }
  }
  exit:
  window.destroy();
  Sdl::quit();
  printf("Goodbye\n");
  return 0;
}
