#pragma once



// CListFormView 폼 보기

class CListFormView : public CFormView
{
	DECLARE_DYNCREATE(CListFormView)

protected:
	CListFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CListFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CListFormView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listDcm;

	virtual void OnInitialUpdate();
	afx_msg void OnNMClickDcmList(NMHDR *pNMHDR, LRESULT *pResult);
};


