#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<queue>
#include<deque>
using namespace std;



 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

/*
������32 - I. ���ϵ��´�ӡ������
���ϵ��´�ӡ����������ÿ���ڵ㣬ͬһ��Ľڵ㰴�մ����ҵ�˳���ӡ��
����:
����������: [3,9,20,null,null,15,7],
3
/ \
9  20
/  \
15   7
���أ�
[3,9,20,15,7]
��ʾ��
�ڵ����� <= 1000
*/
 //˼·��������� ���������Ĳ��������Ҫ�������У�
class Solution {
public:
	vector<int> levelOrder(TreeNode* root) {
		if (root == NULL){
			return;
		}
		vector<int> res;
		queue<TreeNode*> q;
		TreeNode* Front;
		q.push(root);
		while (!q.empty()){
			//������Ϊ�ǿ� ˵����û�б������
			Front = q.front();//��ʱ���浱ǰ�������
			q.pop();//�ö�ͷ����
			//�øýڵ��val������
			res.push_back(Front->val);
			if (Front->left){
				//��������
				q.push(Front->left);
			}
			if (Front->right){
				//�����ҽ��
				q.push(Front->right);
			}
		}
		return res;
	}
};

/*
������32 - III. ���ϵ��´�ӡ������ III
��ʵ��һ����������֮����˳���ӡ������������һ�а��մ����ҵ�˳���ӡ���ڶ��㰴�մ��ҵ����˳���ӡ��
�������ٰ��մ����ҵ�˳���ӡ���������Դ����ơ�
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
[20,9],
[15,7]
]
��ʾ��
�ڵ����� <= 1000
*/
//˼·1����Ȼ�ǲ������ ����Ҫʹ��˫�˶���deque �������� ���ڴ������ұ�����ǰ�����
//       ��ż����ͺ��ǰ��
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		bool flag = true;//��������Ϊ�� ż����Ϊ�ٵ�
		deque<TreeNode*> q;
		if (root == NULL){
			return res;
		}
		q.push_back(root);
		while (!q.empty()){
			int n = q.size();
			vector<int> tmp;
			TreeNode* node = NULL;
			while (n){
				if (flag){
					//������ǰ�����
					node = q.front();
					q.pop_front();
					if (node->left){ //���
						q.push_back(node->left);
					}
					if (node->right){
						q.push_back(node->right);
					}
				}
				else{
					//ż������ǰ��
					node = q.back();
					q.pop_back();
					if (node->right){ //���   ������һ��ż�����ǰ������� ����������Ҫ����ͷ�� �����Һ���
						q.push_front(node->right);
					}
					if (node->left){
						q.push_front(node->left);
					}
				}
				tmp.push_back(node->val);
				--n;
			}
			res.push_back(tmp);
			flag = !flag;
		}
		return res;
	}
};