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

struct Step {
public:
  u8 just_continue : 1;
  u8 calculate_delta_time : 1;
  u8 window_check : 1;
  u8 window_undef : 1;
  u8 window_def : 1;
  // ReSharper disable once CppDeclaratorNeverUsed
  u8 _pad03_ : 1;
  // ReSharper disable once CppDeclaratorNeverUsed
  u8 _pad02_ : 1;
  // ReSharper disable once CppDeclaratorNeverUsed
  u8 _pad01_ : 1;
  // ReSharper disable once CppDeclaratorNeverUsed
  u8 _pad00_[mmBufferSize(0) - 1];
};
staticAssert(sizeof(Step) == sizeof(Buffer0), Step_FIT_INTO_ONE_Buffer0)

struct Bootstrapper {
  Pool4* pools_[sizeof(Buffer0) / sizeof(Pool4*)];
  Step step_a;
  Step step_b;
  SdlWindow window;
  usize _pad1_[63];
  // ReSharper disable once CppDeclaratorNeverUsed
  Buffer0 _pad_[124];
  Bootstrapper() : pools_(), step_a(), step_b(), window(SdlWindow::def()), _pad1_() {}
  Bootstrapper* undef() {
    window.destroy();
    for (int i = 1; pools_[i] != null; i++) {
      pools_[i] = pools_[i]->undef();
    }
    pools_[0]->undef();
    return null;
  }
};
staticAssert(sizeof(Bootstrapper) == sizeof(Block0), BOOTSTRAPPER_FIT_INTO_ONE_BLOCK0)

struct DebugData {
  u64 frequency;
  u64 past;
private:
  DebugData() : frequency(clockFrequencyU64() / MSPS), past(clockU64()) {}
public:
  static DebugData* def() { return new DebugData(); }
  DebugData* undef() const { delete this; return null; }
};

// ReSharper disable once CppMemberFunctionMayBeStatic
ESysStatus MainDispatcher::preSdlInit(int, char**) { // NOLINT(*-convert-member-functions-to-static)
  return E_SYS_CONTINUE;
}

ESysStatus MainDispatcher::initSdl(int, char**) {
  const Sdl::Status res = Sdl::def().timer().video().events().noParachute().eventThread().init();
  if (res != Sdl::INIT_SUCCEED) {
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

  db_ = DebugData::def();

  // 1. Building the first memory data structure.
  // 2. Running the system.

  // Route: advance(); // May allocate more memory.
  // Route: shutdown(); // Rely on pre-allocated memory.

  // 1. Building the first memory data structure.
  Pool4* initial_pool = Pool4::def();
  if (initial_pool == null) {
    All::firstPoolAllocationFailed();
    exit_code = EXIT_FAILURE;
    debugBreak;
    return E_SYS_FATALITY;
  }
  const IndexBlock fi = IndexBlock::def(0);
  Block0* fb = fi.toBlock0(initial_pool);
  assert(static_cast<void*>(initial_pool) == static_cast<void*>(fb));
  boot_ = reinterpret_cast<Bootstrapper*>(fb);
  boot_->pools_[0] = initial_pool;
  current_ = &(boot_->step_a);
  next_ = &(boot_->step_b);
  next_->calculate_delta_time = true;

  if (boot_->window.create() == null) {
    exit_code = EXIT_FAILURE;
    debugBreak;
    return E_SYS_FATALITY;
  }

  print("Current video driver: %s\n", SdlWindow::getCurrentVideoDriverName());
#if IS_USING_SDL_2 || IS_USING_SDL_3
  const int video_count = SdlWindow::getVideoDriverCount();
  if (video_count < 1) {
    exit_code = EXIT_FAILURE;
    debugBreak;
    return E_SYS_FATALITY;
  }
  print("Found %d video drivers.\n", video_count);
  for (int i = 0; i < video_count; i++) {
    const char* name = SdlWindow::getVideoDriverName(i);
    print("Video driver %d: %s\n", i, name);
  }
#endif

  {
    const VkResult res = volkInitialize();
    if (res != VK_SUCCESS) {
      print("Failed to initialize volk!");
      return E_SYS_FATALITY;
    }
  }

  {
    u32 version = 0;
    VkResult res = vkEnumerateInstanceVersion(&version);
    if (res == VK_SUCCESS) {
      print("Vulkan Instance Version Variant: %d\n", VK_API_VERSION_VARIANT(version));
      print("Vulkan Instance Version Major: %d\n", VK_API_VERSION_MAJOR(version));
      print("Vulkan Instance Version Minor: %d\n", VK_API_VERSION_MINOR(version));
      print("Vulkan Instance Version Patch: %d\n", VK_API_VERSION_PATCH(version));
    } else {
      print("Failed to get Vulkan instance version. res: %d\n", res);
    }
    VkExtensionProperties properties[32] = {};
    u32 count = sizeof(properties) / sizeof(VkExtensionProperties);
    res = vkEnumerateInstanceExtensionProperties(null, &count, properties);
    if (res == VK_SUCCESS) {
      print("Vulkan Extension Count: %u\n", count);
      for (u32 i = 0; i < count; i++) {
        print("Extension %d: %s\n", i, properties[i].extensionName);
      }
    } else {
      print("Failed to get Vulkan extension count. res: %d\n", res);
    }
  }

  return E_SYS_CONTINUE;
}

ESysStatus MainDispatcher::eventSdl(const SDL_Event& event) {
  return static_cast<SdlEventDispatcher*>(this)->eventSdl(event); // NOLINT(*-pro-type-static-cast-downcast)
}

void MainDispatcher::calculateDeltaTime(DebugData& db) {
  /* Begin { Print Frame Time } */ {
    const u64 now = clockU64();
    const double delta = castDouble(now - db.past) / castDouble(db.frequency);
    const double fps = castDouble(MSPS) / delta;
    db.past = now;
    /** / print("delta: %f\t fps: %f\n", delta, fps); /**/
    char title[128] = {0};
    snprintf(title, sizeof(title), "delta: %.2f fps: %.2f", delta, fps);
    boot_->window.setTitle(title);
  } /* End { Print Frame Time } */
}

ESysStatus MainDispatcher::stepEngine() {

  /* Step Dispatch */
  if (current_->just_continue) {}
  if (current_->calculate_delta_time) {
    current_->calculate_delta_time = false;
    calculateDeltaTime(*db_);
    next_->calculate_delta_time = true;
  }
  if (current_->window_check) {}
  if (current_->window_undef) {}
  if (current_->window_def) {}

  Step* t = current_;
  current_ = next_;
  next_ = t;

  return E_SYS_CONTINUE;
}

void MainDispatcher::shutEngine() {
  db_ = db_ ? db_->undef() : null;
  next_ = null;
  current_ = null;
  boot_ = boot_ ? boot_->undef() : null;
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
  db_ = null;
  boot_ = null;
  current_ = null;
  next_ = null;
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


