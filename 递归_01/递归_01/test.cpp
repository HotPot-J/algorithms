#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

/*面试题10- I. 斐波那契数列
写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项。斐波那契数列的定义如下：
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
示例 1：
输入：n = 2
输出：1
示例 2：
输入：n = 5
输出：5
提示：
0 <= n <= 100
*/
class Solution {
public:
	int fib(int n) {
		if (n == 0){
			return 0;
		}
		if (n == 1){
			return 1;
		}
		int a = 0, b = 1, r = 1;
		for (int i = 2; i <= n; ++i){
			r = (a + b) % 1000000007;
			a = b;
			b = r;
		}
		return r;
	
	}
};

/*
面试题10- II. 青蛙跳台阶问题
一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
示例 1：
输入：n = 2
输出：2
示例 2：
输入：n = 7
输出：21
提示：
0 <= n <= 100
*/
//思路：动态规划 
//当台阶为2是 有两种选择 选择一次一步此时方法个数为前f(n-1) 选择一次2步此时方法为前f(n-2) 所以递推方程为
//f(n) = f(n-1)+f(n-2)  有例题可推出 f(0) = 1 f(1) = 1
class Solution {
public:
	int numWays(int n) {
		//由于从0至n个数据 所以声明为n+1个空间
		vector<int> a(n + 1, 1);
		for (int i = 2; i <= n; ++i){
			a[i] = (a[i - 1] + a[i - 2]) % 1000000007;
		}
		return a[n];
	}
};