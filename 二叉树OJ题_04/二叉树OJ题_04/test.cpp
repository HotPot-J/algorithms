#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<queue>
using namespace std;


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
/*
������32 - II. ���ϵ��´�ӡ������ II
���ϵ��°����ӡ��������ͬһ��Ľڵ㰴�����ҵ�˳���ӡ��ÿһ���ӡ��һ�С�
����:
����������: [3,9,20,null,null,15,7],
3
/ \
9  20
/  \
15   7
�������α��������
[
[3],
[9,20],
[15,7]
]
��ʾ��
�ڵ����� <= 1000
*/
 //˼· ��������� ��ÿһ������ݷ��ڶ�ά�����У���Ȼ��Ҫ�õ�queue�Ƚ��ȳ����ص㣩
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (!root){
			return res;
		}
		queue<TreeNode*> q;
		TreeNode* p ;
		q.push(root);
		while (!q.empty()){
			int flag = q.size();//��¼�����ǰ���еĳ��ȣ�����ǰ��Ľ����� ���ڿ���ѭ����
			vector<int> tmp;
			while (flag){
				p = q.front();
				q.pop();
				tmp.push_back(p->val);
				if (p->left){
					q.push(p->left);
				}
				if (p->right){
					q.push(p->right);
				}
				--flag;
			}
			res.push_back(tmp);
		}
		return res;
	}
};

/*
������54. �����������ĵ�k��ڵ�
����һ�ö��������������ҳ����е�k��Ľڵ㡣
ʾ�� 1:
����: root = [3,1,4,null,2], k = 1
3
/ \
1   4
\
2
���: 4
ʾ�� 2:
����: root = [5,3,6,2,4,null,null,1], k = 3
5
/ \
3   6
/ \
2   4
/
1
���: 4
���ƣ�
1 �� k �� ����������Ԫ�ظ���
*/

//˼·: �����������������������������ң�Ϊ�������� ��topk��Ҫ�ݼ����и�Ϊ�������������ԣ��Ҹ��󣩵�˳��ȥ����
//�õ��ݼ�����
class Solution {
public:
	vector<int> res;
	void  help(TreeNode* root){
		if (root == NULL){
			return;
		}
        help(root->right);
		res.push_back(root->val);
        help(root->left);
	
	}
	int kthLargest(TreeNode* root, int k) {
		help(root);
		return res[k - 1];
	}
};

/*
������26. �����ӽṹ
�������ö�����A��B���ж�B�ǲ���A���ӽṹ��(Լ��������������һ�������ӽṹ)
B��A���ӽṹ�� �� A���г��ֺ�B��ͬ�Ľṹ�ͽڵ�ֵ��
����:
�������� A:
3
/ \
4   5
/ \
1   2
�������� B��
4
/
1
���� true����Ϊ B �� A ��һ������ӵ����ͬ�Ľṹ�ͽڵ�ֵ��
ʾ�� 1��
���룺A = [1,2,3], B = [3,1]
�����false
ʾ�� 2��
���룺A = [3,4,5,1,2], B = [4,1]
�����true
���ƣ�
0 <= �ڵ���� <= 10000
*/

//˼·�����ҵ�A��������B���ڵ���ͬ�Ľ�� �����򱣴��λ���������� 
//      ���������еĽ����ȥ�ȶ��Ƿ�ṹ��ͬ
class Solution {
public:
	vector<TreeNode*> arr;
	bool res = true;
	void fun1(TreeNode*A, int _val){
		//Ѱ�Ҳ�����A�н��ֵ��_val��B�ĸ��ڵ㣩��ͬ�Ľ��
		if (A == NULL){
			return;
		}
		if (A->val == _val){
			arr.push_back(A);
		}
		fun1(A->left,_val);
		fun1(A->right,_val);
	}
	
	bool fun2(TreeNode* A, TreeNode*B){
		if (A==NULL||B==NULL){
			if (B != NULL){
				res == false;
			}
			return;
		}
		if (A->val != B->val){
			res = false;
			return;
		}
		fun2(A->left, B->left);
		fun2(A->right, B->right);
	}
	bool isSubStructure(TreeNode* A, TreeNode* B) {
		if (A == NULL || B == NULL){
			return false;
		}
		fun1(A, B->val);//�ҵ�A������ֵ��Bһ���Ľ��
		int n = arr.size();
		if (n == 0){
			//��ʱ˵����A�в�û���ҵ���Bͷ�ڵ���ͬ�Ľ�㽫res��Ϊfalse
			res == false;
		}
		while (n){
			fun2(arr.back(), B);
			arr.pop_back();
			--n;
		}
		return res;
	}
};

/*
������55 - I. �����������
����һ�ö������ĸ��ڵ㣬���������ȡ��Ӹ��ڵ㵽Ҷ�ڵ����ξ����Ľڵ㣨������Ҷ�ڵ㣩�γ�����һ��·����
�·���ĳ���Ϊ������ȡ�
���磺
���������� [3,9,20,null,null,15,7]��
 3
/ \
9  20
/  \
15   7
�������������� 3 ��
��ʾ��
�ڵ����� <= 10000
*/
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == NULL){
			return 0;
		}
		int leftDepth = maxDepth(root->left)+1;
		int rightDepth = maxDepth(root->right)+1;
		return leftDepth > rightDepth ? leftDepth : rightDepth;
	}
};

/*
������27. �������ľ���
�����һ������������һ�����������ú���������ľ���
�������룺
4
/   \
2     7
/ \   / \
1   3 6   9
���������
4
/   \
7     2
/ \   / \
9   6 3   1
ʾ�� 1��

���룺root = [4,2,7,1,3,6,9]
�����[4,7,2,9,6,3,1]
*/
//˼·���ݹ齻�����ҽڵ㼴��
class Solution {
public:
	TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* mirrorTree(TreeNode* root) {
		if (!root){
			return NULL;
		}
		swap(root->left, root->right);
		TreeNode* Left = mirrorTree(root->left);
		TreeNode* right = mirrorTree(root->right);
		return root;
	}
};