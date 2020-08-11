#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<climits>
#include<vector>
#include<stack>
using namespace std;

/*
��������������
��Ŀ����
HZż������Щרҵ������������Щ�Ǽ����רҵ��ͬѧ����������鿪����,���ַ�����:�ڹ��ϵ�һάģʽʶ����,
������Ҫ��������������������,������ȫΪ������ʱ��,����ܺý��������,��������а�������,�Ƿ�Ӧ�ð���ĳ������,
�������Աߵ��������ֲ����أ�����:{6,-3,-2,7,-15,1,2,2},����������������Ϊ8(�ӵ�0����ʼ,����3��Ϊֹ)����һ����
�飬��������������������еĺͣ���᲻�ᱻ������ס��(�������ĳ���������1)
*/
/*
˼·���ҳ�ÿ��������������ͣ��������С��0�Ͳ���Ѱ���� ��Ϊû���壩��ά��һ��_max����
*/
class Solution1 {
public:
	int FindGreatestSumOfSubArray(vector<int> array) {
		int size = array.size();
		int _max = INT_MIN;
		for (int i = 0; i<size; ++i){
			int tmp = array[i], tmp_max = array[i];
			for (int j = i + 1; j<size; ++j){
				tmp += array[j];
				if (tmp>tmp_max){ tmp_max = tmp; }
				if (tmp<0){ break; }
			}
			if (tmp_max>_max){ _max = tmp_max; }
		}
		return _max;
	}
};

//int main(){
//	Solution a;
//	vector<int> arr = { 6, -3, -2, 7, -15, 1, 2, 2 };
//	a.FindGreatestSumOfSubArray(arr);
//	return 0;
//}

/*
��ת������
����һ��������ת��������������ı�ͷ��
*/
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
}; 

/*
˼·һ���ݹ�
*/
class Solution2 {
public:
	//�ݹ�汾
	ListNode* res = NULL; //ͷ�ڵ�
	void fun(ListNode* pre, ListNode* rear, ListNode* pHead){
		if (rear == NULL){
			pHead->next = NULL; //ԭ�ȵ�ͷ�ڵ�����Ϊ���һ���ڵ㣬������next�ÿ�
			res = pre;
			return;
		}
		fun(pre->next, rear->next, pHead);
		rear->next = pre;
	}
	ListNode* ReverseList(ListNode* pHead) {
		if (pHead == NULL || pHead->next == NULL){ return pHead; }
		ListNode* pre = pHead, *rear = pHead->next;
		fun(pre, rear, pHead);
		return res;
	}
};

//���� ����ջģ��ݹ�Ĺ���
class Solution {
public:
	ListNode* ReverseList(ListNode* pHead) {
		stack<ListNode*> s;
		if (pHead == NULL || pHead->next == NULL){ return pHead; }
		ListNode* cur = pHead;
		while (cur){
			s.push(cur);
			cur = cur->next;
		}
		ListNode* res = s.top();//��¼ͷ�ڵ�
		while (s.size()>1){
			ListNode* rear = s.top();
			s.pop();
			rear->next = s.top();
		}
		s.top()->next = NULL;
		return res;
	}
};

//int main(){
//	Solution a;
//	ListNode* pHead = new ListNode(0);
//	ListNode* cur = pHead;
//	for (int i = 1; i < 5; ++i){
//		ListNode* tmp = new ListNode(i);
//		cur->next = tmp;
//		cur = cur->next;
//	}
//	a.ReverseList(pHead);
//	return 0;
//}