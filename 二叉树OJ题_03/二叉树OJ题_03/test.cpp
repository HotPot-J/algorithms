#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<queue>
#include<deque>
using namespace std;



 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

/*
面试题32 - I. 从上到下打印二叉树
从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
例如:
给定二叉树: [3,9,20,null,null,15,7],
3
/ \
9  20
/  \
15   7
返回：
[3,9,20,15,7]
提示：
节点总数 <= 1000
*/
 //思路：层序遍历 （二叉树的层序遍历需要借助队列）
class Solution {
public:
	vector<int> levelOrder(TreeNode* root) {
		if (root == NULL){
			return;
		}
		vector<int> res;
		queue<TreeNode*> q;
		TreeNode* Front;
		q.push(root);
		while (!q.empty()){
			//当队列为非空 说明还没有遍历完成
			Front = q.front();//临时保存当前遍历结点
			q.pop();//让队头出队
			//让该节点的val进数组
			res.push_back(Front->val);
			if (Front->left){
				//若有左结点
				q.push(Front->left);
			}
			if (Front->right){
				//若有右结点
				q.push(Front->right);
			}
		}
		return res;
	}
};

/*
面试题32 - III. 从上到下打印二叉树 III
请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，
第三行再按照从左到右的顺序打印，其他行以此类推。
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
[20,9],
[15,7]
]
提示：
节点总数 <= 1000
*/
//思路1：依然是层序遍历 但是要使用双端队列deque 当奇数层 由于从左至右遍历就前出后进
//       当偶数层就后出前进
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		bool flag = true;//当奇数行为真 偶数行为假的
		deque<TreeNode*> q;
		if (root == NULL){
			return res;
		}
		q.push_back(root);
		while (!q.empty()){
			int n = q.size();
			vector<int> tmp;
			TreeNode* node = NULL;
			while (n){
				if (flag){
					//奇数层前出后进
					node = q.front();
					q.pop_front();
					if (node->left){ //后进
						q.push_back(node->left);
					}
					if (node->right){
						q.push_back(node->right);
					}
				}
				else{
					//偶数层后出前进
					node = q.back();
					q.pop_back();
					if (node->right){ //后进   由于下一层偶数层从前往后遍历 所以这里需要逆序头插 （先右后左）
						q.push_front(node->right);
					}
					if (node->left){
						q.push_front(node->left);
					}
				}
				tmp.push_back(node->val);
				--n;
			}
			res.push_back(tmp);
			flag = !flag;
		}
		return res;
	}
};