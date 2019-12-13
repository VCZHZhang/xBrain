#ifndef __ERROR_INFO_H__
#define __ERROR_INFO_H__
#include <string>
// error no.


typedef struct ErrorInfo
{
    ErrorInfo()
    {
        _errNo = 0;
    }

    int _errNo;
    int _lineNum;
    std::string _info;
}ErrorInfo;


enum ErrNo
{
    //  IniReader
    ERR_INI_SYNTAX_ERR = 1,
    ERR_INI_NO_SECTION = 2

};



#endif 