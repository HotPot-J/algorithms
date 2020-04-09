#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

/*
������34. �������к�Ϊĳһֵ��·��
����һ�ö�������һ����������ӡ���������нڵ�ֵ�ĺ�Ϊ��������������·����
�����ĸ��ڵ㿪ʼ����һֱ��Ҷ�ڵ��������Ľڵ��γ�һ��·����
ʾ��:
�������¶��������Լ�Ŀ��� sum = 22��
 5
 / \
4    8
/    / \
11  13  4
/  \    / \
7   2  5   1
����:
[
[5,4,11,2],
[5,8,4,5]
]
��ʾ��
�ڵ����� <= 10000
*/


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
/*
˼·�����ݷ� ʹ��path��¼·�� tar��ʼ��Ϊsum
��tar==0 �� root->right==NULL&&root->left==NULLʱ����ǰ·������ret�� 
������л��� ʹtar-=��ǰroot->val ����������ķ�ʽȥѰ����ȷ��
*/
class Solution {
public:
	vector<vector<int>> ret;
	vector<int> path;
	void findPath(TreeNode* root, int tar){
		if (root == NULL) return ;
		path.push_back(root->val);
		tar -= root->val;
		if (tar == 0 && root->left == NULL&&root->right == NULL){
			//��·������
			ret.push_back(path);
		}
		findPath(root->left, tar);
		findPath(root->right, tar);
		//���������·��pop����
		path.pop_back();
	}
	vector<vector<int>>pathSum(TreeNode* root, int sum) {
		findPath(root, sum);
		return ret;
	}
};

/*
������28. �ԳƵĶ�����
��ʵ��һ�������������ж�һ�ö������ǲ��ǶԳƵġ����һ�ö����������ľ���һ������ô���ǶԳƵġ�
���磬������ [1,2,2,3,4,4,3] �ǶԳƵġ�
1
/ \
2   2
/ \ / \
3  4 4  3
����������� [1,2,2,null,3,null,3] ���Ǿ���ԳƵ�:
1
/ \
2   2
\   \
3    3

ʾ�� 1��
���룺root = [1,2,2,3,4,4,3]
�����true
ʾ�� 2��
���룺root = [1,2,2,null,3,null,3]
�����false
���ƣ�
0 <= �ڵ���� <= 1000
*/
class Solution {
public:
	bool fun(TreeNode* _left, TreeNode* _right){
		if (_left == NULL&&_right == NULL){
			return true;
		}
		if (_left == NULL || _right == NULL){
			return false;
		}
		if (_left->val != _right->val){
			return false;
		}
		return fun(_left->left, _right->right) && fun(_left->right,_right->left);//ǰ�����
	}
	bool isSymmetric(TreeNode* root) {
		if (root == NULL){
			return true;
		}
		return fun(root->left, root->right);
	}
};