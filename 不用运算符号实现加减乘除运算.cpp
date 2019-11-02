#include <iostream>
using namespace std;

//�ӷ�
//(�ݹ鷽��)
int getAddNumber(int a, int b)
{
	if (b == 0) return a;
	int sum = a^b;
	//���Եõ���λ
	int carray = (a & b) << 1;
	return  getAddNumber(sum, carray);
}
//(�ǵݹ鷽��)
int getAddNumber1(int a, int b) {
	while (b) {
		// ��ֹ AddressSanitizer ���з������Ƶ������������
		auto c = ((unsigned int)a & b) << 1;
		a = a ^ b;
		b = c;
	}
	return a;
}
int getAddNumber2(int a, int b) {
	int sum;
	int carry;
	if (a == 0) return b;
	if (b == 0) return a;
	carry = a & b;
	sum = a ^ b;
	while (carry) {
		int temp = sum;
		//���λΪ1���������ƻᱨ��, ʹcarry���λ��ԶΪ0
		carry = carry & (-1);
		sum = sum ^ (carry << 1);
		carry = temp & (carry << 1);
	}
	return sum;
}
//����
int getSubNUm(int a, int b)
{
	while (b != 0)
	{
		// ȥ���������ͼ�����ͬΪ1��λ
		int sameNum = a & b;
		a ^= sameNum;
		b ^= sameNum;
		// ��ʱ��a �� b ������ͬʱΪ1 ��λ
		// 0 - 1 �� 1 - 0 ��Ϊ1
		a |= b; // �õ��������ʱ����������ǽ�λ��
		b = b << 1; // ����Ϊ1 ʱ�����н�λ
	}
	return a;
}


int maxNumFlag()
{
	int bitsOfByte = 8;

	int maxNum = 0x80;
	int tmp = maxNum;
	while (tmp != 0)
	{
		maxNum = tmp;
		tmp <<= bitsOfByte;
	}
	return maxNum;
}

//�˷�
int getMultip(int a, int b)
{
	// 1.��ֻ���������������
	// 2.��������������������

	int maxNum = maxNumFlag();
	int flag_a = 1;
	if ((maxNum & a) != 0)
	{
		flag_a = 0; // ����
		a = getAddNumber(~a, 1);
	}

	int flag_b = 1;
	if ((maxNum & b) != 0)
	{
		flag_b = 0;
		b = getAddNumber(~b, 1);
	}

	int result = 0;
	for (int bits = 1; bits != 0; bits <<= 1)
	{
		if ((bits & b) != 0)
		{
			result = getAddNumber(result, a);
			if ((result & maxNum) != 0
				|| (a & maxNum) != 0)
			{
				cout << "���ݹ���" << endl;
			}
		}
		a <<= 1;
	}

	return (flag_a ^ flag_b) == 0 ? result : getAddNumber(~result, 1);
}

//����
int getDivision(int a, int b)
{
	if (b == 0)
	{
		cout<< "��������Ϊ0����"<< endl;
	}

	int maxNum = maxNumFlag();
	int flag_a = 1;
	if ((maxNum & a) != 0)
	{
		flag_a = 0; // ����
		a = getAddNumber(~a, 1);
	}

	int flag_b = 1;
	if ((maxNum & b) != 0)
	{
		flag_b = 0;
		b = getAddNumber(~b, 1);
	}

	int index = 1;
	int tmp = getSubNUm(a, b);
	if (tmp < 0)
	{
		return 0;
	}
	
	while (tmp >= b)
	{
		tmp = getSubNUm(tmp, b); // ���һ��ѭ�����tmp ����a/b ������
		index = getAddNumber(index, 1);
	}
	return (flag_a ^ flag_b) == 0 ? index : getAddNumber(~index, 1);
}

int getDivision1(int a, int b)
{
           
	if (b == 0)
	{
		cout<< "��������Ϊ0����"<< endl;
	}

	int maxNum = maxNumFlag();
	int flag_a = 1;
	if ((maxNum & a) != 0)
	{
		flag_a = 0; // ����
		a = getAddNumber(~a, 1);
	}

	int flag_b = 1;
	if ((maxNum & b) != 0)
	{
		flag_b = 0;
		b = getAddNumber(~b, 1);
	}

	int quotient = 0;
	int backupB = b;
	while (a >= b)
	{
		int tempB = b << 1;
		int tempQ = 1;
		while ((tempB <= a) && ((tempB & maxNumFlag()) == 0))
		{
			b = tempB;
			tempQ <<= 1;
			tempB <<= 1;
		}

		a = getSubNUm(a, b);
		quotient |= tempQ;
		b = backupB;
	}

	if (((maxNum & a) != 0) && (a != 0))
	{
		quotient = getAddNumber(quotient, 1);
	}

	return (flag_a ^ flag_b) == 0 ? quotient : getAddNumber(~quotient, 1);
}

int main()
{
	cout << getAddNumber(-2, 8) << endl;

	cout << getAddNumber1(10, 999999) << endl;
	
	cout << getAddNumber2(-2, -30) << endl;

	cout << getSubNUm(100, -3) << endl;

	cout << getMultip(-30, 6) << endl;

	cout << getDivision(42,3) << endl;

	cout << getDivision(13,2) << endl;
	return 0;
}