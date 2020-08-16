#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

/*从上往下打印出二叉树
从上往下打印出二叉树的每个节点，同层节点从左至右打印。
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
	vector<int> PrintFromTopToBottom(TreeNode* root) {
		vector<int> res;
		if (root == NULL){ return res; }
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()){
			res.push_back(q.front()->val);
			if (q.front()->left){ q.push(q.front()->left); }
			if (q.front()->right){ q.push(q.front()->right); }
			q.pop();
		}
		return res;
	}
};

/*题目描述 二叉搜索树的后序遍历
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则返回true, 否则返回false。
假设输入的数组的任意两个数字都互不相同。
*/
/*
思路一：递归
根据二叉搜索树的性质，其后序遍历的最后一个结点是当前子树的根节点：
序列的最后一个结点设为rear
1.一定可以在其之前数字中找到一个 [小于]（rear）[大于] 的位置 或者
[小于]（rear）或者（rear）[大于]这样的位置
2.不可能是[大于]（rear）的位置 这样的话不满足二叉搜索树的性质
3.根据这样的结论就可以分治 递归的去解决问题。
*/
class Solution {
public:
	bool fun(vector<int>& seq, int prev, int rear){
		if (prev >= rear){ return true; }
		int i = prev;
		for (i; i<rear; ++i){
			if (seq[i]>seq[rear]){ break; } //找到分界点 即 [小于]（rear）[大于] 或者[小于]（rear）或者（rear）[大于]的位置i
		}
		int j = i + 1;
		for (j; j<rear; ++j){
			if (seq[j]<seq[rear]){ return false; }
		}
		//递归左右子树进行判断
		return fun(seq, prev, i - 1) && //左子树
			fun(seq, i, rear - 1);  //右子树
	}
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty()){ return false; }
		return fun(sequence, 0, sequence.size() - 1);
	}
};

/*
思路二:非递归方法
	基于递归的思想，我们每次寻找子树的满足条件，不如直接从后至前，判断每一个子树的根节点是否满足[左小](root)[右大]
	或者[左小](root)或者(root)[右小] 
	也就是说要么你满足我左小右大的分界点，要么你就一路从左小到底，要么你就从左一路大到底 就满足平衡二叉树的原理
*/
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		int size = sequence.size();
		if (size == 0){ return false; }
		//从后往前 判断每一个子树根结点是否满足条件
		size -= 1; //下标
		while (size){
			int i = 0;
			while(i<size&&sequence[i] < sequence[size]){ ++i;}
			while(i<size&&sequence[i] > sequence[size]){ ++i;}
			//这两个下来i一定是能走到size-1这个位置的
			if (i < size - 1){ return false; }
			else{
				--size;
			}
		}
		return true;
	}
};