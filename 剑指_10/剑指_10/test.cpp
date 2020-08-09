#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};
/*
平衡二叉树
输入一棵二叉树，判断该二叉树是否是平衡二叉树。

在这里，我们只需要考虑其平衡性，不需要考虑其是不是排序二叉树
*/

/*
思路：前序遍历 
*/
class Solution {
public:
	int fun(TreeNode* pRoot){
		if (pRoot == NULL){
			return 0;
		}
		int leftDepth = fun(pRoot->left) + 1;
		int rightDepth = fun(pRoot->right) + 1;
		return leftDepth>rightDepth ? leftDepth : rightDepth;
	}
	bool IsBalanced_Solution(TreeNode* pRoot) {
		if (pRoot == NULL){
			return true;
		}
		//判断一次当前
		int leftDepth = fun(pRoot->left);
		int rightDepth = fun(pRoot->right);
		return (abs(leftDepth - rightDepth) <= 1)
			&& IsBalanced_Solution(pRoot->left)
			&& IsBalanced_Solution(pRoot->right);
	}
};

/*
后序遍历+剪枝  （如果某一个分支不满足条件 直接返回 （剪枝））
*/

class Solution2 {
public:
	int fun(TreeNode* pRoot){
		if (pRoot == NULL){
			return 0;
		}
		int leftDepth = fun(pRoot->left) + 1;
		int rightDepth = fun(pRoot->right) + 1;
		return leftDepth>rightDepth ? leftDepth : rightDepth;
	}
	bool IsBalanced_Solution(TreeNode* pRoot) {
		if (pRoot == NULL){
			return true;
		}
		if (!IsBalanced_Solution(pRoot->left)){ return false; } //为false直接剪枝
		int leftDepth = fun(pRoot->left);
		if (!IsBalanced_Solution(pRoot->right)) { return false; }//为false直接剪枝
		int rightDepth = fun(pRoot->right);
		if (abs(leftDepth - rightDepth) <= 1){ return true; }
		else{ return false; }
	}
};

/*
2、二叉树的深度
输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，
最长路径的长度为树的深度。
*/

/*
思路:深度优先遍历
*/
class Solution4{
public:
	int TreeDepth(TreeNode* pRoot)
	{
		if (pRoot == NULL){ return 0; }
		int left = TreeDepth(pRoot->left)+1;
		int right = TreeDepth(pRoot->right)+1;
		return left > right ? left : right;
	}
};

/*
二维数组中的查找
在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序
排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维
数组和一个整数，判断数组中是否含有该整数。
*/

/*
思路：dfs 递归回溯法遍历整个数组 将走过的路不在再继续寻找 
*/
class Solution {
public:
	int ret = 0;
	bool check(vector<vector<int>>& arr, int i, int j, vector<vector<bool>>& m){
		int row = arr.size(), col = arr[0].size();
		if (i<0 || i >= row || j<0 || j >= col || !m[i][j]){
			return false;
		}
		return true;
	}
	void dfs(int target, vector<vector<int>>& arr, int i, int j, vector<vector<bool>>& m){
		if (!check(arr, i, j, m)){ return; }
		if (arr[i][j] == target){ ret = 1; }
		if (ret == 1){ return; }
		//小于就去下或者右去找
		m[i][j] = false;  //走过的就不走了
		dfs(target, arr, i + 1, j, m);
		dfs(target, arr, i, j + 1, m);
		if (arr[i][j]>target){ return; }
	}
	bool Find(int target, vector<vector<int> > array) {
		vector<vector<bool>> m;
		m.resize(array.size());
		for (int i = 0; i < array.size(); ++i){
			m[i].resize(array[0].size(), true);
		}
		dfs(target, array, 0, 0, m);
		if (ret == 1){ return true; }
		return false;
	}
};

int main(){
	Solution a;
	vector<vector<int>> b;
	int n = 0, target = 0;
	cin >> n >> target;
	b.resize(n);
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			int tmp = 0;
			cin >> tmp;
			b[i].push_back(tmp);
		}
	}
	a.Find(target, b);
	return 0;
}