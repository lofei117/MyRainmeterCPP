#pragma once

#include "Meter.h"
#include "Meansure.h"

////
// ConfigParser class 
////
class CConfigParser
{
// Constructor and Destructor
public:
	CConfigParser(CString fileName);
	~CConfigParser(void);

// public attributes
public:

// private attributes
private:
	CString configFileName;
	CFile* pConfigFile;
	
	unordered_set<wstring> m_Sections;
	unordered_map<wstring, wstring> m_BuiltInVariables;
	unordered_map<wstring, wstring> m_Variables;
	unordered_map<wstring, CMeter*> m_Meters;
	unordered_map<wstring, CMeansure*> m_Meansures;
//	CList<CMeter, CMeter&> m_Meters;
//	CList<CMeansure, CMeansure&> m_Measures;
	
	
//protected attributes
protected:


// public methods
public:
	unordered_set<wstring> GetSections();
	unordered_map<wstring, wstring> GetBuiltIntVariables();
	unordered_map<wstring, wstring> GetVariables();
	unordered_map<wstring, wstring> GetKeyValuePairs();
	void SetVariable(std::wstring strVariable, const std::wstring& strValue);
	void SetBuiltInVariables(std::wstring strVariable, const std::wstring& strValue);
	// GetValue
	wstring GetValue(LPCTSTR section, LPCTSTR key, LPCTSTR defValue);
	// Get value as string
	std::wstring GetValueString(LPCTSTR section, LPCTSTR key, LPCTSTR defValue);
	// Get value as integer
	int ReadInt(LPCTSTR section, LPCTSTR key, int defValue);
	uint32_t ReadUInt(LPCTSTR section, LPCTSTR key, uint32_t defValue);
	uint64_t ReadUInt64(LPCTSTR section, LPCTSTR key, uint64_t defValue);

	void AddSection(wstring section);
	void SetValue(wstring section, wstring key, wstring value);
	void SetComment(wstring section, wstring key, wstring comment);
	void DelSection(wstring section);
	void DelValue(wstring section, wstring key);
	void DelComment(wstring section, wstring key);
	void CleanConfig();

	unordered_map<std::wstring, CMeter*> GetMeterList();
	unordered_map<std::wstring, CMeansure*> GetMeansureLIst();
	CMeter* GetMeter(std::wstring meterName);
	//CString GetValue(CString section, CString key, CString defaultValue);
	bool SetValue(CString section, CString key);

// private methods
private:
	static std::wstring StrToUpper(const std::wstring& str) { std::wstring strTmp(str); StrToUpperC(strTmp); return strTmp; }
	static std::wstring StrToUpper(const WCHAR* str) { std::wstring strTmp(str); StrToUpperC(strTmp); return strTmp; }
	static std::wstring& StrToUpperC(std::wstring& str) { _wcsupr(&str[0]); return str; }	
	void ReadVariables();
	void ReadIniFile();
	bool ReplaceVariables(std::wstring& result);
	const std::wstring* GetVariable(const std::wstring& strVariable);
	
	// protected methods
protected:

	
};

