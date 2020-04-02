#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
面试题22. 链表中倒数第k个节点
输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。
示例：
给定一个链表: 1->2->3->4->5, 和 k = 2.
返回链表 4->5.
*/
//思路：快慢指针法 左边的指针L指向head 右边的指针R先走k个结点 当R!=NULL时 R和L指针每次走1步 
//当R!=NULL时 则从L位置返回链表即可
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
			//若k为0直接返回该链表
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
面试题24. 反转链表
定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
限制：
0 <= 节点个数 <= 5000
*/

//解法一：双指针 top 和 tail指针分别表示 当前遍历结点的前一个结点和当前遍历结点 tmp指向当前遍历结点的后一个结点
//每次tail的next指向top top = tail tail = tmp tmp = tmp->next 以达到翻转的效果
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

//解法二：递归 
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == NULL || head->next == NULL){
			return head;
		}
		ListNode* p = reverseList(head->next);//成为返回的头节点
		head->next->next = head;  //让最后一个结点的next指向当前head结点 head结点的next置空
		head->next = NULL;
		return p;
	}
};