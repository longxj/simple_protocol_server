#define __INFILE_HPP
#define __INFILE_HPP

#include <string>
#include <map>
#include <iostream>

using namespace std;

#define MAX_LINE_BUF_SIZE               80
#define MAX_SECTION_CONTEXT_BUF_SIZE    40
#define MAX_KEY_SIZE                    40
#define MAX_VALUE_SIZE                  40

class IniFile
{
	typedef std::map< string, string > MapKeyValue;
	typedef map< string, MapKeyValue > MapSection;

public:
	IniFile();
	~IniFile();

	bool Init(char* szFileName);
	void Save();
	bool SaveAs(char* szFileName);
	void ShowFileContext();

	string GetValue(const string& strKey);
	string GetValueFromSection(const string& strSection, const string& strKey);

	int GetInt(const string& strKey);
	float GetFloat(const string& strKey);

private:
	void DelInvalidSign(char* szOldLine, char* szNewLine);
	bool IsNoteLine(char* szLine);
	bool IsEmptyLine(char* szLine);
	bool IsNewSection(char* szLine);
	bool IsKeyValueLine(char* szLine);

	bool GetNewSectionContext(char* szLine, string& strNewSectionContext);
	bool GetKeyValue(char* szLine, string& strKey, string& strValue);

private:
	string m_strFileName;
	MapSection m_mapSection;
};

#endif
