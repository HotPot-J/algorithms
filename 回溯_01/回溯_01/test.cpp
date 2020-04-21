#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<string>
#include<stdio.h>
using namespace std;
/*
回溯算法的基本模板:
  
int check(参数)
{
    if(满足条件)
        return 1;
    return 0;
}
 
void dfs(int step)
{
        判断边界
        {
            相应操作
        }
        尝试每一种可能
        {
               满足check条件
               标记
               继续下一步dfs(step+1)
               恢复初始状态（回溯的时候要用到）
        }
} 
*/
/*
784. 字母大小写全排列
给定一个字符串S，通过将字符串S中的每个字母转变大小写，我们可以获得一个新的字符串。返回所有可能得到的字符串集合。
示例:
输入: S = "a1b2"
输出: ["a1b2", "a1B2", "A1b2", "A1B2"]
输入: S = "3z4"
输出: ["3z4", "3Z4"]
输入: S = "12345"
输出: ["12345"]
注意：
S 的长度不超过12。
S 仅由数字和字母组成。
*/
//a-z 97-122  A-Z 65-90
/*
  小结论：若A与a相差32  A^32 = a   a^32 = A
 例子：
  1 1 1 1   15 和10差了5
  0 1 0 1
异或：
  1 0 1 0  8+2 = 10   
*/

//class Solution {
//public:
//	vector<string> ans;
//	vector<string> letterCasePermutation(string S) {
//		dfs(S, 0);
//		return ans;
//	}
//	void dfs(string& S, int index){
//		//返回其引用 因为是在修改以后的基础上再去寻找其他可能性
//		if (index == S.size()){
//			ans.push_back(S);
//			return;
//		}
//		dfs(S, index + 1);
//		//判断其是否为字母 
//		if (isalpha(S[index])){
//			//改变其大小写
//			S[index] = S[index] ^ 32;
//			//从该位置起对其分支进行遍历
//			dfs(S, index+1);
//		}
//	}
//};

//int main(){
//	Solution a;
//	string s("abcd");
//	a.letterCasePermutation(s);
//	return 0;
//}


/*
401. 二进制手表
二进制手表顶部有 4 个 LED 代表小时（0-11），底部的 6 个 LED 代表分钟（0-59）。
每个 LED 代表一个 0 或 1，最低位在右侧。
例如，上面的二进制手表读取 “3:25”。
给定一个非负整数 n 代表当前 LED 亮着的数量，返回所有可能的时间。
案例:
输入: n = 1
返回: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
注意事项:
输出的顺序没有要求。
小时不会以零开头，比如 “01:00” 是不允许的，应为 “1:00”。
分钟必须由两位数组成，可能会以零开头，比如 “10:2” 是无效的，应为 “10:02”。
*/

//解法一：双层循环找出所有解（位运算）
//格式化一个字符串使用：sprint()
//class Solution {
//public:
//	vector<string> readBinaryWatch(int num) {
//		vector<string> res ;
//		char s[10];
//		for (int i = 0; i < 12; ++i){
//			for (int j = 0; j < 60; ++j){
//				if (count_one_bits(i)+count_one_bits(j) == num){
//					sprintf(s, "%d:%02d", i, j);
//					res.push_back(s);
//				}
//			}
//		}
//		return res;
//	}
//	int count_one_bits(unsigned int value)
//	{
//		//计算一个数字的二进制有几个1
//		int count = 0; // 保存1的个数
//		for (int i = 0; i < 32; i++){
//			if ((value >> i) & 1){
//				count++;
//			}
//		}
//		return count;
//	}
//};

//解法二 ：回溯法
class Solution {
public:
	vector<string> res;
	char tmp[10];
	int flag1 = 0, flag2 = 0;
	vector<string> readBinaryWatch(int num) {
		int arr[10] = { 1, 2, 4, 8, 1, 2, 4, 8, 16, 32 };
		int map[10] = { 0 };
		dfs(num, 0, arr, map);
		return res;
	}
	int check(int* m){
		int flag = 0;
		for (int i = 0; i < 10; ++i){
			if (!m[i]){
				++flag;
			}
		}
		return flag;
	}
	void dfs(int num, int index, int* arr, int*map){
		if (index == 10){
			//遍历完一遍
			if (check(map) == num){
				//满足条件
				for (int i = 0; i < 4; ++i){
					if (!map[i]){
						flag1 += arr[i];
					}
				}
				for (int j = 4; j < 10; ++j){
					if (!map[j]){
						flag2 += arr[j];
					}
				}
				if (flag1<12 && flag2<60){
					sprintf(tmp, "%d:%02d", flag1, flag2);
					res.push_back(tmp);
				}

				flag1 = 0;
				flag2 = 0;
			}
			return;
		}
		if (map[index] == 0){
			map[index] = 1;
		}
		dfs(num, index + 1, arr, map);
		map[index] = 0;
		dfs(num, index + 1, arr, map);
	}
};


int main(){
	Solution a;
	a.readBinaryWatch(1);
	return 0;
}