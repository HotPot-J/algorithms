#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std; 
/*
121. 买卖股票的最佳时机
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
注意：你不能在买入股票前卖出股票。
示例 1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
*/
/*
思路:
	维护一个最小值（买入点）
	维护一个最大值（卖出点）
*/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int _min = INT_MAX;
		int res = 0;
		for (int i = 0; i < prices.size(); ++i){
			if (prices[i] < _min){
				_min = prices[i];
			}
			else if (prices[i] - _min>res){
				res = prices[i] - _min;
			}
		}
		return res;
	}
};
//int main(){
//	vector<int> arr = { 7, 1, 5, 3, 6, 4 };
//	Solution a;
//	cout<<a.maxProfit(arr)<<endl;
//	return 0;
//}
/*
198. 打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有
相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。给定一个代表每个房屋存放金额的非
负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
示例 1：
输入：[1, 2, 3, 1]
输出：4
解释：偷窃 1 号房屋(金额 = 1) ，然后偷窃 3 号房屋(金额 = 3)。
偷窃到的最高金额 = 1 + 3 = 4 。
示例 2：
输入：[2, 7, 9, 3, 1]
输出：12
解释：偷窃 1 号房屋(金额 = 2), 偷窃 3 号房屋(金额 = 9)，接着偷窃 5 号房屋(金额 = 1)。
偷窃到的最高金额 = 2 + 9 + 1 = 12 。*/
/*
1.目标，在不触发报警装置的情况下能偷到的最大金额
2.状态:f(i):偷到第i家时的最大金额
3.f(2):2  (代表第一家)
  f(3):7 (不能连续偷)
  f(4):f(1)+arr[3-1]
f(i) = max(f(i),f(j)+arr[i-2]) （j<i-1）
*/
class Solution1 {
public:
	int rob(vector<int>& nums) {
		if (nums.empty()) return 0;
		int len = nums.size();
		vector<int> dp(len + 2, 0);
		int res = INT_MIN;
		for (int i = 2; i <= len + 1; ++i){
			for (int j = 0; j < i - 1; ++j){
				dp[i] = max(dp[i], dp[j] + nums[i - 2]);
			}
			if (dp[i]>res) res = dp[i];
		}
		return res;
	}
};
//int main(){
//	vector<int> arr = { 2, 7, 9, 3, 1 };
//	Solution1 a;
//	cout << a.rob(arr) << endl;
//	return 0;
//}

/*
303. 区域和检索 - 数组不可变
给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。

示例：

给定 nums = [-2, 0, 3, -5, 2, -1]，求和函数为 sumRange()

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
说明:

你可以假设数组不可变。
会多次调用 sumRange 方法。
*/

/*
思路一：动态规划（比暴力法能好点，空间换时间）
1.f(i,j):表示从i-j之和
2.由于只有i~j,不会有j~i,所以这是一个上半三角矩阵
3.i=j:f(i,j) = nums[j]
  i<j:f(i,j) = dp[i][j-1]+nums[j]
*/
class NumArray {
	vector<vector<int>> dp;
public:
	NumArray(vector<int>& nums) {
		int len = nums.size();
		dp.resize(len);
		for (int i = 0; i < len; ++i){
			dp[i].resize(len, 0);
			for (int j = i; j< len; ++j){
				if (i == j){ dp[i][j] = nums[j];}
				else{ dp[i][j] = dp[i][j - 1] + nums[j]; }
			}
		}
	}

	int sumRange(int i, int j) {
		return dp[i][j];
	}
};
//int main(){
//	vector<int> arr = { -2, 0, 3, -5, 2, -1 };
//	NumArray a(arr);
//	cout << a.sumRange(0, 2) << endl;
//	cout << a.sumRange(2, 5) << endl;
//	cout << a.sumRange(0, 5) << endl;
//	return 0;
//}

/*
思路二：动态规划（优化）
f(i)表示从第一个数字到第i个数字之和
f(i) = f(i-1)+nums[i]
nums:-2, 0, 3, -5, 2, -1
f(i):0,-2,-2,1,-4,-2,-1 (初始状态f(0)=0)
F(0,0) = f(1)-f(0) = -2
F(0,5):f(6)-f(0) = -1

那么F(i,j) = f(j+1)-f(i)
初始状态:f(0) = 0;
*/

class NumArray1 {
public:
	vector<int> dp;
	NumArray1(vector<int>& nums) {
		dp.resize(nums.size() + 1, 0);
		for (int i = 1; i <= nums.size(); ++i){
			dp[i] = dp[i - 1] + nums[i - 1];
		}
	}

	int sumRange(int i, int j) {
		return dp[j + 1] - dp[i];
	}
};

/*
746. 使用最小花费爬楼梯
数组的每个索引作为一个阶梯，第 i个阶梯对应着一个非负数的体力花费值 cost[i](索引从0开始)。
每当你爬上一个阶梯你都要花费对应的体力花费值，然后你可以选择继续爬一个阶梯或者爬两个阶梯。
您需要找到达到楼层顶部的最低花费。在开始时，你可以选择从索引为 0 或 1 的元素作为初始阶梯。
示例 1:
输入: cost = [10, 15, 20]
输出: 15
解释: 最低花费是从cost[1]开始，然后走两步即可到阶梯顶，一共花费15。
示例 2:
输入: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
输出: 6
解释: 最低花费方式是从cost[0]开始，逐个经过那些1，跳过cost[3]，一共花费6。
注意：
cost 的长度将会在 [2, 1000]。
每一个 cost[i] 将会是一个Integer类型，范围为 [0, 999]。
*/

/*
思路:
	目标:到达楼层顶部的最低花费 
	状态: f(i)表示到达当前楼层的最低花费
	初始状态f(0):0 表示一开始在起点位置的花费为0
	f(1):cost[0]如果跳上第一阶的花费为cost[0]
	f(2):cost[1]如果跳上第二阶的花费为cost[1]
	f(3):min(cost[0],cost[1])+cost[2]
	即：f(i) = min(f(i-1),f(i-2))+cost[i-1]

	int len = cost.size();
	我们可以将数组多开辟两个位置，f(0)=0最为初始状态，而f(i+1)存储结果
*/

class Solution3 {
public:
	int minCostClimbingStairs(vector<int>& cost) {
		if (cost.empty()) return 0;
		int len = cost.size();
		vector<int> dp(len + 2, 0);
		dp[1] = cost[0];
		for (int i = 2; i <= len + 1; ++i){
			dp[i] = min(dp[i - 1], dp[i - 2]);
			if (i <len+1){ dp[i] += cost[i - 1]; }
		}
		return dp[len + 1];
	}
};
//int main(){
//	vector<int> arr = { 10, 15, 20 };
//	Solution3 a;
//	a.minCostClimbingStairs(arr);
//	return 0;
//}