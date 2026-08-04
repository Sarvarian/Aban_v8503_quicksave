#pragma once

#ifndef AB_SDL_INIT_HPP
#define AB_SDL_INIT_HPP


/** SDL Initializer */
class Sdl {
public:

  enum Status {
    INIT_FAILED = false,
    INIT_SUCCEED = true
  };

  static Sdl def();
  Status init();
  static void quit();

  /** Add timer subsystem to init flags. */
  Sdl& timer();
  /** Add audio subsystem to init flags. */
  Sdl& audio();
  /** Add video subsystem to init flags. */
  Sdl& video();
  /** Add joystick subsystem to init flags. */
  Sdl& joystick();
  /** Add haptic subsystem to init flags. */
  Sdl& haptic();
  /** Add gamepad subsystem to init flags. */
  Sdl& gamepad();
  /** Add events subsystem to init flags. */
  Sdl& events();
  /** Add sensor subsystem to init flags. */
  Sdl& sensor();
  /** Add camera subsystem to init flags. */
  Sdl& camera();
  /** Add event thread subsystem to init flags. */
  Sdl& eventThread();

private:
  Sdl();
  unsigned int subsystem_flags_;

public:
  /** For SDL1 these will be equivalent to SDLKey.
   *  For SDL2 and SDL3 these will be equivalent to SDL_Scancode.
   */
  enum Key {
#if IS_USING_SDL_1
    BACKSPACE = SDLK_BACKSPACE,
    TAB = SDLK_TAB,
    CLEAR = SDLK_CLEAR,
    RETURN = SDLK_RETURN,
    PAUSE = SDLK_PAUSE,
    ESCAPE = SDLK_ESCAPE,
    SPACE = SDLK_SPACE,
    EXCLAIM = SDLK_EXCLAIM,
    QUOTEDBL = SDLK_QUOTEDBL,
    HASH = SDLK_HASH,
    DOLLAR = SDLK_DOLLAR,
    AMPERSAND = SDLK_AMPERSAND,
    QUOTE = SDLK_QUOTE,
    LEFTPAREN = SDLK_LEFTPAREN,
    RIGHTPAREN = SDLK_RIGHTPAREN,
    ASTERISK = SDLK_ASTERISK,
    PLUS = SDLK_PLUS,
    COMMA = SDLK_COMMA,
    MINUS = SDLK_MINUS,
    PERIOD = SDLK_PERIOD,
    SLASH = SDLK_SLASH,
    NUM_0 = SDLK_0,
    NUM_1 = SDLK_1,
    NUM_2 = SDLK_2,
    NUM_3 = SDLK_3,
    NUM_4 = SDLK_4,
    NUM_5 = SDLK_5,
    NUM_6 = SDLK_6,
    NUM_7 = SDLK_7,
    NUM_8 = SDLK_8,
    NUM_9 = SDLK_9,
    COLON = SDLK_COLON,
    SEMICOLON = SDLK_SEMICOLON,
    LESS = SDLK_LESS,
    EQUALS = SDLK_EQUALS,
    GREATER = SDLK_GREATER,
    QUESTION = SDLK_QUESTION,
    AT = SDLK_AT,
    LEFTBRACKET = SDLK_LEFTBRACKET,
    BACKSLASH = SDLK_BACKSLASH,
    RIGHTBRACKET = SDLK_RIGHTBRACKET,
    CARET = SDLK_CARET,
    UNDERSCORE = SDLK_UNDERSCORE,
    BACKQUOTE = SDLK_BACKQUOTE,
    A = SDLK_a,
    B = SDLK_b,
    C = SDLK_c,
    D = SDLK_d,
    E = SDLK_e,
    F = SDLK_f,
    G = SDLK_g,
    H = SDLK_h,
    I = SDLK_i,
    J = SDLK_j,
    K = SDLK_k,
    L = SDLK_l,
    M = SDLK_m,
    N = SDLK_n,
    O = SDLK_o,
    P = SDLK_p,
    Q = SDLK_q,
    R = SDLK_r,
    S = SDLK_s,
    T = SDLK_t,
    U = SDLK_u,
    V = SDLK_v,
    W = SDLK_w,
    X = SDLK_x,
    Y = SDLK_y,
    Z = SDLK_z,
    DELETE = SDLK_DELETE,
    KP0 = SDLK_KP0,
    KP1 = SDLK_KP1,
    KP2 = SDLK_KP2,
    KP3 = SDLK_KP3,
    KP4 = SDLK_KP4,
    KP5 = SDLK_KP5,
    KP6 = SDLK_KP6,
    KP7 = SDLK_KP7,
    KP8 = SDLK_KP8,
    KP9 = SDLK_KP9,
    KP_PERIOD = SDLK_KP_PERIOD,
    KP_DIVIDE = SDLK_KP_DIVIDE,
    KP_MULTIPLY = SDLK_KP_MULTIPLY,
    KP_MINUS = SDLK_KP_MINUS,
    KP_PLUS = SDLK_KP_PLUS,
    KP_ENTER = SDLK_KP_ENTER,
    KP_EQUALS = SDLK_KP_EQUALS,
    UP = SDLK_UP,
    DOWN = SDLK_DOWN,
    RIGHT = SDLK_RIGHT,
    LEFT = SDLK_LEFT,
    INSERT = SDLK_INSERT,
    HOME = SDLK_HOME,
    END = SDLK_END,
    PAGEUP = SDLK_PAGEUP,
    PAGEDOWN = SDLK_PAGEDOWN,
    F1 = SDLK_F1,
    F2 = SDLK_F2,
    F3 = SDLK_F3,
    F4 = SDLK_F4,
    F5 = SDLK_F5,
    F6 = SDLK_F6,
    F7 = SDLK_F7,
    F8 = SDLK_F8,
    F9 = SDLK_F9,
    F10 = SDLK_F10,
    F11 = SDLK_F11,
    F12 = SDLK_F12,
    F13 = SDLK_F13,
    F14 = SDLK_F14,
    F15 = SDLK_F15,
    NUMLOCK = SDLK_NUMLOCK,
    CAPSLOCK = SDLK_CAPSLOCK,
    SCROLLOCK = SDLK_SCROLLOCK,
    RSHIFT = SDLK_RSHIFT,
    LSHIFT = SDLK_LSHIFT,
    RCTRL = SDLK_RCTRL,
    LCTRL = SDLK_LCTRL,
    RALT = SDLK_RALT,
    LALT = SDLK_LALT,
    RMETA = SDLK_RMETA,
    LMETA = SDLK_LMETA,
    LSUPER = SDLK_LSUPER,
    RSUPER = SDLK_RSUPER,
    MODE = SDLK_MODE,
    COMPOSE = SDLK_COMPOSE,
    HELP = SDLK_HELP,
    PRINT = SDLK_PRINT,
    SYSREQ = SDLK_SYSREQ,
    BREAK = SDLK_BREAK,
    MENU = SDLK_MENU,
    POWER = SDLK_POWER,
    EURO = SDLK_EURO,
    UNDO = SDLK_UNDO
#elif IS_USING_SDL_2
#elif IS_USING_SDL_3
#endif
  };

};

/** SDL Window Handle Manager */
class SdlWindow {
public:

  enum Status {
    CREATION_FAILED = 0,
    CREATION_SUCCEED = 1
  };

  static SdlWindow def();
  Status create();
  void destroy();

  /** Wrapper around `SDL_GetNumVideoDrivers`
   *  - SDL1: Will always return -1
   *  - Thread Safety: This function should only be called on the main thread.
   */
  static int getVideoDriverCount();

  /** Wrapper around `SDL_GetVideoDriver`
   *  - SDL1: Will always return null
   *  - Thread Safety: This function should only be called on the main thread.
   */
  static const char* getVideoDriverName(const int index);

  /** Wrapper around `SDL_GetCurrentVideoDriver`
   *  - SDL1: Will return result of `SDL_VideoDriverName`
   *  - SDL1: Returns null if video has not been initialized with SDL_Init
   *  - Thread Safety: This function should only be called on the main thread.
   */
  static const char* getCurrentVideoDriverName();


private:
  SdlWindow();

  /** On SDL1 this will be `SDL_Surface`
   *  while in SDl2 and SDL3 this will be
   *  `SDL_Window`
   */
  void* handle_;
};



#endif /* AB_SDL_INIT_HPP */
