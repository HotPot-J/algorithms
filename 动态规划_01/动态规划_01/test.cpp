#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using namespace std;
/*
动态规划：
	特点: 1.把原来的问题分解成了几个相似的子问题
	      2.所有子问题都只需要解决一次
		  3.存储子问题的解
	本质:是对问题状态的定义和状态转移方程的定义（状态以及状态之间的递推关系）
		1.状态定义
		2.状态间的转移方程定义
		3.状态的初始化
		4.返回结果
	状态定义的要求：定义状态一定要形成递推关系。
适用场景:最大值/最小值，可不可行，是不是，方案个数
*/

/*
一、变态跳台阶
	一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。
	求该青蛙跳上一个n级的台阶总共有多少种跳法。
*/
/*
思路：动态规划
	1个台阶：1
	2个台阶：（1，1）（2）
	3个台阶：（1，1，1）（1，2）（2，1）（3）
	4个台阶：（1，1，1，1）（1，2，1）（2，1，1）（2，2）（1，1，2）（3，1）（1，3）（4）
	f(n) = f(n-1)+f(n-2)+...+f(0)
	f(n-1) = f(n-2)+...+f(0)
	可得:f(n) = f(n-1)+f(n-1) = 2*f(n-1)
*/

//递归版
class Solution {
public:
	int jumpFloorII(int number) {
		if (number == 0){ return 0; }
		if ( number == 1){ return 1; }
		return 2 * jumpFloorII(number - 1);
	}
};

//动态规划版
class Solution1 {
public:
	int jumpFloorII(int number) {
		if (number == 0){ return 0; }
		int ret = 1;
		for (int i = 2; i <= number; ++i){
			//ret *= 2;
			ret  = ret << 1;
		}
		return ret;
	}
};

/*
变形：
	如果每次只能跳1或2阶台阶，而不能跳n阶，该如何求解?
*/
/*
思路：
	1：1
	2：（1,1）(2)
	3:(1,1,1)(2,1)(1,2)
	4:(1,1,1,1)(2,1,1)(2,2)(1,2,1)(1,1,2)
	在n的下一个台阶我可以选择跳1步到n，n的下两个台阶我可以选择跳两个台阶 所以可得递推公式：
	f(n) = f(n-1)+f(n-2)
    其实就是一个斐波那契数列
*/

/*
矩形覆盖：
	我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无
	重叠地覆盖一个2*n的大矩形，总共有多少种方法？
    比如n=3时，2*3的矩形块有3种覆盖方法：
*/

/*
思路: （见图1）
   f(i)表示用i个2*1的小矩形覆盖2*i的大矩形，分为横着放和竖着放两种情况:
   第一个竖着放:   矩形面积变为2*(i-1)  此时f(i-1)表示2*(i-1)个2*1的小矩形覆盖  
   第一个横着放:   当横着放，该对矩形对面也只能横着放，所以面积变为2*(i-2) 
			      此时f(i-2)表示2*(i-2)个2*1的小矩形覆盖
  可得递推公式：
   f(i) = f(i-1)+f(i-2)  
   是一个斐波那契数列（主要理解求递推公式的思想，就不做实现了）
*/


/*
三、连续子数组最大和
	{6,-3,-2,7,-15,1,2,2}

思路:
	假设一（错误）:状态f(i):表示前i个元素组成的数组，其最大的连续子序列和
	那么状态转移方程为:f(i)=f(i-1)  
	但是题目要求是连续子序列最大和，如果f(i-1)中不包含第i-1个元素，则不能满足
	连续的条件
	f(1)= (f(0)=6 
	f(2)= (f(1)=6
	f(3)= (f(2)=6
	...
	由此可见，f(i-1)并不包含第i-1个元素，所以不满足题意
	以arr[i]结尾的连续子序列，要么包含第arr[i-1]，要么该序列只包含arr[i]一个元素才构成连续
	假设二（正确）：状态f(i)表示以第i个元素结尾的最大连续子序列和(这次加上第i个元素，保证其连续性)
    1.包含arr[i-1]:那么状态转移方程为：f(i) = f(i-1)+arr[i]
	2.不包含arr[i-1]:可是如果当前的arr[i]本身大于f(i-1)+arr[i],则以当前arr[i]结尾的最大子序列和应该是arr[i]本身
	所以最终：f(i) = max(f(i-1)+arr[i],arr[i])
	3.初始状态：max = arr[0]
	4.返回值：max(f(i))
	以第0个元素结尾：f(0) = 6
	以第1个元素结尾：f(1) = max(6+(-3),(-3)) = 3
	以第2个元素结尾：f(2) = max(3+(-2),(-2)) = 1
	以第3个元素结尾：f(3) = max(1+7,7) = 8
	以第4个元素结尾：f(4) = max(8+(-15),(-15)) = -7
	以第5个元素结尾：f(5) = max((-7)+1,1) = 1
*/

