
// MFC_BlackoutToolDoc.h: CMFCBlackoutToolDoc 클래스의 인터페이스
//


#pragma once
#include "DicomImg.h"
#include "CDraw.h"
#include "JsonFile.h"
//#include "CPresetFormView.h"
#include "MainFrm.h"

class CMFCBlackoutToolDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCBlackoutToolDoc() noexcept;
	DECLARE_DYNCREATE(CMFCBlackoutToolDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	DicomImg m_dcmImg;
	vector<CDraw> m_vCdraw;
	CDraw m_drawTmp;
	JsonFile m_jsonFile;

	int m_nDrawType;

public:
	BOOL RemoveMouseMessage();

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCBlackoutToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnDicomLoad();
	afx_msg void OnDrawRect();
	afx_msg void OnDrawMouse();
	afx_msg void OnJsonSave();
	afx_msg void OnDeleteUndo();
	afx_msg void OnDeleteAll();
};
