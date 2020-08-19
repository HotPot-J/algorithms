#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*
题目描述
输入一颗二叉树的根节点和一个整数，按字典序打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点
开始往下一直到叶结点所经过的结点形成一条路径。
*/
/*
思路：dfs 回溯 注意对左右子树都为空的正确结果截胡（防止左右两次回溯，造成重复）
*/

struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};
class Solution {
public:
	vector<vector<int>> res;
	vector<int> path;
	void dfs(TreeNode* root, int& expectNumber, int tmp){
		if (root == NULL&&tmp == expectNumber){
			//保存结果
			res.push_back(path);
			return;
		}
		//大于目标值不必再继续
		if (tmp>expectNumber){ return; }
		if (root == NULL){ return; }
		tmp += root->val;
		path.push_back(root->val);
		//如果该路径结果正确 且该节点的左右孩子都为空 则截胡 
		if (tmp == expectNumber&&root->left == NULL&&root->right == NULL){
			res.push_back(path);
			tmp -= root->val;
			path.pop_back();
			return;
		}
		//递归
		dfs(root->left, expectNumber, tmp);
		dfs(root->right, expectNumber, tmp);


		//回溯
		path.pop_back();
		tmp -= root->val;
	}
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
		vector<vector<int>> path;
		if (root == NULL){ return path; }
		dfs(root, expectNumber, 0);
		return res;
	}
};


/*
题目描述
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于数组的
后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
*/
/*
思路：最直接简单且粗暴的就是开空间
时间复杂度O（n） 空间复杂度O（2）
*/
class Solution {
public:
	void reOrderArray(vector<int> &array) {
		vector<int> tmp;
		tmp.resize(array.size(), 0);
		int i = 0;
		for (auto e : array){
			if (e % 2 != 0){
				tmp[i++] = e;
			}
		}
		for (auto e : array){
			if (e % 2 == 0){
				tmp[i++] = e;
			}
		}
		array = tmp;
	}
};