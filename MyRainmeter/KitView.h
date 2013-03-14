
#pragma once

#include "ViewTree.h"


class CKitView : public CDockablePane
{
public:
	CKitView();
	virtual ~CKitView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	CXTPTaskPanel* GetTaskPanel();

protected:
	CImageList m_KitViewImages;
	UINT m_nCurrSort;
	CXTPTaskPanel	  m_wndTaskPanel;	// 生成ToolBox效果的CXTPTaskPanel类

	

protected:
	//BOOL CreateTaskPanel();
	void ResetToolboxItems();
	CXTPTaskPanelGroup* CreateToolboxGroup(UINT nID);

	// 重写
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

