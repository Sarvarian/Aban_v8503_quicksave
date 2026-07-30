
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

#include "SdlInit.hpp"

int main(int argc, char** argv) {
  int res = 0;
  SDL_Window* window = null;
  int video_count;
  res = Sdl().video().init();
  if (res) {
    printf("SDL Init Successful!\n");
  } else {
    printf("SDL Init Failed!\nSDL: %s\n", SDL_GetError());
    goto exit;
  }
  window = SDL_CreateWindow(
    "Zero",
    800, 600,
    0
  );
  if (window == null) {
    printf("SDL Window Creation Failed!\n");
    printf("%s\n", SDL_GetError());
    goto exit;
  }
  printf("AB_PROFILE: %s\n", stringify(AB_PROFILE));
  printf("Hello my dear friends!\n");
  video_count = SDL_GetNumVideoDrivers();
  if (video_count < 1) {
    goto exit;
  }
  printf("Found %d video drivers.\n", video_count);
  for (int i = 0; i < video_count; i++) {
    const char* name = SDL_GetVideoDriver(i);
    printf("Video driver %d: %s\n", i, name);
  }
  printf("Current video driver: %s\n", SDL_GetCurrentVideoDriver());
  SDL_Event event;
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        goto exit;
      }
    }
  }
  exit:
  SDL_DestroyWindow(window);
  Sdl::quit();
  printf("Goodbye\n");
  return 0;
}
