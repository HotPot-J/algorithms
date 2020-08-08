#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
using namespace std;


/*
把字符串转换成整数
将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 数值为0或者字符串不是一个合法的数值则返回0
输入描述:
输入一个字符串,包括数字字母符号,可以为空
输出描述:
如果是合法的数值表达则返回该数字，否则返回0
*/

/*
思路：字符数字 - '0' = 数字
*/
class Solution {
public:
	int StrToInt(string str) {
		int len = str.size(), j = 0, res = 0, flag = 0;
		if (len>0){
			if (str[0] == '+'){ ++j; }
			else if (str[0] == '-'){ flag = 1; ++j; }
		}
		for (int i = j; i<len; ++i){
			if (!(str[i] >= '0'&&str[i] <= '9')){
				//不在数字范围内
				return 0;
			}
			res = res * 10 + (str[i] - '0');
		}
		if (flag){ res *= (-1); }
		return res;
	}
};

/*
圆圈中最后剩下的数
每年六一儿童节,牛客都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。HF作为牛客的资深元老,自然也准备了一些小游戏。其中,有个游戏是这样的:首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,可以不用表演,并且拿到牛客名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。请你试着想下,哪个小朋友会得到这份礼品呢？(注：小朋友的编号是从0到n-1)

如果没有小朋友，请返回-1
*/

/*
思路：利用迭代器循环遍历数组  （模拟循环即可）
*/

class Solution {
public:
	int LastRemaining_Solution(int n, int m)
	{
		vector<int> a;
		int flag = -1;
		for (int i = 0; i<n; ++i){
			a.push_back(i);
		}
		auto it = a.begin();
		while (!a.empty() && it != a.end()){
			if (a.size() == 1){ return a[0]; }
			++flag;
			if (flag == m - 1){
				it = a.erase(it);
				flag = -1;
			}
			else{ ++it; }
			if (!a.empty() && it == a.end()){ it = a.begin(); }
		}
		return -1;
	}
};
