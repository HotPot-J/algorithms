#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<unordered_map>
using namespace std;
/*
������35. ��������ĸ���
��ʵ�� copyRandomList ����������һ�����������ڸ��������У�
ÿ���ڵ������һ�� next ָ��ָ����һ���ڵ㣬����һ�� random ָ��
ָ�������е�����ڵ���� null��
��ʾ��
-10000 <= Node.val <= 10000
Node.random Ϊ�գ�null����ָ�������еĽڵ㡣
�ڵ���Ŀ������ 1000 ��
*/
//˼·����ϣ�� ����һ��û��randomָ����������ʱ��ԭ������ڵı���Ķ�Ӧ
//��ϵ�Ѿ����ڣ��ù�ϣ���¼һ�� �ٱ���һ�飬ÿ��λ�ö�ȡrandomָ���ԭ����
//���ݹ�ϣ��鵽���ƺ��Ӧ�Ľ�㣬��������
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};
class Solution {
public:
	Node* copyRandomList(Node* head) {
		if (head == NULL){
			return head;
		}
		//����һ����ϣ��
		unordered_map<Node*, Node*> m;
		//Ϊ�µ�ͷ�ڵ㿪�ٿռ�
		Node* newhead = new Node(head->val);
		//������һ�� ���Ʋ���random���� ��ʹ�¾�����������
		Node* n = newhead;
		Node* o = head;
		while (o){
			m[o] = n;
			o = o->next; //һ��ʼ����һ������Ϊ��һ��Ϊ�˽�����������ͷ�ڵ�Ĺ�ϣ��ϵ ����ǰ�Ѿ����ƹ�ͷ�ڵ��� ����Ҫ����һ����㿪ʼ����
			if (o == NULL){
				n->next = NULL;
			}
			else{
				Node* next = new Node(o->val);
				n->next = next;
			}
			n = n->next;
		}
		//����old��new����Ĺ�ϣ��ϵΪnew��random��ֵ
		n = newhead;
		o = head;
		while (o){
			n->random = m[o->random];//m[o->random]�� o->random�ĵ�ַ��m�ж�Ӧ���������е�ĳ����ַ
			                    //���õ�ַ��ֵ����ǰ��n->random �������˸ýڵ�ĸ������� 
			o = o->next;
			n = n->next;
		}
		return newhead;
	}
};