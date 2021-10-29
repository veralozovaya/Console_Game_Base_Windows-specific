#pragma once

class Size {
	using PointType = long long int;
public:
	Size(PointType width, PointType height);

	PointType width() const;
	PointType height() const;

	PointType& width();
	PointType& height();

	PointType area() const;

private:
	PointType m_Width;
	PointType m_Height;
};

