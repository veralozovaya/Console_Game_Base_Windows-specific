#include "Size.h"

Size::Size(PointType width, PointType height) 
	: m_Width(width)
	, m_Height(height) {

}

Size::PointType Size::width() const {
	return m_Width;
}

Size::PointType Size::height() const {
	return m_Height;
}

Size::PointType& Size::width() {
	return m_Width;
}

Size::PointType& Size::height() {
	return m_Height;
}

Size::PointType Size::area() const {
	return width() * height();
}
