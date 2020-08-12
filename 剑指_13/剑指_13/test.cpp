#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
using namespace std;

/*
合并两个排序链表
输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。
*/
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};
/*
思路：
	归并排序 注意指针的走向即可 
*/
class Solution {
public:
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{
		ListNode* res = NULL, *cur = NULL;
		while (pHead1&&pHead2){
			if (pHead1->val<pHead2->val){
				if (res == NULL){ res = pHead1; cur = pHead1; } //res为首地址
				else{
					cur->next = pHead1;
					cur = pHead1;
				}
				pHead1 = pHead1->next;
			}
			else{
				if (res == NULL){ res = pHead2; cur = pHead2; } //res为首地址
				else{
					cur->next = pHead2;
					cur = pHead2;
				}
				pHead2 = pHead2->next;
			}
		}
		if (pHead1){
			if (res == NULL){ res = pHead1; }
			else{ cur->next = pHead1; }
		}
		if (pHead2){
			if (res == NULL){ res = pHead2; }
			else{ cur->next = pHead2; }
		}
		return res;
	}
};
//测试
//int main(){
//	ListNode* pHead1 = new ListNode(0);
//	ListNode* pHead2 = new ListNode(0);
//	ListNode* cur1 = pHead1, *cur2 = pHead2;
//	for (int i = 1; i < 6; ++i){
//		if (i % 2 == 0){
//			ListNode* node = new ListNode(i);
//			cur1->next = node;
//			cur1 = cur1->next;
//		}
//		else{
//			ListNode* node = new ListNode(i);
//			cur2->next = node;
//			cur2 = cur2->next;
//		}
//	}
//	Solution a;
//	a.Merge(pHead1, pHead2);
//	return 0;
//}


/*
题目描述
操作给定的二叉树，将其变换为源二叉树的镜像。
输入描述:
二叉树的镜像定义：源二叉树
8
/  \
6   10
/ \  / \
5  7 9 11
镜像二叉树
8
/  \
10   6
/ \  / \
11 9 7  5
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
思路一：递归版本 先序遍历直接交换 
*/
class Solution {
public:
	void Mirror(TreeNode *pRoot) {
		if (pRoot == NULL){ return; }
		swap(pRoot->left, pRoot->right);
		Mirror(pRoot->left);
		Mirror(pRoot->right);
	}
};

//思路二：非递归版本 (二叉树的非递归 无非就是使用栈或者队列（层序）去模拟递归的过程)

class Solution {
public:
	void Mirror(TreeNode *pRoot) {
		if (pRoot == NULL){ return; }
		stack<TreeNode*> s;
		s.push(pRoot);
		while (s.size()){
			//当s栈里还有数据说明并未遍历完
			TreeNode* tmp = s.top();
			s.pop();
			if (tmp->left || tmp->right){
				swap(tmp->left, tmp->right);
			}
			if (tmp->left){ s.push(tmp->left); }
			if (tmp->right){ s.push(tmp->right); }
		}
	}
};