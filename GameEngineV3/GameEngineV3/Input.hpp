//
//  Input.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#define code(key) SDL_GetScancodeFromKey(key)

#ifdef __cplusplus
#include "GE_SDL.hpp"
#include "Vector.hpp"

namespace engine {

  /**
   Enum with all the mouse buttons supported.
   */
enum MouseInput {
  MOUSE_LEFT_BUTTON   = SDL_BUTTON_LEFT,
  MOUSE_MIDDLE_BUTTON = SDL_BUTTON_MIDDLE,
  MOUSE_RIGHT_BUTTON  = SDL_BUTTON_RIGHT
};

  
  /**
   Enum with all the keyboard keys supported.
   */
enum KeyCode {
  KEY_UNKNOW           = SDLK_UNKNOWN,
  KEY_RETURN           = SDLK_RETURN,
  KEY_ESCAPE           = SDLK_ESCAPE,
  KEY_BACKSPACE        = SDLK_BACKSPACE,
  KEY_TAB              = SDLK_TAB,
  KEY_SPACE            = SDLK_SPACE,
  KEY_EXCLAIN          = SDLK_EXCLAIM,
  KEY_QUOTEDBL         = SDLK_QUOTEDBL,
  KEY_HASH             = SDLK_HASH,
  KEY_PERCENT          = SDLK_PERCENT,
  KEY_DOLLAR           = SDLK_DOLLAR,
  KEY_AMPERSAND        = SDLK_AMPERSAND,
  KEY_QUOTE            = SDLK_QUOTE,
  KEY_LEFTPAREN        = SDLK_LEFTPAREN,
  KEY_RIGHTPAREN       = SDLK_RIGHTPAREN,
  KEY_ASTERISK         = SDLK_ASTERISK,
  KEY_PLUS             = SDLK_PLUS,
  KEY_COMMA            = SDLK_COMMA,
  KEY_MINUS            = SDLK_MINUS,
  KEY_PERIOD           = SDLK_PERIOD,
  KEY_SPLASH           = SDLK_SLASH,

  KEY_0                = SDLK_0,
  KEY_1                = SDLK_1,
  KEY_2                = SDLK_2,
  KEY_3                = SDLK_3,
  KEY_4                = SDLK_4,
  KEY_5                = SDLK_5,
  KEY_6                = SDLK_6,
  KEY_7                = SDLK_7,
  KEY_8                = SDLK_8,
  KEY_9                = SDLK_9,
  KEY_COLON            = SDLK_COLON,
  KEY_SEMICOLON        = SDLK_SEMICOLON,
  KEY_LESS             = SDLK_LESS,
  KEY_EQUALS           = SDLK_EQUALS,
  KEY_GREATER          = SDLK_GREATER,
  KEY_QUESTION         = SDLK_QUESTION,
  KEY_AT               = SDLK_AT,

  KEY_LEFTBRACKET      = SDLK_LEFTBRACKET,
  KEY_BACKSLASH        = SDLK_BACKSLASH,
  KEY_RIGHTBRACKET     = SDLK_RIGHTBRACKET,
  KEY_CARET            = SDLK_CARET,
  KEY_UNDERSCORE       = SDLK_UNDERSCORE,
  KEY_BACKQUOTE        = SDLK_BACKQUOTE,

  KEY_A                = SDLK_a,
  KEY_B                = SDLK_b,
  KEY_C                = SDLK_c,
  KEY_D                = SDLK_d,
  KEY_E                = SDLK_e,
  KEY_F                = SDLK_f,
  KEY_G                = SDLK_g,
  KEY_H                = SDLK_h,
  KEY_I                = SDLK_i,
  KEY_J                = SDLK_j,
  KEY_K                = SDLK_k,
  KEY_L                = SDLK_l,
  KEY_M                = SDLK_m,
  KEY_N                = SDLK_n,
  KEY_O                = SDLK_o,
  KEY_P                = SDLK_p,
  KEY_Q                = SDLK_q,
  KEY_R                = SDLK_r,
  KEY_S                = SDLK_s,
  KEY_T                = SDLK_t,
  KEY_U                = SDLK_u,
  KEY_V                = SDLK_v,
  KEY_W                = SDLK_w,
  KEY_X                = SDLK_x,
  KEY_Y                = SDLK_y,
  KEY_Z                = SDLK_z,

