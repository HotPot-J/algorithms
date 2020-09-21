#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
1372. 二叉树中的最长交错路径
给你一棵以 root 为根的二叉树，二叉树中的交错路径定义如下：

选择二叉树中 任意 节点和一个方向（左或者右）。
如果前进方向为右，那么移动到当前节点的的右子节点，否则移动到它的左子节点。
改变前进方向：左变右或者右变左。
重复第二步和第三步，直到你在树中无法继续移动。
交错路径的长度定义为：访问过的节点数目 - 1（单个节点的路径长度为 0 ）。

请你返回给定树中最长 交错路径 的长度。
*/


/*
思路：dfs 深度优先遍历
   从根开始，寻找其左子树的最长交叉路经
             再寻找其右子树的最长交叉路经
*/
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	int res;
	//flag为true向左，flag为false向右
	void dfs(TreeNode* cur, bool flag, int len){
		if (cur == NULL) return;
		res = max(res, len);
		if (flag){
			dfs(cur->left, false, len + 1); //走左  false代表下一次走右  
			//如果走到这里，说明当前cur没有左结点，只能从走右重新去寻找，以当前结点开始的最长交叉路径
			//所以将len置为1 （0+1）
			dfs(cur->right, true, 1);//走右 true代表下一次走左  
		}
		else{
			dfs(cur->right, true, len + 1);
			dfs(cur->left, false, 1);
		}
	}
	int longestZigZag(TreeNode* root) {
		if (root == NULL) return 0;
		res = 0;
		dfs(root, true, 0);
		dfs(root, false, 0);
		return res;
	}
};

/*
978. 最长湍流子数组
当 A 的子数组 A[i], A[i+1], ..., A[j] 满足下列条件时，我们称其为湍流子数组：
若 i <= k < j，当 k 为奇数时， A[k] > A[k+1]，且当 k 为偶数时，A[k] < A[k+1]；
或 若 i <= k < j，当 k 为偶数时，A[k] > A[k+1] ，且当 k 为奇数时， A[k] < A[k+1]。
也就是说，如果比较符号在子数组中的每个相邻元素对之间翻转，则该子数组是湍流子数组。
返回 A 的最大湍流子数组的长度。
示例 1：
输入：[9,4,2,10,7,8,8,1,9]
输出：5
解释：(A[1] > A[2] < A[3] > A[4] < A[5])
示例 2：
输入：[4,8,12,16]
输出：2
示例 3：
输入：[100]
输出：1
*/
class Solution1 {
public:
	int maxTurbulenceSize(vector<int>& A) {
		int len = A.size();
		if (len <= 1) return len;
		vector<int> up(len + 1, 1);
		vector<int> down(len + 1, 1);
		int res = 0;
		for (int i = 2; i <= len; ++i){
			if (A[i - 2] > A[i - 1]){
				//下降
				up[i] = down[i - 1] + 1;
				down[i] = 1;
			}
			else if (A[i - 2] < A[i - 1]){
				//上升
				up[i] = 1;
				down[i] = up[i - 1] + 1;
			}
			else{
				up[i] = 1;
				down[i] = 1;
			}
			res = max(res, up[i]);
			res = max(res, down[i]);
		}
		return res;
	}
};

int main(){
	vector<int> arr = { 9, 4, 2, 10, 7, 8, 8, 1, 9 };
	Solution1 a;
	a.maxTurbulenceSize(arr);
	return 0;
}
class Solution {
public:
	/**
	*
	* @param num int整型 非负整数 num
	* @return int整型vector
	*/
	int fun(int a){
		int res = 0;
		for (int i = 0; i < 32; ++i){
			if ((a >> i) & 1) ++res;
		}
		return res;
	}
	vector<int> countBits(int num) {
		vector<int> res;
		for (int i = 0; i <= num; ++i){
			res.push_back(fun(i));
		}
		return res;
	}
};
//class Solution {
//public:
//	/**
//	* 合并数组
//	* @param arrayA int整型一维数组 数组A
//	* @param arrayALen int arrayA数组长度
//	* @param arrayB int整型一维数组 数组B
//	* @param arrayBLen int arrayB数组长度
//	* @return int整型vector
//	*/
//	vector<int> mergerArrays(int* arrayA, int arrayALen, int* arrayB, int arrayBLen) {
//		// write code here
//		vector<int> res;
//		if (arrayA == NULL || arrayB == NULL) return res;
//		unordered_map<int, bool> mapa;
//		for (int i = 0; i < arrayALen; ++i){
//			mapa[arrayA[i]] = true;
//		}
//		for (int i = 0; i < arrayBLen; ++i){
//			if (mapa[arrayB[i]] == true){
//				res.push_back(arrayB[i]);
//			}
//		}
//		sort(res.begin(), res.end());
//	}
//};
int main(){
	Solution a;
	a.countBits(5);

	return 0;
}