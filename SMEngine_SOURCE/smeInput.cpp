#include "smeInput.h"

namespace smeApp
{
	std::vector<Input::Key> Input::Keys = {};

	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};

	void Input::Initailize()
	{
		initKeys();
	}

	void Input::Update()
	{
		updateKeys();
	}

	void Input::initKeys()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
		{
			Key key = {};
			key.keyCode = (eKeyCode)i;
			key.keyState = eKeyState::None;
			key.keyPressed = false;

			Keys.push_back(key);
		}
	}

	void Input::updateKeys()
	{
		std::for_each(Keys.begin(), Keys.end(),
			[](Key& key) -> void
			{
				updateKey(key);
			});

		for (size_t i = 0; i < Keys.size(); i++)
		{
			// Key pressed
			if (GetAsyncKeyState(ASCII[i]) && 0x8000)
			{
				if (Keys[i].keyPressed)
					Keys[i].keyState = eKeyState::KeyPressed;
				else
					Keys[i].keyState = eKeyState::KeyDown;

				Keys[i].keyPressed = true;
			}
			// Key not pressed
			else
			{
				if (Keys[i].keyPressed)
					Keys[i].keyState = eKeyState::KeyUp;
				else
					Keys[i].keyState = eKeyState::None;

				Keys[i].keyPressed = false;
			}
		}
	}

	void Input::updateKey(Input::Key& key)
	{
		if (isKeyDown(key.keyCode))
			updateKeyDown(key);
		else
			updateKeyUp(key);
	}

	bool Input::isKeyDown(eKeyCode code)
	{
		return GetAsyncKeyState(ASCII[(UINT)code]) && 0x8000;
	}

	void Input::updateKeyDown(Input::Key& key)
	{
		if (key.keyPressed)
			key.keyState = eKeyState::KeyPressed;
		else
			key.keyState = eKeyState::KeyDown;

		key.keyPressed = true;
	}

	void Input::updateKeyUp(Input::Key& key)
	{
		if (key.keyPressed)
			key.keyState = eKeyState::KeyUp;
		else
			key.keyState = eKeyState::None;

		key.keyPressed = false;
	}
}