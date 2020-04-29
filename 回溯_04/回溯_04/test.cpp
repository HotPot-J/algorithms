#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

/*
39. 组合总和
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。
示例 1:
输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
[7],
[2,2,3]
]
示例 2:
输入: candidates = [2,3,5], target = 8,
所求解集为:
[
[2,2,2,2],
[2,3,3],
[3,5]
]
*/
//思想：回溯 深度优先搜索
class Solution {
public:
	//定义全局变量 
	vector<vector<int>> res;
	vector<int> path;
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());//排序 若当前数字已经不适合加入path 那么其后面的数字更不合适 进行“剪枝”
		dfs(0, target, candidates);
		return res;
	}
	void dfs(int begin,int target,vector<int>& candidates){
		//begin为本轮搜索的起点下标  
		if (target == 0){
			//找到可行解
			res.push_back(path);
			return;
		}
		for (size_t i = begin; i < candidates.size(); ++i){
		  //使用这样的起点循环巧妙地去重（打比方 搜索完含有1的所有可行解 就不用1了 而是去搜索包含下一个数字的全部可行解）
			if (target - candidates[i] < 0){
				//不符合条件 "剪枝" 后边的数字也不用判断了 退出循环进行回溯
				break;
			}
			path.push_back(candidates[i]);
			dfs(i, target - candidates[i], candidates);
			path.pop_back();
		}
	}
};

//int main(){
//	vector<int> a = { 2,3,6,7 };
//	Solution b;
//	b.combinationSum(a, 7);
//	return 0;
//}

/*
40. 组合总和 II
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。
说明：
所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。
示例 1:
输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
[1, 7],
[1, 2, 5],
[2, 6],
[1, 1, 6]
]
示例 2:
输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
[1,2,2],
[5]
]
*/
class Solution {
public:
	vector<vector<int>> res;
	vector<int> path;
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end()); 
		dfs(0,target,candidates);
		return res;
	}

	void dfs(int begin,int target,vector<int>& candidates){
		if (target == 0){
			//符合条件
			res.push_back(path);
			return;
		}
		for (int i = begin; i < candidates.size(); ++i){
			if (target - candidates[i] < 0){
				break;
			}
			if (i>begin&&candidates[i] == candidates[i - 1]){
				//相同层次剪枝 如果说当前项和前一项相等 
				/*
				对于 1 1 2 3 4来所
				下标为0起始时  其候选项为1，2，3，4
				下标为1起始时  其候选项为2，3，4    所以下标为1的可行结果一定在下标为0的情况中出现过 需要进行剪枝
				*/
				continue;
			}
			path.push_back(candidates[i]);
			dfs(i+1, target - candidates[i], candidates); //这里较上一题为i+1是由于每个数字只能使用一次
			path.pop_back();
		}
	}
};
int main(){
	vector<int> a = { 10, 1, 2, 7, 6, 1, 5 };
	Solution b;
	b.combinationSum2(a,8);
	return 0;
}

/*
216. 组合总和 III
找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。
说明：
所有数字都是正整数。
解集不能包含重复的组合。
示例 1:
输入: k = 3, n = 7
输出: [[1,2,4]]
示例 2:
输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
*/
class Solution {
	vector<vector<int>> res;
	vector<int> tmp;
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		dfs(1, k, n);
		return res;
	}
	void dfs(int begin, int k, int n){
		if (n == 0 && tmp.size() == k){
			//满足收割条件
			res.push_back(tmp);
			return;
		}
		for (int i = begin; i < 10; ++i){
			if (n - i < 0){
				//剪枝
				break;
			}
			if (tmp.size() >= k){
				//当前tmp没达到收割条件 而且尺度即将或已经超出k 剪枝
				break;
			}
			tmp.push_back(i);
			dfs(i + 1, k, n-i);
			tmp.pop_back();
		}
	}
};
int main(){
	Solution b;
	b.combinationSum3(3, 7);
	return 0;
}
