#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<vector>
#include<queue>
using namespace std;
/*
面试题59 - I. 滑动窗口的最大值
给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。
示例:
输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7]
解释:
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
1 [3  -1  -3] 5  3  6  7       3
1  3 [-1  -3  5] 3  6  7       5
1  3  -1 [-3  5  3] 6  7       5
1  3  -1  -3 [5  3  6] 7       6
1  3  -1  -3  5 [3  6  7]      7
提示：
你可以假设 k 总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。
*/
//思路：维护一个栈大小为1的栈 每次保存当前窗口最大值 在窗口满了以后将该最大值放入ret中
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		stack<int> a;
		vector<int> ret;
		vector<int>::iterator it = nums.begin();
		vector<int>::iterator end1 = nums.end();
		if (nums.size() == 0){
			return ret;
		}
		int k1 = k;
		while (--k1){
			--end1;
		}
		int flag1 = 0, flag2 = 0;
		while (it != end1){
			k1 = k;
			while (k1--){
				if (a.empty()){
					a.push(nums[flag1]);
				}
				else{
					if (nums[flag1] > a.top()){
						a.pop();
						a.push(nums[flag1]);
					}
				}
				++flag1;
			}
			ret.push_back(a.top());
			a.pop();
			++flag2;
			flag1 = flag2;
			++it;
		}	
		return ret;
	}
};
//int main(){
//	Solution a;
//	vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
//	vector<int> ret;
//	ret = a.maxSlidingWindow(nums,3);
//}
/*
面试题59 - II. 队列的最大值
请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。
若队列为空，pop_front 和 max_value 需要返回 -1
示例 1：
输入:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出: [null,null,null,2,1,2]
示例 2：
输入:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出: [null,-1,-1]
限制：
1 <= push_back,pop_front,max_value的总操作数 <= 10000
1 <= value <= 10^5
*/
/*
思路： 该思路借助了答案
本算法基于问题的一个重要性质：当一个元素进入队列的时候，它前面所有比它小的元素就不会再对答案产生影响。

举个例子，如果我们向队列中插入数字序列 1 1 1 1 2，那么在第一个数字 2 被插入后，数字 2 前面的所有数字 1 将不会对结果产生影响。因为按照队列的取出顺序，数字 2 只能在所有的数字 1 被取出之后才能被取出，因此如果数字 1 如果在队列中，那么数字 2 必然也在队列中，使得数字 1 对结果没有影响。

按照上面的思路，我们可以设计这样的方法：从队列尾部插入元素时，我们可以提前取出队列中所有比这个元素小的元素，使得队列中只保留对结果有影响的数字。这样的方法等价于要求维持队列单调递减，即要保证每个元素的前面都没有比它小的元素。

那么如何高效实现一个始终递减的队列呢？我们只需要在插入每一个元素 value 时，从队列尾部依次取出比当前元素 value 小的元素，直到遇到一个比当前元素大的元素 value' 即可。

上面的过程保证了只要在元素 value 被插入之前队列递减，那么在 value 被插入之后队列依然递减。
而队列的初始状态（空队列）符合单调递减的定义。
由数学归纳法可知队列将会始终保持单调递减。
上面的过程需要从队列尾部取出元素，因此需要使用双端队列来实现。另外我们也需要一个辅助队列来记录所有被插入的值，以确定 pop_front 函数的返回值。

保证了队列单调递减后，求最大值时只需要直接取双端队列中的第一项即可。

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/solution/mian-shi-ti-59-ii-dui-lie-de-zui-da-zhi-by-leetcod/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
class MaxQueue {
	queue<int> q;
	deque<int> d;
public:
	MaxQueue() {
	}

	int max_value() {
		if (d.empty())
			return -1;
		return d.front();
	}

	void push_back(int value) {
		while (!d.empty() && d.back() < value) {
			d.pop_back();
		}
		d.push_back(value);
		q.push(value);
	}

	int pop_front() {
		if (q.empty())
			return -1;
		int ans = q.front();
		if (ans == d.front()) {
			d.pop_front();
		}
		q.pop();
		return ans;
	}
};
