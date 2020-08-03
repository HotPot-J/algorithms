#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
#include<string>
using namespace std;
/*
把二叉树打印成多行
从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。
*/
/*
思路：二叉树的层序遍历
遇到层序遍历 用队列刚就完了  （记得要一层一层遍历 for(int i = 0;i<q.size()(当前层的长度);++i)）
*/
class Solution {
public:
	vector<vector<int> > Print(TreeNode* pRoot) {
		vector<vector<int>> res;
		if (pRoot == NULL){ return res; }
		queue<TreeNode*> q;
		int i = 0;
		TreeNode* cur = pRoot;
		q.push(cur);
		while (!q.empty()){
			//当队列不为空时进行层序遍历
			int len = q.size();
			vector<int> tmp;
			for (int i = 0; i<len; ++i){
				if (q.front() != NULL){
					tmp.push_back(q.front()->val);
					//让下一层顺便入队
					q.push(q.front()->left);
					q.push(q.front()->right);
				}
				//队头出队
				q.pop();
			}
			if (!tmp.empty()){
				res.push_back(tmp);
			}
		}
		return res;
	}
};


/*
二叉树的序列化与反序列化
请实现两个函数，分别用来序列化和反序列化二叉树

二叉树的序列化是指：把一棵二叉树按照某种遍历方式的结果以某种格式保存为字符串，从而使得内存中建立起来的二叉树
可以持久保存。序列化可以基于先序、中序、后序、层序的二叉树遍历方式来进行修改，序列化的结果是一个字符串，序列
化时通过 某种符号表示空节点（#），以 ！ 表示一个结点值的结束（value!）。

二叉树的反序列化是指：根据某种遍历顺序得到的序列化字符串结果str，重构二叉树。

例如，我们可以把一个只有根节点为1的二叉树序列化为"1,"，然后通过自己的函数来解析回这个二叉树
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
思路:
1.序列化：层序遍历 使用队列完成 当遍历某一层时，将下一层的结点入队（即使为空也要入队 因为反序列化时需要这些空的位置）
2.反序列化：层序遍历 当下一层结点非空，则入队，只有非空才能为其赋值left/right 
3.本题坑很多 例如需要判断空格 "12 3 # 34 4"  还需要用到itoa 和stoa函数
4.遇到层序遍历 用队列刚就完了  （记得要一层一层遍历 for(int i = 0;i<q.size()(当前层的长度);++i)）
*/
class Solution {
public:
	char* Serialize(TreeNode *root) {
		if (root == NULL){ return NULL; }
		queue<TreeNode*> q;
		string res;
		int i = 0;
		TreeNode* cur = root;
		q.push(cur);
		while (!q.empty()){
			//当队列不为空时进行层序遍历
			int len = q.size();
			for (int i = 0; i<len; ++i){
				if (q.front() == NULL){
					res += "# ";
				}
				else{
					res += to_string(q.front()->val) + ' '; //序列化结果
					//让下一层顺便入队
					q.push(q.front()->left);
					q.push(q.front()->right);
				}
				//队头出队
				q.pop();
			}
		}
		char* tmp = strdup(res.c_str());
		return tmp;
	}
	//层序创建二叉树
	TreeNode* Deserialize(char *str) {
		if (str == NULL){ return NULL; }
		queue<TreeNode*> q;
		int len = strlen(str);
		int i = 0;
		TreeNode* root = createNode(str, i, len);
		q.push(root);
		while (!q.empty()){
			int size = q.size();
			for (int j = 0; j<size; ++j){
				//创建左右结点
				q.front()->left = createNode(str, i, len);
				q.front()->right = createNode(str, i, len);
				//非空即可入队 为了下一层的创建
				if (q.front()->left){ q.push(q.front()->left); }
				if (q.front()->right){ q.push(q.front()->right); }
				q.pop();
			}
		}
		return root;
	}
	//创建一个结点并返回
	TreeNode* createNode(char* str, int& i, int& len){
		if (str == NULL){ return NULL; }
		string tmp;
		while (i<len&&str[i] != ' '){
			if (str[i] == '#'){
				i += 2; //跳过#和一个空格
				return NULL;
			}
			tmp += str[i];
			++i;
		}
		//跳过一个空格 来到下一个有效字符
		++i;
		if (!tmp.empty()){
			TreeNode* Node = new TreeNode(stoi(tmp));
			return Node;
		}
		return NULL;
	}
};