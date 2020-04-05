#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include <algorithm>
using namespace std;
/*
定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈，
调用 min、push 及 pop 的时间复杂度都是 O(1)。
示例:
 MinStack minStack = new MinStack();
 minStack.push(-2);
 minStack.push(0);
 minStack.push(-3);
 minStack.min();   --> 返回 -3.
 minStack.pop();
 minStack.top();      --> 返回 0.
 minStack.min();   --> 返回 -2.
  提示：
  各函数的调用总次数不超过 20000 次
  来源：力扣（LeetCode）
  链接：https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof
  著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
class MinStack {
public:
	/** initialize your data structure here. */
	stack<int> s_data;//存放数据
	stack<int> s_min;//存放每一次压入后，栈内的最小值
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

