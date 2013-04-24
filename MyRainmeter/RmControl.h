#pragma once

class CConfigParser;
class CMyRainmeterDoc;
class CMyRainmeterGraphView;
// CRmControl

class CRmControl : public CObject
{
	

public:
	CRmControl(CXTPTaskPanelGroupItem *pItem, CMyRainmeterGraphView* pView);
	
	virtual ~CRmControl();

	// Attributes
public:
	CRect m_Position;
	CXTPTaskPanelGroupItem* m_pItem;
private:
protected:
	CMyRainmeterDoc* m_pDocument;
	CMyRainmeterGraphView *m_pGraphView;

	// Operations
public:	
	virtual void Draw(CDC* pDC, CXTPTaskPanel* taskPanel );
	virtual void Draw(CDC* pDC, CXTPTaskPanel* taskPanel, CXTPTaskPanelGroupItem* pItem );
	virtual void Remove();
	virtual void Serialize(CArchive& ar);
	virtual void InitProperties(CMFCPropertyGridCtrl* pPropGridCtrl);
	virtual void UpdateProperties();
	virtual void PropertyChanged (CMFCPropertyGridProperty* pProp);
	virtual CString ToString() const;	// To string
	void Invalidate();
	void InternalRelease();

protected:
	CRmControl();
};


typedef CArray<CRmControl*, CRmControl*> CRmCtrlList;