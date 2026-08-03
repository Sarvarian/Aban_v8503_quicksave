#include "Journal.hpp"

#include "Main.hpp"

void Journal::sdlInitFailed() {
    fprintf(stderr, "SDL Init Failed!\nSDL: %s\n", SDL_GetError());
}

void Journal::firstPoolAllocationFailed() {
  const char* title = "First Pool Allocation Failed! [Engine]";
  const char* message = "Failed to allocate memory for the first memory pool "
    "at engine initialization stage.";
#if IS_USING_SDL_2 || IS_USING_SDL_3
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, null);
#endif
  perror(message);
}
