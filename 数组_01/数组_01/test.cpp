#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*链接：https://www.nowcoder.com/questionTerminal/94a4d381a68b47b7a8bed86f2975db46
来源：牛客网

[编程题]构建乘积数组
热度指数：240898时间限制：C / C++ 1秒，其他语言2秒空间限制：C / C++ 32M，其他语言64M
算法知识视频讲解
给定一个数组A[0, 1, ..., n - 1], 请构建一个数组B[0, 1, ..., n - 1], 其中B中的元素B[i] = A[0] * A[1] * ...*A[i - 1] * A[i + 1] * ...*A[n - 1]。不能使用除法。（注意：规定B[0] = A[1] * A[2] * ... * A[n - 1]，B[n - 1] = A[0] * A[1] * ... * A[n - 2]; ）
对于A长度为1的情况，B无意义，故而无法构建，因此该情况不会存在。
*/

/*
思路:上下三角连乘，动态规划
f（i+1） =  f(i-1)*A[i-1]
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
		int tmp = 1;//改tmp起到保留上一层乘积的作用
		for (int i = len - 2; i >= 0; --i){
			tmp *= A[i + 1];
			B[i] *= tmp;
		}
		return B;
	}
};