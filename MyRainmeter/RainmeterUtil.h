#pragma once

// utilities
class CRainmeterUtil
{
public:
	CRainmeterUtil(void);
	~CRainmeterUtil(void);

public:
	// Organize the KeyValuePair and the comments
	static CString OrgKeyValuePair(CString strKey, CString strValue, CString strComment=L"");
	static CString OrgKeyValuePair(CString strKey, int intValue, CString strComment=L"");
	static CString OrgKeyValuePair(CString strKey, float floatValue, CString strComment=L"");
	static bool LoadImageFromResource(IN CImage* pImage, IN UINT nResID, IN LPCTSTR lpTyp=_T("PNG"));
};

