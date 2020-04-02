#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
������22. �����е�����k���ڵ�
����һ����������������е�����k���ڵ㡣Ϊ�˷��ϴ�����˵�ϰ�ߣ������1��ʼ�������������β�ڵ��ǵ�����1���ڵ㡣
���磬һ��������6���ڵ㣬��ͷ�ڵ㿪ʼ�����ǵ�ֵ������1��2��3��4��5��6���������ĵ�����3���ڵ���ֵΪ4�Ľڵ㡣
ʾ����
����һ������: 1->2->3->4->5, �� k = 2.
�������� 4->5.
*/
//˼·������ָ�뷨 ��ߵ�ָ��Lָ��head �ұߵ�ָ��R����k����� ��R!=NULLʱ R��Lָ��ÿ����1�� 
//��R!=NULLʱ ���Lλ�÷���������
struct ListNode {
     int val;
	 ListNode *next;
	 ListNode(int x) : val(x), next(NULL) {}
 };
class Solution {
public:
	ListNode* getKthFromEnd(ListNode* head, int k) {
		ListNode* L = head;
		ListNode* R = head;
		if (k == 0){
			//��kΪ0ֱ�ӷ��ظ�����
			return head;
		}
		while (k&&R!=NULL){
			R = R->next;
			--k;
		}
		while (R != NULL){
			L = L->next;
			R = R->next;
		}
		return L;
	}
};

/*
������24. ��ת����
����һ������������һ�������ͷ�ڵ㣬��ת�����������ת�������ͷ�ڵ㡣
ʾ��:
����: 1->2->3->4->5->NULL
���: 5->4->3->2->1->NULL
���ƣ�
0 <= �ڵ���� <= 5000
*/

//�ⷨһ��˫ָ�� top �� tailָ��ֱ��ʾ ��ǰ��������ǰһ�����͵�ǰ������� tmpָ��ǰ�������ĺ�һ�����
//ÿ��tail��nextָ��top top = tail tail = tmp tmp = tmp->next �Դﵽ��ת��Ч��
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* top = nullptr;
		ListNode* tail = head;
		while (tail){
			ListNode* tmp = tail->next;
			tail->next = top;
			top = tail;
			tail = tmp;
		}
		return top;
	}
};

//�ⷨ�����ݹ� 
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == NULL || head->next == NULL){
			return head;
		}
		ListNode* p = reverseList(head->next);//��Ϊ���ص�ͷ�ڵ�
		head->next->next = head;  //�����һ������nextָ��ǰhead��� head����next�ÿ�
		head->next = NULL;
		return p;
	}
};