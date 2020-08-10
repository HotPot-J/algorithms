#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

/*
替换空格
请实现一个函数，将一个字符串中的每个空格替换成“%20”。
例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
*/
class Solution {
public:
	void replaceSpace(char *str, int length) {
		char* tmp = new char[1024];
		char* cur = str;
		int i = 0;
		while (*cur){
			if (*cur == ' '){
				tmp[i++] = '%';
				tmp[i++] = '2';
				tmp[i++] = '0';
			}
			else{
				tmp[i++] = *cur;
			}
			++cur;
		}
		tmp[i] = '\0';
		strcpy(str, tmp);
	}
};

/*
从尾到头打印链表
输入一个链表，按链表从尾到头的顺序返回一个ArrayList。
*/
  struct ListNode {
        int val;
        struct ListNode *next;
        ListNode(int x) :
              val(x), next(NULL) {
        }
  };

class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> res;
		ListNode* cur = head;
		while (cur){
			res.push_back(cur->val);
			cur = cur->next;
		}
		reverse(res.begin(), res.end());
		return res;
	}
};

/*
重建二叉树
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
*/
/*
思路:递归 分治
*/
struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	TreeNode* built(vector<int>& pre, int ps, int pe, vector<int>& vin, int vs, int ve){
		if (ps>pe || vs>ve){ return NULL; }
		TreeNode* root = new TreeNode(pre[ps]); //先序遍历 先创造当前头节点
		for (int i = vs; i <= ve; ++i){
			if (vin[i] == pre[ps]){
				//在中序遍历中找到该先序遍历的结点 进行分治
				root->left = built(pre, ps + 1, ps + i - vs, vin, vs, i - 1);
				root->right = built(pre, ps + i - vs + 1, pe, vin, i + 1, ve);
				break;
			}
		}
		return root;
	}
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		TreeNode* root = built(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
		return root;
	}
};