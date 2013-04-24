
// MyRainmeterDoc.h : CMyRainmeterDoc 类的接口
//

#pragma once

#include "ConfigParser.h"
#include "Rainmeter.h"
#include "ConstInfo.h"

class CMyRainmeterGraphView;
class CMyRainmeterTextView;


class CMyRainmeterDoc : public CDocument
{
protected: // 仅从序列化创建
	CMyRainmeterDoc();
	DECLARE_DYNCREATE(CMyRainmeterDoc)

// 特性
public:
	CString m_SystemBgPath;	//背景图片地址
	CRainmeter m_Rainmeter;
	CMetadata m_MeterData;
	CString m_Text;
	CConfigParser *m_pConfigParser;
	/// Items 
	CRmCtrlList m_arrItems;
	CRmControl* m_pCurRmCtrl;
		
	CArray<CString> m_Sections;
	unordered_map<wstring, wstring> m_Variables;

	CString m_SkinPath;
	CString m_CurrentPath;
	CString m_RelativePath;

protected:
	

// 操作
public:	
	// General legal Meter Name
	CString GeneralSectionName(CString prefix);
	BOOL IsSectionExits(CString secionName);
	// SwitchView to Text View, to view code
	void OpenTxtViewFrame();
 	
//	void Draw(CDC* pDC, CXTPTaskPanel* pTaskPanel);
	void RemoveAt(int index);
	
	void Add(CRmControl* pObj);
	void Remove(CRmControl* pObj);
	void MoveUp(CRmControl* pObj);		// move pObj backward
	void MoveDown(CRmControl* pObj);	// move pObj forward

	CMyRainmeterTextView* GetTextView();	// GetTextView
	CMyRainmeterGraphView* GetGraphView();
	virtual void UpdateAllViews(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
	virtual BOOL DoSave(LPCTSTR pszPathName, BOOL bReplace = TRUE);

private:
	void InitDocument();

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMyRainmeterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};


