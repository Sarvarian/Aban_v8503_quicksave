
#include <cstdio>
#include "Main.hpp"

int main() {
  const int res = SDL_Init(SDL_INIT_EVERYTHING);
  if (res == 0) {
    printf("SDL Init Successful!\n");
  }
  printf("AB_PROFILE: %s\n", stringify(AB_PROFILE));
  printf("Hello my dear friends!\n");
  SDL_Quit();
}
