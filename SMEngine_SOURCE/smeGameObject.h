#pragma once

#include "CommonInclude.h"

namespace smeApp
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void SetPosition(float x, float y) { pos_x = x; pos_y = y; }
		float GetPositionX() { return pos_x; }
		float GetPositionY() { return pos_y; }

	private:
		float pos_x;
		float pos_y;

	};

}

