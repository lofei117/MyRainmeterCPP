#pragma once

#define AFX_PROP_HAS_LIST 0x0001
#define AFX_PROP_HAS_BUTTON 0x0002
#define AFX_PROP_HAS_SPIN 0x0004

class CMyPropertyGridActionProterty : public CMFCPropertyGridProperty
{
	DECLARE_DYNAMIC(CMyPropertyGridActionProterty)

public:
	CMyPropertyGridActionProterty(const CString& strName, const CString& strActionValue, LPCTSTR lpszDescr=_T(""), DWORD_PTR dwData=NULL);
	virtual ~CMyPropertyGridActionProterty();

public:
	virtual void OnClickButton(CPoint point);

protected:
};



// 用于Action设置的 CActionDlg 对话框

class CActionDlg : public CDialogEx
{
public:
	CActionDlg();

	// 对话框数据
	enum { IDD = IDD_ACTION_DLG };

public:
	CString GetActionString() const;
	void SetActionString(CString strAction);

protected:
	CString m_Path;
	CString m_Args;
	CString m_Action;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangePathArgsEdit();
	afx_msg void OnBnClickedBrowserBtn();
};
