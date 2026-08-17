#include "All.hpp"

#include "Main.hpp"

void All::reportSystemError(const char* custom_message) {
#if IS_OS_LINUX
  perror(custom_message);
#elif IS_OS_WINDOWS
  char buffer[1024] = {};
  const DWORD error = GetLastError();
  const DWORD format_result = FormatMessage(
    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    null,
    error,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    buffer,
    sizeof(buffer),
    null
  );
  fprintf(stderr, "%s: Error 0x%lx: %s\n", custom_message, error, buffer);
#endif
}


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