  KEY_CAPSLOCK         = SDLK_CAPSLOCK,

  KEY_F1               = SDLK_F1,
  KEY_F2               = SDLK_F2,
  KEY_F3               = SDLK_F3,
  KEY_F4               = SDLK_F4,
  KEY_F5               = SDLK_F5,
  KEY_F6               = SDLK_F6,
  KEY_F7               = SDLK_F7,
  KEY_F8               = SDLK_F8,
  KEY_F9               = SDLK_F9,
  KEY_F10              = SDLK_F10,
  KEY_F11              = SDLK_F11,
  KEY_F12              = SDLK_F12,

  KEY_PRINTSCREEN      = SDLK_PRINTSCREEN,
  KEY_SCROLLLOCK       = SDLK_SCROLLLOCK,
  KEY_PAUSE            = SDLK_PAUSE,
  KEY_INSERT           = SDLK_INSERT,
  KEY_HOME             = SDLK_HOME,
  KEY_PAGEUP           = SDLK_PAGEUP,
  KEY_DELETE           = SDLK_DELETE,
  KEY_END              = SDLK_END,
  KEY_PAGEDOWN         = SDLK_PAGEDOWN,
  KEY_RIGHT_ARROW      = SDLK_RIGHT,
  KEY_LEFT_ARROW       = SDLK_LEFT,
  KEY_DOWN_ARROW       = SDLK_DOWN,
  KEY_UP_ARROW         = SDLK_UP,

  KEY_NUMPAD_LOCKCLEAR = SDLK_NUMLOCKCLEAR,
  KEY_NUMPAD_DIVIDE    = SDLK_KP_DIVIDE,
  KEY_NUMPAD_MULTIPLY  = SDLK_KP_MULTIPLY,
  KEY_NUMPAD_MINUS     = SDLK_KP_MINUS,
  KEY_NUMPAD_PLUS      = SDLK_KP_PLUS,
  KEY_NUMPAD_ENTER     = SDLK_KP_ENTER,
  KEY_NUMPAD_PERIOD    = SDLK_KP_PERIOD,
  KEY_NUMPAD_EQUALS    = SDLK_KP_EQUALS,

  KEY_NUMPAD_1         = SDLK_KP_1,
  KEY_NUMPAD_2         = SDLK_KP_2,
  KEY_NUMPAD_3         = SDLK_KP_3,
  KEY_NUMPAD_4         = SDLK_KP_4,
  KEY_NUMPAD_5         = SDLK_KP_5,
  KEY_NUMPAD_6         = SDLK_KP_6,
  KEY_NUMPAD_7         = SDLK_KP_7,
  KEY_NUMPAD_8         = SDLK_KP_8,
  KEY_NUMPAD_9         = SDLK_KP_9,
  KEY_NUMPAD_0         = SDLK_KP_0,

