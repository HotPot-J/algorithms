#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
/*
1.二叉树的下一个节点
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，
树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
*/

/*
思路:分三种情况：
前提：前序遍历 左根右
	1.判空
	2.当无右结点，寻找其第一个把自己当作左子树的祖先结点
	3.当有右结点，寻找其右子树中序遍历的第一个结点即可
*/

struct TreeLinkNode {
int val;
struct TreeLinkNode *left;
struct TreeLinkNode *right;
struct TreeLinkNode *next;
TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

}
};

class Solution {
public:
	TreeLinkNode* fun(TreeLinkNode* prev, TreeLinkNode* rear){
		//前序遍历右子树
		if (rear == NULL){
			return prev;
		}
		return fun(rear, rear->left);
	}
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		//判空 或者根节点无右以直接返回NULL
		if (pNode == NULL){ return NULL; }
		//既没有右也不是根 
		if (pNode->right == NULL){
			//找其第一个把它当作左子树的祖先结点（因为左根右）
			while (pNode->next != NULL&&pNode->next->left != pNode){
				pNode = pNode->next;
			}
			return pNode->next;
		}
		//有右 则就按照前序遍历的顺序 寻找到pNode的下一个结点
		return fun(pNode, pNode->right);
	}
};


/*
删除链表中的重复结点
在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 
例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
*/

/*
思路一:
非递归版本：双指针（较复杂 较难）
1.首先判空 判一个结点的情况
2.确定头节点 （有可能一开始就是重复的）
3.确定头节点以后 进行判空判和一个结点的情况直接返回
4.如果是两个结点 也可以直接返回，因为这两个节点一定是不相等的（因为确定的头节点一定不是重复的）
5.三个及以上的结点，定义tmp 去为头节点的next进行绑定  p和r一前以后去寻找不重复的结点
6.此时又分为两种情况：经历了删除 未经历删除
7.重复6过程遍历即可
*/

struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};

class Solution1 {
public:
	ListNode* deleteDuplication(ListNode* pHead)
	{
		if (pHead == NULL){ return NULL; }
		if (pHead->next == NULL){ return pHead; } //只有一个结点
		//先寻找Phead的真正起点（因为有可能直接头就是重复的）
		ListNode* p = pHead->next;
		while (p != NULL&&pHead != NULL && (p->val == pHead->val)){
			while (p != NULL&&p->val == pHead->val){
				p = p->next;
			}
			pHead = p;
			if (p != NULL){ p = p->next; }
		}
		//找到真正起点 继续判头节点的情况
		if (pHead == NULL){ return NULL; }
		if (p == NULL || p->next == NULL){
			//只有一个或两个结点 
			return pHead;
		}
		//三个及以上结点 

		ListNode* r = p->next, *tmp = pHead;
		while (r != NULL){
			bool flag = false;
			while (r != NULL&&r->val == p->val){
				flag = true;
				r = r->next;
			}
			if (flag){
				//有删除 移动p r（判断下一个数字是否重复）
				p = r;
				if (r != NULL){ r = r->next; }
				if (p == NULL || r == NULL || p->val != r->val){
					//判断此时的p r若不相等，则p可保留不必删除
					tmp->next = p;
					tmp = tmp->next;
					//p r继续向后遍历
					if (p != NULL&&r != NULL){ p = p->next; r = r->next; }
				}
			}
			else{
				//没删除
				tmp->next = p;
				tmp = tmp->next;
				//p r继续向后遍历
				p = r;
				if (r != NULL){ r = r->next; }
			}
		}
		return pHead;
	}
};

/*
思路二：递归 
*/
class Solution {
public:
	ListNode* res;
	ListNode* deleteDuplication(ListNode* pHead)
	{
		if (pHead == NULL){ return NULL; }
		if (pHead!= NULL&&pHead->next == NULL){ return pHead; }
		
		ListNode* tmp;
		if (pHead->val == pHead->next->val){
			//重复
			tmp = pHead->next->next;
			while (tmp != NULL&&tmp->val == pHead->val){
				//跳过当前重复
				tmp = tmp->next;
			}
			return deleteDuplication(tmp);
		}
		else{
			//不
			tmp = pHead->next;
			pHead->next = deleteDuplication(tmp);
			return pHead;
		}
	}
};