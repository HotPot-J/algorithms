#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
/*
1.����������һ���ڵ�
����һ�������������е�һ����㣬���ҳ��������˳�����һ����㲢�ҷ��ء�ע�⣬
���еĽ�㲻�����������ӽ�㣬ͬʱ����ָ�򸸽���ָ�롣
*/

/*
˼·:�����������
ǰ�᣺ǰ����� �����
	1.�п�
	2.�����ҽ�㣬Ѱ�����һ�����Լ����������������Ƚ��
	3.�����ҽ�㣬Ѱ������������������ĵ�һ����㼴��
*/

struct TreeLinkNode {
int val;
struct TreeLinkNode *left;
struct TreeLinkNode *right;
struct TreeLinkNode *next;
TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

}
};

class Solution {
public:
	TreeLinkNode* fun(TreeLinkNode* prev, TreeLinkNode* rear){
		//ǰ�����������
		if (rear == NULL){
			return prev;
		}
		return fun(rear, rear->left);
	}
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		//�п� ���߸��ڵ�������ֱ�ӷ���NULL
		if (pNode == NULL){ return NULL; }
		//��û����Ҳ���Ǹ� 
		if (pNode->right == NULL){
			//�����һ���������������������Ƚ�㣨��Ϊ����ң�
			while (pNode->next != NULL&&pNode->next->left != pNode){
				pNode = pNode->next;
			}
			return pNode->next;
		}
		//���� ��Ͱ���ǰ�������˳�� Ѱ�ҵ�pNode����һ�����
		return fun(pNode, pNode->right);
	}
};


/*
ɾ�������е��ظ����
��һ������������У������ظ��Ľ�㣬��ɾ�����������ظ��Ľ�㣬�ظ��Ľ�㲻��������������ͷָ�롣 
���磬����1->2->3->3->4->4->5 �����Ϊ 1->2->5
*/

/*
˼·һ:
�ǵݹ�汾��˫ָ�루�ϸ��� ���ѣ�
1.�����п� ��һ���������
2.ȷ��ͷ�ڵ� ���п���һ��ʼ�����ظ��ģ�
3.ȷ��ͷ�ڵ��Ժ� �����п��к�һ���������ֱ�ӷ���
4.������������ Ҳ����ֱ�ӷ��أ���Ϊ�������ڵ�һ���ǲ���ȵģ���Ϊȷ����ͷ�ڵ�һ�������ظ��ģ�
5.���������ϵĽ�㣬����tmp ȥΪͷ�ڵ��next���а�  p��rһǰ�Ժ�ȥѰ�Ҳ��ظ��Ľ��
6.��ʱ�ַ�Ϊ���������������ɾ�� δ����ɾ��
7.�ظ�6���̱�������
*/

struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};

class Solution1 {
public:
	ListNode* deleteDuplication(ListNode* pHead)
	{
		if (pHead == NULL){ return NULL; }
		if (pHead->next == NULL){ return pHead; } //ֻ��һ�����
		//��Ѱ��Phead��������㣨��Ϊ�п���ֱ��ͷ�����ظ��ģ�
		ListNode* p = pHead->next;
		while (p != NULL&&pHead != NULL && (p->val == pHead->val)){
			while (p != NULL&&p->val == pHead->val){
				p = p->next;
			}
			pHead = p;
			if (p != NULL){ p = p->next; }
		}
		//�ҵ�������� ������ͷ�ڵ�����
		if (pHead == NULL){ return NULL; }
		if (p == NULL || p->next == NULL){
			//ֻ��һ����������� 
			return pHead;
		}
		//���������Ͻ�� 

		ListNode* r = p->next, *tmp = pHead;
		while (r != NULL){
			bool flag = false;
			while (r != NULL&&r->val == p->val){
				flag = true;
				r = r->next;
			}
			if (flag){
				//��ɾ�� �ƶ�p r���ж���һ�������Ƿ��ظ���
				p = r;
				if (r != NULL){ r = r->next; }
				if (p == NULL || r == NULL || p->val != r->val){
					//�жϴ�ʱ��p r������ȣ���p�ɱ�������ɾ��
					tmp->next = p;
					tmp = tmp->next;
					//p r����������
					if (p != NULL&&r != NULL){ p = p->next; r = r->next; }
				}
			}
			else{
				//ûɾ��
				tmp->next = p;
				tmp = tmp->next;
				//p r����������
				p = r;
				if (r != NULL){ r = r->next; }
			}
		}
		return pHead;
	}
};

/*
˼·�����ݹ� 
*/
class Solution {
public:
	ListNode* res;
	ListNode* deleteDuplication(ListNode* pHead)
	{
		if (pHead == NULL){ return NULL; }
		if (pHead!= NULL&&pHead->next == NULL){ return pHead; }
		
		ListNode* tmp;
		if (pHead->val == pHead->next->val){
			//�ظ�
			tmp = pHead->next->next;
			while (tmp != NULL&&tmp->val == pHead->val){
				//������ǰ�ظ�
				tmp = tmp->next;
			}
			return deleteDuplication(tmp);
		}
		else{
			//��
			tmp = pHead->next;
			pHead->next = deleteDuplication(tmp);
			return pHead;
		}
	}
};