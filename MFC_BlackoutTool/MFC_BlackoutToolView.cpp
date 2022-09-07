
// MFC_BlackoutToolView.cpp: CMFCBlackoutToolView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_BlackoutTool.h"
#endif

#include "MFC_BlackoutToolDoc.h"
#include "MFC_BlackoutToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBlackoutToolView

IMPLEMENT_DYNCREATE(CMFCBlackoutToolView, CView)

BEGIN_MESSAGE_MAP(CMFCBlackoutToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_COMMAND(IDM_DRAW_RECT, &CMFCBlackoutToolView::OnDrawRect)
	ON_WM_MOUSEMOVE()
//	ON_COMMAND(IDM_DRAW_MOUSE, &CMFCBlackoutToolView::OnDrawMouse)
END_MESSAGE_MAP()

// CMFCBlackoutToolView 생성/소멸

CMFCBlackoutToolView::CMFCBlackoutToolView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCBlackoutToolView::~CMFCBlackoutToolView()
{
}

BOOL CMFCBlackoutToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCBlackoutToolView 그리기

void CMFCBlackoutToolView::OnDraw(CDC* pDC)
{
	CMFCBlackoutToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	Graphics g(pDC->m_hDC);

	CRect rectDraw;		// 사각형 도화지 준비
	GetClientRect(rectDraw);	// 도화지 선언
	Bitmap memBit(rectDraw.Width(), rectDraw.Height());
	Graphics memDC(&memBit);	// 메모리bitmap
	Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 0, 0, 0));
	memDC.FillRectangle(&blackBrush, 0, 0, memBit.GetWidth(), memBit.GetHeight());	// 도화지 == 검은색

	pDoc->m_dcmImg.DrawImage(g, memDC, this);
	

	if (pDoc->m_drawTmp.m_nType)
	{
		Color color(124, 247, 0);
		pDoc->m_drawTmp.Draw(memDC, this, color);
	}

	Color color(128, 0, 0);

	for (auto m_Cdraw : pDoc->m_vCdraw) {
		m_Cdraw.Draw(memDC, this, color);
		m_Cdraw.Brush(memDC);
	}

	g.DrawImage(&memBit, 0, 0);

}


// CMFCBlackoutToolView 인쇄

BOOL CMFCBlackoutToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCBlackoutToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCBlackoutToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCBlackoutToolView 진단

#ifdef _DEBUG
void CMFCBlackoutToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCBlackoutToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCBlackoutToolDoc* CMFCBlackoutToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCBlackoutToolDoc)));
	return (CMFCBlackoutToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCBlackoutToolView 메시지 처리기


void CMFCBlackoutToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCBlackoutToolDoc* pDoc = GetDocument();
	
	if (!(pDoc->m_dcmImg.empty())) {
		if (pDoc->m_nDrawType == IDM_DRAW_RECT) {

			//SetCapture();

			CRect  rc;
			POINT p1, p2;

			GetClientRect(&rc);    // 클라이언트 크기

			// 클라이언트 크기를 좌표로 변환
			p1.x = rc.left;
			p1.y = rc.top;
			p2.x = rc.right;
			p2.y = rc.bottom;

			// 클라이언트 크기를 스크린 크기로 변환
			ClientToScreen(&p1);
			ClientToScreen(&p2);

			rc.left = p1.x;
			rc.top = p1.y;
			rc.right = p2.x;
			rc.bottom = p2.y;

			//해당 좌표를 기준으로 커서를 고정
			ClipCursor(&rc);


			point.x = (point.x - pDoc->m_dcmImg.m_pt.x) / (pDoc->m_dcmImg.m_dAligmentRate);
			point.y = (point.y - pDoc->m_dcmImg.m_pt.y) / (pDoc->m_dcmImg.m_dAligmentRate);


			pDoc->m_drawTmp.m_nType = 1;

			pDoc->m_drawTmp.m_vPoint.reserve(4);
			pDoc->m_drawTmp.m_vPoint.resize(4);

			pDoc->m_drawTmp.m_vPoint[0] = (Gdiplus::Point(point.x, point.y));

		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMFCBlackoutToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCBlackoutToolDoc* pDoc = GetDocument();

	if (!(pDoc->m_dcmImg.empty())) {

		if (pDoc->m_nDrawType == IDM_DRAW_RECT && pDoc->m_drawTmp.m_nType) {

			point.x = (point.x - pDoc->m_dcmImg.m_pt.x) / (pDoc->m_dcmImg.m_dAligmentRate);
			point.y = (point.y - pDoc->m_dcmImg.m_pt.y) / (pDoc->m_dcmImg.m_dAligmentRate);

			pDoc->m_drawTmp.m_vPoint[2] = (Gdiplus::Point(point.x, point.y));

			pDoc->m_vCdraw.push_back(pDoc->m_drawTmp);
			pDoc->m_drawTmp.m_vPoint.clear();
			pDoc->m_drawTmp.m_nType = 0;

			//ReleaseCapture();
			ClipCursor(NULL);
		}

		Invalidate(false);
	}


	CView::OnLButtonUp(nFlags, point);
}

void CMFCBlackoutToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCBlackoutToolDoc* pDoc = GetDocument();

	if (!(pDoc->m_dcmImg.empty())) {
		if (pDoc->m_nDrawType == IDM_DRAW_RECT && ((nFlags & MK_LBUTTON) == MK_LBUTTON) && pDoc->m_drawTmp.m_nType) {
			point.x = (point.x - pDoc->m_dcmImg.m_pt.x) / (pDoc->m_dcmImg.m_dAligmentRate);
			point.y = (point.y - pDoc->m_dcmImg.m_pt.y) / (pDoc->m_dcmImg.m_dAligmentRate);


			pDoc->m_drawTmp.m_vPoint[2] = (Gdiplus::Point(point.x, point.y));

			Invalidate(FALSE);
		}
	}

	CView::OnMouseMove(nFlags, point);
}

