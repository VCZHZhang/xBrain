#ifndef __INI_READER_H__
#define __INI_READER_H__
#include <string>
#include <map>
using std::string;
using std::map;

namespace ACE
{

enum Type {
     typ_empty = 1, //
     typ_comment,
     typ_section,
     typ_field
};

typedef struct LineInfo
{
    int _lineNum;
    std::string _src;
    Type _type;
    std::string _sectionName;
    std::string _key;
    std::string _val;
}LineInfo;

class IniReaderPlus
{
public:
    IniReaderPlus(const string &strfile);
    ~IniReaderPlus();

    // 返回：0 成功
    int ScanCfgFile();
    int Transfer();
    string GetValue(const char * section, const char *szname);
    string GetOptValue(const char *section, const char *szname, const string &strdefault);
    int Remove(std::string &section, std::string &key);
    int Modify(std::string &section, std::string &key, std::string &newval);
    void show();
private:
    
private:
    bool _bscan;
    string _strfile;
    map<string, map<string, LineInfo> *> _cfgDict;
    map<int, LineInfo>  _allLine;
};

} // namespace ACE

#endif 
