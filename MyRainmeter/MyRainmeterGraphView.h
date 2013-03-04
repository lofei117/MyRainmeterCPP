
// MyRainmeterGraphView.h : CMyRainmeterGraphView 类的接口
//

#pragma once
#include "ChildFrm.h"


class CMyRainmeterGraphView : public CScrollView
{
protected: // 仅从序列化创建
	CMyRainmeterGraphView();
	DECLARE_DYNCREATE(CMyRainmeterGraphView)

// 特性
public:
	CMyRainmeterDoc* GetDocument() const;
private:	
	CImage m_BackgroundImage;
	CChildFrame* m_pParent;
	CBrush       m_BrushBackGround;
	CSize		 m_DesktopSize;
	CPoint       m_RefScroll;
	CPoint       m_RefPoint;
	BOOL         m_bShowRulers;

// 操作
public:

private:
	void UpdateRulersInfo(int nMessage, CPoint ScrollPos, CPoint Pos = CPoint(0, 0)); 


// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// 实现
public:
	virtual ~CMyRainmeterGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewCode();
	//{{AFX_MSG(CDemoView)
	afx_msg void OnRulersTogglerulers();
	afx_msg void OnUpdateRulersTogglerulers(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

#ifndef _DEBUG  // MyRainmeterGraphView.cpp 中的调试版本
inline CMyRainmeterDoc* CMyRainmeterGraphView::GetDocument() const
   { return reinterpret_cast<CMyRainmeterDoc*>(m_pDocument); }
#endif

