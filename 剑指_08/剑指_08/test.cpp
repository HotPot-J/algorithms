#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdio.h>
/*
������ʽƥ��:
��ʵ��һ����������ƥ�����'.'��'*'��������ʽ��ģʽ�е��ַ�'.'��ʾ����һ���ַ�����'*'��ʾ��ǰ����ַ����Գ���
����Σ�����0�Σ��� �ڱ����У�ƥ����ָ�ַ����������ַ�ƥ������ģʽ�����磬�ַ���"aaa"��ģʽ"a.a"��"ab*ac*a"ƥ�䣬
������"aa.a"��"ab*a"����ƥ��
*/

/*
˼·��
	1.   '.'����������� ��Ҫ��������һ����'*'����� ���ǲ���
	�����һ����'*'�����ƥ�� ��ô����ѡ�������'*'���浱ǰ��ĸ �����ǲ����� ��||���ݹ鼴��
						��ƥ�� ������ǰ����ĸ
	�����һ������'*'�����ƥ�䣬��������һ��
						��ƥ�䣺�򷵻�false
	��������:
		�������ַ���ͬʱ�ߵ�'\0'
		��ԭ�ַ���δ���꣬����һ���ַ��������ˣ���ʧ�ܣ���Ϊ����һ���ַ��������ˣ��п�����*ʹ��ǰһ���ַ�Ϊ0�� ���Ը���������ж�Ϊʧ�ܳ��ڣ�
*/
class Solution {
public:
	bool match(char* str, char* pattern)
	{
		if (*str == '\0'&&*pattern == '\0'){ return true; }
		if (*str != '\0'&&*pattern == '\0'){ return false; }
		//.�����κ����� ��*�������ֿ����۵Ĺؼ�
		if (*(pattern + 1) == '*'){
			if (*str == *pattern || (*str != '\0'&&*pattern == '.')){
				//��ǰ�ɹ�ƥ�� �ݹ������һ��
				//����*���߲�����*
				return match(str, pattern + 2) || match(str + 1, pattern);
			}
			else{
				//δƥ���� ��*���⵱ǰ�ַ���0
				return match(str, pattern + 2);
			}
		}
		else{
			if (*str == *pattern || (*str != '\0'&&*pattern == '.')){
				//������һ��
				return match(str + 1, pattern + 1);
			}
			else{
				return false;
			}
		}
	}
};

/*
�������ظ�������
��һ������Ϊn����������������ֶ���0��n - 1�ķ�Χ�ڡ� ������ĳЩ�������ظ��ģ�����֪���м����������ظ��ġ�
Ҳ��֪��ÿ�������ظ����Ρ����ҳ�����������һ���ظ������֡� ���磬������볤��Ϊ7������{ 2, 3, 1, 0, 2, 5, 3 }��
��ô��Ӧ������ǵ�һ���ظ�������2��
*/
/*
˼·������ ��ϣ
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