#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
using namespace std;


/*
���ַ���ת��������
��һ���ַ���ת����һ��������Ҫ����ʹ���ַ���ת�������Ŀ⺯���� ��ֵΪ0�����ַ�������һ���Ϸ�����ֵ�򷵻�0
��������:
����һ���ַ���,����������ĸ����,����Ϊ��
�������:
����ǺϷ�����ֵ����򷵻ظ����֣����򷵻�0
*/

/*
˼·���ַ����� - '0' = ����
*/
class Solution {
public:
	int StrToInt(string str) {
		int len = str.size(), j = 0, res = 0, flag = 0;
		if (len>0){
			if (str[0] == '+'){ ++j; }
			else if (str[0] == '-'){ flag = 1; ++j; }
		}
		for (int i = j; i<len; ++i){
			if (!(str[i] >= '0'&&str[i] <= '9')){
				//�������ַ�Χ��
				return 0;
			}
			res = res * 10 + (str[i] - '0');
		}
		if (flag){ res *= (-1); }
		return res;
	}
};

/*
ԲȦ�����ʣ�µ���
ÿ����һ��ͯ��,ţ�Ͷ���׼��һЩС����ȥ�����¶�Ժ��С����,����������ˡ�HF��Ϊţ�͵�����Ԫ��,��ȻҲ׼����һЩС��Ϸ������,�и���Ϸ��������:����,��С������Χ��һ����Ȧ��Ȼ��,�����ָ��һ����m,�ñ��Ϊ0��С���ѿ�ʼ������ÿ�κ���m-1���Ǹ�С����Ҫ���г��׸�,Ȼ���������Ʒ�����������ѡ����,���Ҳ��ٻص�Ȧ��,��������һ��С���ѿ�ʼ,����0...m-1����....������ȥ....ֱ��ʣ�����һ��С����,���Բ��ñ���,�����õ�ţ������ġ�����̽���ϡ���ذ�(��������Ŷ!!^_^)��������������,�ĸ�С���ѻ�õ������Ʒ�أ�(ע��С���ѵı���Ǵ�0��n-1)

���û��С���ѣ��뷵��-1
*/

/*
˼·�����õ�����ѭ����������  ��ģ��ѭ�����ɣ�
*/

class Solution {
public:
	int LastRemaining_Solution(int n, int m)
	{
		vector<int> a;
		int flag = -1;
		for (int i = 0; i<n; ++i){
			a.push_back(i);
		}
		auto it = a.begin();
		while (!a.empty() && it != a.end()){
			if (a.size() == 1){ return a[0]; }
			++flag;
			if (flag == m - 1){
				it = a.erase(it);
				flag = -1;
			}
			else{ ++it; }
			if (!a.empty() && it == a.end()){ it = a.begin(); }
		}
		return -1;
	}
};
