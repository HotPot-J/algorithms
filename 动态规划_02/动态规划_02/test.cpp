#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
/*
一、unique-paths
链接：https://www.nowcoder.com/questionTerminal/166eaff8439d4cd898e3ba933fbc6358
来源：牛客网
一个机器人在m×n大小的地图的左上角（起点，下图中的标记“start"的位置）。
机器人每次向下或向右移动。机器人要到达地图的右下角。（终点，下图中的标记“Finish"的位置）。
可以有多少种不同的路径从起点走到终点？
*/

/*
思路一：回溯 dfs
（无法AC：时间复杂度过高）
*/
class Solution {
public:
	int res = 0;
	bool check(int m,int n,int i,int j){
		if (i >= m ||i<0|| j >= n||j<0){
			return false;
		}
		return true;
	}
	void dfs(int m,int n,int i,int j){
		if (i == m - 1 && j == n - 1){
			++res;
			return;
		}
		//下
		dfs(m, n, i + 1, j);
		dfs(m, n, i, j + 1);
		
	}
	int uniquePaths(int m, int n) {
		dfs(m, n, 0, 0);
		return res;
	}
};

/*
思路二：动态规划
f(i,j):代表走到（i,j）点有多少种路径
f(0,0) = 1;
f(0,1) = 1;
f(1,0) = 1;
f(1,1) = 2;
由此可得状态转移方程为：
	f(i,j) = f(i-1,j)+f(i,j-1)
	初始状态为：f(0,0) = 1
*/

