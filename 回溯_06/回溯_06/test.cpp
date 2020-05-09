#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

/*
22. 括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
示例：
输入：n = 3
输出：[
"((()))",
"(()())",
"(())()",
"()(())",
"()()()"
]
*/

/*
思路：回溯法 通过left和right分别判断当前左右括号的放置数量，当left<n 才可放置(   当right<left才可放置 )
通过回溯去寻找各种可能解
*/
//class Solution {
//public:
//	vector<string> res;
//	string tmp;
//	vector<string> generateParenthesis(int n) {
//		fun(0, 0, n);
//		return res;
//	}
//	void fun(int left, int right, int n){
//		if (left == n&&right == n){
//			res.push_back(tmp);
//			return;
//		}
//		if (left < n){
//			tmp += '(';
//			fun(left + 1, right, n);
//			tmp.pop_back();
//		}
//		if (right < left){
//			tmp += ')';
//			fun(left, right + 1, n);
//			tmp.pop_back();
//		}
//	}
//};

//int main(){
//	Solution a;
//	a.generateParenthesis(3);
//	return 0;
//}

/*
89. 格雷编码
格雷编码是一个二进制数字系统，在该系统中，两个连续的数值仅有一个位数的差异。
给定一个代表编码总位数的非负整数 n，打印其格雷编码序列。即使有多个不同答案，你也只需要返回其中一种。
格雷编码序列必须以 0 开头。
示例 1:
输入: 2
输出: [0,1,3,2]
解释:
00 - 0
01 - 1
11 - 3
10 - 2
对于给定的 n，其格雷编码序列并不唯一。
例如，[0,2,3,1] 也是一个有效的格雷编码序列。
00 - 0
10 - 2
11 - 3
01 - 1
示例 2:
输入: 0
输出: [0]
解释: 我们定义格雷编码序列必须以 0 开头。
给定编码总位数为 n 的格雷编码序列，其长度为 2^n。当 n = 0 时，长度为 2^0 = 1。
因此，当 n = 0 时，其格雷编码序列为 [0]。
*/

/*
思路：  借鉴了力扣上的大佬 这个解法属实自己没想出来
  设 nn 阶格雷码集合为 G(n)G(n)，则 G(n+1)G(n+1) 阶格雷码为：
给 G(n)G(n) 阶格雷码每个元素二进制形式前面添加 00，得到 G'(n)G ′(n)；
设 G(n)G(n) 集合倒序（镜像）为 R(n)R(n)，给 R(n)R(n) 每个元素二进制形式前面添加 11，得到 R'(n)R ′(n)；
G(n+1) = G'(n) ∪ R'(n)G(n+1)=G ′(n)∪R ′(n) 拼接两个集合即可得到下一阶格雷码。
根据以上规律，可从 00 阶格雷码推导致任何阶格雷码。

n = 0  ： 0
n = 1  ： 0                 1
n = 2  ： 00  01            11 10
n = 3  ： 000 001 011       111 101 100
*/
class Solution {
public:
	vector<int> grayCode(int n) {
		vector<int> res;
		res.push_back(0);
		int head = 1;
		for (int i = 0; i < n; ++i){
			for (int j = res.size() - 1; j >= 0; --j){ //倒序操作
				//为其首位添加1
				int tmp = res[j] | head;
				res.push_back(tmp);
			}
			head <<= 1; //head放大一位  
		}
		return res;
	}
};

