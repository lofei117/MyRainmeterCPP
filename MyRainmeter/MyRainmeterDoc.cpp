
// MyRainmeterDoc.cpp : CMyRainmeterDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyRainmeter.h"
#endif

#include "MyRainmeterDoc.h"
#include "MainFrm.h"

#include "MyRainmeterTextView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyRainmeterDoc

IMPLEMENT_DYNCREATE(CMyRainmeterDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyRainmeterDoc, CDocument)
END_MESSAGE_MAP()


// CMyRainmeterDoc 构造/析构

CMyRainmeterDoc::CMyRainmeterDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMyRainmeterDoc::~CMyRainmeterDoc()
{
	
//	delete systemBgPath;
//	delete pConfigParser;
}

BOOL CMyRainmeterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	InitDocument();

	return TRUE;
}


BOOL CMyRainmeterDoc::OnOpenDocument( LPCTSTR lpszPathName )
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	InitDocument();
	return TRUE;
}


void CMyRainmeterDoc::InitDocument()
{
	///获取桌面背景图片地址
	HRESULT hr;//用于保存返回值
	IActiveDesktop* pIAD;//桌面接口实例
	hr=CoCreateInstance(CLSID_ActiveDesktop, NULL,CLSCTX_INPROC_SERVER,IID_IActiveDesktop,(void**)&pIAD);//初始化
	WCHAR wszWallpaper[MAX_PATH];//用于保存背景图片路径
	hr=pIAD->GetWallpaper(wszWallpaper,MAX_PATH,0);//获取背景图片路径
	systemBgPath = wszWallpaper;

	pConfigParser = new CConfigParser(_T("E:\\rainmeter\\Rainmeter\\Skins\\阿狸\\ini.ini"));
	wstring val1 = pConfigParser->GetValueString(_T("Rainmeter"),_T("Author"), _T("null"));
	MessageBox(NULL, val1.c_str(), _T("aaa"), 0);
	CMainFrame* pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrame->AddStrLogToOutputWnd(val1.c_str());
	
}


void CMyRainmeterDoc::SwitchViewCodeFrame()
{
	CFrameWnd *m_pTextViewFrame = NULL;

	// Check and set the TextViewFrame
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView( pos );
		if (pView->IsKindOf(RUNTIME_CLASS(CMyRainmeterTextView)))
		{
			m_pTextViewFrame = pView->GetParentFrame();
			break;
		}
	}
		
	// if TextViewFrame doesn't exist (NULL), initialize and display it.
	if(m_pTextViewFrame == NULL)
	{
		// Create TextView frame
		CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
		CMDIChildWnd* pActiveChild = pMainFrame->MDIGetActive();

		if (pActiveChild == NULL )
		{
			TRACE0("Warning: No active document for WindowNew command\n");
			AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
			return ;     // command failed
		}
		CDocTemplate* pTemplate = theApp.m_pTemplateTxt;
		ASSERT_VALID(pTemplate);

		m_pTextViewFrame = pTemplate->CreateNewFrame(this, pActiveChild);
		if (m_pTextViewFrame == NULL)
		{
			TRACE0("Warning: failed to create new frame\n");
			AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
			return ;     // command failed
		}
		pTemplate->InitialUpdateFrame(m_pTextViewFrame, this);
	}
	else	// TextViewFrame exists, just switch to show it
	{		
		CDocTemplate* pTemplate = theApp.m_pTemplateTxt;
		pTemplate->InitialUpdateFrame(m_pTextViewFrame, this);
	}
}


// CMyRainmeterDoc 序列化

void CMyRainmeterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMyRainmeterDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CMyRainmeterDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMyRainmeterDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyRainmeterDoc 诊断

#ifdef _DEBUG
void CMyRainmeterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyRainmeterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}


#endif //_DEBUG


// CMyRainmeterDoc 命令
