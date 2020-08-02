#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<vector>
#include<queue>
#include <functional> 
using namespace std;


/*
1.��εõ�һ���������е���λ����������������ж�����������ֵ����ô��λ������������ֵ����֮��λ���м����ֵ��
������������ж���ż������ֵ����ô��λ������������ֵ����֮���м���������ƽ��ֵ������ʹ��Insert()������ȡ��������
ʹ��GetMedian()������ȡ��ǰ��ȡ���ݵ���λ����
*/

/*
˼·��
1.����С��
2.ά����ѵ�����ֵС��С��
3.ά��С�ѵ�ֵ���ڴ��
(ÿ�β��붼�õ�ǰ���ֵ��С�Ѳ�  ��ǰ��Сֵ����Ѳ��� ��֤��������������ȷŽ�����ٴӴ����������min��
�����ż���� �ȷ���С�� ��С����С�ĸ����)
�����ͱ�֤�� ���<С�Ѻ����
����Ϊ����������λ�� = min.top()
ż��������λ��= (max.top()+min.top())/2
*/
class Solution {
public:
	Solution()
		:flag(0)
	{}
	void Insert(int num)
	{
		if (flag % 2 == 0){
			max.push(num);
			//������е����ֵ��С��
			min.push(max.top());
			max.pop();
		}
		else{
			min.push(num);
			//��С�������ĸ����
			max.push(min.top());
			min.pop();
		}
		++flag;
	}

	double GetMedian()
	{
		if (flag % 2){
			return (double)min.top();
		}
		return (double)(max.top() + min.top()) / 2;
	}
private:
	int flag;
	priority_queue<int> max;
	priority_queue<int, vector<int>, greater<int>> min;
};


/*
��Ŀ�����������������ĵ�kС�ڵ�
����һ�ö��������������ҳ����еĵ�kС�Ľ�㡣���磬 ��5��3��7��2��4��6��8�� 
�У��������ֵ��С˳�����С����ֵΪ4��
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
˼·��
1�����������������ʾ�������������򣨽��򣩣������push
2�� k-1�ξ��ǵ�kС��ֵ
3.ע�⣺���ܴ�������ָ��Ϊ�գ�����kԽ��
*/

//�ݹ���������汾
class Solution {
public:
	void fun(TreeNode*cur, vector<TreeNode*>&s){
		if (cur == NULL){ return; }
		fun(cur->left, s);
		s.push_back(cur);
		fun(cur->right, s);
	}
	TreeNode* KthNode(TreeNode* pRoot, int k)
	{
		if (pRoot == NULL || k <= 0){ return NULL; }
		vector<TreeNode*> s;
		fun(pRoot, s);
		if (k>s.size()){
			return NULL;
		}
		return s[k - 1];
	}
};

//�ǵݹ���������汾 ����ջ ģ��ݹ�Ĺ���

class Solution {
public:

	void MidOrder(TreeNode* cur,stack<TreeNode*>& s,vector<TreeNode*>& res){
		while (cur || !s.empty){
			while (cur){
				s.push(cur);
				cur = cur->left;
			}
			TreeNode* top = s.top();
			s.pop();
			res.push_back(top);
			cur = top->right;
		}
	}

	TreeNode* KthNode(TreeNode* pRoot, int k)
	{
		if (pRoot == NULL || k <= 0){ return NULL; }
		vector<TreeNode*> res;
		stack<TreeNode*> s;
		MidOrder(pRoot, s, res);
		if (k > res.size()){ return NULL; }
		return res[k - 1];
	}
};