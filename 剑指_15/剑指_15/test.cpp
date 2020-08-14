#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

/*
题目描述 旋转数组的最小数字
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
*/

/*
思路一：空间复杂度0(1) 时间复杂度0(N)
1.遍历数组找到第一个非递增的位置，返回
2.若整个遍历都是递增的，那么直接返回第一个数字即可（说明没旋转）
*/
class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.size() == 0){ return 0; }
		for (int i = 0; i<rotateArray.size() - 1; ++i){
			if (rotateArray[i]>rotateArray[i + 1]){
				return rotateArray[i + 1];
			}
		}
		return rotateArray[0];
	}
};

/*
思路:二分查找空间复杂度O(1) 时间复杂度(logN)
1.定义左右指针指向最左（left）和最右（right）
2.依然是找到第一个非递增的位置
*/

class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.size() == 0){ return 0; }
		//如果左边大于右边，且其不相邻（相邻即是第一个非递增的位置）
		int left = 0, right = rotateArray.size() - 1, mid = -1;
		while (rotateArray[left] >= rotateArray[right]){
			if (right - left == 1){
				mid = right;
				break;
			}
			mid = left + (right - left) / 2;
			if (rotateArray[mid] >= rotateArray[left]){
				//说明left到mid还是递增的 但是left又大于right
				left = mid;
			}
			if (rotateArray[mid] <= rotateArray[right]){
				//说明mid到right是递增的，但是left又大于right
				//这必然是旋转过后的，所以right直接到mid的位置
				right = mid;
			}
		}
		return rotateArray[mid];
	}
};

/*
题目描述 矩形覆盖
我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？

比如n=3时，2*3的矩形块有3种覆盖方法：
*/

/*
思路：老斐波那契递推写法了，用空间换时间....
*/
class Solution {
public:
	int rectCover(int number) {
		vector<int> a;
		a.reserve(number + 1);
		a[0] = 0; a[1] = 1; a[2] = 2;
		for (int i = 3; i<number + 1; ++i){
			a[i] = a[i - 1] + a[i - 2];
		}
		return a[number];
	}
};