class Solution9 {
public:
	int FindGreatestSumOfSubArray(vector<int> array) {
		if (array.empty()){ return 0; }
		int len = array.size(), res = array[0];
		for (int i = 1; i < len; ++i){
			array[i] = max((array[i - 1] + array[i]), array[i]);
			if (array[i]>res){ res = array[i]; }
		}
		return res;
	}
};

/*
四、给定一个字符串s和一组单词dict，判断s是否可以用空格分割成一个单词序列，
使得单词序列中所有的单词都是dict中的单词(序列可以包含多个单词)
例子:  s="leetcode"
	dict=["leet","code"]
	返回true。因为leetcode可以被分割成leetcode
*/
/*
思路:
	问题：单词是否可以成功分割
	子问题：单词前几个字符是否可以成功分割
	状态F(i):单词前i个字符是否可以成功分隔
	(注意：接下来的推导过程|是个分隔符 不是或的意思)
	f(1) = l  false
	f(2) = 利用f（1）的结果：l|e （显然f(1):lfalse 我们只需要判断e是否能找到即可）  
	           f(2)本身：   le  flase
	f(3) = l|ee            [f(1)&&ee] false  
	       l|e|e  le|e     [f(2)&&e]false
		   lee  false
	f(4) = l|let           [f(1)&&let]false
	       l|e|et  le|et   [f(2)&&et]false
		   l|ee|t  l|e|e|t  le|e|t lee|t     [f(3)&&t]false
		   leet     true
	f(5) = 显然可利用的只有f(4)  leet|c    [f(4)&&c]false
	f(6) = [f(4)&&co] false
	f(7) = [f(4)&&cod]false
	f(8) = [f(4)&&code] true
	      leet|code
可得递推公式: f(i) =  (j<i)&&f(j)&&[j+1,i](代表j+1~i的闭区间内的字符串也是可以找到的)
*/

class Solution3{
public:
	bool wordBreak(string s, unordered_set<string> &dict) {
		int len = s.size();
		if (len == 0){ return false; }
		vector<bool> dp(len + 1, false); //初始化map均为false
		for (int i = 0; i < len; ++i){
			if (dict.find(s.substr(0, i + 1)) != dict.end()){
				//判断[0,i]整体
				//如果在dict中找到当前[0,i]个字符组成的字母，那么该dp[i]为真
				dp[i] = true;
			}
			else{
				//没找到就利用先前的dp[i] = true的状态去分割字符串
				//f(i) = (j<i)&&f(j)&&[j+1，i]
				for (int j = i - 1; j >= 0; --j){
					//该条for循环限定了j<i
					if (dp[j] == true){
						//寻找[j+1,i]之间组成的字符串能否找到
						if (dict.find(s.substr(j + 1, i - j)) != dict.end()){
							dp[i] = true;
						}
					}
				}
			}
		}
		return dp[len - 1];
	}
};
//int main(){
//	string s = "a";
//	unordered_set<string> dict;
//	dict.insert("a");
//	Solution3 a;
//	a.wordBreak(s, dict);
//	return 0;
//}

/*
五、triangle
链接：https://www.nowcoder.com/questionTerminal/2b7995aa4f7949d99674d975489cb7da
来源：牛客网
给出一个三角形，计算从三角形顶部到底部的最小路径和，每一步都可以移动到下面一行相邻的数字，
例如，给出的三角形如下：
[[2],[3,4],[6,5,7],[4,1,8,3]]
最小的从顶部到底部的路径和是2 + 3 + 5 + 1 = 11。
注意：
如果你能只用O（N）的额外的空间来完成这项工作的话，就可以得到附加分，其中N是三角形中的行总数。
*/

/*
思路：
2
3 4
6 5 7
4 1 8 3
f(i,j):当前层当前路径最小和
从题意出发（三角矩阵）：
上一行有哪些点可以直接到达（i,j）呢？
1.当j==0（第一列）： (i-1,j)
2.当j==i（每一行的结尾）：（i-1，j-1）
3.中间数字：（i-1,j）||（i-1,j-1）

递推公式
f(i,j) = min(f(i-1,j),f(i-1,j-1))+arr[i][j]
初始状态:f(0,0) = arr[0][0]
*/
class Solution {
public:
	int minimumTotal(vector<vector<int> > &triangle) {
		if (triangle.empty()){ return 0; }
		int row = triangle.size();
		//初始化dp,f(0,0) = triangle[0][0]
		vector<vector<int>>dp(triangle);
		for (int i = 1; i < row; ++i){
			for (int j = 0; j <= i; ++j){
				//分情况
				if (j == 0){
					//第一列
					dp[i][j] = dp[i - 1][j] + triangle[i][j];
				}
				else if (i == j){
					//最后一列
					dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
				}
				else{
					dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
				}
			}
		}
		//找到最后一行中的最小数字(最后一行有row列)
		int res = dp[row - 1][0];
		for (int j = 1; j < row; ++j){
			res = min(res, dp[row - 1][j]);
		}
		return res;
	}
};
