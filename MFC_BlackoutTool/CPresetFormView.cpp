// CPresetFormView.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_BlackoutTool.h"
#include "CPresetFormView.h"


// CPresetFormView

IMPLEMENT_DYNCREATE(CPresetFormView, CFormView)

CPresetFormView::CPresetFormView()
	: CFormView(IDD_CPresetFormView)
	, m_strManufacturer(_T(""))
	, m_strModel(_T(""))
	, m_strSize(_T(""))
{

}

CPresetFormView::~CPresetFormView()
{
}

void CPresetFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DCM_MANUFACTURER, m_strManufacturer);
	DDX_Text(pDX, IDC_DCM_MODEL, m_strModel);
	DDX_Text(pDX, IDC_DCM_SIZE, m_strSize);
}

BEGIN_MESSAGE_MAP(CPresetFormView, CFormView)
END_MESSAGE_MAP()


// CPresetFormView 진단

#ifdef _DEBUG
void CPresetFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPresetFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}



#endif
#endif //_DEBUG
