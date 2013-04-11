#include "StdAfx.h"
#include "ConfigParser.h"
#include <Windows.h>
#include "ConstInfo.h"


CConfigParser::CConfigParser(CString fileName)
{
	this->configFileName = fileName;
	ReadIniFile();
}


CConfigParser::~CConfigParser(void)
{
}



/*
** Replaces environment and internal variables in the given string.
**
*/
bool CConfigParser::ReplaceVariables(std::wstring& result)
{
	bool replaced = false;
	
	// Check for variables (#VAR#)
	size_t start = 0, end;
	bool loop = true;

	do
	{
		start = result.find(L'#', start);
		if (start != std::wstring::npos)
		{
			size_t si = start + 1;
			end = result.find(L'#', si);
			if (end != std::wstring::npos)
			{
				size_t ei = end - 1;
				if (si != ei && result[si] == L'*' && result[ei] == L'*')
				{
					result.erase(ei, 1);
					result.erase(si, 1);
					start = ei;
				}
				else
				{
					std::wstring strVariable = result.substr(si, end - si);
					const std::wstring* value = GetVariable(strVariable);
					if (value)
					{
						// Variable found, replace it with the value
						result.replace(start, end - start + 1, *value);
						start += (*value).length();
						replaced = true;
					}
					else
					{
						start = end;
					}
				}
			}
			else
			{
				loop = false;
			}
		}
		else
		{
			loop = false;
		}
	}
	while (loop);

	return replaced;
}

/*
** Gets a value for the variable. Returns NULL if not found.
**
*/
const std::wstring* CConfigParser::GetVariable(const std::wstring& strVariable)
{
	const std::wstring strTmp = StrToUpper(strVariable);

	// #1: Built-in variables
	std::unordered_map<std::wstring, std::wstring>::const_iterator iter = m_BuiltInVariables.find(strTmp);
	if (iter != m_BuiltInVariables.end())
	{
		return &(*iter).second;
	}

	// #2: Monitor variables
	/*iter = c_MonitorVariables.find(strTmp);
	if (iter != c_MonitorVariables.end())
	{
	return &(*iter).second;
	}*/

	// #3: User-defined variables
	iter = m_Variables.find(strTmp);
	if (iter != m_Variables.end())
	{
		return &(*iter).second;
	}

	return NULL;
}

// Get sections from initialization file
void CConfigParser::ReadIniFile()
{
	// Get all the sections (i.e. different meters)
	std::list<std::wstring> sections;
	std::unordered_set<std::wstring> unique;
	std::wstring key, value;  // buffer

	DWORD itemsSize = MAX_LINE_LENGTH;
	WCHAR* items = new WCHAR[itemsSize];
	WCHAR* pos = NULL;
	WCHAR* epos = NULL;
	// Get all the sections
	do
	{
		items[0] = 0;
		DWORD res = GetPrivateProfileSectionNames(items, itemsSize, this->configFileName);
		if (res == 0)		// File not found
		{
			delete [] items;
		//	if (temporary) CSystem::RemoveFile(iniRead);
			return;
		}
		if (res < itemsSize - 2)		// Fits in the buffer
		{
			epos = items + res;
			break;
		}

		delete [] items;
		itemsSize *= 2;
		items = new WCHAR[itemsSize];
	}
	while (true);

	// Read the sections
	pos = items;
	while (pos < epos)
	{
		if (*pos)
		{
			value = pos;  // section name
			key.assign(value);
			//StrToUpperC(key.assign(value));
			if (unique.insert(key).second)
			{
				/*if (m_FoundSections.insert(key).second)
				{
					m_Sections.insert(m_SectionInsertPos, value);
				}*/
				m_Sections.insert((key));
				sections.push_back(value);
			}
			pos += value.size() + 1;
		}
		else  // Empty string
		{
			++pos;
		}
	}

	do
	{
		items[0] = 0;
		DWORD res = GetPrivateProfileSection(_T("Variables"), items, itemsSize, this->configFileName);
		if (res < itemsSize - 2)		// Fits in the buffer
		{
			epos = items + res;
			break;
		}

		delete [] items;
		itemsSize *= 2;
		items = new WCHAR[itemsSize];
	}
	while (true);

	wstring pair;
	unique.clear();
	pos = items;
	while (pos < epos)
	{
		if (*pos)
		{
			pair = pos;  // section name

			size_t len = wcslen(pos);
			WCHAR* sep = wmemchr(pos, L'=', len);
			if (sep != NULL && sep != pos)
			{
				size_t clen = sep - pos;  // key's length
				key.assign(pos, clen);
				if (unique.insert(key).second)
				{
					++sep;
					clen = len - (clen + 1);  // value's length

					// Trim surrounded quotes from value
					if (clen >= 2 && (sep[0] == L'"' || sep[0] == L'\'') && sep[clen - 1] == sep[0])
					{
						clen -= 2;
						++sep;
					}
					value.assign(sep, clen);
					SetVariable(key, value);
				}
			}
			pos += pair.size() + 1;
		}
		else  // Empty string
		{
			++pos;
		}
	}

}

unordered_set<wstring> CConfigParser::GetSections()
{
	return this->m_Sections;

}

unordered_map<wstring, wstring> CConfigParser::GetVariables()
{
	return this->m_Variables;
}

void CConfigParser::SetVariable( std::wstring strVariable, const std::wstring& strValue )
{
	StrToUpperC(strVariable);
	m_Variables[strVariable] = strValue;
}

unordered_map<wstring, wstring> CConfigParser::GetBuiltIntVariables()
{
	return this->m_BuiltInVariables;
}

void CConfigParser::SetBuiltInVariables( std::wstring strVariable, const std::wstring& strValue )
{
	m_BuiltInVariables[strVariable] = strValue;
}


CString CConfigParser::GetValueString(LPCTSTR section, LPCTSTR key, LPCTSTR defValue)
{
	TCHAR strTmp[MAX_LINE_LENGTH];
	DWORD nSize = MAX_LINE_LENGTH;
	DWORD res = GetPrivateProfileString(section, key, defValue, strTmp, nSize, this->configFileName);
	return strTmp;
}

CString CConfigParser::GetValue(LPCTSTR section, LPCTSTR key, LPCTSTR defValue)
{
	return GetValueString(section, key, defValue);
}

int CConfigParser::ReadInt( LPCTSTR section, LPCTSTR key, int defValue )
{
	const std::wstring& result = GetValueString(section, key, L"").GetBuffer();
	const WCHAR* string = result.c_str();
	if (*string == L'(')
	{
		/*double dblValue;
		const WCHAR* errMsg = MathParser::CheckedParse(string, &dblValue);
		if (!errMsg)
		{
		return (int)dblValue;
		}
		LogWithArgs(LOG_ERROR, L"Formula: %s in key \"%s\" in [%s]", errMsg, key, section);*/
	}
	else if (*string)
	{
		errno = 0;
		int intValue = wcstol(string, NULL, 10);
		if (errno != ERANGE)
		{
			return intValue;
		}
	}
	return defValue;
}

std::uint32_t CConfigParser::ReadUInt( LPCTSTR section, LPCTSTR key, uint32_t defValue )
{
	return defValue;
}

std::uint64_t CConfigParser::ReadUInt64( LPCTSTR section, LPCTSTR key, uint64_t defValue )
{
	// not implemented
	return defValue;
}

void CConfigParser::AddSection( LPCTSTR section )
{
}

void CConfigParser::SetValueString( LPCTSTR section, LPCTSTR key, LPCTSTR value )
{
	WritePrivateProfileString(section, key, value, this->configFileName);
}




