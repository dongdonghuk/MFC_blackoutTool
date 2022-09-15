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
ON_NOTIFY(NM_CLICK, IDC_DCM_LIST, &CListFormView::OnNMClickDcmList)
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


void CListFormView::OnNMClickDcmList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 행 클릭시 행 넘버값 받아오기
	//NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//int idx = pNMListView->iItem;

	//// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
	//CString sIndexValue;

	//sIndexValue = m_listDcm.GetItemText(idx, 1);
	//AfxMessageBox(sIndexValue);

	//UpdateWindow();

	*pResult = 0;
}
