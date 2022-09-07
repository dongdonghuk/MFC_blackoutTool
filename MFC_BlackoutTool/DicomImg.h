#pragma once
class DicomImg
{
public:
	Mat m_dcmImg;
	shared_ptr<Bitmap> m_bitImg;
	shared_ptr<DicomImage> m_ptrDicomImage;

	CString m_dcmName;
	CString m_dcmPath;
	int m_nFrame;
	CPoint m_pt;
	double m_dAligmentRate;

public:
	DicomImg();
	~DicomImg();

public:
	void ImgAlignment(CRect& rect);
	void dcmRead(CString filePath, CString fileName);
	void DrawImage(Graphics& g, Graphics& memDC, CWnd* cwnd);
	BOOL empty();


};

