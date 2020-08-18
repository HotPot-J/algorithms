#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
树的子结构：
输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
*/

/*
思路：先序遍历A树，找到A树与B头结点点相等的结点，然后用这两个结点去判断。
	判断函数也采用先序遍历
*/

struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};

/*
先序遍历pRoot1，把每一个和pRoot2相等的结点，拿出去判断其结构是否一致
*/
class Solution {
public:
	//判断函数check
	bool check(TreeNode* pRoot1, TreeNode* pRoot2){
		//如果pRoot结点为空,说明pRoot走完了
		if (pRoot2 == NULL){ return true; } //
		//而pRoot2不为空，但是pRoot1走完了，说明2不是1的子结构
		if (pRoot1 == NULL){ return false; }
		//如果两个结点都不为空 但数值不同
		if (pRoot1&&pRoot2 && (pRoot1->val != pRoot2->val)){ return false; }
		//走到这里说明相等 接着遍历
		return check(pRoot1->left, pRoot2->left) &&
			check(pRoot1->right, pRoot2->right);
	}

	bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
	{
		if (pRoot1 == NULL || pRoot2 == NULL){ return false; }
		//先序遍历pRoot1 寻找和pRoot->val相等的结点
		if (pRoot1->val == pRoot2->val&&check(pRoot1->left, pRoot2->left) &&
			check(pRoot1->right, pRoot2->right)){
			return true;
		}
		return HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
	}
};

/*
剑指 Offer 52. 两个链表的第一个公共节点
输入两个链表，找出它们的第一个公共节点。
*/

/*
思路一：哈希
*/

#include<unordered_map>
using namespace std;

struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) :
val(x), next(NULL) {
}
};
class Solution {
public:
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		if (pHead1 == NULL || pHead2 == NULL){ return NULL; }
		unordered_map<ListNode*, bool> map1;
		ListNode* cur1 = pHead1, *cur2 = pHead2;
		while (cur1){
			map1[cur1] = true;
			cur1 = cur1->next;
		}
		while (cur2){
			if (map1[cur2]){
				return cur2;
			}
			cur2 = cur2->next;
		}
		return NULL;
	}
};

/*

思路二：双指针 
	假设A与B公共部分长度为C，而B比A的非公共部分长x ，那么当A走完一趟回到B的起点时，B距离终点为x，而当B走完回到A的起点
	，A恰好走了x距离，此时AB的非公共长度整好相等，那么其相遇点就是公共结点
*/

class Solution {
public:
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		if (pHead1 == NULL || pHead2 == NULL){ return NULL; }
		ListNode* cur1 = pHead1, *cur2 = pHead2;
		while (cur1 != cur2){
			//不能是cur1->next==NULL就开始回到彼此的起点
			//由于有可能不相交，所以一定要让他们走到NULL再回到彼此的起点
			//在不相交的情况下，当他们同时为NULL也算相等，那么才不会造成死循环
			if (cur1 == NULL){ cur1 = pHead1; }
			else{ cur1 = cur1->next; }
			if (cur2 == NULL){ cur2 = pHead2; }
			else{
				cur2 = cur2->next;
			}
		}
		return cur1;
	}
};