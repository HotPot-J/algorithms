#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;

/*
1、按之字形顺序打印二叉树。
请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，
第三行按照从左到右的顺序打印，其他行以此类推。
*/
struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};

/*
思路：1.层序遍历 只不过是采用双端队列的层序遍历
2.从左到右遍历：结点也是从左到右进 从队尾进 队头出
3.从右到左遍历：结点也是从右到左进 从队头进 队尾出
*/
class Solution {
public:
	vector<vector<int> > Print(TreeNode* pRoot) {
		vector<vector<int>> res;
		if (pRoot == NULL){ return res; }
		deque<TreeNode*> s;
		bool flag = true;
		s.push_back(pRoot);
		while (!s.empty()){
			int len = s.size();
			vector<int> tmp;
			if (flag == true){
				//从左到右存
				for (int i = 0; i<len; ++i){
					//从左到右存
					tmp.push_back(s.front()->val);
					if (s.front()->left){ s.push_back(s.front()->left); }
					if (s.front()->right){ s.push_back(s.front()->right); }
					s.pop_front();
				}
				flag = false; //下一次就是从右到左
			}
			else{
				//从右到左存
				for (int i = 0; i<len; ++i){
					tmp.push_back(s.back()->val);
					if (s.back()->right){ s.push_front(s.back()->right); }
					if (s.back()->left){ s.push_front(s.back()->left); }
					s.pop_back();
				}
				flag = true; //下一次就是从左到右
			}
			res.push_back(tmp);
		}
		return res;
	}
};

/*
3、对称二叉树
请实现一个函数，用来判断一棵二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，
定义其为对称的。
*/

/*
思路：递归 先序遍历（先去对比当前状态 如果正确再进行下一步遍历）
对称：即镜像 左的左和右的右对称  左的右也得和右的左对称！！！
*/
class Solution {
public:
	bool check(TreeNode* left, TreeNode* right){
		if (left == NULL&&right == NULL){ return true; }
		if (left == NULL || right == NULL){ return false; }
		if (left->val != right->val){ return false; }
		//否则就可以进行下一层的比较了
		return check(left->left, right->right) && check(left->right, right->left);//对称
	}
	bool isSymmetrical(TreeNode* pRoot)
	{
		if (pRoot == NULL){ return true; }
		return check(pRoot->left, pRoot->right);
	}
};