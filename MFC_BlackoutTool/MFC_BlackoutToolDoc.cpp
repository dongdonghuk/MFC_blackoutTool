
// MFC_BlackoutToolDoc.cpp: CMFCBlackoutToolDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_BlackoutTool.h"
#endif

#include "MFC_BlackoutToolDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCBlackoutToolDoc

IMPLEMENT_DYNCREATE(CMFCBlackoutToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCBlackoutToolDoc, CDocument)
	ON_COMMAND(IDM_DICOM_LOAD, &CMFCBlackoutToolDoc::OnDicomLoad)
	ON_COMMAND(IDM_DRAW_RECT, &CMFCBlackoutToolDoc::OnDrawRect)
	ON_COMMAND(IDM_DRAW_MOUSE, &CMFCBlackoutToolDoc::OnDrawMouse)
	ON_COMMAND(IDM_JSON_SAVE, &CMFCBlackoutToolDoc::OnJsonSave)
	ON_COMMAND(IDM_DELETE_UNDO, &CMFCBlackoutToolDoc::OnDeleteUndo)
	ON_COMMAND(IDM_DELETE_ALL, &CMFCBlackoutToolDoc::OnDeleteAll)
END_MESSAGE_MAP()


// CMFCBlackoutToolDoc 생성/소멸

CMFCBlackoutToolDoc::CMFCBlackoutToolDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCBlackoutToolDoc::~CMFCBlackoutToolDoc()
{
}

BOOL CMFCBlackoutToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	m_drawTmp.m_nType = 0;


	return TRUE;
}




// CMFCBlackoutToolDoc serialization

void CMFCBlackoutToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCBlackoutToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCBlackoutToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCBlackoutToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCBlackoutToolDoc 진단

#ifdef _DEBUG
void CMFCBlackoutToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCBlackoutToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCBlackoutToolDoc 명령


void CMFCBlackoutToolDoc::OnDicomLoad()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	TCHAR szFilter[] = _T("Dicom(*.dcm)|*.dcm|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal()) {

		m_vCdraw.clear();
		//m_nDrawType = IDM_DRAW_MOUSE;
		//m_drawTmp.m_nType = 0;

		m_dcmImg.dcmRead(dlg.GetPathName(),dlg.GetFileName());

		m_jsonFile.jsonLoad(m_vCdraw, m_dcmImg.m_dcmPath);
		UpdateAllViews(NULL);
	}
	RemoveMouseMessage();

}



void CMFCBlackoutToolDoc::OnDrawRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawType = IDM_DRAW_RECT;
	//m_drawTmp.m_nType = 1;
	RemoveMouseMessage();
}


void CMFCBlackoutToolDoc::OnDrawMouse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawType = IDM_DRAW_MOUSE;
	RemoveMouseMessage();

}

BOOL CMFCBlackoutToolDoc::RemoveMouseMessage()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, WM_LBUTTONDOWN, WM_LBUTTONUP, PM_REMOVE));
	return TRUE;
}

void CMFCBlackoutToolDoc::OnJsonSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_vCdraw.empty()) {
		m_jsonFile.jsonSave(m_vCdraw, m_dcmImg);
	}
	RemoveMouseMessage();
}


void CMFCBlackoutToolDoc::OnDeleteUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_vCdraw.empty())
	{
		m_vCdraw.pop_back();
		UpdateAllViews(NULL);
	}
	RemoveMouseMessage();
}


void CMFCBlackoutToolDoc::OnDeleteAll()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_vCdraw.empty()) {
		m_vCdraw.clear();
		UpdateAllViews(NULL);
	}
	RemoveMouseMessage();
}
