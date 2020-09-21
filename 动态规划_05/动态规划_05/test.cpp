#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
1372. �������е������·��
����һ���� root Ϊ���Ķ��������������еĽ���·���������£�

ѡ��������� ���� �ڵ��һ������������ң���
���ǰ������Ϊ�ң���ô�ƶ�����ǰ�ڵ�ĵ����ӽڵ㣬�����ƶ����������ӽڵ㡣
�ı�ǰ����������һ����ұ���
�ظ��ڶ����͵�������ֱ�����������޷������ƶ���
����·���ĳ��ȶ���Ϊ�����ʹ��Ľڵ���Ŀ - 1�������ڵ��·������Ϊ 0 ����

���㷵�ظ�������� ����·�� �ĳ��ȡ�
*/


/*
˼·��dfs ������ȱ���
   �Ӹ���ʼ��Ѱ�����������������·��
             ��Ѱ�����������������·��
*/
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	int res;
	//flagΪtrue����flagΪfalse����
	void dfs(TreeNode* cur, bool flag, int len){
		if (cur == NULL) return;
		res = max(res, len);
		if (flag){
			dfs(cur->left, false, len + 1); //����  false������һ������  
			//����ߵ����˵����ǰcurû�����㣬ֻ�ܴ���������ȥѰ�ң��Ե�ǰ��㿪ʼ�������·��
			//���Խ�len��Ϊ1 ��0+1��
			dfs(cur->right, true, 1);//���� true������һ������  
		}
		else{
			dfs(cur->right, true, len + 1);
			dfs(cur->left, false, 1);
		}
	}
	int longestZigZag(TreeNode* root) {
		if (root == NULL) return 0;
		res = 0;
		dfs(root, true, 0);
		dfs(root, false, 0);
		return res;
	}
};

/*
978. �����������
�� A �������� A[i], A[i+1], ..., A[j] ������������ʱ�����ǳ���Ϊ���������飺
�� i <= k < j���� k Ϊ����ʱ�� A[k] > A[k+1]���ҵ� k Ϊż��ʱ��A[k] < A[k+1]��
�� �� i <= k < j���� k Ϊż��ʱ��A[k] > A[k+1] ���ҵ� k Ϊ����ʱ�� A[k] < A[k+1]��
Ҳ����˵������ȽϷ������������е�ÿ������Ԫ�ض�֮�䷭ת����������������������顣
���� A ���������������ĳ��ȡ�
ʾ�� 1��
���룺[9,4,2,10,7,8,8,1,9]
�����5
���ͣ�(A[1] > A[2] < A[3] > A[4] < A[5])
ʾ�� 2��
���룺[4,8,12,16]
�����2
ʾ�� 3��
���룺[100]
�����1
*/
class Solution1 {
public:
	int maxTurbulenceSize(vector<int>& A) {
		int len = A.size();
		if (len <= 1) return len;
		vector<int> up(len + 1, 1);
		vector<int> down(len + 1, 1);
		int res = 0;
		for (int i = 2; i <= len; ++i){
			if (A[i - 2] > A[i - 1]){
				//�½�
				up[i] = down[i - 1] + 1;
				down[i] = 1;
			}
			else if (A[i - 2] < A[i - 1]){
				//����
				up[i] = 1;
				down[i] = up[i - 1] + 1;
			}
			else{
				up[i] = 1;
				down[i] = 1;
			}
			res = max(res, up[i]);
			res = max(res, down[i]);
		}
		return res;
	}
};

int main(){
	vector<int> arr = { 9, 4, 2, 10, 7, 8, 8, 1, 9 };
	Solution1 a;
	a.maxTurbulenceSize(arr);
	return 0;
}
class Solution {
public:
	/**
	*
	* @param num int���� �Ǹ����� num
	* @return int����vector
	*/
	int fun(int a){
		int res = 0;
		for (int i = 0; i < 32; ++i){
			if ((a >> i) & 1) ++res;
		}
		return res;
	}
	vector<int> countBits(int num) {
		vector<int> res;
		for (int i = 0; i <= num; ++i){
			res.push_back(fun(i));
		}
		return res;
	}
};
//class Solution {
//public:
//	/**
//	* �ϲ�����
//	* @param arrayA int����һά���� ����A
//	* @param arrayALen int arrayA���鳤��
//	* @param arrayB int����һά���� ����B
//	* @param arrayBLen int arrayB���鳤��
//	* @return int����vector
//	*/
//	vector<int> mergerArrays(int* arrayA, int arrayALen, int* arrayB, int arrayBLen) {
//		// write code here
//		vector<int> res;
//		if (arrayA == NULL || arrayB == NULL) return res;
//		unordered_map<int, bool> mapa;
//		for (int i = 0; i < arrayALen; ++i){
//			mapa[arrayA[i]] = true;
//		}
//		for (int i = 0; i < arrayBLen; ++i){
//			if (mapa[arrayB[i]] == true){
//				res.push_back(arrayB[i]);
//			}
//		}
//		sort(res.begin(), res.end());
//	}
//};
int main(){
	Solution a;
	a.countBits(5);

	return 0;
}