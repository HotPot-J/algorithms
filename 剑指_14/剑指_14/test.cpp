#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
链表的倒数第K个结点
输入一个链表，输出该链表中倒数第k个结点。
*/

/*
思路:前后指针 后边的指针先走K步  然后前后指针同时往后遍历 当后指针走到空 则前指针正好为倒数第K个结点
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
		if (tmp > 0){ return NULL; } //此种情况为K大于链表长度
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
思路：topk问题 最小的K个数 建空间为k的大堆，但凡堆顶大于即将入堆的 则pop堆顶 最终留下来的即为最小的K个数
*/
class Solution {
public:
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
		//说明input还不够K个 则直接返回input
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