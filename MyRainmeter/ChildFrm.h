
// ChildFrm.h : CChildFrame 类的接口
//

#pragma once
#include "Ruler.h"

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 特性
public:

private:
	CRulerSplitterWnd m_Rulers;

// 操作
public:
	void ShowRulers(BOOL bShow);
	void UpdateRulersInfo(stRULER_INFO stRulerInfo);

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnClose();
};
