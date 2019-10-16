/***************************************************
Module: IniReaderPlus
Creator: jxdeng3264@163.com
Time: 2019-10-15
Function: read the Ini config file.
值可以占多行
***************************************************/

#include "IniReaderPlus.h"
#include "UtilString.h"
#include <iostream>
#include <fstream>
using std::string;
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;

namespace ACE {

IniReaderPlus::IniReaderPlus(const string &strfile):_strfile(strfile), _bscan(false) 
{
}

IniReaderPlus::~IniReaderPlus() 
{
	map<string, map<string, string> *>::iterator iter = _cfgdict.begin();
	for (; iter != _cfgdict.end(); ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}
}

string IniReaderPlus::GetValue(const char * section, const char *szname) 
{
	if (!_bscan) {
		ScanCfgFile();
	}
	
	map<string, map<string, string>*>::const_iterator iter = _cfgdict.find(section);
	if (iter != _cfgdict.end()) {
		map<string, string> &tmp = *(iter->second);
		map<string, string>::const_iterator iter2 = tmp.find(szname);
		if (iter2 != tmp.end())
		{
			return iter2->second;
		}
	}
	
	return "";
}

string IniReaderPlus::GetOptValue(const char *section, const char *szname, const string &strdefault) {
	string ret = GetValue(section, szname);
	return (ret=="")? strdefault:ret;
}

int IniReaderPlus::ScanCfgFile() {
	std::ifstream file(_strfile.c_str(), ios::in);
	if (!file.is_open())	return -1;
	// 0x0A 换行符
	//# 注释行
	// ; 一个键对应的值结束
	// [] 块
	string strsection;
	char szline[256];
	string key;
	string value;
	string kv;
	while (!file.eof() && file.getline(szline, sizeof(szline), 0x0A)) {
		string tt = string(szline);
		string &sline = Trim(tt);
		
		// 注释行跳过
		if (sline.empty() || sline[0] == '#') {
			continue;
		}
		// 块名
		if ('[' == sline[0] && ']' == sline[sline.size() - 1]) {
			strsection = sline.substr(1, sline.size()-2);
			kv.clear();
			continue;
		}

		// 1. 最后一个字符是否是分号 ?
		if (';' == sline[sline.size() - 1])
		{
			string sub = sline.substr(0, sline.size()-1);
			kv += sline;
			if (strsection.empty()) 
			{
				return -1;
			}

			doGetKeyValue(strsection, kv);
			kv = "";
			continue;
		}
		
		kv += sline;
	}// end while

	_bscan = true;
	return 0;
}

void IniReaderPlus::doGetKeyValue(const string &sectionname, string &kv)
{
	string::size_type pos = kv.find("=");
	if (string::npos == pos) {
		return ;
	}

	string left = kv.substr(0, pos);
	string right = kv.substr(pos+1, kv.size() - pos -1);
	string key = Trim(left);
	string value = Trim(right);
	// 删除最后一个 ;
	value.erase(value.length()-1, 1);
	auto iter = _cfgdict.lower_bound(sectionname);
	if (iter != _cfgdict.end() && sectionname == iter->first)
	{
		iter->second->insert(make_pair(key, value));
	} 
	else 
	{
		map<string, string> *tmp = new map<string, string>;
		tmp->insert(make_pair(key, value));
		_cfgdict.insert(iter, make_pair(sectionname, tmp));
	}
	return ;
}

void IniReaderPlus::show() 
{
	if (!_bscan) ScanCfgFile();

	auto it = _cfgdict.begin();
	while (it != _cfgdict.end()) {
		cout<<it->first<<endl;
		auto it_in = it->second->begin();
		while (it_in != ((it->second))->end()) {
			cout<<(it_in)->first<<"="<<(it_in)->second<<endl;
			++it_in;
		}
		++it;
	}
}

}// namespace ACE