// MyPropertyGridProterty.cpp : 实现文件
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "MyPropertyGridProterty.h"


CActionDlg::CActionDlg() : CDialogEx(CActionDlg::IDD)
{
}

void CActionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATH_EDIT, m_Path);
	DDX_Text(pDX, IDC_ARGS_EDIT, m_Args);
	DDX_Text(pDX, IDC_ACTION_EDIT, m_Action);
}

BEGIN_MESSAGE_MAP(CActionDlg, CDialogEx)
	//	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CActionDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_PATH_EDIT, &CActionDlg::OnEnChangePathArgsEdit)
	ON_EN_CHANGE(IDC_ARGS_EDIT, &CActionDlg::OnEnChangePathArgsEdit)
	ON_BN_CLICKED(IDC_BROWSER_BTN, &CActionDlg::OnBnClickedBrowserBtn)
END_MESSAGE_MAP()

// CMyPropertyGridProterty 消息处理程序

void CActionDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}

CString CActionDlg::GetActionString() const
{
	return m_Action;
}

void CActionDlg::SetActionString( CString strAction )
{
	m_Action = strAction;
	//UpdateData(FALSE);
}

void CActionDlg::OnEnChangePathArgsEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_Action = _T("[!Execute \"")+m_Path+_T("\" \"")+m_Args+_T("\"]");
	UpdateData(FALSE);
}

void CActionDlg::OnBnClickedBrowserBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, NULL,m_Path);
	if(dlg.DoModal()==IDOK)
	{
		m_Path=dlg.GetPathName();	
		m_Action = _T("[!Execute \"")+m_Path+_T("\" \"")+m_Args+_T("\"]");
		UpdateData(FALSE);
	}	
}





// CMyPropertyGridActionProterty

IMPLEMENT_DYNAMIC(CMyPropertyGridActionProterty, CMFCPropertyGridProperty)

CMyPropertyGridActionProterty::CMyPropertyGridActionProterty(const CString& strName, const CString& strActionValue, LPCTSTR lpszDescr, DWORD_PTR dwData) : CMFCPropertyGridProperty(strName, COleVariant((LPCTSTR)strActionValue), lpszDescr, dwData)
{
	m_dwFlags = AFX_PROP_HAS_BUTTON;
	m_varValue = strActionValue;
}

CMyPropertyGridActionProterty::~CMyPropertyGridActionProterty()
{
}

void CMyPropertyGridActionProterty::OnClickButton( CPoint point )
{
	ASSERT_VALID(this);
	ASSERT_VALID(m_pWndList);
	ASSERT_VALID(m_pWndInPlace);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	m_bButtonIsDown = TRUE;
	Redraw();

	CString strPath = m_varValue.bstrVal;
	BOOL bUpdate = FALSE;

	CActionDlg dlg;
	dlg.SetActionString(strPath);

	//CFileDialog dlg(m_bOpenFileDialog, m_strDefExt, strPath, m_dwFileOpenFlags, m_strFilter, m_pWndList);
	if (dlg.DoModal() == IDOK)
	{		
		bUpdate = TRUE;
		strPath = dlg.GetActionString();
	}
	

	if (bUpdate)
	{
		if (m_pWndInPlace != NULL)
		{
			m_pWndInPlace->SetWindowText(strPath);
		}

		m_varValue = (LPCTSTR) strPath;
	}

	m_bButtonIsDown = FALSE;
	Redraw();

	if (m_pWndInPlace != NULL)
	{
		m_pWndInPlace->SetFocus();
	}
	else
	{
		m_pWndList->SetFocus();
	}
}


//////////////////////////////////////////////////////////////////////////
//CMFCPropertyGridColor32Property

CMyPropertyGridColor32Property::CMyPropertyGridColor32Property(const CString& strName, const COLORREF& color,CPalette* pPalette/*=NULL*/,LPCTSTR lpszDescr/*=NULL*/,DWORD_PTR dwData/*=0*/)
	:CMFCPropertyGridColorProperty(strName,color,pPalette,lpszDescr,dwData)
{
	 
}

CMyPropertyGridColor32Property::~CMyPropertyGridColor32Property()
{
	
}

BOOL CMyPropertyGridColor32Property::OnUpdateValue()
{
	ASSERT_VALID(this);

	if (m_pWndInPlace == NULL)
	{
		return FALSE;
	}

	ASSERT_VALID(m_pWndInPlace);
	ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

	CString strText;
	m_pWndInPlace->GetWindowText(strText);

	COLORREF colorCurr = m_Color;
	int nA = 0,nR = 0, nG = 0, nB = 0;
	_stscanf_s(strText, _T("%3d,%3d,%3d,%3d"), &nR, &nG, &nB, &nA);
	
	if(nA == 0 && (nR !=0 || nG != 0 || nB !=  0))
		nA = 0xFF;
	/*if(nA == 0 && (nR ==0 && nG == 0 && nB ==  0))
		nA = 0xFF;*/
	
	m_Color = RGBA(nR, nG, nB, nA);

	if (colorCurr != m_Color)
	{
		m_pWndList->OnPropertyChanged(this);
	}

	return TRUE;
}

void CMyPropertyGridColor32Property::OnDrawValue(CDC* pDC, CRect rect)
{
	// Initialize GDI+Obj
	Graphics GDIplusObj(pDC->m_hDC); 

	CRect rectColor = rect;

	rect.left += rect.Height();
	CMFCPropertyGridProperty::OnDrawValue(pDC, rect);

	rectColor.right = rectColor.left + rectColor.Height(); 
	rectColor.DeflateRect(1, 1);
	rectColor.top++;
	rectColor.left++;	

	RectF drawRect((Gdiplus::REAL)rectColor.left, (Gdiplus::REAL)rectColor.top, (Gdiplus::REAL)rectColor.Height(), (Gdiplus::REAL)rectColor.Height());

	SolidBrush brush(Color(GetAValue(m_Color),GetRValue(m_Color),GetGValue(m_Color),GetBValue(m_Color)));	
	GDIplusObj.FillRectangle(&brush, drawRect);

	GDIplusObj.ReleaseHDC(pDC->m_hDC);
	/*CBrush br(m_Color == (COLORREF)-1 ? m_ColorAutomatic : (m_Color&0x00FFFFFF));	
	pDC->FillRect(rectColor, &br);
	pDC->Draw3dRect(rectColor, 0, 0);*/
}

CString CMyPropertyGridColor32Property::FormatProperty()
{
	ASSERT_VALID(this);

	CString str;
	str.Format(_T("%d,%d,%d,%d"),GetRValue(m_Color),GetGValue(m_Color),GetBValue(m_Color),GetAValue(m_Color));

	return str;
}

BOOL CMyPropertyGridColor32Property::OnEdit( LPPOINT lptClick )
{
	__super::OnEdit(lptClick);
	CMFCMaskedEdit* pWndEdit = (CMFCMaskedEdit *)m_pWndInPlace;
	pWndEdit->SetValidChars(_T("01234567890ABCDEFabcdef,"));	
	m_pWndInPlace->SetWindowText(FormatProperty());
	return TRUE;
}

COleVariant CMyPropertyGridColor32Property::GetValue()
{
	COleVariant value = FormatProperty();
	return value;
}




