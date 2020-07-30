#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*���ӣ�https://www.nowcoder.com/questionTerminal/94a4d381a68b47b7a8bed86f2975db46
��Դ��ţ����

[�����]�����˻�����
�ȶ�ָ����240898ʱ�����ƣ�C / C++ 1�룬��������2��ռ����ƣ�C / C++ 32M����������64M
�㷨֪ʶ��Ƶ����
����һ������A[0, 1, ..., n - 1], �빹��һ������B[0, 1, ..., n - 1], ����B�е�Ԫ��B[i] = A[0] * A[1] * ...*A[i - 1] * A[i + 1] * ...*A[n - 1]������ʹ�ó�������ע�⣺�涨B[0] = A[1] * A[2] * ... * A[n - 1]��B[n - 1] = A[0] * A[1] * ... * A[n - 2]; ��
����A����Ϊ1�������B�����壬�ʶ��޷���������˸����������ڡ�
*/

/*
˼·:�����������ˣ���̬�滮
f��i+1�� =  f(i-1)*A[i-1]
*/
class Solution {
public:
	vector<int> multiply(const vector<int>& A) {
		int len = A.size();
		vector<int> B;
		B.resize(len, 0);
		B[0] = 1;
		for (int i = 1; i<len; ++i){
			B[i] = B[i - 1] * A[i - 1];
		}
		int tmp = 1;//��tmp�𵽱�����һ��˻�������
		for (int i = len - 2; i >= 0; --i){
			tmp *= A[i + 1];
			B[i] *= tmp;
		}
		return B;
	}
};