#include "IniReaderPlusTest.h"
#include "../xFile/IniReaderPlus.h"
void IniTest()
{
    ACE::IniReaderPlus  ini("./test.ini");
    std::string v1 = ini.GetValue("section", "key");
    cout<<"----------"
    cout<<"va:"<<v1<<endl;
    ini.show();

}