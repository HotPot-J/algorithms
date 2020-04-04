#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<unordered_map>
using namespace std;
/*
面试题35. 复杂链表的复制
请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，
每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针
指向链表中的任意节点或者 null。
提示：
-10000 <= Node.val <= 10000
Node.random 为空（null）或指向链表中的节点。
节点数目不超过 1000 。
*/
//思路：哈希表 复制一遍没有random指针的链表，这个时候原表和现在的表结点的对应
//关系已经存在，用哈希表记录一下 再遍历一遍，每个位置读取random指向的原表结点
//根据哈希表查到复制后对应的结点，建立连接
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
		//定义一个哈希表
		unordered_map<Node*, Node*> m;
		//为新的头节点开辟空间
		Node* newhead = new Node(head->val);
		//遍历第一遍 复制不带random链表 并使新旧链表建立关联
		Node* n = newhead;
		Node* o = head;
		while (o){
			m[o] = n;
			o = o->next; //一开始就走一步是因为上一行为了建立两个链表头节点的哈希关系 而先前已经复制过头节点了 所以要从下一个结点开始复制
			if (o == NULL){
				n->next = NULL;
			}
			else{
				Node* next = new Node(o->val);
				n->next = next;
			}
			n = n->next;
		}
		//根据old和new链表的哈希关系为new的random赋值
		n = newhead;
		o = head;
		while (o){
			n->random = m[o->random];//m[o->random]： o->random的地址在m中对应的新链表中的某结点地址
			                    //将该地址赋值给当前的n->random 则建立起了该节点的复杂连接 
			o = o->next;
			n = n->next;
		}
		return newhead;
	}
};