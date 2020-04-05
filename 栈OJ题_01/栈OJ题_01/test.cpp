#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include <algorithm>
using namespace std;
/*
����ջ�����ݽṹ�����ڸ�������ʵ��һ���ܹ��õ�ջ����СԪ�ص� min �����ڸ�ջ��
���� min��push �� pop ��ʱ�临�Ӷȶ��� O(1)��
ʾ��:
 MinStack minStack = new MinStack();
 minStack.push(-2);
 minStack.push(0);
 minStack.push(-3);
 minStack.min();   --> ���� -3.
 minStack.pop();
 minStack.top();      --> ���� 0.
 minStack.min();   --> ���� -2.
  ��ʾ��
  �������ĵ����ܴ��������� 20000 ��
  ��Դ�����ۣ�LeetCode��
  ���ӣ�https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof
  ����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/
class MinStack {
public:
	/** initialize your data structure here. */
	stack<int> s_data;//�������
	stack<int> s_min;//���ÿһ��ѹ���ջ�ڵ���Сֵ
	MinStack() {
	}
	void push(int x) {
		s_data.push(x);
		if (s_min.size() == 0) s_min.push(x);
		else
		{
			if (x < s_min.top()) s_min.push(x);
			else s_min.push(s_min.top());
		}
	}
	void pop() {
		if (s_data.size() == 0) return;
		s_data.pop();
		s_min.pop();
	}
	int top() {
		return s_data.top();
	}
	int min() {
		return s_min.top();
	}
};

