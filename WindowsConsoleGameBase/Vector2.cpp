#include "Vector2.h"

Vector2::Vector2()
	: m_X(0)
	, m_Y(0) {

}

Vector2::Vector2(PointType x, PointType y)
	: m_X(x)
	, m_Y(y) {

}

Vector2::PointType Vector2::x() const {
	return m_X;
}

Vector2::PointType Vector2::y() const {
	return m_Y;
}

Vector2::PointType& Vector2::x() {
	return m_X;
}

Vector2::PointType& Vector2::y() {
	return m_Y;
}