  KEY_LCONTROL         = SDLK_LCTRL,
  KEY_LSHIFT           = SDLK_LSHIFT,
  KEY_LALT             = SDLK_LALT,
  KEY_LGUI             = SDLK_LGUI,
  KEY_RCONTROL         = SDLK_RCTRL,
  KEY_RSHIFT           = SDLK_RSHIFT,
  KEY_RALT             = SDLK_RALT,
  KEY_RGUI             = SDLK_RGUI,

//  		= SDLK_APPLICATION,
//  		= SDLK_POWER,
//
//  		= SDLK_F13,
//  		= SDLK_F14,
//  		= SDLK_F15,
//  		= SDLK_F16,
//  		= SDLK_F17,
//  		= SDLK_F18,
//  		= SDLK_F19,
//  		= SDLK_F20,
//  		= SDLK_F21,
//  		= SDLK_F22,
//  		= SDLK_F23,
//  		= SDLK_F24,
//  		= SDLK_EXECUTE,
//  		= SDLK_HELP,
//  		= SDLK_MENU,
//  		= SDLK_SELECT,
//  		= SDLK_STOP,
//  		= SDLK_AGAIN,
//  		= SDLK_UNDO,
//  		= SDLK_CUT,
//  		= SDLK_COPY,
//  		= SDLK_PASTE,
//  		= SDLK_FIND,
//  		= SDLK_MUTE,
//  		= SDLK_VOLUMEUP,
//  		= SDLK_VOLUMEDOWN,
//  		= SDLK_KP_COMMA,
//  		= SDLK_KP_EQUALSAS400,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),
//  	
//  		= SDLK_ALTERASE,
//  		= SDLK_SYSREQ,
//  		= SDLK_CANCEL,
//  		= SDLK_CLEAR,
//  		= SDLK_PRIOR,
//  		= SDLK_RETURN2,
//  		= SDLK_SEPARATOR,
//  		= SDLK_OUT,
//  		= SDLK_OPER,
//  		= SDLK_CLEARAGAIN,
//  		= SDLK_CRSEL,
//  		= SDLK_EXSEL,
//  	
//  		= SDLK_KP_00,
//  		= SDLK_KP_000,
//  		= SDLK_THOUSANDSSEPARATOR,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
//  		= SDLK_DECIMALSEPARATOR,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
//  		= SDLK_CURRENCYUNIT,
//  		= SDLK_CURRENCYSUBUNIT,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
//  		= SDLK_KP_LEFTPAREN,
//  		= SDLK_KP_RIGHTPAREN,
//  		= SDLK_KP_LEFTBRACE,
//  		= SDLK_KP_RIGHTBRACE,
//  		= SDLK_KP_TAB,
//  		= SDLK_KP_BACKSPACE,
//  		= SDLK_KP_A,
//  		= SDLK_KP_B,
//  		= SDLK_KP_C,
//  		= SDLK_KP_D,
//  		= SDLK_KP_E,
//  		= SDLK_KP_F,
//  		= SDLK_KP_XOR,
//  		= SDLK_KP_POWER,
//  		= SDLK_KP_PERCENT,
//  		= SDLK_KP_LESS,
//  		= SDLK_KP_GREATER,
//  		= SDLK_KP_AMPERSAND,
//  		= SDLK_KP_DBLAMPERSAND,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
//  		= SDLK_KP_VERTICALBAR,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
//  		= SDLK_KP_DBLVERTICALBAR,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
//  		= SDLK_KP_COLON,
//  		= SDLK_KP_HASH,
//  		= SDLK_KP_SPACE,
//  		= SDLK_KP_AT,
//  		= SDLK_KP_EXCLAM,
//  		= SDLK_KP_MEMSTORE,
//  		= SDLK_KP_MEMRECALL,
//  		= SDLK_KP_MEMCLEAR,
//  		= SDLK_KP_MEMADD,
//  		= SDLK_KP_MEMSUBTRACT,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
//  		= SDLK_KP_MEMMULTIPLY,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
//  		= SDLK_KP_MEMDIVIDE,
//  		= SDLK_KP_PLUSMINUS,
//  		= SDLK_KP_CLEAR,
//  		= SDLK_KP_CLEARENTRY,
//  		= SDLK_KP_BINARY,
//  		= SDLK_KP_OCTAL,
//  		= SDLK_KP_DECIMAL,
//  		= SDLK_KP_HEXADECIMAL,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),
//  	
//
//  	
//  		= SDLK_MODE,
//  	
//  		= SDLK_AUDIONEXT,
//  		= SDLK_AUDIOPREV,
//  		= SDLK_AUDIOSTOP,
//  		= SDLK_AUDIOPLAY,
//  		= SDLK_AUDIOMUTE,
//  		= SDLK_MEDIASELECT,
//  		= SDLK_WWW,
//  		= SDLK_MAIL,
//  		= SDLK_CALCULATOR,
//  		= SDLK_COMPUTER,
//  		= SDLK_AC_SEARCH,
//  		= SDLK_AC_HOME,
//  		= SDLK_AC_BACK,
//  		= SDLK_AC_FORWARD,
//  		= SDLK_AC_STOP,
//  		= SDLK_AC_REFRESH,
//  		= SDLK_AC_BOOKMARKS,
//  	
//  		= SDLK_BRIGHTNESSDOWN,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
//  		= SDLK_BRIGHTNESSUP,
//  		= SDLK_DISPLAYSWITCH,
//  		= SDLK_KBDILLUMTOGGLE,
//  		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
//  		= SDLK_KBDILLUMDOWN,
//  		= SDLK_KBDILLUMUP,
//  		= SDLK_EJECT,
//  		= Sleep_Key,
};

class Input {
  /**
   *  Private constructor
   */
  Input(){};

public:
  
