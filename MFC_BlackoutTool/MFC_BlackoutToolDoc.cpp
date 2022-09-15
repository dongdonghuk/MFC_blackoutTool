
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
	ON_COMMAND(IDM_DIR_LOAD, &CMFCBlackoutToolDoc::OnDirLoad)
	ON_COMMAND(IDM_DCM_NEXT, &CMFCBlackoutToolDoc::OnDcmNext)
	ON_COMMAND(IDM_DCM_PREV, &CMFCBlackoutToolDoc::OnDcmPrev)
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

		m_jsonFile.jsonLoad(m_vCdraw, m_dcmImg);

		CPresetFormView *pView = (CPresetFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter2.GetPane(0, 0);

		pView->m_strManufacturer = m_dcmImg.m_manufacturer;
		pView->m_strModel = m_dcmImg.m_modelName;
		pView->m_strSize.Format(_T("%d x %d"), m_dcmImg.m_dcmImg.cols, m_dcmImg.m_dcmImg.rows);

		pView->UpdateData(FALSE);

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


void CMFCBlackoutToolDoc::OnDirLoad()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];                                      // 경로저장 버퍼 

	::ZeroMemory(&BrInfo, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, 512);

	BrInfo.hwndOwner = NULL;
	BrInfo.lpszTitle = _T("파일이 저장될 폴더를 선택하세요");
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder(&BrInfo);
	::SHGetPathFromIDList(pItemIdList, szBuffer);				// 파일경로 읽어오기

	CString dcmPath;
	dcmPath.Format(_T("%s\\*.dcm"), szBuffer);


	CListFormView *pListView = (CListFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter2.GetPane(1, 0);

	pListView->m_listDcm.DeleteAllItems();

	CFileFind finder;

	// CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함
	BOOL bWorking = finder.FindFile(dcmPath); //

	CString fileName;


	int i = 0;
	while (bWorking)
	{
		//다음 파일 or 폴더 가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();

		// folder 일 경우는 continue
		if (finder.IsDirectory() || finder.IsDots())
			continue;

		fileName = finder.GetFileTitle();
		m_strDir = finder.GetRoot();

		CString tmp;

		tmp.Format(_T("    %d"),i+1);
		pListView->m_listDcm.InsertItem(i, tmp);
		pListView->m_listDcm.SetItemText(i, 1, fileName);
		i++;
	}

	pListView->m_listDcm.SetSelectionMark(0);
	pListView->m_listDcm.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	pListView->m_listDcm.SetFocus();


	m_vCdraw.clear();

	fileName = pListView->m_listDcm.GetItemText(pListView->m_listDcm.GetSelectionMark(), 1);

	m_dcmImg.dcmRead(m_strDir + fileName + _T(".dcm"), fileName);

	m_jsonFile.jsonLoad(m_vCdraw, m_dcmImg);

	CPresetFormView *pPrestView = (CPresetFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter2.GetPane(0, 0);

	pPrestView->m_strManufacturer = m_dcmImg.m_manufacturer;
	pPrestView->m_strModel = m_dcmImg.m_modelName;
	pPrestView->m_strSize.Format(_T("%d x %d"), m_dcmImg.m_dcmImg.cols, m_dcmImg.m_dcmImg.rows);

	pPrestView->UpdateData(FALSE);
	UpdateAllViews(NULL);
}


void CMFCBlackoutToolDoc::OnDcmNext()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CListFormView *pListView = (CListFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter2.GetPane(1, 0);

	int nSelect = pListView->m_listDcm.GetSelectionMark();

	pListView->m_listDcm.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	pListView->m_listDcm.SetSelectionMark(nSelect + 1);
	pListView->m_listDcm.SetItemState(nSelect + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	pListView->m_listDcm.SetFocus();

	m_vCdraw.clear();

	CString fileName;

	fileName = pListView->m_listDcm.GetItemText(pListView->m_listDcm.GetSelectionMark(), 1);

	m_dcmImg.dcmRead(m_strDir + fileName + _T(".dcm"), fileName);

	m_jsonFile.jsonLoad(m_vCdraw, m_dcmImg);

	CPresetFormView *pPrestView = (CPresetFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter2.GetPane(0, 0);

	pPrestView->m_strManufacturer = m_dcmImg.m_manufacturer;
	pPrestView->m_strModel = m_dcmImg.m_modelName;
	pPrestView->m_strSize.Format(_T("%d x %d"), m_dcmImg.m_dcmImg.cols, m_dcmImg.m_dcmImg.rows);

	pPrestView->UpdateData(FALSE);
	UpdateAllViews(NULL);
}


void CMFCBlackoutToolDoc::OnDcmPrev()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CListFormView *pListView = (CListFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter2.GetPane(1, 0);

	int nSelect = pListView->m_listDcm.GetSelectionMark();

	pListView->m_listDcm.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);
	pListView->m_listDcm.SetSelectionMark(nSelect - 1);
	pListView->m_listDcm.SetItemState(nSelect - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	pListView->m_listDcm.SetFocus();

	if (nSelect > 0) {
		m_vCdraw.clear();

		CString fileName;

		fileName = pListView->m_listDcm.GetItemText(pListView->m_listDcm.GetSelectionMark(), 1);

		m_dcmImg.dcmRead(m_strDir + fileName + _T(".dcm"), fileName);

		m_jsonFile.jsonLoad(m_vCdraw, m_dcmImg);

		CPresetFormView *pPrestView = (CPresetFormView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter2.GetPane(0, 0);

		pPrestView->m_strManufacturer = m_dcmImg.m_manufacturer;
		pPrestView->m_strModel = m_dcmImg.m_modelName;
		pPrestView->m_strSize.Format(_T("%d x %d"), m_dcmImg.m_dcmImg.cols, m_dcmImg.m_dcmImg.rows);

		pPrestView->UpdateData(FALSE);
		UpdateAllViews(NULL);
	}
}
