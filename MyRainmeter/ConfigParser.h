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
	//CString GetStringFromText(CString sectin, CString key, CString defValue, CString srcText);

	unordered_set<wstring> GetSections();
	unordered_map<wstring, wstring> GetBuiltIntVariables();
	unordered_map<wstring, wstring> GetVariables();
	unordered_map<wstring, wstring> GetKeyValuePairs();
	void SetVariable(std::wstring strVariable, const std::wstring& strValue);
	void SetBuiltInVariables(std::wstring strVariable, const std::wstring& strValue);
	// GetValue
	CString GetValue(LPCTSTR section, LPCTSTR key, LPCTSTR defValue=L"");
	// Get value as string
	CString GetValueString(LPCTSTR section, LPCTSTR key, LPCTSTR defValue=L"");	
	
	// Get value as integer
	int GetValueInt(LPCTSTR section, LPCTSTR key, int defValue=0);
	uint32_t ReadUInt(LPCTSTR section, LPCTSTR key, uint32_t defValue);
	uint64_t ReadUInt64(LPCTSTR section, LPCTSTR key, uint64_t defValue);

	// Get value as float
	float GetValueFloat(LPCTSTR section, LPCTSTR key, float defValue=0.0);

	// Write value to config
	void SetValueString(LPCTSTR section, LPCTSTR key, LPCTSTR value);
	void AddSection(LPCTSTR section);	
	void SetComment(LPCTSTR section, LPCTSTR key, LPCTSTR comment);
	void DelSection(LPCTSTR section);
	void DelValueString(LPCTSTR section, LPCTSTR key);
	void DelComment(LPCTSTR section, LPCTSTR key);
	void CleanConfig();

	unordered_map<std::wstring, CMeter*> GetMeterList();
	unordered_map<std::wstring, CMeansure*> GetMeansureList();
	CMeter* GetMeter(std::wstring meterName);
	CString GetValue(CString section, CString key, CString defaultValue);
	bool SetValue(CString section, CString key);	

// private methods
private:
	
	void ReadVariables();
	void ReadIniFile();
	bool ReplaceVariables(std::wstring& result);
	const std::wstring* GetVariable(const std::wstring& strVariable);
	
	// protected methods
protected:

	
};

