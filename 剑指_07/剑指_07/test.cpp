#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;

/*
1、链表中环的入口节点
给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。
*/


/*
思路：该文件下画图板有推导过程和图解
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
			fast = fast->next->next;//每次走两步
			slow = slow->next; //每次走一步
			if (fast == slow){
				//第一次相遇
				break;
			}
		}
		if (fast == NULL || fast->next == NULL){
			//没有环 
			return NULL;
		}
		fast = pHead;
		while (1){
			if (fast == slow){ break; }  //有可能该链表直接就是个环-- 
			fast = fast->next; slow = slow->next;
		}
		return fast;
	}
};

/*
题目描述 :字符流中第一个不重复的字符
请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。
输出描述:
如果当前字符流没有存在出现一次的字符，返回#字符。
*/

/*
思路：哈希 利用一个int[256]的数组 
	  队列 用来判断先后顺序 （注意 只有在第一次遍历到的字母方可入队 则避免了很多重复判断 提高效率）
*/
class Solution
{
public:
	//Insert one char from stringstream
	void Insert(char ch)
	{
		m[ch]++;
		if (m[ch] == 1){
			//第一次遇见
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