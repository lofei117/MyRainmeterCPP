#pragma once


// CMyRainmeterTextView 视图

class CMyRainmeterTextView : public CEditView
{
	DECLARE_DYNCREATE(CMyRainmeterTextView)

protected:
	CMyRainmeterTextView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMyRainmeterTextView();

public:
	void SetText(CString sText);
	CString GetText();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	afx_msg void OnEditChange();
	DECLARE_MESSAGE_MAP()	
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};

