#pragma once

class Vector2 {
	using PointType = long long int;
public:
	Vector2();
	Vector2(PointType x, PointType y);

	PointType x() const;
	PointType y() const;

	PointType& x();
	PointType& y();

private:
	PointType m_X;
	PointType m_Y;
};
