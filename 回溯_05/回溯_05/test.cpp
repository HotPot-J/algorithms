#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
/*
77. ���
������������ n �� k������ 1 ... n �����п��ܵ� k ��������ϡ�
ʾ��:
����: n = 4, k = 2
���:
[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]
*/
class Solution2 {
public:
	vector<vector<int>> res;
	vector<int> tmp;
	vector<vector<int>> combine(int n, int k) {
		dfs(1, n, k);
		return res;
	}
	void dfs(int begin, int n, int k){
		if (tmp.size() == k){
			//��������
			res.push_back(tmp);
			return;
		}
		for (int i = begin; i <= n; ++i){
			tmp.push_back(i);
			dfs(i + 1, n, k);
			tmp.pop_back();
		}
	}
};
//int main(){
//	Solution a;
//	a.combine(3, 2);
//	return 0;
//}

/*
357. �������λ����ͬ�����ָ���
����һ���Ǹ����� n�������λ���ֶ���ͬ������ x �ĸ��������� 0 �� x < 10^n ��
ʾ��:
����: 2
���: 91
����: ��ӦΪ��ȥ 11,22,33,44,55,66,77,88,99 �⣬�� [0,100) �����ڵ��������֡�
*/

//˼·����ϣ������ʱ�临�Ӷȹ��ߣ�
class Solution1 {
public:
	vector<int> map;
	int res = 0;
	bool a = true;
	int countNumbersWithUniqueDigits(int n) {
		int tmp = (int)pow((double)10, (double)n);
		for (int i = 0; i < tmp; ++i){
			map = { 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0};
			int flag = i;
			while (flag){
				int a = flag % 10;
				flag = flag / 10;
				++map[a];
			}
			for (int i = 0; i <= 9;++i){
				if (map[i]>1){
				 //˵�����ظ�
					a = false;
					break;
				}
			}
			if (a){
				++res;
			}
			a = true;
		}
		return res;
	}
};

/* 
   ���ö�̬�滮�����¹��ɣ�
   �����������
   һλ����0-9  10��
   2λ���� 9*9+һλ���Ŀ�����
   3λ����9*9*8+��λ���Ŀ�����+һλ���Ŀ�����
   
   ���ݴ˹��ɣ� ʹ�ö�̬�滮 
*/
class Solution {
public:
	int countNumbersWithUniqueDigits(int n) {
		if (n == 0){
			return 1;
		}
		if (n == 1){
			return 10;
		}
		int* dp = new int[n + 1];
		dp[1] = 10; dp[2] = 81;
		int sum = dp[1] + dp[2];
		for (int i = 3; i <= n; ++i){
			dp[i] = dp[i - 1] * (10 - i + 1);
			sum += dp[i];
		}
		return sum;
	}
};

int main(){
	Solution a;
	a.countNumbersWithUniqueDigits(0);
	return 0;
}