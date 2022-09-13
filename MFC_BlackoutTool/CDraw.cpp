#include "pch.h"
#include "CDraw.h"

void CDraw::Draw(Gdiplus::Graphics& memDC, CWnd* cwnd, Color color) {

	int thick = 2;

	Pen pen(color, thick);

	// »ç°¢Çü
	if (m_nType == 1) {

		m_vPoint[1] = Gdiplus::Point(m_vPoint[0].X, m_vPoint[2].Y);
		m_vPoint[3] = Gdiplus::Point(m_vPoint[2].X, m_vPoint[0].Y);

		memDC.DrawPolygon(&pen, m_vPoint.data(),4);

	}
}

void CDraw::Brush(Gdiplus::Graphics& memDC) {

	HatchBrush myHatchBrush(
		HatchStyleDiagonalCross,
		Color(150, 0, 0, 255),
		Color(0, 0, 0, 0));

	memDC.FillPolygon(&myHatchBrush, m_vPoint.data(), 4);
}


