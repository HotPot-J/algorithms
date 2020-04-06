#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<vector>
#include<queue>
using namespace std;
/*
������59 - I. �������ڵ����ֵ
����һ������ nums �ͻ������ڵĴ�С k�����ҳ����л�������������ֵ��
ʾ��:
����: nums = [1,3,-1,-3,5,3,6,7], �� k = 3
���: [3,3,5,5,6,7]
����:
�������ڵ�λ��                ���ֵ
---------------               -----
[1  3  -1] -3  5  3  6  7       3
1 [3  -1  -3] 5  3  6  7       3
1  3 [-1  -3  5] 3  6  7       5
1  3  -1 [-3  5  3] 6  7       5
1  3  -1  -3 [5  3  6] 7       6
1  3  -1  -3  5 [3  6  7]      7
��ʾ��
����Լ��� k ������Ч�ģ����������鲻Ϊ�յ�����£�1 �� k �� ��������Ĵ�С��
*/
//˼·��ά��һ��ջ��СΪ1��ջ ÿ�α��浱ǰ�������ֵ �ڴ��������Ժ󽫸����ֵ����ret��
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
������59 - II. ���е����ֵ
�붨��һ�����в�ʵ�ֺ��� max_value �õ�����������ֵ��Ҫ����max_value��push_back �� pop_front �ľ�̯ʱ�临�Ӷȶ���O(1)��
������Ϊ�գ�pop_front �� max_value ��Ҫ���� -1
ʾ�� 1��
����:
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
���: [null,null,null,2,1,2]
ʾ�� 2��
����:
["MaxQueue","pop_front","max_value"]
[[],[],[]]
���: [null,-1,-1]
���ƣ�
1 <= push_back,pop_front,max_value���ܲ����� <= 10000
1 <= value <= 10^5
*/
/*
˼·�� ��˼·�����˴�
���㷨���������һ����Ҫ���ʣ���һ��Ԫ�ؽ�����е�ʱ����ǰ�����б���С��Ԫ�ؾͲ����ٶԴ𰸲���Ӱ�졣

�ٸ����ӣ��������������в����������� 1 1 1 1 2����ô�ڵ�һ������ 2 ����������� 2 ǰ����������� 1 ������Խ������Ӱ�졣��Ϊ���ն��е�ȡ��˳������ 2 ֻ�������е����� 1 ��ȡ��֮����ܱ�ȡ�������������� 1 ����ڶ����У���ô���� 2 ��ȻҲ�ڶ����У�ʹ������ 1 �Խ��û��Ӱ�졣

���������˼·�����ǿ�����������ķ������Ӷ���β������Ԫ��ʱ�����ǿ�����ǰȡ�����������б����Ԫ��С��Ԫ�أ�ʹ�ö�����ֻ�����Խ����Ӱ������֡������ķ����ȼ���Ҫ��ά�ֶ��е����ݼ�����Ҫ��֤ÿ��Ԫ�ص�ǰ�涼û�б���С��Ԫ�ء�

��ô��θ�Чʵ��һ��ʼ�յݼ��Ķ����أ�����ֻ��Ҫ�ڲ���ÿһ��Ԫ�� value ʱ���Ӷ���β������ȡ���ȵ�ǰԪ�� value С��Ԫ�أ�ֱ������һ���ȵ�ǰԪ�ش��Ԫ�� value' ���ɡ�

����Ĺ��̱�֤��ֻҪ��Ԫ�� value ������֮ǰ���еݼ�����ô�� value ������֮�������Ȼ�ݼ���
�����еĳ�ʼ״̬���ն��У����ϵ����ݼ��Ķ��塣
����ѧ���ɷ���֪���н���ʼ�ձ��ֵ����ݼ���
����Ĺ�����Ҫ�Ӷ���β��ȡ��Ԫ�أ������Ҫʹ��˫�˶�����ʵ�֡���������Ҳ��Ҫһ��������������¼���б������ֵ����ȷ�� pop_front �����ķ���ֵ��

��֤�˶��е����ݼ��������ֵʱֻ��Ҫֱ��ȡ˫�˶����еĵ�һ��ɡ�

���ߣ�LeetCode-Solution
���ӣ�https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/solution/mian-shi-ti-59-ii-dui-lie-de-zui-da-zhi-by-leetcod/
��Դ�����ۣ�LeetCode��
����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
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
