#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;

/*
1�������л�����ڽڵ�
��һ�����������а����������ҳ�������Ļ�����ڽ�㣬�������null��
*/


/*
˼·�����ļ��»�ͼ�����Ƶ����̺�ͼ��
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
	ListNode* EntryNodeOfLoop(ListNode* pHead)
	{
		ListNode* fast = pHead, *slow = pHead;
		while (fast&&fast->next){
			fast = fast->next->next;//ÿ��������
			slow = slow->next; //ÿ����һ��
			if (fast == slow){
				//��һ������
				break;
			}
		}
		if (fast == NULL || fast->next == NULL){
			//û�л� 
			return NULL;
		}
		fast = pHead;
		while (1){
			if (fast == slow){ break; }  //�п��ܸ�����ֱ�Ӿ��Ǹ���-- 
			fast = fast->next; slow = slow->next;
		}
		return fast;
	}
};

/*
��Ŀ���� :�ַ����е�һ�����ظ����ַ�
��ʵ��һ�����������ҳ��ַ����е�һ��ֻ����һ�ε��ַ������磬�����ַ�����ֻ����ǰ�����ַ�"go"ʱ����һ��ֻ����һ�ε��ַ���"g"�����Ӹ��ַ����ж���ǰ�����ַ���google"ʱ����һ��ֻ����һ�ε��ַ���"l"��
�������:
�����ǰ�ַ���û�д��ڳ���һ�ε��ַ�������#�ַ���
*/

/*
˼·����ϣ ����һ��int[256]������ 
	  ���� �����ж��Ⱥ�˳�� ��ע�� ֻ���ڵ�һ�α���������ĸ������� ������˺ܶ��ظ��ж� ���Ч�ʣ�
*/
class Solution
{
public:
	//Insert one char from stringstream
	void Insert(char ch)
	{
		m[ch]++;
		if (m[ch] == 1){
			//��һ������
			q.push(ch);
		}
	}
	//return the first appearence once char in current stringstream
	char FirstAppearingOnce()
	{
		while (!q.empty()){
			if (m[q.front()] == 1){ return q.front(); break; }
			q.pop();
		}
		return '#';
	}
private:
	int m[256] = { 0 };
	queue<char> q;
};