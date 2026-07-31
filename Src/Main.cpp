#include "Main.hpp"

#if IS_USING_SDL_3
  #include <SDL3/SDL.h>
  #include <SDL3/SDL_main.h>
#elif IS_USING_SDL_2
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_main.h>
#elif IS_USING_SDL_1
  #include <SDL/SDL.h>
  #include <SDL/SDL_main.h>
#endif

#include "Engine.hpp"


struct Timing {
private:
  const u64 frequency_;
  u64 post_;
  u32 delay_;
  Timing()
  : frequency_(clockFrequencyU64() / MSPS)
  , post_(clockU64())
  , delay_(0)
  {}
public:
  void frameEnd(const u32 target_delta_ms) {
    const u64 now = clockU64();
    const u64 past = post_ + delay_;
    const u64 delta = (now - past) / frequency_;
    delay_
    = target_delta_ms > delta
    ? target_delta_ms - delta
    : 0
    ;
    SDL_Delay(delay_);
    post_ = clockU64();
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
      CHECK(engine.eventSdl(&event));
    }
    CHECK(engine.stepEngine());
    timing.frameEnd(engine.target_delta_ms);
  }
  /* ReSharper disable once CppDFAUnreachableCode */
  return shutdown(engine);
}

