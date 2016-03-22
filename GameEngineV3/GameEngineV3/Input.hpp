//
//  Input.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 3/21/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include "GE_SDL.hpp"
#include "Vector.hpp"

enum MouseInput {
	MOUSE_LEFT_BUTTON = SDL_BUTTON_LEFT,
	MOUSE_MIDDLE_BUTTON = SDL_BUTTON_MIDDLE,
	MOUSE_RIGHT_BUTTON = SDL_BUTTON_RIGHT
};
enum KeyCode
{
	KEY_UNKNOW = SDLK_UNKNOWN,
	KEY_RETURN = SDLK_RETURN,
	KEY_ESCAPE = SDLK_ESCAPE,
	KEY_BACKSPACE = SDLK_BACKSPACE,
	KEY_TAB = SDLK_TAB,
	KEY_SPACE = SDLK_SPACE,
	KEY_EXCLAIN = SDLK_EXCLAIM,
	KEY_QUOTEDBL = SDLK_QUOTEDBL,
	KEY_HASH = SDLK_HASH,
	KEY_PERCENT = SDLK_PERCENT,
	KEY_DOLLAR = SDLK_DOLLAR,
	KEY_AMPERSAND = SDLK_AMPERSAND,
	KEY_QUOTE = SDLK_QUOTE,
	KEY_LEFTPARENTHESIS = SDLK_LEFTPAREN,
	KEY_RIGHTPARENTHESIS = SDLK_RIGHTPAREN,
	KEY_STERISK = SDLK_ASTERISK,
	KEY_PLUS = SDLK_PLUS,
	KEY_COMMA = SDLK_COMMA,
	KEY_MINUS = SDLK_MINUS,
	KEY_PERIOD = SDLK_PERIOD,
	KEY_SPLASH = SDLK_SLASH,
	KEY_0 = SDLK_0,
	KEY_1 = SDLK_1,
	KEY_2 = SDLK_2,
	KEY_3 = SDLK_3,
	KEY_4 = SDLK_4,
	KEY_5 = SDLK_5,
	KEY_6 = SDLK_6,
	KEY_7 = SDLK_7,
	KEY_8 = SDLK_8,
	KEY_9 = SDLK_9,
	KEY_COLON= SDLK_COLON,
	KEY_SEMICOLON = SDLK_SEMICOLON,
	KEY_LESS = SDLK_LESS,
	KEY_EQUALS = SDLK_EQUALS,
	KEY_GREATER = SDLK_GREATER,
	KEY_QUESTION = SDLK_QUESTION,
	KEY_AT = SDLK_AT,
	/*
	 Skip uppercase letters
	 */
	KEY_LEFTBRACKET = SDLK_LEFTBRACKET,
	KEY_BACKSLASH = SDLK_BACKSLASH,
	KEY_RIGHTBRACKET = SDLK_RIGHTBRACKET,
	KEY_CARET = SDLK_CARET,
	KEY_UNDERSCORE = SDLK_UNDERSCORE,
	KEY_BACKQUOTE = SDLK_BACKQUOTE,
	KEY_A = SDLK_a,
	KEY_B = SDLK_b,
	KEY_C = SDLK_c,
	KEY_D = SDLK_d,
	KEY_E = SDLK_e,
	KEY_F = SDLK_f,
	KEY_G = SDLK_g,
	KEY_H = SDLK_h,
	KEY_I = SDLK_i,
	KEY_J = SDLK_j,
	KEY_K = SDLK_k,
	KEY_L = SDLK_l,
	KEY_M = SDLK_m,
	KEY_N = SDLK_n,
	KEY_O = SDLK_o,
	KEY_P = SDLK_p,
	KEY_Q = SDLK_q,
	KEY_R = SDLK_r,
	KEY_S = SDLK_s,
	KEY_T = SDLK_t,
	KEY_U = SDLK_u,
	KEY_V = SDLK_v,
	KEY_W = SDLK_w,
	KEY_X = SDLK_x,
	KEY_Y = SDLK_y,
	KEY_Z = SDLK_z,
	
	KEY_CAPSLOCK = SDLK_CAPSLOCK,
	
	KEY_F1 = SDLK_F1,
	KEY_F2 = SDLK_F2,
	KEY_F3 = SDLK_F3,
	KEY_F4 = SDLK_F4,
	KEY_F5 = SDLK_F5,
	KEY_F6 = SDLK_F6,
	KEY_F7 = SDLK_F7,
	KEY_F8 = SDLK_F8,
	KEY_F9 = SDLK_F9,
	KEY_F10 = SDLK_F10,
	KEY_F11 = SDLK_F11,
	KEY_F12 = SDLK_F12,
	
