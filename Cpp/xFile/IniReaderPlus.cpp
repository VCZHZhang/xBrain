/***************************************************
Module: IniReaderPlus
Creator: jxdeng3264@163.com
Time: 2019-10-15
Function: read the Ini config file.
***************************************************/

#include <iostream>
#include <fstream>
#include "IniReaderPlus.h"
#include "../util_string.h"
#include "../ErrorInfo.h"
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
	map<string, map<string, LineInfo> *>::iterator iter = _cfgDict.begin();
	for (; iter != _cfgDict.end(); ++iter)
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
	
	map<string, map<string, LineInfo>*>::const_iterator iter = _cfgDict.find(section);
	if (iter != _cfgDict.end()) {
		map<string, LineInfo> &tmp = *(iter->second);
		map<string, LineInfo>::const_iterator iter2 = tmp.find(szname);
		if (iter2 != tmp.end())
		{
			return iter2->second._val;
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
	string strSection;
	char szline[256];
	string key;
	string value;
	string kv;
	int lineNum = 0;
	ErrorInfo  ei;
	cout<<__FUNCTION__<<__LINE__<<endl;
	while (!file.eof() && file.getline(szline, sizeof(szline), 0x0A)) 
	{
		string tt = string(szline);
		lineNum++;
		LineInfo li;
		li._lineNum = lineNum;
		li._src = tt;

		string &sline = Trim(tt);
		char firstCh = '\0';
		if (!sline.empty())
			firstCh = sline[0];

		switch (firstCh)
		{
		case '\0':
			li._type = typ_empty;
			break;
		case '[':
			li._type = typ_section;
			strSection = sline.substr(1, sline.size()-2);
			li._sectionName = strSection;
			break;
		case '#':
			li._type = typ_comment;
			break;
		default:
			if (strSection.empty())
			{
				ei._errNo = ERR_INI_NO_SECTION;
				ei._lineNum = lineNum;
				break;
			}
			li._sectionName = strSection;
			li._type = typ_field;

			string::size_type pos = sline.find("=");
			if (string::npos == pos)
			{
				ei._errNo = ERR_INI_SYNTAX_ERR;
				ei._lineNum = lineNum;
				break;
			}
			
			string strtemp = sline.substr(0, pos);
			string key = Trim(strtemp);
			strtemp = sline.substr(pos + 1, sline.size() - pos - 1);
			string val = Trim(strtemp);

			if (key.empty() || val.empty())
			{
				ei._errNo = ERR_INI_SYNTAX_ERR;
				ei._lineNum = lineNum;
				break;
			}

			li._key = key;
			li._val = val;
		}

		_allLine[lineNum] = li;
		if (ei._errNo)
		{
			break;
		}

	}// end while

	if (ei._errNo)
	{
		return -1;
	}
	// do transfer
	this->Transfer();
	_bscan = true;
	return 0;
}

int IniReaderPlus::Transfer()
{
	cout<<"xx"<<endl;
	for (auto it = _allLine.begin(); it != _allLine.end(); ++it)
	{
		if (typ_field != it->second._type)
		{
			continue;
		}
		cout<<"xx"<<endl;
		//
		map<string, map<string, LineInfo> *>::iterator iter = _cfgDict.find(it->second._sectionName);
		if (iter != _cfgDict.end())
		{
			(iter->second)->insert(make_pair(it->second._key, it->second));
		}
		else 
		{
			map<string, LineInfo> *tmp = new map<string, LineInfo>;
			tmp->insert(make_pair(it->second._key, it->second));
			_cfgDict.insert(make_pair(it->second._sectionName, tmp));
		}
	}

	return 1;
}

void IniReaderPlus::show() 
{
	if (!_bscan) 
	{
		int ret = ScanCfgFile();
		cout<<"ret:"<<ret<<endl;
	}

	cout<<"s"<<endl;
	auto it = _cfgDict.begin();
	while (it != _cfgDict.end()) 
	{
		cout<<it->first<<endl;
		auto it_in = it->second->begin();
		while (it_in != ((it->second))->end()) 
		{
			cout<<(it_in)->first<<"="<<(it_in)->second._val<<endl;
			++it_in;
		}
		++it;
	}
}

int IniReaderPlus::Remove(std::string &section, std::string &key)
{	
	
	return 1;
}

int IniReaderPlus::Modify(std::string &section, std::string &key, std::string &newval)
{
	return 1;
}

}// namespace ACE
