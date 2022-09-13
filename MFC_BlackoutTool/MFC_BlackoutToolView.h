
// MFC_BlackoutToolView.h: CMFCBlackoutToolView 클래스의 인터페이스
//

#pragma once
#include "MFC_BlackoutToolDoc.h"



class CMFCBlackoutToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCBlackoutToolView() noexcept;
	DECLARE_DYNCREATE(CMFCBlackoutToolView)

// 특성입니다.
public:
	CMFCBlackoutToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCBlackoutToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // MFC_BlackoutToolView.cpp의 디버그 버전
inline CMFCBlackoutToolDoc* CMFCBlackoutToolView::GetDocument() const
   { return reinterpret_cast<CMFCBlackoutToolDoc*>(m_pDocument); }
#endif