	KEY_PRINTSCREEN = SDLK_PRINTSCREEN,
	KEY_SCROLLLOCK = SDLK_SCROLLLOCK,
	KEY_PAUSE = SDLK_PAUSE,
	KEY_INSERT = SDLK_INSERT,
	KEY_HOME = SDLK_HOME,
	KEY_PAGEUP = SDLK_PAGEUP,
	KEY_DELETE = SDLK_DELETE,
	KEY_END = SDLK_END,
	KEY_PAGEDOWN = SDLK_PAGEDOWN,
	KEY_RIGHT_ARROW = SDLK_RIGHT,
	KEY_LEFT_ARROW = SDLK_LEFT,
	KEY_DOWN_ARROW = SDLK_DOWN,
	KEY_UP_ARROW   = SDLK_UP,
	
	KEY_NUMPAD_LOCKCLEAR = SDLK_NUMLOCKCLEAR,
	KEY_NUMPAD_DIVIDE = SDLK_KP_DIVIDE,
	KEY_NUMPAD_MULTIPLY = SDLK_KP_MULTIPLY,
	KEY_NUMPAD_MINUS = SDLK_KP_MINUS,
	KEY_NUMPAD_PLUS = SDLK_KP_PLUS,
	KEY_NUMPAD_ENTER = SDLK_KP_ENTER,
	KEY_NUMPAD_1 = SDLK_KP_1,
	KEY_NUMPAD_2 = SDLK_KP_2,
	KEY_NUMPAD_3 = SDLK_KP_3,
	KEY_NUMPAD_4 = SDLK_KP_4,
	KEY_NUMPAD_5 = SDLK_KP_5,
	KEY_NUMPAD_6 = SDLK_KP_6,
	KEY_NUMPAD_7 = SDLK_KP_7,
	KEY_NUMPAD_8 = SDLK_KP_8,
	KEY_NUMPAD_9 = SDLK_KP_9,
	KEY_NUMPAD_0 = SDLK_KP_0,
	KEY_NUMPAD_PERIOD = SDLK_KP_PERIOD,
//
//	//	= SDLK_APPLICATION,
//	//	= SDLK_POWER,
//	//	= SDLK_KP_EQUALS,
//	//	= SDLK_F13,
//	//	= SDLK_F14,
//	//	= SDLK_F15,
//	//	= SDLK_F16,
//	//	= SDLK_F17,
//	//	= SDLK_F18,
//	//	= SDLK_F19,
//	//	= SDLK_F20,
//	//	= SDLK_F21,
//	//	= SDLK_F22,
//	//	= SDLK_F23,
//	//	= SDLK_F24,
//	//	= SDLK_EXECUTE,
//	//	= SDLK_HELP,
//	//	= SDLK_MENU,
//	//	= SDLK_SELECT,
//	//	= SDLK_STOP,
//	//	= SDLK_AGAIN,
//	//	= SDLK_UNDO,
//	//	= SDLK_CUT,
//	//	= SDLK_COPY,
//	//	= SDLK_PASTE,
//	//	= SDLK_FIND,
//	//	= SDLK_MUTE,
//	//	= SDLK_VOLUMEUP,
//	//	= SDLK_VOLUMEDOWN,
//	//	= SDLK_KP_COMMA,
//	//	= SDLK_KP_EQUALSAS400,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),
//	//
//	//	= SDLK_ALTERASE,
//	//	= SDLK_SYSREQ,
//	//	= SDLK_CANCEL,
//	//	= SDLK_CLEAR,
//	//	= SDLK_PRIOR,
//	//	= SDLK_RETURN2,
//	//	= SDLK_SEPARATOR,
//	//	= SDLK_OUT,
//	//	= SDLK_OPER,
//	//	= SDLK_CLEARAGAIN,
//	//	= SDLK_CRSEL,
//	//	= SDLK_EXSEL,
//	//
//	//	= SDLK_KP_00,
//	//	= SDLK_KP_000,
//	//	= SDLK_THOUSANDSSEPARATOR,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
//	//	= SDLK_DECIMALSEPARATOR,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
//	//	= SDLK_CURRENCYUNIT,
//	//	= SDLK_CURRENCYSUBUNIT,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
//	//	= SDLK_KP_LEFTPAREN,
//	//	= SDLK_KP_RIGHTPAREN,
//	//	= SDLK_KP_LEFTBRACE,
//	//	= SDLK_KP_RIGHTBRACE,
//	//	= SDLK_KP_TAB,
//	//	= SDLK_KP_BACKSPACE,
//	//	= SDLK_KP_A,
//	//	= SDLK_KP_B,
//	//	= SDLK_KP_C,
//	//	= SDLK_KP_D,
//	//	= SDLK_KP_E,
//	//	= SDLK_KP_F,
//	//	= SDLK_KP_XOR,
//	//	= SDLK_KP_POWER,
//	//	= SDLK_KP_PERCENT,
//	//	= SDLK_KP_LESS,
//	//	= SDLK_KP_GREATER,
//	//	= SDLK_KP_AMPERSAND,
//	//	= SDLK_KP_DBLAMPERSAND,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
//	//	= SDLK_KP_VERTICALBAR,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
//	//	= SDLK_KP_DBLVERTICALBAR,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
//	//	= SDLK_KP_COLON,
//	//	= SDLK_KP_HASH,
//	//	= SDLK_KP_SPACE,
//	//	= SDLK_KP_AT,
//	//	= SDLK_KP_EXCLAM,
//	//	= SDLK_KP_MEMSTORE,
//	//	= SDLK_KP_MEMRECALL,
//	//	= SDLK_KP_MEMCLEAR,
//	//	= SDLK_KP_MEMADD,
//	//	= SDLK_KP_MEMSUBTRACT,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
//	//	= SDLK_KP_MEMMULTIPLY,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
//	//	= SDLK_KP_MEMDIVIDE,
//	//	= SDLK_KP_PLUSMINUS,
//	//	= SDLK_KP_CLEAR,
//	//	= SDLK_KP_CLEARENTRY,
//	//	= SDLK_KP_BINARY,
//	//	= SDLK_KP_OCTAL,
//	//	= SDLK_KP_DECIMAL,
//	//	= SDLK_KP_HEXADECIMAL,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),
//	//
//	//	= SDLK_LCTRL,
//	//	= SDLK_LSHIFT,
//	//	= SDLK_LALT,
//	//	= SDLK_LGUI,
//	//	= SDLK_RCTRL,
//	//	= SDLK_RSHIFT,
//	//	= SDLK_RALT,
//	//	= SDLK_RGUI,
//	//
//	//	= SDLK_MODE,
//	//
//	//	= SDLK_AUDIONEXT,
//	//	= SDLK_AUDIOPREV,
//	//	= SDLK_AUDIOSTOP,
//	//	= SDLK_AUDIOPLAY,
//	//	= SDLK_AUDIOMUTE,
//	//	= SDLK_MEDIASELECT,
//	//	= SDLK_WWW,
//	//	= SDLK_MAIL,
//	//	= SDLK_CALCULATOR,
//	//	= SDLK_COMPUTER,
//	//	= SDLK_AC_SEARCH,
//	//	= SDLK_AC_HOME,
//	//	= SDLK_AC_BACK,
//	//	= SDLK_AC_FORWARD,
//	//	= SDLK_AC_STOP,
//	//	= SDLK_AC_REFRESH,
//	//	= SDLK_AC_BOOKMARKS,
//	//
//	//	= SDLK_BRIGHTNESSDOWN,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
//	//	= SDLK_BRIGHTNESSUP,
//	//	= SDLK_DISPLAYSWITCH,
//	//	= SDLK_KBDILLUMTOGGLE,
//	//	SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
//	//	= SDLK_KBDILLUMDOWN,
//	//	= SDLK_KBDILLUMUP,
//	//	= SDLK_EJECT,
//	//	= Sleep_Key,
};

