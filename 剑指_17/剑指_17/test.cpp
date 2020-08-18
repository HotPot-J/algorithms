#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
�����ӽṹ��
�������ö�����A��B���ж�B�ǲ���A���ӽṹ����ps������Լ��������������һ�������ӽṹ��
*/

/*
˼·���������A�����ҵ�A����Bͷ������ȵĽ�㣬Ȼ�������������ȥ�жϡ�
	�жϺ���Ҳ�����������
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
�������pRoot1����ÿһ����pRoot2��ȵĽ�㣬�ó�ȥ�ж���ṹ�Ƿ�һ��
*/
class Solution {
public:
	//�жϺ���check
	bool check(TreeNode* pRoot1, TreeNode* pRoot2){
		//���pRoot���Ϊ��,˵��pRoot������
		if (pRoot2 == NULL){ return true; } //
		//��pRoot2��Ϊ�գ�����pRoot1�����ˣ�˵��2����1���ӽṹ
		if (pRoot1 == NULL){ return false; }
		//���������㶼��Ϊ�� ����ֵ��ͬ
		if (pRoot1&&pRoot2 && (pRoot1->val != pRoot2->val)){ return false; }
		//�ߵ�����˵����� ���ű���
		return check(pRoot1->left, pRoot2->left) &&
			check(pRoot1->right, pRoot2->right);
	}

	bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
	{
		if (pRoot1 == NULL || pRoot2 == NULL){ return false; }
		//�������pRoot1 Ѱ�Һ�pRoot->val��ȵĽ��
		if (pRoot1->val == pRoot2->val&&check(pRoot1->left, pRoot2->left) &&
			check(pRoot1->right, pRoot2->right)){
			return true;
		}
		return HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
	}
};

/*
��ָ Offer 52. ��������ĵ�һ�������ڵ�
�������������ҳ����ǵĵ�һ�������ڵ㡣
*/

/*
˼·һ����ϣ
*/

#include<unordered_map>
using namespace std;

struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};
class Solution {
public:
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		if (pHead1 == NULL || pHead2 == NULL){ return NULL; }
		unordered_map<ListNode*, bool> map1;
		ListNode* cur1 = pHead1, *cur2 = pHead2;
		while (cur1){
			map1[cur1] = true;
			cur1 = cur1->next;
		}
		while (cur2){
			if (map1[cur2]){
				return cur2;
			}
			cur2 = cur2->next;
		}
		return NULL;
	}
};

/*

˼·����˫ָ�� 
	����A��B�������ֳ���ΪC����B��A�ķǹ������ֳ�x ����ô��A����һ�˻ص�B�����ʱ��B�����յ�Ϊx������B����ص�A�����
	��Aǡ������x���룬��ʱAB�ķǹ�������������ȣ���ô����������ǹ������
*/

class Solution {
public:
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		if (pHead1 == NULL || pHead2 == NULL){ return NULL; }
		ListNode* cur1 = pHead1, *cur2 = pHead2;
		while (cur1 != cur2){
			//������cur1->next==NULL�Ϳ�ʼ�ص��˴˵����
			//�����п��ܲ��ཻ������һ��Ҫ�������ߵ�NULL�ٻص��˴˵����
			//�ڲ��ཻ������£�������ͬʱΪNULLҲ����ȣ���ô�Ų��������ѭ��
			if (cur1 == NULL){ cur1 = pHead1; }
			else{ cur1 = cur1->next; }
			if (cur2 == NULL){ cur2 = pHead2; }
			else{
				cur2 = cur2->next;
			}
		}
		return cur1;
	}
};