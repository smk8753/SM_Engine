#pragma once
#include "CommonInclude.h"

namespace smeApp
{
	enum class eKeyState
	{
		KeyDown,
		KeyPressed,
		KeyUp,
		None,
	};

	enum class eKeyCode
	{
		// 모든 키 추가해보기...
		//Escape, 
		//F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		//Print, Delete, Insert,
		//BackQuote,
		//Alpha1, Alpha2, Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9, Alpha0,
		//Minus, Equals, Backspace,
		//.....
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		End,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode	keyCode;
			eKeyState	keyState;
			bool		keyPressed;
		};

		static void Initailize();
		static void Update();

		static bool GetKeyDown(eKeyCode code)	 
		{ return Keys[(UINT)code].keyState == eKeyState::KeyDown; }
		static bool GetKey(eKeyCode code)		
		{ return Keys[(UINT)code].keyState == eKeyState::KeyPressed; }
		static bool GetKeyUp(eKeyCode code)		
		{ return Keys[(UINT)code].keyState == eKeyState::KeyUp; }

	private:
		static void initKeys();
		static void updateKeys();
		static void updateKey(Input::Key& key);
		static bool isKeyDown(eKeyCode code);
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);

	private:
		static std::vector<Key> Keys;
	};

}
