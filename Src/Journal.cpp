#include "Journal.hpp"

#include "Main.hpp"

void Journal::firstPoolAllocationFailed() {
  const char* title = "First Pool Allocation Failed! [Engine]";
  const char* message = "Failed to allocate memory for the first memory pool "
    "at engine initialization stage.";
  // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, null);
  perror(message);
}
