#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>

using namespace std;
/*
1219. 黄金矿工
你要开发一座金矿，地质勘测学家已经探明了这座金矿中的资源分布，并用大小为 m * n 的网格 grid 进行了标注。
每个单元格中的整数就表示这一单元格中的黄金数量；如果该单元格是空的，那么就是 0。
为了使收益最大化，矿工需要按以下规则来开采黄金：
每当矿工进入一个单元，就会收集该单元格中的所有黄金。
矿工每次可以从当前位置向上下左右四个方向走。
每个单元格只能被开采（进入）一次。
不得开采（进入）黄金数目为 0 的单元格。
矿工可以从网格中 任意一个 有黄金的单元格出发或者是停止。

示例 1：
输入：grid = [[0,6,0],[5,8,7],[0,9,0]]
输出：24
解释：
[[0,6,0],
[5,8,7],
[0,9,0]]
一种收集最多黄金的路线是：9 -> 8 -> 7。
示例 2：
输入：grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
输出：28
解释：
[[1,0,7],
[2,0,6],
[3,4,5],
[0,3,0],
[9,0,20]]
一种收集最多黄金的路线是：1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7。
提示：
1 <= grid.length, grid[i].length <= 15
0 <= grid[i][j] <= 100
最多 25 个单元格中有黄金。
*/
class Solution {
public:
	int getMaximumGold(vector<vector<int>>& grid) {
		int res = 0;
		int MaxRes = 0;
		for (int i = 0; i < grid.size(); ++i){
			for (int j = 0; j < grid[0].size(); ++j){
				//使grid每一个坐标都有可能成为起点
					dfs(grid, i, j,res,MaxRes);
			}
		}
		return MaxRes;
	}
	bool check(vector<vector<int>>& grid,int i,int j){
		//判断该路径是否可以走通
		//走通的条件：1.其未被开采过(数值 != -1) 2.含有黄金（数值 != 0） 3.在边界内 i>=0&&i<m j>=0&&j<n
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
		//当前路径可走
		int tmp = grid[i][j];//为了之后的回溯过程 要保存当前要挖的金子数值
		int cur = res + grid[i][j];//挖金子
		grid[i][j] = -1;//做标记代表挖过金子了
		MaxRes = cur > MaxRes ? cur : MaxRes;
		//走上
			dfs(grid, i - 1, j,cur,MaxRes);
		//走下
			dfs(grid, i + 1, j,cur, MaxRes);
		//走左
			dfs(grid, i, j - 1, cur, MaxRes);
		//走右
			dfs(grid, i, j + 1, cur, MaxRes);
		//回溯
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