#include <iostream>
#include "IniReaderPlusTest.h"
#include "../xFile/IniReaderPlus.h"
using std::endl;
void IniTest()
{
    ACE::IniReaderPlus  ini("./test.ini");
    std::string v1 = ini.GetValue("section", "key");
    std::cout<<"----------"<<endl;
    std::cout<<"va:"<<v1<<endl;
    ini.show();

}