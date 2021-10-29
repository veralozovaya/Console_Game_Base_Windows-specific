#pragma once
#include "Vector2.h"
#include "Size.h"

class Square {
public:
	Square(const Vector2& position, const Size& size);

	bool hit(const Vector2& point) const;
	bool collide(const Square& other) const;

	Vector2 top_left() const;
	Vector2 bottom_right() const;

private:
	Vector2 m_Position;
	Size m_Size;
};

