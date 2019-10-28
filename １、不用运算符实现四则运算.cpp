#include <iostream>
using namespace std;

//实现加法
int getAddNumber(int a,int b)
{
	if( b == 0 ) return a;
	int sum = a^b;
    //可以得到进位
	int carray = ( a & b ) << 1;
	return  getAddNumber(sum,carray);
}


int main()
{
    cout<< getAddNumber(-25,30) << endl;
    return 0;
}
