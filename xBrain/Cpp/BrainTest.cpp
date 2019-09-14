#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

/**
 * Welcome to vivo !
 */

#define MAX_NUM 101
int dp[10005][2];//1代表前面的珠子消去，0代表没消去 
int solution(int boxs[], int N)
{
        // TODO Write your code here
	dp[1][0] = 0;
	
	for (int i = 2; i <= N; i++)
	{
		dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);//当前珠子没消去 
		dp[i][1] = dp[i - 1][0] + boxs[i] * boxs[i - 1];//当前珠子消去 
	} 

 	return max(dp[N][0], dp[N][1]);
}

int main()
{
	string str("");
	 getline(cin, str);
	 int boxs[MAX_NUM];
	 int i = 1;
	 char *p;
	 int count = 0;
	 
	 const char* strs = str.c_str();
	 p = strtok((char *)strs, " ");
	 while(p)
	 {
	  	boxs[i] = atoi(p);
	  	count++;
	  	p = strtok(NULL, " ");
	  	i++;
	  	if(i >= MAX_NUM)
	   	break;
	 }
	
	 int num = solution(boxs, count);
	 	cout << num << endl;
	 return 0;
}
