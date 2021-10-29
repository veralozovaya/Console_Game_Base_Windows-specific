#include "Square.h"

Square::Square(const Vector2& position, const Size& size)
	: m_Position(position)
	, m_Size(size) {
}

bool Square::hit(const Vector2& point) const {
	return point.x() >= top_left().x() && point.x() <= bottom_right().x()
		&& point.y() >= top_left().y() && point.y() <= bottom_right().y();
}

Vector2 Square::top_left() const {
	return m_Position;
}

Vector2 Square::bottom_right() const {
	return Vector2(m_Position.x() + m_Size.width(), m_Position.y() + m_Size.height()) + Vector2(-1, -1);
}

bool Square::collide(const Square& other) const {
	const bool xProjectionCollide =
		top_left().x() <= other.bottom_right().x() && bottom_right().x() >= other.top_left().x();
	const bool yProjectionCollide =
		top_left().y() <= other.bottom_right().y() && bottom_right().y() >= other.top_left().y();

	return xProjectionCollide && yProjectionCollide;
}
