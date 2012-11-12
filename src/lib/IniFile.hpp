#ifndef __INFILE_HPP
#define __INFILE_HPP

#include <string>
#include <map>
#include <iostream>

#define MAX_LINE_BUF_SIZE               80
#define MAX_SECTION_CONTEXT_BUF_SIZE    40
#define MAX_KEY_SIZE                    40
#define MAX_VALUE_SIZE                  40

class IniFile
{
	typedef std::map<std::string, std::string > MapKeyValue;
	typedef std::map<std::string, MapKeyValue > MapSection;

public:
	IniFile();
	~IniFile();

	bool Init(char* szFileName);
	void Save();
	bool SaveAs(char* szFileName);
	void ShowFileContext();

	string GetValue(const std::string& strKey);
	string GetValueFromSection(const std::string& strSection, const std::string& strKey);

	int GetInt(const std::string& strKey);
	float GetFloat(const std::string& strKey);

private:
	void DelInvalidSign(char* szOldLine, char* szNewLine);
	bool IsNoteLine(char* szLine);
	bool IsEmptyLine(char* szLine);
	bool IsNewSection(char* szLine);
	bool IsKeyValueLine(char* szLine);

	bool GetNewSectionContext(char* szLine, std::string& strNewSectionContext);
	bool GetKeyValue(char* szLine, std::string& strKey, std::string& strValue);

private:
	std::string m_strFileName;
	MapSection m_mapSection;
};

#endif
