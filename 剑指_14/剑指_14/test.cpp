#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
����ĵ�����K�����
����һ����������������е�����k����㡣
*/

/*
˼·:ǰ��ָ�� ��ߵ�ָ������K��  Ȼ��ǰ��ָ��ͬʱ������� ����ָ���ߵ��� ��ǰָ������Ϊ������K�����
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
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		if (pListHead == NULL){ return NULL; }
		ListNode* prev = pListHead;
		ListNode* rear = pListHead;
		 int tmp = k;
		while (rear&&tmp){
			rear = rear->next;
			--tmp;
		}
		if (tmp > 0){ return NULL; } //�������ΪK����������
		while (rear){
			rear = rear->next;
			prev = prev->next;
		}
		return prev;
	}
};

//int main(){
//	ListNode* head = new ListNode(0);
//	ListNode* cur = head;
//	for (int i = 1; i <= 4; ++i){
//		ListNode* a = new ListNode(i);
//		cur->next = a;
//		cur = cur->next;
//	}
//	Solution b;
//	b.FindKthToTail(head, 3);
//	return 0;
//}

/*
˼·��topk���� ��С��K���� ���ռ�Ϊk�Ĵ�ѣ������Ѷ����ڼ�����ѵ� ��pop�Ѷ� �����������ļ�Ϊ��С��K����
*/
class Solution {
public:
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
		//˵��input������K�� ��ֱ�ӷ���input
		vector<int> res; res.reserve(k);
		if (input.size()<k || k == 0){ return res; }
		priority_queue<int> pq;
		int i = 0;
		while (i<k&&i<input.size()){
			pq.push(input[i]);
			++i;
		}
		for (int j = k; j<input.size(); ++j){
			if (input[j]<pq.top()){
				pq.pop();
				pq.push(input[j]);
			}
		}
		for (int j = 0; j<k; ++j){
			res.push_back(pq.top());
			pq.pop();
		}
		return res;
	}
};

//int main(){
//	vector<int> arr = { 4, 5, 1, 6, 2, 7, 3, 8 };
//	Solution a;
//	a.GetLeastNumbers_Solution(arr, 4);
//	return 0;
//}