  /**
   *   Updates and saves the keyboard state within _keyState 
   *   as well asupdates mouse state and position with the
   *   variables _mouseState and _mousePosition
   */
  static inline void Update() {
    int x, y;

    while (SDL_PollEvent(&_input._event)) {
      if (_input._event.type == SDL_KEYUP) {
        _input._isPressed[code(_input._event.key.keysym.sym)] = false;
      }
    }
    int i = 0;
    _input._keyState = (Uint8 *)SDL_GetKeyboardState(&i);
    _input._mouseState = SDL_GetMouseState(&x, &y);
    _input._mousePosition.x = x;
    _input._mousePosition.y = y;
  }

  /**
   *  Checks if a quit event was triggered and ends the game
   *
   *  @return Returns True if a quit event was triggered
   */
  static inline bool Quit() { return _input._event.type == SDL_QUIT; }

  /**
   *  Checks if a key was pressed but not if hold. To handle
   *  a key that is being held down, use KeyDown().
   *
   *  @param key Any value from the KeyCode enum.
   *
   *  @return Returns true once if the key was pressed.
   */
  static inline bool KeyPressed(KeyCode key) {
    unsigned int keyCode = code(key);
    if (_input._keyState[keyCode]) {
      if (_input._isPressed[keyCode]) {
        return false;
      } else {
        return _input._isPressed[keyCode] = true;
      }
    }
    return false;
  }

  /**
   *  Checks if a key was realesed.
   *
   *  @param key Any value from the KeyCode enum.
   *
   *  @return Returns True if the key was released.
   */
  static inline bool KeyReleased(KeyCode key) {
    return _input._event.type == SDL_KEYUP and
           _input._event.key.keysym.sym == key;
  }


  /**
   *  Checks if a key is being held down.
   *
   *  @param key Any value from the KeyCode enum.
   *
   *  @return Returns True if the key is pressed.
   */
  static inline bool KeyDown(KeyCode key) {
    return _input._keyState[code(key)];
  }

  /**
   *  Checks if a mouse button is beign held down. To handle
   *  a button that is being held down, use MouseButtonPressed().
   *
   *  @param key Any value from the MouseInput enum.
   *
   *  @return Returns true once if the button was pressed.
   */
  static inline bool MouseButton(MouseInput button) {
    return _input._event.type == SDL_MOUSEBUTTONUP and
           _input._event.button.button == button;
  }

  /**
   *  Checks if a mouse button is beign held down.
   *
   *  @param button Any value from the MouseInput enum.
   *
   *  @return Return True if the mouse button is pressed
   */
  static inline bool MouseButtonPressed(MouseInput button) {
    return _input._mouseState & SDL_BUTTON(button);
  }

  /**
   *  Checks if a mouse button was released
   *
   *  @param button Any value from the MouseInput enum.
   *
   *  @return Return True if the mouse button was released
   */
  static inline bool MouseButtonReleased(MouseInput button) {
    return _input._event.type == SDL_MOUSEBUTTONUP and
           _input._event.button.button == button;
  }

  /**
   *  Gets the cursor position of the last click.
   *
   *  @return Returns a Vector2 with the position of the last click.
   */
  static inline Vector2 GetMouseClickPosition() {
    return _input._mousePosition;
  }
  
  
  static inline Vector2 GetAxis(){
    Vector2 v = Vector2(0,0);
    if (_input._keyState[code(KEY_LEFT_ARROW)]){
      v.x -= 1;
    }
    if (_input._keyState[code(KEY_RIGHT_ARROW)]){
      v.x += 1;
    }
    if (_input._keyState[code(KEY_UP_ARROW)]){
      v.y -= 1;
    }
    if (_input._keyState[code(KEY_DOWN_ARROW)]){
      v.y += 1;
    }
    return v;
  }

private:
  static Input _input;          /// Global input handler
  
  SDL_Event _event;             /// Events handler
  Vector2  _mousePosition;     /// Mouse Position
  bool      _isPressed[512];    /// Array that store which keys are already pressed
  Uint8    *_keyState   = NULL; /// Keyboard State
  Uint32    _mouseState = 0;    /// Mouse's Key State
};
}

#endif

#endif /* Input_hpp */
