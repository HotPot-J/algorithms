#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<queue>
using namespace std;


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
/*
面试题32 - II. 从上到下打印二叉树 II
从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。
例如:
给定二叉树: [3,9,20,null,null,15,7],
3
/ \
9  20
/  \
15   7
返回其层次遍历结果：
[
[3],
[9,20],
[15,7]
]
提示：
节点总数 <= 1000
*/
 //思路 ：层序遍历 让每一层的数据放在二维数组中（依然需要用到queue先进先出的特点）
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (!root){
			return res;
		}
		queue<TreeNode*> q;
		TreeNode* p ;
		q.push(root);
		while (!q.empty()){
			int flag = q.size();//记录这个当前队列的长度（即当前层的结点个数 用于控制循环）
			vector<int> tmp;
			while (flag){
				p = q.front();
				q.pop();
				tmp.push_back(p->val);
				if (p->left){
					q.push(p->left);
				}
				if (p->right){
					q.push(p->right);
				}
				--flag;
			}
			res.push_back(tmp);
		}
		return res;
	}
};

/*
面试题54. 二叉搜索树的第k大节点
给定一棵二叉搜索树，请找出其中第k大的节点。
示例 1:
输入: root = [3,1,4,null,2], k = 1
3
/ \
1   4
\
2
输出: 4
示例 2:
输入: root = [5,3,6,2,4,null,null,1], k = 3
5
/ \
3   6
/ \
2   4
/
1
输出: 4
限制：
1 ≤ k ≤ 二叉搜索树元素个数
*/

//思路: 由于搜索二叉树的中序遍历（左根右）为递增序列 求topk需要递减序列更为方便所以我们以（右根左）的顺序去遍历
//得到递减序列
class Solution {
public:
	vector<int> res;
	void  help(TreeNode* root){
		if (root == NULL){
			return;
		}
        help(root->right);
		res.push_back(root->val);
        help(root->left);
	
	}
	int kthLargest(TreeNode* root, int k) {
		help(root);
		return res[k - 1];
	}
};

/*
面试题26. 树的子结构
输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
B是A的子结构， 即 A中有出现和B相同的结构和节点值。
例如:
给定的树 A:
3
/ \
4   5
/ \
1   2
给定的树 B：
4
/
1
返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。
示例 1：
输入：A = [1,2,3], B = [3,1]
输出：false
示例 2：
输入：A = [3,4,5,1,2], B = [4,1]
输出：true
限制：
0 <= 节点个数 <= 10000
*/

//思路：先找到A中有无与B根节点相同的结点 若有则保存该位置在数组中 
//      根据数组中的结点再去比对是否结构相同
class Solution {
public:
	vector<TreeNode*> arr;
	bool res = true;
	void fun1(TreeNode*A, int _val){
		//寻找并保存A中结点值与_val（B的根节点）相同的结点
		if (A == NULL){
			return;
		}
		if (A->val == _val){
			arr.push_back(A);
		}
		fun1(A->left,_val);
		fun1(A->right,_val);
	}
	
	bool fun2(TreeNode* A, TreeNode*B){
		if (A==NULL||B==NULL){
			if (B != NULL){
				res == false;
			}
			return;
		}
		if (A->val != B->val){
			res = false;
			return;
		}
		fun2(A->left, B->left);
		fun2(A->right, B->right);
	}
	bool isSubStructure(TreeNode* A, TreeNode* B) {
		if (A == NULL || B == NULL){
			return false;
		}
		fun1(A, B->val);//找到A中所有值和B一样的结点
		int n = arr.size();
		if (n == 0){
			//此时说明在A中并没有找到与B头节点相同的结点将res置为false
			res == false;
		}
		while (n){
			fun2(arr.back(), B);
			arr.pop_back();
			--n;
		}
		return res;
	}
};

/*
面试题55 - I. 二叉树的深度
输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，
最长路径的长度为树的深度。
例如：
给定二叉树 [3,9,20,null,null,15,7]，
 3
/ \
9  20
/  \
15   7
返回它的最大深度 3 。
提示：
节点总数 <= 10000
*/
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == NULL){
			return 0;
		}
		int leftDepth = maxDepth(root->left)+1;
		int rightDepth = maxDepth(root->right)+1;
		return leftDepth > rightDepth ? leftDepth : rightDepth;
	}
};

/*
面试题27. 二叉树的镜像
请完成一个函数，输入一个二叉树，该函数输出它的镜像。
例如输入：
4
/   \
2     7
/ \   / \
1   3 6   9
镜像输出：
4
/   \
7     2
/ \   / \
9   6 3   1
示例 1：

输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]
*/
//思路：递归交换左右节点即可
class Solution {
public:
	TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* mirrorTree(TreeNode* root) {
		if (!root){
			return NULL;
		}
		swap(root->left, root->right);
		TreeNode* Left = mirrorTree(root->left);
		TreeNode* right = mirrorTree(root->right);
		return root;
	}
};