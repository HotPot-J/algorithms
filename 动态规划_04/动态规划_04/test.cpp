#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std; 
/*
121. ������Ʊ�����ʱ��
����һ�����飬���ĵ� i ��Ԫ����һ֧������Ʊ�� i ��ļ۸�
��������ֻ�������һ�ʽ��ף������������һ֧��Ʊһ�Σ������һ���㷨�����������ܻ�ȡ���������
ע�⣺�㲻���������Ʊǰ������Ʊ��
ʾ�� 1:
����: [7,1,5,3,6,4]
���: 5
����: �ڵ� 2 �죨��Ʊ�۸� = 1����ʱ�����룬�ڵ� 5 �죨��Ʊ�۸� = 6����ʱ��������������� = 6-1 = 5 ��
ע���������� 7-1 = 6, ��Ϊ�����۸���Ҫ��������۸�ͬʱ���㲻��������ǰ������Ʊ��
ʾ�� 2:
����: [7,6,4,3,1]
���: 0
����: �����������, û�н������, �����������Ϊ 0��
*/
/*
˼·:
	ά��һ����Сֵ������㣩
	ά��һ�����ֵ�������㣩
*/
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int _min = INT_MAX;
		int res = 0;
		for (int i = 0; i < prices.size(); ++i){
			if (prices[i] < _min){
				_min = prices[i];
			}
			else if (prices[i] - _min>res){
				res = prices[i] - _min;
			}
		}
		return res;
	}
};
//int main(){
//	vector<int> arr = { 7, 1, 5, 3, 6, 4 };
//	Solution a;
//	cout<<a.maxProfit(arr)<<endl;
//	return 0;
//}
/*
198. ��ҽ���
����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݡ�ÿ�䷿�ڶ�����һ�����ֽ�Ӱ����͵�Ե�Ψһ��Լ���ؾ������ڵķ���װ��
�໥��ͨ�ķ���ϵͳ������������ڵķ�����ͬһ���ϱ�С͵���룬ϵͳ���Զ�����������һ������ÿ�����ݴ�Ž��ķ�
���������飬������ ����������װ�õ������ ��һҹ֮���ܹ�͵�Ե�����߽�
ʾ�� 1��
���룺[1, 2, 3, 1]
�����4
���ͣ�͵�� 1 �ŷ���(��� = 1) ��Ȼ��͵�� 3 �ŷ���(��� = 3)��
͵�Ե�����߽�� = 1 + 3 = 4 ��
ʾ�� 2��
���룺[2, 7, 9, 3, 1]
�����12
���ͣ�͵�� 1 �ŷ���(��� = 2), ͵�� 3 �ŷ���(��� = 9)������͵�� 5 �ŷ���(��� = 1)��
͵�Ե�����߽�� = 2 + 9 + 1 = 12 ��*/
/*
1.Ŀ�꣬�ڲ���������װ�õ��������͵���������
2.״̬:f(i):͵����i��ʱ�������
3.f(2):2  (�����һ��)
  f(3):7 (��������͵)
  f(4):f(1)+arr[3-1]
f(i) = max(f(i),f(j)+arr[i-2]) ��j<i-1��
*/
class Solution1 {
public:
	int rob(vector<int>& nums) {
		if (nums.empty()) return 0;
		int len = nums.size();
		vector<int> dp(len + 2, 0);
		int res = INT_MIN;
		for (int i = 2; i <= len + 1; ++i){
			for (int j = 0; j < i - 1; ++j){
				dp[i] = max(dp[i], dp[j] + nums[i - 2]);
			}
			if (dp[i]>res) res = dp[i];
		}
		return res;
	}
};
//int main(){
//	vector<int> arr = { 2, 7, 9, 3, 1 };
//	Solution1 a;
//	cout << a.rob(arr) << endl;
//	return 0;
//}

/*
303. ����ͼ��� - ���鲻�ɱ�
����һ����������  nums�������������� i �� j  (i �� j) ��Χ��Ԫ�ص��ܺͣ����� i,  j ���㡣

ʾ����

���� nums = [-2, 0, 3, -5, 2, -1]����ͺ���Ϊ sumRange()

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
˵��:

����Լ������鲻�ɱ䡣
���ε��� sumRange ������
*/

