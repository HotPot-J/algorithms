#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;

/*
1����֮����˳���ӡ��������
��ʵ��һ����������֮���δ�ӡ������������һ�а��մ����ҵ�˳���ӡ���ڶ��㰴�մ��������˳���ӡ��
�����а��մ����ҵ�˳���ӡ���������Դ����ơ�
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
˼·��1.������� ֻ�����ǲ���˫�˶��еĲ������
2.�����ұ��������Ҳ�Ǵ����ҽ� �Ӷ�β�� ��ͷ��
3.���ҵ�����������Ҳ�Ǵ��ҵ���� �Ӷ�ͷ�� ��β��
*/
class Solution {
public:
	vector<vector<int> > Print(TreeNode* pRoot) {
		vector<vector<int>> res;
		if (pRoot == NULL){ return res; }
		deque<TreeNode*> s;
		bool flag = true;
		s.push_back(pRoot);
		while (!s.empty()){
			int len = s.size();
			vector<int> tmp;
			if (flag == true){
				//�����Ҵ�
				for (int i = 0; i<len; ++i){
					//�����Ҵ�
					tmp.push_back(s.front()->val);
					if (s.front()->left){ s.push_back(s.front()->left); }
					if (s.front()->right){ s.push_back(s.front()->right); }
					s.pop_front();
				}
				flag = false; //��һ�ξ��Ǵ��ҵ���
			}
			else{
				//���ҵ����
				for (int i = 0; i<len; ++i){
					tmp.push_back(s.back()->val);
					if (s.back()->right){ s.push_front(s.back()->right); }
					if (s.back()->left){ s.push_front(s.back()->left); }
					s.pop_back();
				}
				flag = true; //��һ�ξ��Ǵ�����
			}
			res.push_back(tmp);
		}
		return res;
	}
};

/*
3���Գƶ�����
��ʵ��һ�������������ж�һ�ö������ǲ��ǶԳƵġ�ע�⣬���һ��������ͬ�˶������ľ�����ͬ���ģ�
������Ϊ�ԳƵġ�
*/

/*
˼·���ݹ� �����������ȥ�Աȵ�ǰ״̬ �����ȷ�ٽ�����һ��������
�Գƣ������� �������ҵ��ҶԳ�  �����Ҳ�ú��ҵ���Գƣ�����
*/
class Solution {
public:
	bool check(TreeNode* left, TreeNode* right){
		if (left == NULL&&right == NULL){ return true; }
		if (left == NULL || right == NULL){ return false; }
		if (left->val != right->val){ return false; }
		//����Ϳ��Խ�����һ��ıȽ���
		return check(left->left, right->right) && check(left->right, right->left);//�Գ�
	}
	bool isSymmetrical(TreeNode* pRoot)
	{
		if (pRoot == NULL){ return true; }
		return check(pRoot->left, pRoot->right);
	}
};