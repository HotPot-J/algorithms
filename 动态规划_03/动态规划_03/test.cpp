#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;     

/*
一、edit-distance
链接：https://www.nowcoder.com/questionTerminal/81d7738f954242e5ade5e65ec40e5027
来源：牛客网

给定两个单词word1和word2，请计算将word1转换为word2至少需要多少步操作。
你可以对一个单词执行以下3种操作：
a）在单词中插入一个字符
b）删除单词中的一个字符
c）替换单词中的一个字符
-------------
示例1
输入
"b",""
输出
1
-------------
示例2
输入
"ab","bc"
输出
2
*/
/*
思路:
s1:ab --> s2:cdab

状态f(i,j)表示s1前i个字符转换成s2前j个字符所需要的步骤
f(1,1):即从a->c 需要1步 （替换）
f(1,2):即从a->cd 借助f(1,1)的状态，再插入d即可
f(1,3):即从a->cda 借助f(1,2)的状态，再插入a即可...
f(2,2):即从ab->cd 借助f(1,1)的状态，再将b替换为b即可
f(2,1):即从ab->c  借助f(1,1)的状态，再将b删除
...

可得状态转移方程:
	s1[i]==s2[i]: f(i,j) = min(dp[i-1][j-1],dp[i-1][j],dp[i][j])
	s1[i]!=s2[i]: f(i,j) = min(dp[i-1][j-1],dp[i-1][j],dp[i][j])
*/
class Solution {
public:
	int _min(int a, int b, int c){
		int tmp = min(a, b);
		return min(tmp, c);
	}
	int minDistance(string word1, string word2) {
		if (word1.empty() && word2.empty()){ return 0; }
		if (word1.empty()){ return word2.size(); }
		if (word2.empty()){ return word1.size(); }
		int len1 = word1.size(), len2 = word2.size();
		vector<vector<int>> dp(len1+1, vector<int>(len2+1, 0));
		
		for (int i = 1; i <= len1; ++i){
				if (word1[i-1] == word2[0]){
					dp[i][1] = dp[i - 1][1];
				}
				else{
					dp[i][1] = dp[i - 1][1]+1; 
				}
		}

		for (int j = 1; j <= len2; ++j){
			if (word1[0] == word2[j-1]){
				dp[1][j] = dp[1][j-1];
			}
			else{
				dp[1][j] = dp[1][j-1]+1;
			}
		}

		for (int i = 2; i <= len1; ++i){
			for (int j = 2; j <= len2; ++j){
				if (word1[i-1] == word2[j-1]){
					dp[i][j] = _min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]);
				}
				else{
					dp[i][j] = _min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]) + 1;
				}
			}
		}
		return dp[len1][len2];
	}
};

//int main(){
//	string s1 = "ab";
//	string s2 = "cdab";
//	Solution a;
//	a.minDistance(s1, s2);
//	return 0;
//}

/*
二、distinct-subsequences（不同子序列个数）
链接：https://www.nowcoder.com/questionTerminal/ed2923e49d3d495f8321aa46ade9f873
来源：牛客网

给定两个字符串S和T，返回S子序列等于T的不同子序列个数有多少个？
字符串的子序列是由原来的字符串删除一些字符（也可以不删除）在不改变相对位置的情况下的剩余字符
（例如，"ACE"is a subsequence of"ABCDE"但是"AEC"不是）
例如：
S ="rabbbit", T ="rabbit"
返回3
*/
/*
思路：
目标：寻找S子序列等于T的不同子序列个数有多少个
状态：f(i,j) = s前i-1个字符 与 j-1个字符相同的子串个数
例子： s:rabbbit t:rabbit
^        ^
i        j
当s[i]==t[i]：
以当前i j所指向的b作为结尾：我们需要找到s中前i-1个字符串的ra即：f(i-1,j-1)
以s[i-1]对应的b结尾：我们需要找到s中前i-1个字符串的rab即:f（i-1，j）
以上两种情况的b不同，所以是不同的两种子情况，应相加则:
f(i,j) = f(i-1,j-1)+f(i-1,j)
当s[i]!=t[i]
我们应该寻找s中前i-1个字符所对应的t前j个字符：即f(i-1,j)
f(i,j) = f(i-1,j-1)
初始状态：
f(i,0):从s的前i个字符中寻找其子串，与空字符串相等：空集 ，能够找到-》1
f(0,j):从空串中寻找子串，与非空串相等，找不到-》0

*/

class Solution {
public:
	int numDistinct(string S, string T) {
		int len1 = S.size(), len2 = T.size();
		//初始化dp
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		for (int i = 0; i <= len1; ++i){
			dp[i][0] = 1;
		}
		for (int i = 1; i <= len1; ++i){
			for (int j = 1; j <= len2; ++j){
				if (S[i - 1] == T[j - 1]){
					dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
				}
				else{
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
		return dp[len1][len2];
	}
};
//int main(){
//	Solution2 a;
//	a.numDistinct("b", "b");
//	return 0;
//}

//奇安信笔试：（两道动态规划题）
/*
三、
公司有一个楼梯，同事们每次嫌太慢，所以有时候一次上一个台阶，有时候一次上两个台阶。
请问如果有n个台阶，同事有多少种上楼梯的方法呢?(为了不让同事太累，最多36个台阶)
*/
/*
思路：动态规划
f(i) = f(i-1)+f(i-2)
*/
int main(){
	int n = 0;
	while (cin >> n){
		if (n <= 0){
			cout << 0 << endl;
		}
		else{
			vector<int> dp(n + 1, 0);
			//初始状态
			dp[0] = 1;
			dp[1] = 1;//到达第一个台阶只有一种方法
			for (int i = 2; i <= n; ++i){
				dp[i] = dp[i - 1] + dp[i - 2];
			}
			cout << dp[n] << endl;
		}
	}
	return 0;
}

/*
一个城市改建，有一排房子需要拆迁，请问最少需要分配多少套房子。
要求:
    1.保证每个住户都至少有一套房子
	2.相邻房子，分配给住户人数多的房子数量要高于住户人数少的房子。
	3.不论是否相邻，人数相同的房子，分配到的房子数量可以不同。
*/
/*
思路：动态规划：
当arr[i-1]<arr[i]: f(i) = f(i-1)+1
当arr[i-1]>arr[i]: s) = f(i)+1
初始状态：每户都先分一套房子 保证至少分一套
*/
class Solution {
public:
	int house(int* person, int personLen) {
		if (personLen == 0 || person == NULL){ return 0; }
		if (personLen == 1){ return 1; }
		vector<int>dp(personLen + 1, 1);
		for (int i = 2; i <= personLen; ++i){
			if (person[i - 1] == 0){
				dp[i] = 0;
			}
			else if (person[i - 2] < person[i - 1]){
				dp[i] = dp[i - 1] + 1;
			}
			else if (person[i - 2] > person[i - 1]){
				dp[i - 1] = dp[i] + 1;
			}
		}
		long res = 0;
		for (int i = 1; i <= personLen; ++i){
			res += dp[i];
		}
		return res;
	}
};