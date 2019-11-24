#ifndef __INI_READER_H__
#define __INI_READER_H__
#include <string>
#include <map>
using std::string;
using std::map;
namespace ACE
{
class IniReaderPlus
{
public:
	IniReaderPlus(const string &strfile);
	~IniReaderPlus();

	string GetValue(const char * section, const char *szname);
	string GetOptValue(const char *section, const char *szname, const string &strdefault);
	void doGetKeyValue(const string &sectionname, string &kv);
	void show();
private:
	// 返回：0 成功
	int ScanCfgFile();
private:
	string _strfile;
	map<string, map<string, string>*> _cfgdict;
	bool _bscan;

};

}

#endif 