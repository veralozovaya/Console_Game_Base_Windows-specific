#pragma once
#include <ostream>

class Vector2 {
	using PointType = long long int;
	friend bool operator==(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator+(Vector2 lhs, const Vector2& rhs);
	friend Vector2 operator-(Vector2 lhs, const Vector2& rhs);

public:
	Vector2();
	Vector2(PointType x, PointType y);

	PointType x() const;
	PointType y() const;

	PointType& x();
	PointType& y();

	Vector2 operator*(const Vector2::PointType& rhs) const
	{
		return Vector2(m_X * rhs, m_Y * rhs);
	}

	Vector2& operator+=(const Vector2& rhs) {
		m_X += rhs.m_X;
		m_Y += rhs.m_Y;
		return *this;
	}

	Vector2& operator-=(const Vector2& rhs) {
		m_X -= rhs.m_X;
		m_Y -= rhs.m_Y;
		return *this;
	}

private:
	PointType m_X;
	PointType m_Y;
};

bool operator==(const Vector2& lhs, const Vector2& rhs);
bool operator!=(const Vector2& lhs, const Vector2& rhs);

Vector2 operator+(Vector2 lhs, const Vector2& rhs);
Vector2 operator-(Vector2 lhs, const Vector2& rhs);

std::ostream& operator<<(std::ostream& os, const Vector2& obj);
