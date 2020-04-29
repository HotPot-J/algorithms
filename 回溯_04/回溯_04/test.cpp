#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

/*
39. ����ܺ�
����һ�����ظ�Ԫ�ص����� candidates ��һ��Ŀ���� target ���ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�
candidates �е����ֿ����������ظ���ѡȡ��
˵����
�������֣����� target��������������
�⼯���ܰ����ظ�����ϡ�
ʾ�� 1:
����: candidates = [2,3,6,7], target = 7,
����⼯Ϊ:
[
[7],
[2,2,3]
]
ʾ�� 2:
����: candidates = [2,3,5], target = 8,
����⼯Ϊ:
[
[2,2,2,2],
[2,3,3],
[3,5]
]
*/
//˼�룺���� �����������
class Solution {
public:
	//����ȫ�ֱ��� 
	vector<vector<int>> res;
	vector<int> path;
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());//���� ����ǰ�����Ѿ����ʺϼ���path ��ô���������ָ������� ���С���֦��
		dfs(0, target, candidates);
		return res;
	}
	void dfs(int begin,int target,vector<int>& candidates){
		//beginΪ��������������±�  
		if (target == 0){
			//�ҵ����н�
			res.push_back(path);
			return;
		}
		for (size_t i = begin; i < candidates.size(); ++i){
		  //ʹ�����������ѭ�������ȥ�أ���ȷ� �����꺬��1�����п��н� �Ͳ���1�� ����ȥ����������һ�����ֵ�ȫ�����н⣩
			if (target - candidates[i] < 0){
				//���������� "��֦" ��ߵ�����Ҳ�����ж��� �˳�ѭ�����л���
				break;
			}
			path.push_back(candidates[i]);
			dfs(i, target - candidates[i], candidates);
			path.pop_back();
		}
	}
};

//int main(){
//	vector<int> a = { 2,3,6,7 };
//	Solution b;
//	b.combinationSum(a, 7);
//	return 0;
//}

/*
40. ����ܺ� II
����һ������ candidates ��һ��Ŀ���� target ���ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�
candidates �е�ÿ��������ÿ�������ֻ��ʹ��һ�Ρ�
˵����
�������֣�����Ŀ������������������
�⼯���ܰ����ظ�����ϡ�
ʾ�� 1:
����: candidates = [10,1,2,7,6,1,5], target = 8,
����⼯Ϊ:
[
[1, 7],
[1, 2, 5],
[2, 6],
[1, 1, 6]
]
ʾ�� 2:
����: candidates = [2,5,2,1,2], target = 5,
����⼯Ϊ:
[
[1,2,2],
[5]
]
*/
class Solution {
public:
	vector<vector<int>> res;
	vector<int> path;
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end()); 
		dfs(0,target,candidates);
		return res;
	}

	void dfs(int begin,int target,vector<int>& candidates){
		if (target == 0){
			//��������
			res.push_back(path);
			return;
		}
		for (int i = begin; i < candidates.size(); ++i){
			if (target - candidates[i] < 0){
				break;
			}
			if (i>begin&&candidates[i] == candidates[i - 1]){
				//��ͬ��μ�֦ ���˵��ǰ���ǰһ����� 
				/*
				���� 1 1 2 3 4����
				�±�Ϊ0��ʼʱ  ���ѡ��Ϊ1��2��3��4
				�±�Ϊ1��ʼʱ  ���ѡ��Ϊ2��3��4    �����±�Ϊ1�Ŀ��н��һ�����±�Ϊ0������г��ֹ� ��Ҫ���м�֦
				*/
				continue;
			}
			path.push_back(candidates[i]);
			dfs(i+1, target - candidates[i], candidates); //�������һ��Ϊi+1������ÿ������ֻ��ʹ��һ��
			path.pop_back();
		}
	}
};
int main(){
	vector<int> a = { 10, 1, 2, 7, 6, 1, 5 };
	Solution b;
	b.combinationSum2(a,8);
	return 0;
}

/*
216. ����ܺ� III
�ҳ��������֮��Ϊ n �� k ��������ϡ������ֻ������ 1 - 9 ��������������ÿ������в������ظ������֡�
˵����
�������ֶ�����������
�⼯���ܰ����ظ�����ϡ�
ʾ�� 1:
����: k = 3, n = 7
���: [[1,2,4]]
ʾ�� 2:
����: k = 3, n = 9
���: [[1,2,6], [1,3,5], [2,3,4]]
*/
class Solution {
	vector<vector<int>> res;
	vector<int> tmp;
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		dfs(1, k, n);
		return res;
	}
	void dfs(int begin, int k, int n){
		if (n == 0 && tmp.size() == k){
			//�����ո�����
			res.push_back(tmp);
			return;
		}
		for (int i = begin; i < 10; ++i){
			if (n - i < 0){
				//��֦
				break;
			}
			if (tmp.size() >= k){
				//��ǰtmpû�ﵽ�ո����� ���ҳ߶ȼ������Ѿ�����k ��֦
				break;
			}
			tmp.push_back(i);
			dfs(i + 1, k, n-i);
			tmp.pop_back();
		}
	}
};
int main(){
	Solution b;
	b.combinationSum3(3, 7);
	return 0;
}
