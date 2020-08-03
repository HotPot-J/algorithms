#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
#include<string>
using namespace std;
/*
�Ѷ�������ӡ�ɶ���
���ϵ��°����ӡ��������ͬһ����������������ÿһ�����һ�С�
*/
/*
˼·���������Ĳ������
����������� �ö��иվ�����  ���ǵ�Ҫһ��һ����� for(int i = 0;i<q.size()(��ǰ��ĳ���);++i)��
*/
class Solution {
public:
	vector<vector<int> > Print(TreeNode* pRoot) {
		vector<vector<int>> res;
		if (pRoot == NULL){ return res; }
		queue<TreeNode*> q;
		int i = 0;
		TreeNode* cur = pRoot;
		q.push(cur);
		while (!q.empty()){
			//�����в�Ϊ��ʱ���в������
			int len = q.size();
			vector<int> tmp;
			for (int i = 0; i<len; ++i){
				if (q.front() != NULL){
					tmp.push_back(q.front()->val);
					//����һ��˳�����
					q.push(q.front()->left);
					q.push(q.front()->right);
				}
				//��ͷ����
				q.pop();
			}
			if (!tmp.empty()){
				res.push_back(tmp);
			}
		}
		return res;
	}
};


/*
�����������л��뷴���л�
��ʵ�������������ֱ��������л��ͷ����л�������

�����������л���ָ����һ�ö���������ĳ�ֱ�����ʽ�Ľ����ĳ�ָ�ʽ����Ϊ�ַ������Ӷ�ʹ���ڴ��н��������Ķ�����
���Գ־ñ��档���л����Ի����������򡢺��򡢲���Ķ�����������ʽ�������޸ģ����л��Ľ����һ���ַ���������
��ʱͨ�� ĳ�ַ��ű�ʾ�սڵ㣨#������ �� ��ʾһ�����ֵ�Ľ�����value!����

�������ķ����л���ָ������ĳ�ֱ���˳��õ������л��ַ������str���ع���������

���磬���ǿ��԰�һ��ֻ�и��ڵ�Ϊ1�Ķ��������л�Ϊ"1,"��Ȼ��ͨ���Լ��ĺ��������������������
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
˼·:
1.���л���������� ʹ�ö������ ������ĳһ��ʱ������һ��Ľ����ӣ���ʹΪ��ҲҪ��� ��Ϊ�����л�ʱ��Ҫ��Щ�յ�λ�ã�
2.�����л���������� ����һ����ǿգ�����ӣ�ֻ�зǿղ���Ϊ�丳ֵleft/right 
3.����Ӻܶ� ������Ҫ�жϿո� "12 3 # 34 4"  ����Ҫ�õ�itoa ��stoa����
4.����������� �ö��иվ�����  ���ǵ�Ҫһ��һ����� for(int i = 0;i<q.size()(��ǰ��ĳ���);++i)��
*/
class Solution {
public:
	char* Serialize(TreeNode *root) {
		if (root == NULL){ return NULL; }
		queue<TreeNode*> q;
		string res;
		int i = 0;
		TreeNode* cur = root;
		q.push(cur);
		while (!q.empty()){
			//�����в�Ϊ��ʱ���в������
			int len = q.size();
			for (int i = 0; i<len; ++i){
				if (q.front() == NULL){
					res += "# ";
				}
				else{
					res += to_string(q.front()->val) + ' '; //���л����
					//����һ��˳�����
					q.push(q.front()->left);
					q.push(q.front()->right);
				}
				//��ͷ����
				q.pop();
			}
		}
		char* tmp = strdup(res.c_str());
		return tmp;
	}
	//���򴴽�������
	TreeNode* Deserialize(char *str) {
		if (str == NULL){ return NULL; }
		queue<TreeNode*> q;
		int len = strlen(str);
		int i = 0;
		TreeNode* root = createNode(str, i, len);
		q.push(root);
		while (!q.empty()){
			int size = q.size();
			for (int j = 0; j<size; ++j){
				//�������ҽ��
				q.front()->left = createNode(str, i, len);
				q.front()->right = createNode(str, i, len);
				//�ǿռ������ Ϊ����һ��Ĵ���
				if (q.front()->left){ q.push(q.front()->left); }
				if (q.front()->right){ q.push(q.front()->right); }
				q.pop();
			}
		}
		return root;
	}
	//����һ����㲢����
	TreeNode* createNode(char* str, int& i, int& len){
		if (str == NULL){ return NULL; }
		string tmp;
		while (i<len&&str[i] != ' '){
			if (str[i] == '#'){
				i += 2; //����#��һ���ո�
				return NULL;
			}
			tmp += str[i];
			++i;
		}
		//����һ���ո� ������һ����Ч�ַ�
		++i;
		if (!tmp.empty()){
			TreeNode* Node = new TreeNode(stoi(tmp));
			return Node;
		}
		return NULL;
	}
};