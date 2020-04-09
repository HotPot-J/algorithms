#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

/*
面试题34. 二叉树中和为某一值的路径
输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。
从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。
示例:
给定如下二叉树，以及目标和 sum = 22，
 5
 / \
4    8
/    / \
11  13  4
/  \    / \
7   2  5   1
返回:
[
[5,4,11,2],
[5,8,4,5]
]
提示：
节点总数 <= 10000
*/


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
/*
思路：回溯法 使用path记录路径 tar初始化为sum
当tar==0 并 root->right==NULL&&root->left==NULL时将当前路径放入ret中 
否则进行回溯 使tar-=当前root->val 以先序遍历的方式去寻找正确解
*/
class Solution {
public:
	vector<vector<int>> ret;
	vector<int> path;
	void findPath(TreeNode* root, int tar){
		if (root == NULL) return ;
		path.push_back(root->val);
		tar -= root->val;
		if (tar == 0 && root->left == NULL&&root->right == NULL){
			//该路径满足
			ret.push_back(path);
		}
		findPath(root->left, tar);
		findPath(root->right, tar);
		//将不满足的路径pop出来
		path.pop_back();
	}
	vector<vector<int>>pathSum(TreeNode* root, int sum) {
		findPath(root, sum);
		return ret;
	}
};

/*
面试题28. 对称的二叉树
请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。
例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
1
/ \
2   2
/ \ / \
3  4 4  3
但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
1
/ \
2   2
\   \
3    3

示例 1：
输入：root = [1,2,2,3,4,4,3]
输出：true
示例 2：
输入：root = [1,2,2,null,3,null,3]
输出：false
限制：
0 <= 节点个数 <= 1000
*/
class Solution {
public:
	bool fun(TreeNode* _left, TreeNode* _right){
		if (_left == NULL&&_right == NULL){
			return true;
		}
		if (_left == NULL || _right == NULL){
			return false;
		}
		if (_left->val != _right->val){
			return false;
		}
		return fun(_left->left, _right->right) && fun(_left->right,_right->left);//前序遍历
	}
	bool isSymmetric(TreeNode* root) {
		if (root == NULL){
			return true;
		}
		return fun(root->left, root->right);
	}
};