class Input {
	
public:
	Input(){};
	
	inline void Update(){
		SDL_PollEvent(&event);
		key_state = (Uint8*)SDL_GetKeyboardState(NULL);

	}
	inline bool Quit(){
		return event.type == SDL_QUIT;
	}
	inline bool KeyPressed(KeyCode key){
		if (event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == key){
			return true;
		}
		return false;
	}
	inline bool KeyReleased(KeyCode key){
		if (event.type == SDL_KEYUP &&
			event.key.keysym.sym == key){
			return true;
		}
		return false;
	}
	
	inline bool KeyDown(KeyCode key){
		if (key_state[SDL_GetScancodeFromKey(key)]){
			return true;
		}
		return false;
	}
	
	
	inline bool MouseButtonPressed(MouseInput button){
		if (event.type == SDL_MOUSEBUTTONDOWN &&
			event.button.button == button) {
			return true;
		}
		return false;
	}
	
	inline bool MouseButtonReleased(MouseInput button){
		if (event.type == SDL_MOUSEBUTTONUP &&
			event.button.button == button) {
			return true;
		}
		return false;
	}
	
	inline bool MouseButton(MouseInput button){
		if (event.type == SDL_MOUSEBUTTONUP &&
			event.button.button == button) {
			return true;
		}
		return false;
	}
	
	inline Vector2D GetMouseClickPosition(MouseInput){
		return Vector2D (event.button.x, event.button.y);
	}
	
private:
	SDL_Event event;
	Uint8 *key_state = NULL;
	
	
};



#endif /* Input_hpp */
