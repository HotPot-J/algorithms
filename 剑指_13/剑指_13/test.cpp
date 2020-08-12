#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
using namespace std;

/*
�ϲ�������������
���������������������������������ϳɺ��������Ȼ������Ҫ�ϳɺ���������㵥����������
*/
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};
/*
˼·��
	�鲢���� ע��ָ������򼴿� 
*/
class Solution {
public:
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{
		ListNode* res = NULL, *cur = NULL;
		while (pHead1&&pHead2){
			if (pHead1->val<pHead2->val){
				if (res == NULL){ res = pHead1; cur = pHead1; } //resΪ�׵�ַ
				else{
					cur->next = pHead1;
					cur = pHead1;
				}
				pHead1 = pHead1->next;
			}
			else{
				if (res == NULL){ res = pHead2; cur = pHead2; } //resΪ�׵�ַ
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
//����
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
��Ŀ����
���������Ķ�����������任ΪԴ�������ľ���
��������:
�������ľ����壺Դ������
8
/  \
6   10
/ \  / \
5  7 9 11
���������
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
˼·һ���ݹ�汾 �������ֱ�ӽ��� 
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

//˼·�����ǵݹ�汾 (�������ķǵݹ� �޷Ǿ���ʹ��ջ���߶��У�����ȥģ��ݹ�Ĺ���)

class Solution {
public:
	void Mirror(TreeNode *pRoot) {
		if (pRoot == NULL){ return; }
		stack<TreeNode*> s;
		s.push(pRoot);
		while (s.size()){
			//��sջ�ﻹ������˵����δ������
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