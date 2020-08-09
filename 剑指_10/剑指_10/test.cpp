#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};
/*
ƽ�������
����һ�ö��������жϸö������Ƿ���ƽ���������

���������ֻ��Ҫ������ƽ���ԣ�����Ҫ�������ǲ������������
*/

/*
˼·��ǰ����� 
*/
class Solution {
public:
	int fun(TreeNode* pRoot){
		if (pRoot == NULL){
			return 0;
		}
		int leftDepth = fun(pRoot->left) + 1;
		int rightDepth = fun(pRoot->right) + 1;
		return leftDepth>rightDepth ? leftDepth : rightDepth;
	}
	bool IsBalanced_Solution(TreeNode* pRoot) {
		if (pRoot == NULL){
			return true;
		}
		//�ж�һ�ε�ǰ
		int leftDepth = fun(pRoot->left);
		int rightDepth = fun(pRoot->right);
		return (abs(leftDepth - rightDepth) <= 1)
			&& IsBalanced_Solution(pRoot->left)
			&& IsBalanced_Solution(pRoot->right);
	}
};

/*
�������+��֦  �����ĳһ����֧���������� ֱ�ӷ��� ����֦����
*/

class Solution2 {
public:
	int fun(TreeNode* pRoot){
		if (pRoot == NULL){
			return 0;
		}
		int leftDepth = fun(pRoot->left) + 1;
		int rightDepth = fun(pRoot->right) + 1;
		return leftDepth>rightDepth ? leftDepth : rightDepth;
	}
	bool IsBalanced_Solution(TreeNode* pRoot) {
		if (pRoot == NULL){
			return true;
		}
		if (!IsBalanced_Solution(pRoot->left)){ return false; } //Ϊfalseֱ�Ӽ�֦
		int leftDepth = fun(pRoot->left);
		if (!IsBalanced_Solution(pRoot->right)) { return false; }//Ϊfalseֱ�Ӽ�֦
		int rightDepth = fun(pRoot->right);
		if (abs(leftDepth - rightDepth) <= 1){ return true; }
		else{ return false; }
	}
};

/*
2�������������
����һ�ö����������������ȡ��Ӹ���㵽Ҷ������ξ����Ľ�㣨������Ҷ��㣩�γ�����һ��·����
�·���ĳ���Ϊ������ȡ�
*/

/*
˼·:������ȱ���
*/
class Solution4{
public:
	int TreeDepth(TreeNode* pRoot)
	{
		if (pRoot == NULL){ return 0; }
		int left = TreeDepth(pRoot->left)+1;
		int right = TreeDepth(pRoot->right)+1;
		return left > right ? left : right;
	}
};

/*
��ά�����еĲ���
��һ����ά�����У�ÿ��һά����ĳ�����ͬ����ÿһ�ж����մ����ҵ�����˳��
����ÿһ�ж����մ��ϵ��µ�����˳�����������һ������������������һ����ά
�����һ���������ж��������Ƿ��и�������
*/

/*
˼·��dfs �ݹ���ݷ������������� ���߹���·�����ټ���Ѱ�� 
*/
class Solution {
public:
	int ret = 0;
	bool check(vector<vector<int>>& arr, int i, int j, vector<vector<bool>>& m){
		int row = arr.size(), col = arr[0].size();
		if (i<0 || i >= row || j<0 || j >= col || !m[i][j]){
			return false;
		}
		return true;
	}
	void dfs(int target, vector<vector<int>>& arr, int i, int j, vector<vector<bool>>& m){
		if (!check(arr, i, j, m)){ return; }
		if (arr[i][j] == target){ ret = 1; }
		if (ret == 1){ return; }
		//С�ھ�ȥ�»�����ȥ��
		m[i][j] = false;  //�߹��ľͲ�����
		dfs(target, arr, i + 1, j, m);
		dfs(target, arr, i, j + 1, m);
		if (arr[i][j]>target){ return; }
	}
	bool Find(int target, vector<vector<int> > array) {
		vector<vector<bool>> m;
		m.resize(array.size());
		for (int i = 0; i < array.size(); ++i){
			m[i].resize(array[0].size(), true);
		}
		dfs(target, array, 0, 0, m);
		if (ret == 1){ return true; }
		return false;
	}
};

int main(){
	Solution a;
	vector<vector<int>> b;
	int n = 0, target = 0;
	cin >> n >> target;
	b.resize(n);
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			int tmp = 0;
			cin >> tmp;
			b[i].push_back(tmp);
		}
	}
	a.Find(target, b);
	return 0;
}