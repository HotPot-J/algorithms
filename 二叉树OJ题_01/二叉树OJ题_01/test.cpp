#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;

/*
面试题68 - I. 二叉搜索树的最近公共祖先
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]
示例 1:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6
解释: 节点 2 和节点 8 的最近公共祖先是 6。
示例 2:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。
说明:
所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉搜索树中。
*/

/*
解题思路： 
   1.首先我们要了解二叉搜索树的定义： 
      二叉搜索树又称为二叉排序树，它或者是一颗空树，或者是具有以下性质的二叉树：
 1.若它的左子树不为空，则左子树上所有结点的值都小于根结点的值。
 2.若它的右子树不为空，则右子树上所有结点的值都大于根结点的值。
 3.它的左右子树也分别为二叉搜索树
 例子:int a[] = {5,3,4,1,7,8,2,6,0,9}
           5
	 3           7
  1    4       6    8
 0 2                  9
**根据题意 我们所需要寻找的结点为第一个介于p结点和q结点数值之间的 且由于根据定义最近公共祖先节点可以为节点本身
所以找到该递归结束条件：(p->val - root->val)*(q->val-root->val)<=0 
当root->val >  p->val和q->val了就往左边找 反之往右边找 代码如下：
*/


 struct TreeNode {
     int val;
    TreeNode *left;
	TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if ((root->val - p->val)*(root->val - q->val) <= 0){
			return root;
		}
		 if (root->val > p->val&&root->val > q->val){
			return lowestCommonAncestor(root->left, p, q);
		}
		 if (root->val < p->val&&root->val < q->val){
			return lowestCommonAncestor(root->right, p, q);
		}
		 return NULL;
	}
};

/*
面试题68 - II. 二叉树的最近公共祖先
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4]
示例 1:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。
示例 2:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
说明:
所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉树中。
*/
/*
思路：普通二叉树不具备搜索二叉树的性质 所以难度变大
  可以通过根节点递归去寻找p和q两个结点 当找到后返回该结点
  如果当前结点的左右子树分别包括p q两点 则该节点一定是答案
  如果左边找到了p 而右边没找到q 则p结点为答案 反之一样
  若p或q没找到 则返回NULL
*/
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL){
			//没找到
			return NULL;
		}
		if (root->val == p->val || root->val == q->val){
			//若找到其中一个则返回该结点
			return root;
		}
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);
		if (left&&right){
			//p q都找到了 则返回当前结点
			return root;
		}
		else{
			//只找到一个 那么最近公共祖先节点为节点本身。
			return left ? left : right;
		}
	}
};

/*
面试题55 - II. 平衡二叉树
输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左右子树的深度相差不超过1，
那么它就是一棵平衡二叉树。

示例 1:
给定二叉树 [3,9,20,null,null,15,7]
3
/ \
9  20
/  \
15   7
返回 true 。
示例 2:
给定二叉树 [1,2,2,3,3,null,null,4,4]
1
/ \
2   2
/ \
3   3
/ \
4   4
返回 false 。
限制：
1 <= 树的结点个数 <= 10000
*/
/*
 思路：递归记录左右子树的深度 最终加减法作出比较即可
*/
//先序遍历
class Solution {
public:
	int maxDepth( TreeNode* root){
		int leftDepth = 0, rightDepth = 0;
		if (root == NULL){
			return 0;
		}
		else {
			leftDepth = maxDepth(root->left) + 1;
			rightDepth = maxDepth(root->right) + 1;
			if (leftDepth>rightDepth){
				return leftDepth;
			}
			else{
				return rightDepth;
			}
		}
	}
	bool isBalanced(TreeNode* root) {
		if (root == NULL){
			return true;
		}
		int leftSize = maxDepth(root->left);
		int rightSize = maxDepth(root->right);
		if (abs(leftSize - rightSize) >1){
			return false;
		}
		else{
			return isBalanced(root->left) && isBalanced(root->right);//判断其左右子树是否也满足平衡条件
		}
	}
};