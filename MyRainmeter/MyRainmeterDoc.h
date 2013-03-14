
// MyRainmeterDoc.h : CMyRainmeterDoc 类的接口
//

#pragma once

#include "ConfigParser.h"

class CMyRainmeterGraphView;

class CMyRainmeterDoc : public CDocument
{
protected: // 仅从序列化创建
	CMyRainmeterDoc();
	DECLARE_DYNCREATE(CMyRainmeterDoc)

// 特性
public:
	CString systemBgPath;	//背景图片地址
	CConfigParser *pConfigParser;
//	CRmCtrlList m_RmCtrls;
	/// Items 
	CArray<CXTPTaskPanelGroupItem*, CXTPTaskPanelGroupItem*> m_arrItems;

// 操作
public:
	void SwitchViewCodeFrame();
//	CRmCtrlList* GetRmCtrls(){return &m_RmCtrls;}
	void Draw(CDC* pDC, CMyRainmeterGraphView* pView);
	CRmControl* RmCtrlAt(const CPoint& point);
	// ------ Draw called for live icon and Win7 taskbar thumbnails
	void Draw (CDC* pDC);
	void FixUpRmCtrlPositions();
	void Add(CRmControl* pObj);
	void Remove(CRmControl* pObj);

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
