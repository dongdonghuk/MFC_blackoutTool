// CListFormView.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_BlackoutTool.h"
#include "CListFormView.h"


// CListFormView

IMPLEMENT_DYNCREATE(CListFormView, CFormView)

CListFormView::CListFormView()
	: CFormView(IDD_CListFormView)
{

}

CListFormView::~CListFormView()
{
}

void CListFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DCM_LIST, m_listDcm);
}

BEGIN_MESSAGE_MAP(CListFormView, CFormView)
//	ON_WM_INITMENU()
END_MESSAGE_MAP()


// CListFormView 진단

#ifdef _DEBUG
void CListFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CListFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CListFormView 메시지 처리기


void CListFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_listDcm.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listDcm.InsertColumn(0, _T("No"), LVCFMT_CENTER, 50);
	m_listDcm.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 200);
}