/*
˼·һ����̬�滮���ȱ������ܺõ㣬�ռ任ʱ�䣩
1.f(i,j):��ʾ��i-j֮��
2.����ֻ��i~j,������j~i,��������һ���ϰ����Ǿ���
3.i=j:f(i,j) = nums[j]
  i<j:f(i,j) = dp[i][j-1]+nums[j]
*/
class NumArray {
	vector<vector<int>> dp;
public:
	NumArray(vector<int>& nums) {
		int len = nums.size();
		dp.resize(len);
		for (int i = 0; i < len; ++i){
			dp[i].resize(len, 0);
			for (int j = i; j< len; ++j){
				if (i == j){ dp[i][j] = nums[j];}
				else{ dp[i][j] = dp[i][j - 1] + nums[j]; }
			}
		}
	}

	int sumRange(int i, int j) {
		return dp[i][j];
	}
};
//int main(){
//	vector<int> arr = { -2, 0, 3, -5, 2, -1 };
//	NumArray a(arr);
//	cout << a.sumRange(0, 2) << endl;
//	cout << a.sumRange(2, 5) << endl;
//	cout << a.sumRange(0, 5) << endl;
//	return 0;
//}

/*
˼·������̬�滮���Ż���
f(i)��ʾ�ӵ�һ�����ֵ���i������֮��
f(i) = f(i-1)+nums[i]
nums:-2, 0, 3, -5, 2, -1
f(i):0,-2,-2,1,-4,-2,-1 (��ʼ״̬f(0)=0)
F(0,0) = f(1)-f(0) = -2
F(0,5):f(6)-f(0) = -1

��ôF(i,j) = f(j+1)-f(i)
��ʼ״̬:f(0) = 0;
*/

class NumArray1 {
public:
	vector<int> dp;
	NumArray1(vector<int>& nums) {
		dp.resize(nums.size() + 1, 0);
		for (int i = 1; i <= nums.size(); ++i){
			dp[i] = dp[i - 1] + nums[i - 1];
		}
	}

	int sumRange(int i, int j) {
		return dp[j + 1] - dp[i];
	}
};

/*
746. ʹ����С������¥��
�����ÿ��������Ϊһ�����ݣ��� i�����ݶ�Ӧ��һ���Ǹ�������������ֵ cost[i](������0��ʼ)��
ÿ��������һ�������㶼Ҫ���Ѷ�Ӧ����������ֵ��Ȼ�������ѡ�������һ�����ݻ������������ݡ�
����Ҫ�ҵ��ﵽ¥�㶥������ͻ��ѡ��ڿ�ʼʱ�������ѡ�������Ϊ 0 �� 1 ��Ԫ����Ϊ��ʼ���ݡ�
ʾ�� 1:
����: cost = [10, 15, 20]
���: 15
����: ��ͻ����Ǵ�cost[1]��ʼ��Ȼ�����������ɵ����ݶ���һ������15��
ʾ�� 2:
����: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
���: 6
����: ��ͻ��ѷ�ʽ�Ǵ�cost[0]��ʼ�����������Щ1������cost[3]��һ������6��
ע�⣺
cost �ĳ��Ƚ����� [2, 1000]��
ÿһ�� cost[i] ������һ��Integer���ͣ���ΧΪ [0, 999]��
*/

/*
˼·:
	Ŀ��:����¥�㶥������ͻ��� 
	״̬: f(i)��ʾ���ﵱǰ¥�����ͻ���
	��ʼ״̬f(0):0 ��ʾһ��ʼ�����λ�õĻ���Ϊ0
	f(1):cost[0]������ϵ�һ�׵Ļ���Ϊcost[0]
	f(2):cost[1]������ϵڶ��׵Ļ���Ϊcost[1]
	f(3):min(cost[0],cost[1])+cost[2]
	����f(i) = min(f(i-1),f(i-2))+cost[i-1]

	int len = cost.size();
	���ǿ��Խ�����࿪������λ�ã�f(0)=0��Ϊ��ʼ״̬����f(i+1)�洢���
*/

class Solution3 {
public:
	int minCostClimbingStairs(vector<int>& cost) {
		if (cost.empty()) return 0;
		int len = cost.size();
		vector<int> dp(len + 2, 0);
		dp[1] = cost[0];
		for (int i = 2; i <= len + 1; ++i){
			dp[i] = min(dp[i - 1], dp[i - 2]);
			if (i <len+1){ dp[i] += cost[i - 1]; }
		}
		return dp[len + 1];
	}
};
//int main(){
//	vector<int> arr = { 10, 15, 20 };
//	Solution3 a;
//	a.minCostClimbingStairs(arr);
//	return 0;
//}