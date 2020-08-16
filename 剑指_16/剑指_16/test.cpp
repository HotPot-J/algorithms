#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

/*�������´�ӡ��������
�������´�ӡ����������ÿ���ڵ㣬ͬ��ڵ�������Ҵ�ӡ��
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
	vector<int> PrintFromTopToBottom(TreeNode* root) {
		vector<int> res;
		if (root == NULL){ return res; }
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()){
			res.push_back(q.front()->val);
			if (q.front()->left){ q.push(q.front()->left); }
			if (q.front()->right){ q.push(q.front()->right); }
			q.pop();
		}
		return res;
	}
};

/*��Ŀ���� �����������ĺ������
����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ����������򷵻�true, ���򷵻�false��
�������������������������ֶ�������ͬ��
*/
/*
˼·һ���ݹ�
���ݶ��������������ʣ��������������һ������ǵ�ǰ�����ĸ��ڵ㣺
���е����һ�������Ϊrear
1.һ����������֮ǰ�������ҵ�һ�� [С��]��rear��[����] ��λ�� ����
[С��]��rear�����ߣ�rear��[����]������λ��
2.��������[����]��rear����λ�� �����Ļ����������������������
3.���������Ľ��۾Ϳ��Է��� �ݹ��ȥ������⡣
*/
class Solution {
public:
	bool fun(vector<int>& seq, int prev, int rear){
		if (prev >= rear){ return true; }
		int i = prev;
		for (i; i<rear; ++i){
			if (seq[i]>seq[rear]){ break; } //�ҵ��ֽ�� �� [С��]��rear��[����] ����[С��]��rear�����ߣ�rear��[����]��λ��i
		}
		int j = i + 1;
		for (j; j<rear; ++j){
			if (seq[j]<seq[rear]){ return false; }
		}
		//�ݹ��������������ж�
		return fun(seq, prev, i - 1) && //������
			fun(seq, i, rear - 1);  //������
	}
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty()){ return false; }
		return fun(sequence, 0, sequence.size() - 1);
	}
};

/*
˼·��:�ǵݹ鷽��
	���ڵݹ��˼�룬����ÿ��Ѱ����������������������ֱ�ӴӺ���ǰ���ж�ÿһ�������ĸ��ڵ��Ƿ�����[��С](root)[�Ҵ�]
	����[��С](root)����(root)[��С] 
	Ҳ����˵Ҫô����������С�Ҵ�ķֽ�㣬Ҫô���һ·����С���ף�Ҫô��ʹ���һ·�󵽵� ������ƽ���������ԭ��
*/
class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		int size = sequence.size();
		if (size == 0){ return false; }
		//�Ӻ���ǰ �ж�ÿһ������������Ƿ���������
		size -= 1; //�±�
		while (size){
			int i = 0;
			while(i<size&&sequence[i] < sequence[size]){ ++i;}
			while(i<size&&sequence[i] > sequence[size]){ ++i;}
			//����������iһ�������ߵ�size-1���λ�õ�
			if (i < size - 1){ return false; }
			else{
				--size;
			}
		}
		return true;
	}
};