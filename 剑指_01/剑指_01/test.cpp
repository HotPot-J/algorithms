#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
���ӣ�https://www.nowcoder.com/questionTerminal/57d85990ba5b440ab888fc72b0751bf8
��Դ��ţ����
[�����]������
�ȶ�ָ����157428ʱ�����ƣ�C/C++ 1�룬��������2��ռ����ƣ�C/C++ 64M����������128M
�㷨֪ʶ��Ƶ����
����һ������Ϊn�����ӣ�������Ӽ�����������m�Σ�m��n����������n>1����m>1��m<=n����ÿ�����ӵĳ��ȼ�Ϊk[1],...,k[m]������k[1]x...xk[m]���ܵ����˻��Ƕ��٣����磬�����ӵĳ�����8ʱ�����ǰ������ɳ��ȷֱ�Ϊ2��3��3�����Σ�
��ʱ�õ������˻���18��
��������:
����һ����n����������档��2 <= n <= 60��
�������:
����𰸡�
ʾ��1
����
8
���
18
*/

/*
˼·:��̬�͹滮�� dp[i] = max(dp[i],dp[i-j]*j)
*/

class Solution {
public:
	int cutRope(int number) {
		vector<int> dp;
		dp.resize(number + 1, 1);
		for (int i = 1; i <= number; ++i){
			for (int j = 1; j <= i; ++j){
				dp[i] = max(dp[i], dp[i - j] * j);
			}
		}
		return dp[number];
	}
};

/*
���ӣ�https://www.nowcoder.com/questionTerminal/6e5207314b5241fb83f2329e89fdecc8
��Դ��ţ����

[�����]�����˵��˶���Χ
�ȶ�ָ����360503ʱ�����ƣ�C/C++ 1�룬��������2��ռ����ƣ�C/C++ 32M����������64M
�㷨֪ʶ��Ƶ����
������һ��m�к�n�еķ���һ�������˴�����0,0�ĸ��ӿ�ʼ�ƶ���ÿһ��ֻ�������ң��ϣ����ĸ������ƶ�һ�񣬵��ǲ��ܽ�������������������λ֮�ʹ���k�ĸ��ӡ� ���磬��kΪ18ʱ���������ܹ����뷽��35,37������Ϊ3+5+3+7 = 18�����ǣ������ܽ��뷽��35,38����
��Ϊ3+5+3+8 = 19�����ʸû������ܹ��ﵽ���ٸ����ӣ�
*/

/*
˼·:dfs �ݹ�
*/
class Solution {
public:
	bool check(vector<vector<int>>& map, int threshold, int rows, int cols, int i, int j){
		//Խ��
		if (i<0 || i >= rows || j<0 || j >= cols)
			return false;
		//��������ֵ
		if (map[i][j] == -1) { return false; }
		else{
			int tmp = 0;
			while (i){ tmp += (i % 10); i /= 10; }
			while (j){ tmp += (j % 10); j /= 10; }
			if (tmp>threshold){ map[i][j] == -1; return false; }
		}
		return true;
	}
	void fun(vector<vector<int>>&map, int threshold, int rows, int cols, int i, int j, int& res){
		if (!check(map, threshold, rows, cols, i, j)){
			//����������
			return;
		}
		if (map[i][j] == 0){
			++res;
			map[i][j] = -1; //����ͳ�ƹ���
		}
		//�����������ҵ�Ѱ·����
		fun(map, threshold, rows, cols, i - 1, j, res);
		fun(map, threshold, rows, cols, i + 1, j, res);
		fun(map, threshold, rows, cols, i, j - 1, res);
		fun(map, threshold, rows, cols, i, j + 1, res);
	}
	int movingCount(int threshold, int rows, int cols)
	{
		vector<vector<int>> map(rows, vector<int>(cols, 0));
		int res = 0;
		fun(map, threshold, rows, cols, 0, 0, res);
		return res;
	}
};

