#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>


/*
调整数组顺序使奇数位于偶数前面
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，
所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
*/
/*
思路：利用插入排序的思路，找到奇数将前面的偶数往后覆盖，最终插入奇数
	时间复杂度O（n^2）
	空间复杂度O（1）
*/
using namespace std;
class Solution1 {
public:
	void reOrderArray(vector<int> &array) {
		if (array.size() <= 1){ return; }
		int end = 0;
		for (int i = 0; i<array.size(); ++i){
			end = i;
			//找到下一个奇数
			while (end<array.size() && array[end] % 2 == 0){ ++end; }
			if (end >= array.size()){ break; } //后面没有奇数了直接退出
			int tmp = array[end];
			//如果前面是偶数就覆盖
			while (end>0 && array[end - 1] % 2 == 0){
				array[end] = array[end - 1];
				--end;
			}
			array[end] = tmp;
		}
	}
};

//int main(){
//	vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };
//	Solution a;
//	a.reOrderArray(arr);
//	return 0;
//}

class Solution {
public:
	vector<int> FindNumbersWithSum(vector<int> array, int sum) {
		vector<int> res;
		int left = 0, right = array.size()-1, tmp = INT_MAX;
		while (left<right){
			if ((array[left] + array[right]) == sum){
				if (array[left] * array[right]<tmp){
					tmp = array[left] * array[right];
					res.push_back(array[left]);
					res.push_back(array[right]);
				}
				//继续寻找其他相等解
				++left;
				--right;
			}
			else if ((array[left] + array[right])<sum){
				++left;
			}
			else{
				--right;
			}
		}
		return res;
	}
};
//int main(){
//	vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
//	Solution a;
//	a.FindNumbersWithSum(arr, 21);
//	return 0;
//}