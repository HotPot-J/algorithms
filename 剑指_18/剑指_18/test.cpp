#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*
��Ŀ����
����һ�Ŷ������ĸ��ڵ��һ�����������ֵ����ӡ���������н��ֵ�ĺ�Ϊ��������������·����·������Ϊ�����ĸ����
��ʼ����һֱ��Ҷ����������Ľ���γ�һ��·����
*/
/*
˼·��dfs ���� ע�������������Ϊ�յ���ȷ����غ�����ֹ�������λ��ݣ�����ظ���
*/

struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};
class Solution {
public:
	vector<vector<int>> res;
	vector<int> path;
	void dfs(TreeNode* root, int& expectNumber, int tmp){
		if (root == NULL&&tmp == expectNumber){
			//������
			res.push_back(path);
			return;
		}
		//����Ŀ��ֵ�����ټ���
		if (tmp>expectNumber){ return; }
		if (root == NULL){ return; }
		tmp += root->val;
		path.push_back(root->val);
		//�����·�������ȷ �Ҹýڵ�����Һ��Ӷ�Ϊ�� ��غ� 
		if (tmp == expectNumber&&root->left == NULL&&root->right == NULL){
			res.push_back(path);
			tmp -= root->val;
			path.pop_back();
			return;
		}
		//�ݹ�
		dfs(root->left, expectNumber, tmp);
		dfs(root->right, expectNumber, tmp);


		//����
		path.pop_back();
		tmp -= root->val;
	}
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
		vector<vector<int>> path;
		if (root == NULL){ return path; }
		dfs(root, expectNumber, 0);
		return res;
	}
};


/*
��Ŀ����
����һ���������飬ʵ��һ�����������������������ֵ�˳��ʹ�����е�����λ�������ǰ�벿�֣����е�ż��λ�������
��벿�֣�����֤������������ż����ż��֮������λ�ò��䡣
*/
/*
˼·����ֱ�Ӽ��Ҵֱ��ľ��ǿ��ռ�
ʱ�临�Ӷ�O��n�� �ռ临�Ӷ�O��2��
*/
class Solution {
public:
	void reOrderArray(vector<int> &array) {
		vector<int> tmp;
		tmp.resize(array.size(), 0);
		int i = 0;
		for (auto e : array){
			if (e % 2 != 0){
				tmp[i++] = e;
			}
		}
		for (auto e : array){
			if (e % 2 == 0){
				tmp[i++] = e;
			}
		}
		array = tmp;
	}
};