#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;


/*
1、矩阵中的路径
题目描述
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，
每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入
该格子。 例如 \begin{bmatrix} a & b & c &e \\ s & f & c & s \\ a & d & e& e\\ \end{bmatrix}\quad
​矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第
二个格子之后，路径不能再次进入该格子。
*/

/*
思路：1.回溯
2.记录当前路径中的字符
3.当越界 则返回false
4.走过的路不能再走 将当前路径置'0'即路径为0不可走 之后再回溯即可
*/
class Solution1 {
public:
	//检查是否可行
	bool check(char* matrix, int rows, int cols, int i, int j, char* str, int k){
		if (i<0 || i >= rows || j<0 || j >= cols || matrix[i*cols + j] == '0' || matrix[i*cols + j] != str[k]){
			return false;
		}
		return true;
	}
	//寻找路径
	bool dfs(char* matrix, int rows, int cols, char* str, int i, int j, int k){
		if (check(matrix, rows, cols, i, j, str, k) == false){
			return false;
		}
		if (k == strlen(str) - 1){
			return true;
		}
		char tmp = matrix[i*cols + j];
		matrix[i*cols + j] = '0';
		if (
			dfs(matrix, rows, cols, str, i - 1, j, k + 1) ||
			dfs(matrix, rows, cols, str, i + 1, j, k + 1) ||
			dfs(matrix, rows, cols, str, i, j - 1, k + 1) ||
			dfs(matrix, rows, cols, str, i, j + 1, k + 1)
			){
			return true;
		}
		matrix[i*cols + j] = tmp;
		return false;
	}
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		for (int i = 0; i<rows; ++i){
			for (int j = 0; j<cols; ++j){
				if (matrix[i*cols + j] == str[0]){
					//当起始位置等于str[0]再寻找
					if (dfs(matrix, rows, cols, str, i, j, 0)){
						return true;
					}
				}
			}
		}
		return false;
	}
};

/*
2.链接：https://www.nowcoder.com/questionTerminal/1624bc35a45c42c0bc17d17fa0cba788
来源：牛客网

[编程题]滑动窗口的最大值
热度指数：380852时间限制：C/C++ 1秒，其他语言2秒空间限制：C/C++ 32M，其他语言64M
算法知识视频讲解
给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。
窗口大于数组长度的时候，返回当前数组的最大值
*/
#include<vector>
#include<deque>
/*
思路:定义一个双端队列最为win 维护队头为最大值
	每次判断即将出队的是否为对头值，是pop_front 
	每次将即将入窗的，将win中比其小的都从pop_back 最后将其push_back (这样可以保证是降序的一旦遇到比自己大的直接push_back即可不用继续去前面对比)
	（重点:只pop_back比即将入窗小的，相等的不删除）
*/
class Solution {
public:
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		vector<int> res;
		if (size == 0 || size>num.size()){ return res; } //窗口为0或比数组大都不行
		deque<int> win;
		//先把第一个窗口填满
		for (int i = 0; i<size; ++i){
			if (win.empty()){ win.push_back(num[i]); }
			else{
				//从队尾开始将比其小的都删除
				while (!win.empty() && win.back()<num[i]){
					win.pop_back();
				}
				win.push_back(num[i]);
			}
		}
		res.push_back(win.front()); //将第一个窗口的最大值保存
		//开始滑动~~~~
		int len = num.size();
		for (int i = 0; i<len; ++i){
			int j = i + size;//即将进窗的下标
			if (j >= len){ break; } //超出数组
			if (num[i] == win.front()){
				//如果当前恰好是最大值出窗
				win.pop_front();
			}
			//从队尾开始将比其小的都删除
			while (!win.empty() && win.back()<num[j]){
				win.pop_back();
			}
			win.push_back(num[j]);
			res.push_back(win.front()); //将每个窗口最大值保存
		}
		return res;
	}
};