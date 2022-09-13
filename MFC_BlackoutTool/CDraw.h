#pragma once
class CDraw
{
public:
	void Draw(Gdiplus::Graphics& memDC, CWnd* cwnd, Color color);
	void Brush(Gdiplus::Graphics& memDC);
	

public:
	vector<Gdiplus::Point> m_vPoint;
	int m_nType;
};

