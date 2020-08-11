#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<climits>
#include<vector>
#include<stack>
using namespace std;

/*
连续子数组最大和
题目描述
HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,
常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,
并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。给一个数
组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)
*/
/*
思路：找出每个起点的最大连续和（当这个和小于0就不用寻找了 因为没意义），维护一个_max即可
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
翻转单链表
输入一个链表，反转链表后，输出新链表的表头。
*/
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
}; 

/*
思路一：递归
*/
class Solution2 {
public:
	//递归版本
	ListNode* res = NULL; //头节点
	void fun(ListNode* pre, ListNode* rear, ListNode* pHead){
		if (rear == NULL){
			pHead->next = NULL; //原先的头节点现在为最后一个节点，所以其next置空
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

//迭代 利用栈模拟递归的过程
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
		ListNode* res = s.top();//记录头节点
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