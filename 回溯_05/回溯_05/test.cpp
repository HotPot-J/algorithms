#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
/*
77. 组合
给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
示例:
输入: n = 4, k = 2
输出:
[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]
*/
class Solution2 {
public:
	vector<vector<int>> res;
	vector<int> tmp;
	vector<vector<int>> combine(int n, int k) {
		dfs(1, n, k);
		return res;
	}
	void dfs(int begin, int n, int k){
		if (tmp.size() == k){
			//符合条件
			res.push_back(tmp);
			return;
		}
		for (int i = begin; i <= n; ++i){
			tmp.push_back(i);
			dfs(i + 1, n, k);
			tmp.pop_back();
		}
	}
};
//int main(){
//	Solution a;
//	a.combine(3, 2);
//	return 0;
//}

/*
357. 计算各个位数不同的数字个数
给定一个非负整数 n，计算各位数字都不同的数字 x 的个数，其中 0 ≤ x < 10^n 。
示例:
输入: 2
输出: 91
解释: 答案应为除去 11,22,33,44,55,66,77,88,99 外，在 [0,100) 区间内的所有数字。
*/

//思路：哈希表（但是时间复杂度过高）
class Solution1 {
public:
	vector<int> map;
	int res = 0;
	bool a = true;
	int countNumbersWithUniqueDigits(int n) {
		int tmp = (int)pow((double)10, (double)n);
		for (int i = 0; i < tmp; ++i){
			map = { 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0};
			int flag = i;
			while (flag){
				int a = flag % 10;
				flag = flag / 10;
				++map[a];
			}
			for (int i = 0; i <= 9;++i){
				if (map[i]>1){
				 //说明有重复
					a = false;
					break;
				}
			}
			if (a){
				++res;
			}
			a = true;
		}
		return res;
	}
};

/* 
   采用动态规划，如下规律：
   根据排列组合
   一位数：0-9  10种
   2位数： 9*9+一位数的可能性
   3位数：9*9*8+两位数的可能性+一位数的可能性
   
   根据此规律： 使用动态规划 
*/
class Solution {
public:
	int countNumbersWithUniqueDigits(int n) {
		if (n == 0){
			return 1;
		}
		if (n == 1){
			return 10;
		}
		int* dp = new int[n + 1];
		dp[1] = 10; dp[2] = 81;
		int sum = dp[1] + dp[2];
		for (int i = 3; i <= n; ++i){
			dp[i] = dp[i - 1] * (10 - i + 1);
			sum += dp[i];
		}
		return sum;
	}
};

int main(){
	Solution a;
	a.countNumbersWithUniqueDigits(0);
	return 0;
}