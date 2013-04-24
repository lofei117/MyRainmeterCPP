#pragma once

// utilities
class CRainmeterUtil
{
public:
	CRainmeterUtil(void);
	~CRainmeterUtil(void);

public:
	// Str To Upper
	static std::wstring StrToUpper(const std::wstring& str) { std::wstring strTmp(str); StrToUpperC(strTmp); return strTmp; }
	static std::wstring StrToUpper(const WCHAR* str) { std::wstring strTmp(str); StrToUpperC(strTmp); return strTmp; }
	static std::wstring& StrToUpperC(std::wstring& str) { _wcsupr(&str[0]); return str; }	
	// Organize the KeyValuePair and the comments
	static CString OrgKeyValuePair(CString strKey, CString strValue, CString strComment=L"");
	static CString OrgKeyValuePair(CString strKey, int intValue, CString strComment=L"");
	static CString OrgKeyValuePair(CString strKey, float floatValue, CString strComment=L"");
	// Load Image From Resource
	static bool LoadImageFromResource(IN CImage* pImage, IN UINT nResID, IN LPCTSTR lpTyp=_T("PNG"));
	static bool LoadImageFromResource(IN Gdiplus::Image* & pImage, IN UINT nResID, IN LPCTSTR lpTyp=_T("PNG"));
	// Greyscale the image.... not finished.
	//static void GreyscaleImage(IN Gdiplus::Image* & pImage, OUT Gdiplus::Image* pGrayImage);
	// Parse the colorString to ARGB COLORREF value
	static COLORREF ParseColor2RGBA(CString colorStr);	
	// Parse the color string to RGB COLORREF value
	static COLORREF ParseColor2RGB(CString colorStr);	
	// Choose Folder
	static bool ChooseFolder(HWND hParent, const CString& title, CString& folder);
};

