// ReSharper disable CppMemberFunctionMayBeStatic
#include "Main.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL.h>
  /* ReSharper disable once CppUnusedIncludeDirective */
  #include <SDL3/SDL_main.h>
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

#include "Engine.hpp"

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

static int shutdown(Engine& engine) {
  const int exit_code = engine.exit_code;
  engine.shutEngine();
  engine.shutSdl();
  return exit_code;
}

#define CHECK(ROUTINE_CALL) \
  if ((ROUTINE_CALL) != E_SYS_CONTINUE) { return shutdown(engine); }

/* ReSharper disable once CppParameterMayBeConst */
int main(int argc, char** argv) {
  Engine engine = Engine::def();
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


