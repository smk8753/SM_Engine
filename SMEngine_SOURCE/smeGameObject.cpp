#include "smeGameObject.h"
#include "smeInput.h"

namespace smeApp
{
	GameObject::GameObject()
	{

	}

	GameObject::~GameObject()
	{

	}

	void GameObject::Update()
	{
		if (Input::GetKey(eKeyCode::A))
		{
			pos_x -= 0.01f;
		}

		if (Input::GetKey(eKeyCode::D))
		{
			pos_x += 0.01f;
		}

		if (Input::GetKey(eKeyCode::W))
		{
			pos_y -= 0.01f;
		}

		if (Input::GetKey(eKeyCode::S))
		{
			pos_y += 0.01f;
		}
	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render(HDC hdc)
	{
		HBRUSH grayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, grayBrush);

		Rectangle(hdc, pos_x, pos_y, pos_x + 50.0f, pos_y + 50.0f);

		SelectObject(hdc, oldBrush);
		DeleteObject(grayBrush);
	}

}