class Solution1 {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp;
		dp.resize(m);
		for (int i = 0; i < m; ++i){
			dp[i].resize(n, 0);
		}
		for (int i = 0; i < m; ++i){
			for (int j = 0; j < n; ++j){
				if (i == 0 && j == 0){
					//初始状态
					dp[i][j] = 1;
				}
				else if (i == 0){
					//第一行只能向右
					dp[i][j] = dp[i][j - 1];
				}
				else if (j == 0){
					//第一列只能向下
					dp[i][j] = dp[i - 1][j];
				}
				else{
					//普通情况（下/右）
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		return dp[m - 1][n - 1];
	}
};

//int main(){
//	Solution1 a;
//	a.uniquePaths(1, 2);
//	return 0;
//}

/*
二、unique-paths-ii
链接：https://www.nowcoder.com/questionTerminal/3cdf08dd4e974260921b712f0a5c8752
来源：牛客网
热度指数：14177时间限制：C/C++ 1秒，其他语言2秒空间限制：C/C++ 32M，其他语言64M
算法知识视频讲解
继续思考题目"Unique Paths":
如果在图中加入了一些障碍，有多少不同的路径？
分别用0和1代表空区域和障碍
例如
下图表示有一个障碍在3*3的图中央。
[
[0,0,0],
[0,1,0],
[0,0,0]
]
有2条不同的路径
备注：m和n不超过100.
*/

/*
思路:动态规划
f(i,j):走到(i,j)位置的路径种数
状态转移方程：
f(i,j) = f(i-1,j)+f(i,j-1)
初始状态：
例子：
0 0 0 1 0
1
0
0
想要走到(0,4)的位置需要保证其之前的路径都没有障碍 即： map[0][4]==0&&map[0][i] i<4 
想要走到(3,0)的位置需要保证其之前的路径都没有障碍 即： map[3][0]==0&&map[i][0] i<3
总结初始化状态需要满足的条件:
	i = 0: map[0][i]==0 && map[0][j]==0 &&(j<i)
	i = 0: map[i][0]==0 && map[j][0]==0 &&(j<i)
*/
class Solution3{
public:
	int uniquePathsWithObstacles(vector<vector<int> >& obstacleGrid) {
		if (obstacleGrid.empty()||obstacleGrid[0][0]==1){ return 0; }
		int row = obstacleGrid.size(), col = obstacleGrid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
	/*	dp.resize(row);
		for (int i = 0; i < row; ++i){
			dp[i].resize(col, 0);
		}*/
		//初始化状态
		for (int i = 0; i < col; ++i){
			//第一行
			if (obstacleGrid[0][i] == 0) {
				dp[0][i] = 1;
			}
			else break;
		}
		for (int i = 0; i < row; ++i){
			//第一列
			if (obstacleGrid[i - 1][0] == 0){
				dp[i][0] = 1;
			}
			else break;
		}
		for (int i = 1; i < row; ++i){
			for (int j = 1; j < col; ++j){
				if (obstacleGrid[i][j] == 0){
					//当前点并非路障
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		return  dp[row - 1][col - 1];
	}
};

/*
三、带权值的最小路径和
链接：https://www.nowcoder.com/questionTerminal/23462ed010024fcabb7dbd3df57c715e
来源：牛客网
给定一个由非负整数填充的m x n的二维数组，现在要从二维数组的左上角走到右下角，请找出路径上的所有数字之和最小的路径。
注意：你每次只能向下或向右移动。
示例1
输入
[[1,2],[5,6],[1,1]]
输出
8
*/
/*
思路:
状态 f(i,j)：表示（i,j）当前点的权值和
由于只能向下移动(初始状态)：
	i = 0  f(0,j) = f(0,j-1)+arr[0,j] 
	j = 0  f(i,0) = f(i-1,0)+arr[i,0]
普通状态:
	f(i,j) = min(f(i-1,j),f(i,j-1))+arr[i,j]
*/

class Solution12{
public:
	int minPathSum(vector<vector<int> >& grid) {
		if (grid.empty()){ return 0; }
		int row = grid.size(), col = grid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		//初始状态
		dp[0][0] = grid[0][0];
		for (int i = 1; i < col; ++i){
			//第一行
			dp[0][i] = dp[0][i - 1] + grid[0][i];
		}
		for (int i = 1; i < row; ++i){
			dp[i][0] = dp[i - 1][0] + grid[i][0];
		}
		for (int i = 1; i < row; ++i){
			for (int j = 1; j < col; ++j){
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
			}
		}
		return dp[row - 1][col - 1];
	}
};

/*
四、背包问题
有N件物品和一个容量为V的背包。第i件物品的价值是C[i]，重量是W[i]。求解将哪些物品装入背包可使价值总和最大。
链接：https://www.nowcoder.com/questionTerminal/3ee42c9155c340588729995561ace594
输入描述:
输入第一行数 N V (1 <=N <=500) (1<= V <= 10000)
输入 N行 两个数字 代表 C W (1 <= C <= 50000, 1 <= W <=10000)
输出描述:
输出最大价值
例:
5 10
8 6
10 4
4 2
5 4
5 3
输出
19
*/

/*
思路:
	目标: 当包大小为V时，从n个商品中做选择使得商品总价值最大
	状态：该问题影响最终解因素有两个：物品价值c和物品的大小w
	f(i,j)表示，在考虑第i个商品时，当包大小为j时的最大价值
	讨论：
		如果放入当前商品：
			1.w[i]<=j 可以放进去（拿出之前一部分商品让当前商品放进去）
			2.w[i]>j  不能放进去
	所以：                           不放        放（意味着可能拿出之前的部分商品）
	   当w[i]<=j时 ：f(i,j) = max( f(i-1,j) , f(i-1,j-w[i])+c[i] ) (从放（可能需要取出之前的部分商品，再加上当前商品价值）和不放中选择一个价值较大的)
	   当w[i]>j时  ：f(i,j) = f(i-1,j)   （只有不放的情况）
		
*/

//int main(){
//	int N = 0, V = 0;
//	while (cin >> N >> V){
//		vector<vector<int>> store(N + 1, vector<int>(2, 0));
//		int c = 0, w = 0;//价值和重量
//		for (int i = 1; i <= N; ++i){
//			cin >> c >> w;
//			store[i][0] = c; //价值
//			store[i][1] = w; //重量
//		}
//		vector<vector<int>> dp(N + 1, vector<int>(V + 1, 0));
//		//i代表第几个商品 j代表当前重量
//		for (int i = 1; i <= N; ++i){
//			for (int j = 1; j <= V; ++j){
//				if (store[i][1] <= j){
//					//当前商品质量可以放进背包
//					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - store[i][1]] + store[i][0]);
//				}
//				else{
//					//当前商品质量不可以放进背包
//					dp[i][j] = dp[i - 1][j];
//				}
//			}
//		}
//		cout << dp[N][V] << endl;
//	}
//	return 0;
//}

/*
五、palindrome-partitioning-ii 
  出一个字符串s，分割s使得分割出的每一个子串都是回文串
  计算将字符串s分割成回文分割结果的最小切割数
  例如:给定字符串s="aab",
  返回1，因为回文分割结果["aa","b"]是切割一次生成的。
*/

/*
(注意：牛客上使用strsub函数切割的部分字符串，不能将其引用传递给其他函数)
思路:
	f(i):当前位置切开，前i个字符是否能构成回文串
	例子: aaba
	f(0): |aaba 0
	f(1)  a|aba  a是回文 1
	f(2)  f(1)|a|ba ： 2   aa|ba ：1   min(2,1) = 1
	f(3)  利用f(1)的结果 a|ab|a（不构成回文）   f(2)|b|a 构成回文：f(2)+1 = 2
	f(4)  f(1)|aba:1   f(2)|ba|（不构成回文）   f(3)|b|a| f(3)+1 = 3   min(1,3) = 1
递推公式:
	f(i) = (j<i)&&f(j)&&[j+1,i]+1)
*/
class Solution100{
public:
	bool isPalindrome(string s){
		string tmp = s;
		reverse(tmp.begin(), tmp.end());
		if (strcmp(tmp.c_str(), s.c_str()) == 0){
			return true;
		}
		return false;
	}
	int minCut(string s) {
		if (s.empty()){ return 0; }
		int len = s.size();
		vector<int>dp(len, 0);
		for (int i = 0; i < len; ++i){
			if (isPalindrome(s.substr(0, i + 1))){
				//如果整体就是一个回文串就不用切割
				dp[i] = 0;
			}
			else{
				//整体不是就需要用到之前的状态
				int min = INT_MAX;
				for (int j = i - 1; j >= 0; --j){
					if (isPalindrome(s.substr(j + 1, i - j))){
						//[j+1,i]是一个回文串，维护min
						if (dp[j] + 1 < min){
							min = dp[j] + 1;
						}
					}
				}
				dp[i] = min;
			}
		}
		return dp[len - 1];
	}
};

//int main(){
//	string s("aaba");
//	Solution100 a;
//	a.minCut(s);
//	return 0;
//}

/*
aaba
由于上题时间复杂度较高，我们可以将每个区间是否为回文串的状态保留下来，进行优化
问题:区间[i,j]是否为回文串
状态：f(i,j)：区间[i,j]是否为回文串
   通常判断一个字符串是否为回文，采用碰撞指针的方法，即
   f(i,j)是否为回文，只需要满足：f(i+1,j-1)为回文&&s[i]==[j]
   所以状态转移方程为：
   f(i,j):f(i-1,j-1)&&s[i]==s[j]
  初始状态：
   如果是两个字符：f(i,j):s[i]==s[j]
   单个字符：f(i,i) ：true
*/

vector<vector<bool>> isPal(string& s){
	int len = s.size();
	vector<vector<bool>> pMat(len, vector<bool>(len, false));
	for (int i = len-1; i >=0 ; ++i){
		for (int j = i; j < len; ++j){
			if (i == j){
				pMat[i][j] = true; //单字符区间
			}
			else if (i + 1 == j){
				pMat[i][j] = s[i] == s[j];//双字符区间
			}
			else{
				pMat[i][j] = pMat[i + 1][j - 1] && (s[i] == s[j]);
			}
		}
	}
	return pMat;
}

