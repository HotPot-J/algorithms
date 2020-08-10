#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string.h>
#include<vector>
using namespace std;

/*
�滻�ո�
��ʵ��һ����������һ���ַ����е�ÿ���ո��滻�ɡ�%20����
���磬���ַ���ΪWe Are Happy.�򾭹��滻֮����ַ���ΪWe%20Are%20Happy��
*/
class Solution {
public:
	void replaceSpace(char *str, int length) {
		char* tmp = new char[1024];
		char* cur = str;
		int i = 0;
		while (*cur){
			if (*cur == ' '){
				tmp[i++] = '%';
				tmp[i++] = '2';
				tmp[i++] = '0';
			}
			else{
				tmp[i++] = *cur;
			}
			++cur;
		}
		tmp[i] = '\0';
		strcpy(str, tmp);
	}
};

/*
��β��ͷ��ӡ����
����һ�������������β��ͷ��˳�򷵻�һ��ArrayList��
*/
  struct ListNode {
        int val;
        struct ListNode *next;
        ListNode(int x) :
              val(x), next(NULL) {
        }
  };

class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> res;
		ListNode* cur = head;
		while (cur){
			res.push_back(cur->val);
			cur = cur->next;
		}
		reverse(res.begin(), res.end());
		return res;
	}
};

/*
�ؽ�������
����ĳ��������ǰ���������������Ľ�������ؽ����ö����������������ǰ���������������Ľ���ж������ظ������֡�
��������ǰ���������{1,2,4,7,3,5,6,8}�������������{4,7,2,1,5,3,8,6}�����ؽ������������ء�
*/
/*
˼·:�ݹ� ����
*/
struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	TreeNode* built(vector<int>& pre, int ps, int pe, vector<int>& vin, int vs, int ve){
		if (ps>pe || vs>ve){ return NULL; }
		TreeNode* root = new TreeNode(pre[ps]); //������� �ȴ��쵱ǰͷ�ڵ�
		for (int i = vs; i <= ve; ++i){
			if (vin[i] == pre[ps]){
				//������������ҵ�����������Ľ�� ���з���
				root->left = built(pre, ps + 1, ps + i - vs, vin, vs, i - 1);
				root->right = built(pre, ps + i - vs + 1, pe, vin, i + 1, ve);
				break;
			}
		}
		return root;
	}
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		TreeNode* root = built(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
		return root;
	}
};