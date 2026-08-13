#include "All.hpp"

#include "Main.hpp"


All::All() {
  /* Empty */
}

All All::def() {
  return All();
}















void All::sdlInitFailed() {
    fprintf(stderr, "SDL Init Failed!\nSDL: %s\n", SDL_GetError());
}

void All::vulkanEnumerateInstanceExtensionPropertiesCountFailed() {
  fprintf(stderr, "Failed at vkEnumerateInstanceExtensionProperties for getting count.");
}

void All::firstPoolAllocationForArtFailed() {
  const char* title = "First Pool Allocation For Art Failed! [Engine]";
  const char* message = "Failed to allocate memory for Art.";
#if IS_USING_SDL_2 || IS_USING_SDL_3
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, null);
#endif
}
