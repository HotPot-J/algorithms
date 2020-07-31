#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
链接：https://www.nowcoder.com/questionTerminal/57d85990ba5b440ab888fc72b0751bf8
来源：牛客网
[编程题]剪绳子
热度指数：157428时间限制：C/C++ 1秒，其他语言2秒空间限制：C/C++ 64M，其他语言128M
算法知识视频讲解
给你一根长度为n的绳子，请把绳子剪成整数长的m段（m、n都是整数，n>1并且m>1，m<=n），每段绳子的长度记为k[1],...,k[m]。请问k[1]x...xk[m]可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，
此时得到的最大乘积是18。
输入描述:
输入一个数n，意义见题面。（2 <= n <= 60）
输出描述:
输出答案。
示例1
输入
8
输出
18
*/

/*
思路:动态和规划： dp[i] = max(dp[i],dp[i-j]*j)
*/

class Solution {
public:
	int cutRope(int number) {
		vector<int> dp;
		dp.resize(number + 1, 1);
		for (int i = 1; i <= number; ++i){
			for (int j = 1; j <= i; ++j){
				dp[i] = max(dp[i], dp[i - j] * j);
			}
		}
		return dp[number];
	}
};

/*
链接：https://www.nowcoder.com/questionTerminal/6e5207314b5241fb83f2329e89fdecc8
来源：牛客网

[编程题]机器人的运动范围
热度指数：360503时间限制：C/C++ 1秒，其他语言2秒空间限制：C/C++ 32M，其他语言64M
算法知识视频讲解
地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），
因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？
*/

/*
思路:dfs 递归
*/
class Solution {
public:
	bool check(vector<vector<int>>& map, int threshold, int rows, int cols, int i, int j){
		//越界
		if (i<0 || i >= rows || j<0 || j >= cols)
			return false;
		//不满足阈值
		if (map[i][j] == -1) { return false; }
		else{
			int tmp = 0;
			while (i){ tmp += (i % 10); i /= 10; }
			while (j){ tmp += (j % 10); j /= 10; }
			if (tmp>threshold){ map[i][j] == -1; return false; }
		}
		return true;
	}
	void fun(vector<vector<int>>&map, int threshold, int rows, int cols, int i, int j, int& res){
		if (!check(map, threshold, rows, cols, i, j)){
			//不满足条件
			return;
		}
		if (map[i][j] == 0){
			++res;
			map[i][j] = -1; //代表统计过了
		}
		//进行上下左右的寻路过程
		fun(map, threshold, rows, cols, i - 1, j, res);
		fun(map, threshold, rows, cols, i + 1, j, res);
		fun(map, threshold, rows, cols, i, j - 1, res);
		fun(map, threshold, rows, cols, i, j + 1, res);
	}
	int movingCount(int threshold, int rows, int cols)
	{
		vector<vector<int>> map(rows, vector<int>(cols, 0));
		int res = 0;
		fun(map, threshold, rows, cols, 0, 0, res);
		return res;
	}
};

