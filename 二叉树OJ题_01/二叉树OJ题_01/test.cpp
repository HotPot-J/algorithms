#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;

/*
������68 - I. �����������������������
����һ������������, �ҵ�����������ָ���ڵ������������ȡ�
�ٶȰٿ�������������ȵĶ���Ϊ���������и��� T ��������� p��q������������ȱ�ʾΪһ����� x��
���� x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ�����
���磬�������¶���������:  root = [6,2,8,0,4,7,9,null,null,3,5]
ʾ�� 1:
����: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
���: 6
����: �ڵ� 2 �ͽڵ� 8 ��������������� 6��
ʾ�� 2:
����: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
���: 2
����: �ڵ� 2 �ͽڵ� 4 ��������������� 2, ��Ϊ���ݶ�������������Ƚڵ����Ϊ�ڵ㱾��
˵��:
���нڵ��ֵ����Ψһ�ġ�
p��q Ϊ��ͬ�ڵ��Ҿ������ڸ����Ķ����������С�
*/

/*
����˼·�� 
   1.��������Ҫ�˽�����������Ķ��壺 
      �����������ֳ�Ϊ��������������������һ�ſ����������Ǿ����������ʵĶ�������
 1.��������������Ϊ�գ��������������н���ֵ��С�ڸ�����ֵ��
 2.��������������Ϊ�գ��������������н���ֵ�����ڸ�����ֵ��
 3.������������Ҳ�ֱ�Ϊ����������
 ����:int a[] = {5,3,4,1,7,8,2,6,0,9}
           5
	 3           7
  1    4       6    8
 0 2                  9
**�������� ��������ҪѰ�ҵĽ��Ϊ��һ������p����q�����ֵ֮��� �����ڸ��ݶ�������������Ƚڵ����Ϊ�ڵ㱾��
�����ҵ��õݹ����������(p->val - root->val)*(q->val-root->val)<=0 
��root->val >  p->val��q->val�˾�������� ��֮���ұ��� �������£�
*/


 struct TreeNode {
     int val;
    TreeNode *left;
	TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if ((root->val - p->val)*(root->val - q->val) <= 0){
			return root;
		}
		 if (root->val > p->val&&root->val > q->val){
			return lowestCommonAncestor(root->left, p, q);
		}
		 if (root->val < p->val&&root->val < q->val){
			return lowestCommonAncestor(root->right, p, q);
		}
		 return NULL;
	}
};

/*
������68 - II. �������������������
����һ��������, �ҵ�����������ָ���ڵ������������ȡ�

�ٶȰٿ�������������ȵĶ���Ϊ���������и��� T ��������� p��q������������ȱ�ʾΪһ����� x��
���� x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ�����
���磬�������¶�����:  root = [3,5,1,6,2,0,8,null,null,7,4]
ʾ�� 1:
����: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
���: 3
����: �ڵ� 5 �ͽڵ� 1 ��������������ǽڵ� 3��
ʾ�� 2:
����: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
���: 5
����: �ڵ� 5 �ͽڵ� 4 ��������������ǽڵ� 5����Ϊ���ݶ�������������Ƚڵ����Ϊ�ڵ㱾��
˵��:
���нڵ��ֵ����Ψһ�ġ�
p��q Ϊ��ͬ�ڵ��Ҿ������ڸ����Ķ������С�
*/
/*
˼·����ͨ���������߱����������������� �����Ѷȱ��
  ����ͨ�����ڵ�ݹ�ȥѰ��p��q������� ���ҵ��󷵻ظý��
  �����ǰ�������������ֱ����p q���� ��ýڵ�һ���Ǵ�
  �������ҵ���p ���ұ�û�ҵ�q ��p���Ϊ�� ��֮һ��
  ��p��qû�ҵ� �򷵻�NULL
*/
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL){
			//û�ҵ�
			return NULL;
		}
		if (root->val == p->val || root->val == q->val){
			//���ҵ�����һ���򷵻ظý��
			return root;
		}
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);
		if (left&&right){
			//p q���ҵ��� �򷵻ص�ǰ���
			return root;
		}
		else{
			//ֻ�ҵ�һ�� ��ô����������Ƚڵ�Ϊ�ڵ㱾��
			return left ? left : right;
		}
	}
};

/*
������55 - II. ƽ�������
����һ�ö������ĸ��ڵ㣬�жϸ����ǲ���ƽ������������ĳ������������ڵ���������������������1��
��ô������һ��ƽ���������

ʾ�� 1:
���������� [3,9,20,null,null,15,7]
3
/ \
9  20
/  \
15   7
���� true ��
ʾ�� 2:
���������� [1,2,2,3,3,null,null,4,4]
1
/ \
2   2
/ \
3   3
/ \
4   4
���� false ��
���ƣ�
1 <= ���Ľ����� <= 10000
*/
/*
 ˼·���ݹ��¼������������� ���ռӼ��������Ƚϼ���
*/
//�������
class Solution {
public:
	int maxDepth( TreeNode* root){
		int leftDepth = 0, rightDepth = 0;
		if (root == NULL){
			return 0;
		}
		else {
			leftDepth = maxDepth(root->left) + 1;
			rightDepth = maxDepth(root->right) + 1;
			if (leftDepth>rightDepth){
				return leftDepth;
			}
			else{
				return rightDepth;
			}
		}
	}
	bool isBalanced(TreeNode* root) {
		if (root == NULL){
			return true;
		}
		int leftSize = maxDepth(root->left);
		int rightSize = maxDepth(root->right);
		if (abs(leftSize - rightSize) >1){
			return false;
		}
		else{
			return isBalanced(root->left) && isBalanced(root->right);//�ж������������Ƿ�Ҳ����ƽ������
		}
	}
};