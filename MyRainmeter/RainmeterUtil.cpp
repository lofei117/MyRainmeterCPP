#include "StdAfx.h"
#include "RainmeterUtil.h"


CRainmeterUtil::CRainmeterUtil(void)
{
}


CRainmeterUtil::~CRainmeterUtil(void)
{
}

CString CRainmeterUtil::OrgKeyValuePair( CString strKey, CString strValue, CString strComment )
{	
	CString sTemp;
	if (strKey.IsEmpty()|| strValue.IsEmpty())
	{
		return L""; 
	}
	if (!strComment.IsEmpty())
	{
		sTemp.Append(L";"+strComment);		
		sTemp.Append(L"\r\n");
	}	
	sTemp.Append(strKey+L"="+strValue+"\r\n");
	return sTemp;
}

CString CRainmeterUtil::OrgKeyValuePair( CString strKey, int intValue, CString strComment )
{
	CString intStr;
	intStr.Format(_T("%d"), intValue);
	return OrgKeyValuePair(strKey, intStr, strComment);
	/*if (strKey.IsEmpty())
	{
	return L""; 
	}
	if (!strComment.IsEmpty())
	{
	sTemp.Append(L";"+strComment);		
	sTemp.Append(L"\r\n");
	}	
	sTemp.Append(strKey+L"="+intStr+"\r\n");
	return sTemp;*/
}

CString CRainmeterUtil::OrgKeyValuePair( CString strKey, float floatValue, CString strComment )
{	
	CString floatStr;
	floatStr.Format(_T("%f"), floatValue);
	return OrgKeyValuePair(strKey, floatStr, strComment);	
}

//////////////////////////////////////////////////////////////////////////
/// 从资源文件中加载图片
/// @param [in] pImage 图片指针
/// @param [in] nResID 资源号
/// @param [in] lpTyp 资源类型
//////////////////////////////////////////////////////////////////////////
bool CRainmeterUtil::LoadImageFromResource(IN CImage* pImage,
	IN UINT nResID, 
	IN LPCTSTR lpTyp)
{
	if ( pImage == NULL) return false;

	pImage->Destroy();

	// 查找资源
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL) return false;

	// 加载资源
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid    = ::LockResource(hImgData);

	LPSTREAM pStream = NULL;
	DWORD dwSize    = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew    = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte    = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// 解除内存中的指定资源
	::GlobalUnlock(hNew);

	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if ( ht != S_OK )
	{
		GlobalFree(hNew);
	}
	else
	{
		// 加载图片
		pImage->Load(pStream);

		GlobalFree(hNew);
	}

	// 释放资源
	::FreeResource(hImgData);

	return true;
}