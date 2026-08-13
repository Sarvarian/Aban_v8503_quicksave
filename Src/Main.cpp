#include "Main.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL.h>
  /* ReSharper disable once CppUnusedIncludeDirective */
  #include <SDL3/SDL_main.h>
  /* ReSharper disable once CppUnusedIncludeDirective */
  #include <SDL3/SDL_init.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL.h>
  /* ReSharper disable once CppUnusedIncludeDirective */
  #include <SDL2/SDL_main.h>
#elif IS_USING_SDL_1
  #include <SDL/SDL.h>
  /* ReSharper disable once CppUnusedIncludeDirective */
  #include <SDL/SDL_main.h>
#endif

#include "Alm.hpp"
#include "Art.hpp"
#include "All.hpp"
#include "Aid.hpp"

// ReSharper disable once CppMemberFunctionMayBeStatic
ESysStatus MainDispatcher::preSdlInit(int, char**) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus MainDispatcher::initSdl(int, char**) {
  const ESysStatus res = Sdl::def().timer().video().events().noParachute().eventThread().init();
  if (res != E_SYS_CONTINUE) {
    All::sdlInitFailed();
    exit_code = EXIT_FAILURE;
    debugBreak;
    return E_SYS_FATALITY;
  } else {
    return E_SYS_CONTINUE;
  }
}

ESysStatus MainDispatcher::initEngine(int, char**) {
  art_ = Art::def();
  if (art_ == null) {
    return E_SYS_FATALITY;
  }

#if IS_USING_SDL_2 || IS_USING_SDL_3
  SDL_SetEventFilter(SdlEventDispatcher::sdlEventFilter, this);
#endif

  SdlWindow::debugPrintVideoDriverInformation();

#if AB_VULKAN
  if (Volk::init() != E_SYS_CONTINUE) {
    print("Failed to initialize volk!");
    return E_SYS_FATALITY;
  }
  Vulkan::debugPrintInstanceInformation();
#endif

  return E_SYS_CONTINUE;
}

ESysStatus MainDispatcher::eventSdl(const SDL_Event& event) {
  return static_cast<SdlEventDispatcher*>(this)->eventSdl(event); // NOLINT(*-pro-type-static-cast-downcast)
}

ESysStatus MainDispatcher::stepEngine() {
  return E_SYS_QUIT;
}

void MainDispatcher::shutEngine() {
  art_ = art_ ? art_->undef() : null;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void MainDispatcher::shutSdl() { // NOLINT(*-convert-member-functions-to-static)
#if !AB_SANITIZE
  Sdl::quit();
#endif
}

MainDispatcher::MainDispatcher()
{
  /* FFF: F&^k Fixed Frequency */
  /* target_delta_ms = 0;      */
  target_delta_ms = (MSPS / 10);
  exit_code = EXIT_SUCCESS;
  art_ = null;
}

MainDispatcher MainDispatcher::def() {
  return MainDispatcher();
}

struct Timing {
private:
  const u64 frequency_; /* Clock frequency in millisecond. */
  u64 next_; /* Next Step Starts At */
  Timing() : frequency_(clockFrequencyU64() / MSPS) , next_(0) {}
public:
  void frameEnd(const u32 target_delta_ms) {
    const u64 now = clockU64();
    if (now < next_) {
      u32 delay = (next_ - now) / frequency_;
      delay = delay > 1 ? (delay - 1) : 0;
      if (delay > 0) { SDL_Delay(delay); }
    }
    while (clockU64() < next_) { /* Waste Clock */ }
    next_ = clockU64() + (target_delta_ms * frequency_);
  }
  static Timing def() {
    return Timing();
  }
};

static int shutdown(MainDispatcher& engine) {
  const int exit_code = engine.exit_code;
  engine.shutEngine();
  engine.shutSdl();
  return exit_code;
}

#define CHECK(ROUTINE_CALL) \
  if ((ROUTINE_CALL) != E_SYS_CONTINUE) { return shutdown(engine); }

/* ReSharper disable once CppParameterMayBeConst */
int main(int argc, char** argv) {
  MainDispatcher engine = MainDispatcher::def();
  CHECK(engine.preSdlInit(argc, argv))
  CHECK(engine.initSdl(argc, argv));
  CHECK(engine.initEngine(argc, argv));
  Timing timing = Timing::def();
  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      CHECK(engine.eventSdl(event));
    }
    switch (engine.stepEngine()) {
      case E_SYS_CONTINUE: timing.frameEnd(engine.target_delta_ms); break;
      case E_SYS_REPEAT: break;
      default: return shutdown(engine);
    }
  }
  /* ReSharper disable once CppDFAUnreachableCode */
  return shutdown(engine);
}


