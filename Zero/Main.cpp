
#include <cstdio>
#include <SDL2/SDL.h>
#include "Main.hpp"

int main(int argc, char** argv) {
  const int res = SDL_Init(0);
  if (res == 0) {
    printf("SDL Init Successful!\n");
  }
  SDL_Window* window = SDL_CreateWindow(
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
  printf("Video driver: %s\n", SDL_GetCurrentVideoDriver());
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
