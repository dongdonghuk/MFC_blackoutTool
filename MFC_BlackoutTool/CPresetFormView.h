#pragma once
#include "MFC_BlackoutToolDoc.h"


// CPresetFormView 폼 보기

class CPresetFormView : public CFormView
{
	DECLARE_DYNCREATE(CPresetFormView)

protected:
	CPresetFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CPresetFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPresetFormView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//CMFCBlackoutToolDoc* GetDocument() const;

	CString m_strManufacturer;
	CString m_strModel;
	CString m_strSize;
};

//#ifndef _DEBUG  // MFC_BlackoutToolView.cpp의 디버그 버전
//inline CMFCBlackoutToolDoc* CPresetFormView::GetDocument() const
//{
//	return reinterpret_cast<CMFCBlackoutToolDoc*>(m_pDocument);
//}
//#endif
