﻿#pragma once



// CBtnFormView 폼 보기

class CBtnFormView : public CFormView
{
	DECLARE_DYNCREATE(CBtnFormView)

protected:
	CBtnFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CBtnFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CBtnFormView };
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
};


