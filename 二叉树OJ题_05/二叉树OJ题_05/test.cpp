#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*
面试题07. 重建二叉树
输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如，给出
前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：
3
/ \
9  20
/  \
15   7
限制：
0 <= 节点个数 <= 5000
*/


 struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		//递归分治
		return recursionBuild(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
	}

	//递归分治
	TreeNode* recursionBuild(vector<int>::iterator preBegin, vector<int>::iterator preEnd, vector<int>::iterator inBegin, vector<int>::iterator inEnd)
	{
		if (inEnd == inBegin) return NULL;
		TreeNode* cur = new TreeNode(*preBegin);
		auto root = find(inBegin, inEnd, *preBegin);
		cur->left = recursionBuild(preBegin + 1, preBegin + 1 + (root - inBegin), inBegin, root);
		cur->right = recursionBuild(preBegin + 1 + (root - inBegin), preEnd, root + 1, inEnd);
		return cur;
	}
};
