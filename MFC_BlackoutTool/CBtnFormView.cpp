// CBtnFormView.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_BlackoutTool.h"
#include "CBtnFormView.h"



// CBtnFormView

IMPLEMENT_DYNCREATE(CBtnFormView, CFormView)

CBtnFormView::CBtnFormView()
	: CFormView(IDD_CBtnFormView)
{

}

CBtnFormView::~CBtnFormView()
{
}

void CBtnFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBtnFormView, CFormView)
END_MESSAGE_MAP()


// CBtnFormView 진단
#ifdef _DEBUG

void CBtnFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBtnFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBtnFormView 메시지 처리기
