#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>

using namespace std;
/*
1219. �ƽ��
��Ҫ����һ����󣬵��ʿ���ѧ���Ѿ�̽������������е���Դ�ֲ������ô�СΪ m * n ������ grid �����˱�ע��
ÿ����Ԫ���е������ͱ�ʾ��һ��Ԫ���еĻƽ�����������õ�Ԫ���ǿյģ���ô���� 0��
Ϊ��ʹ������󻯣�����Ҫ�����¹��������ɻƽ�
ÿ���󹤽���һ����Ԫ���ͻ��ռ��õ�Ԫ���е����лƽ�
��ÿ�ο��Դӵ�ǰλ�������������ĸ������ߡ�
ÿ����Ԫ��ֻ�ܱ����ɣ����룩һ�Ρ�
���ÿ��ɣ����룩�ƽ���ĿΪ 0 �ĵ�Ԫ��
�󹤿��Դ������� ����һ�� �лƽ�ĵ�Ԫ�����������ֹͣ��

ʾ�� 1��
���룺grid = [[0,6,0],[5,8,7],[0,9,0]]
�����24
���ͣ�
[[0,6,0],
[5,8,7],
[0,9,0]]
һ���ռ����ƽ��·���ǣ�9 -> 8 -> 7��
ʾ�� 2��
���룺grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
�����28
���ͣ�
[[1,0,7],
[2,0,6],
[3,4,5],
[0,3,0],
[9,0,20]]
һ���ռ����ƽ��·���ǣ�1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7��
��ʾ��
1 <= grid.length, grid[i].length <= 15
0 <= grid[i][j] <= 100
��� 25 ����Ԫ�����лƽ�
*/
class Solution {
public:
	int getMaximumGold(vector<vector<int>>& grid) {
		int res = 0;
		int MaxRes = 0;
		for (int i = 0; i < grid.size(); ++i){
			for (int j = 0; j < grid[0].size(); ++j){
				//ʹgridÿһ�����궼�п��ܳ�Ϊ���
					dfs(grid, i, j,res,MaxRes);
			}
		}
		return MaxRes;
	}
	bool check(vector<vector<int>>& grid,int i,int j){
		//�жϸ�·���Ƿ������ͨ
		//��ͨ��������1.��δ�����ɹ�(��ֵ != -1) 2.���лƽ���ֵ != 0�� 3.�ڱ߽��� i>=0&&i<m j>=0&&j<n
		if (i<0||j<0||i>=grid.size()||j>=grid[0].size()){
			return false;
		}
		return true;
	}
	void dfs(vector<vector<int>>& grid,int i,int j,int res,int& MaxRes){
		if (!check(grid, i, j)){
			return;
		}
		if (grid[i][j] <= 0){
			return;
		}
		//��ǰ·������
		int tmp = grid[i][j];//Ϊ��֮��Ļ��ݹ��� Ҫ���浱ǰҪ�ڵĽ�����ֵ
		int cur = res + grid[i][j];//�ڽ���
		grid[i][j] = -1;//����Ǵ����ڹ�������
		MaxRes = cur > MaxRes ? cur : MaxRes;
		//����
			dfs(grid, i - 1, j,cur,MaxRes);
		//����
			dfs(grid, i + 1, j,cur, MaxRes);
		//����
			dfs(grid, i, j - 1, cur, MaxRes);
		//����
			dfs(grid, i, j + 1, cur, MaxRes);
		//����
			grid[i][j] = tmp;
	}
};
int main(){
	Solution a;
	vector<vector<int>> t;
	t.resize(3);
	for (int i = 0; i < 3; ++i){
		t[i].resize(3);
	}
	t = { { 0, 6, 0 }, { 5, 8, 7 }, { 0, 9, 0 } };
	a.getMaximumGold(t);
	return 0;
}