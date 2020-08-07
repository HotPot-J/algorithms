#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdio.h>
/*
正则表达式匹配:
请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现
任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，
但是与"aa.a"和"ab*a"均不匹配
*/

/*
思路：
	1.   '.'就是正常情况 主要是讨论下一个是'*'的情况 还是不是
	如果下一个是'*'，如果匹配 那么可以选择让这个'*'代替当前字母 或者是不代替 用||来递归即可
						不匹配 跳过当前的字母
	如果下一个不是'*'，如果匹配，则都往后走一部
						不匹配：则返回false
	返回条件:
		当两个字符串同时走到'\0'
		当原字符串未走完，而另一个字符串走完了，则失败（因为，另一个字符串走完了，有可能让*使得前一个字符为0个 所以该情况不能判断为失败出口）
*/
class Solution {
public:
	bool match(char* str, char* pattern)
	{
		if (*str == '\0'&&*pattern == '\0'){ return true; }
		if (*str != '\0'&&*pattern == '\0'){ return false; }
		//.代表任何数字 而*是这个题分开讨论的关键
		if (*(pattern + 1) == '*'){
			if (*str == *pattern || (*str != '\0'&&*pattern == '.')){
				//当前成功匹配 递归进入下一层
				//利用*或者不利用*
				return match(str, pattern + 2) || match(str + 1, pattern);
			}
			else{
				//未匹配上 让*把这当前字符当0
				return match(str, pattern + 2);
			}
		}
		else{
			if (*str == *pattern || (*str != '\0'&&*pattern == '.')){
				//进入下一层
				return match(str + 1, pattern + 1);
			}
			else{
				return false;
			}
		}
	}
};

/*
数组中重复的数字
在一个长度为n的数组里的所有数字都在0到n - 1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。
也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{ 2, 3, 1, 0, 2, 5, 3 }，
那么对应的输出是第一个重复的数字2。
*/
/*
思路：队列 哈希
*/
#include<unordered_map>
#include<queue>
using namespace std;
class Solution {
public:
	// Parameters:
	//        numbers:     an array of integers
	//        length:      the length of array numbers
	//        duplication: (Output) the duplicated number in the array number
	// Return value:       true if the input is valid, and there are some duplications in the array number
	//                     otherwise false
	bool duplicate(int numbers[], int length, int* duplication) {
		unordered_map<int, int> m;
		queue<int> q;
		int* ret = new int[length];
		int j = 0;
		for (int i = 0; i<length; ++i){
			m[numbers[i]]++;
			if (m[numbers[i]] == 1){ q.push(numbers[i]); }
		}
		while (!q.empty()){
			if (m[q.front()]>1){
				*duplication = q.front();
				return true;
			}
			q.pop();
		}
		return false;
	}
};