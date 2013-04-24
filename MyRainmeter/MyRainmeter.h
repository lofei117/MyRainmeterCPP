
// MyRainmeter.h : MyRainmeter 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMyRainmeterApp:
// 有关此类的实现，请参阅 MyRainmeter.cpp
//

class CMyRainmeterApp : public CWinAppEx
{
public:
	CMyRainmeterApp();
	~CMyRainmeterApp();

public:
	CMultiDocTemplate* m_pTemplateTxt;
	CString m_SkinFolder;

protected:
	ULONG_PTR m_gdiplusToken;  

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();	
	afx_msg void OnFileNewConfig();
	afx_msg void OnFileNewSkin();
	afx_msg void OnFileOpenSkin();
	afx_msg void OnFileOpenConfig();

	DECLARE_MESSAGE_MAP()
};

extern CMyRainmeterApp theApp;
