
#include <cstdio>
#include <SDL2/SDL.h>
#include "Main.hpp"

int main(int argc, char** argv) {
  int res = 0;
  SDL_Window* window = null;
  int video_count;
  res = SDL_Init(SDL_INIT_VIDEO);
  if (res == 0) {
    printf("SDL Init Successful!\n");
  } else {
    printf("SDL Init Failed!\n");
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
      if (event.type == SDL_QUIT) {
        goto exit;
      }
    }
  }
  exit:
  SDL_DestroyWindow(window);
  SDL_Quit();
  printf("Goodbye\n");
  return 0;
}
