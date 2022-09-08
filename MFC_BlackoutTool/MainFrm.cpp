
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFC_BlackoutTool.h"
#include "MFC_BlackoutToolView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	m_bViewsExist = FALSE;

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("도구 모음을 만들지 못했습니다.\n");
	//	return -1;      // 만들지 못했습니다.
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("상태 표시줄을 만들지 못했습니다.\n");
	//	return -1;      // 만들지 못했습니다.
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기





BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (!m_wndSplitter1.CreateStatic(this, 1, 3))
	{
		//TRACE0("Fail to create splitter.\n");
		return FALSE;
	}

	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter1, 3, 1, WS_CHILD | WS_VISIBLE | WS_BORDER, m_wndSplitter1.IdFromRowCol(0, 2)))
	{
		//TRACE0("Fail to create splitter.\n");
		return FALSE;
	}

	CRect rect;
	GetClientRect(&rect);
	m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CBtnFormView), CSize(0, 0), pContext);
	m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(CBtnFormView), CSize(0, 0), pContext);
	m_wndSplitter2.CreateView(2, 0, RUNTIME_CLASS(CBtnFormView), CSize(0, 0), pContext);
	m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CBtnFormView), CSize(0, 0), pContext);
	m_wndSplitter1.CreateView(0, 1, RUNTIME_CLASS(CMFCBlackoutToolView), CSize(0, 0), pContext);


	m_wndSplitter1.SetColumnInfo(0, 100, 50);
	m_wndSplitter1.SetColumnInfo(1, rect.right - 350, 50);
	m_wndSplitter1.SetColumnInfo(2, 250, 50);

	m_wndSplitter2.SetRowInfo(0, rect.bottom / 3, 100);
	m_wndSplitter2.SetRowInfo(1, rect.bottom / 3, 100);
	m_wndSplitter2.SetRowInfo(2, rect.bottom / 3, 100);

	//RecalcLayout();

	m_bViewsExist = TRUE;


	return TRUE;

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!m_bViewsExist) return;


	CRect rect;
	GetClientRect(&rect);

	m_wndSplitter1.SetColumnInfo(0, 100, 50);
	m_wndSplitter1.SetColumnInfo(1, rect.right - 350, 50);
	m_wndSplitter1.SetColumnInfo(2, 250, 50);

	m_wndSplitter2.SetRowInfo(0, rect.bottom / 3, 100);
	m_wndSplitter2.SetRowInfo(1, rect.bottom / 3, 100);
	m_wndSplitter2.SetRowInfo(2, rect.bottom / 3, 100);
	RecalcLayout();

}
