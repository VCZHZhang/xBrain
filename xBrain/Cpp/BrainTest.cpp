#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "EmmManager-Test.h"
using namespace std;
int main(int argc, char **argv)
{
#define __EMM_MANAGER_TEST_
#ifdef __EMM_MANAGER_TEST_
	emm_manager_test_main(argc, argv);
#endif 
	 return 0;
}
