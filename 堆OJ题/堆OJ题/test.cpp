#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<functional>
#include<queue>
using namespace std;

/*
面试题40. 最小的k个数
输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，
则最小的4个数字是1、2、3、4。
示例 1：
输入：arr = [3,2,1], k = 2
输出：[1,2] 或者 [2,1]
示例 2：
输入：arr = [0,1,2,1], k = 1
输出：[0]
限制
0 <= k <= arr.length <= 10000
0 <= arr[i] <= 10000
*/
//思路建小堆
//方法一：运用STL中的priority_queue去建小堆
class Solution {
public:
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		priority_queue<int, vector<int>, greater<int>> q(arr.begin(), arr.end());
		vector<int> ret;
		for (int i = 0; i < k; i++){
			ret.push_back(q.top());
			q.pop();
		}
		return ret;
	}
};


//方法二：手写小堆 实现pop方法 弹出前k即可（思路和上边一致，只不过自己实现了小堆和pop函数）
class Solution2 {
public:
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		creatheap(arr);//建立小堆
		vector<int> ret;
		for (int i = 0; i < k; ++i){
			ret.push_back(_popheap(arr));
		}
		return ret;
	}
private:
	////_swap交换函数
	//template<typename T>
	//void _Swap(T& left, T& right)
	//{
	//	T temp = left;
	//	left = right;
	//	right = temp;
	//}
	//向下调整算法 建小堆：
	void adjustdwon(vector<int>& arr,int root){
		int parents = root;
		//先默认左孩子比较小 如果右孩子更下++child即可
		int child = parents * 2 + 1;
		while (child < arr.size()){
			if (child + 1 < arr.size() && arr[child + 1] < arr[child]){
				++child;
			}
			if (arr[child] < arr[parents]){
				swap(arr[child], arr[parents]);
				parents = child;
				child = parents * 2 + 1;
			}
			else{
				break;
			}
		}
	}
	//建小堆
	void creatheap(vector<int>& arr){
		//小堆必须要保证其左右子树都为小堆 所以我们从最后一个结点开始调整
		for (int i = (arr.size() - 1 - 1) / 2; i >= 0; --i){
			adjustdwon(arr, i);
		}
	}
	int _popheap(vector<int>& arr){
		int tmp = arr[0];
		swap(arr[0], arr[arr.size() - 1]);
		arr.pop_back();
		adjustdwon(arr, 0);
		return tmp;
	}
};


//方法三： 实现堆排序 直接选取topk即可
class Solution1 {
public:
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		vector<int> ret;
		HeapSort(arr);
		for (int i = 0; i < k; ++i){
			ret.push_back(arr[i]);
		}
		return ret;
	}
private:
	//向下调整 升序建大堆
	void adjustdown(vector<int>& arr,int size,int root){
		int parents = root;
		int child = parents * 2 + 1;
		while (child < size){
			if (child + 1 < size && arr[child + 1] > arr[child]){
				++child;
			}
			if (arr[child]>arr[parents]){
				swap(arr[child], arr[parents]);
				parents = child;
				child = parents * 2 + 1;
			}
			else{
				break;
			}
		}
	}
	//建堆
	void creatheap(vector<int>& arr){
		for (int i = (arr.size() - 1 - 1) / 2; i >= 0; --i){
			adjustdown(arr, arr.size(),i);
		}
	}
	//堆排序
	void HeapSort(vector<int>& arr){
		creatheap(arr);
		int end = arr.size() - 1;
		while (end > 0){
			swap(arr[0], arr[end]);
			adjustdown(arr, end,0);
			--end;
		}
	}
};
//int main(){
//	Solution1 a;
//	vector<int> arr = { 0,1,1,2,4,4,1,3,3,2 };
//	a.getLeastNumbers(arr,2);
//	return 0;
//}

/*
面试题41. 数据流中的中位数
如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
例如，
[2,3,4] 的中位数是 3
[2,3] 的中位数是 (2 + 3) / 2 = 2.5
设计一个支持以下两种操作的数据结构：
void addNum(int num) - 从数据流中添加一个整数到数据结构中。
double findMedian() - 返回目前所有元素的中位数。
示例 1：

输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]
*/

/*思路：使用大小堆来解决 用大堆存储一个有序序列的左半边 小堆用来存储一个有序序列的右半边 永远保持两个堆的大小一至
例如：12345 奇数情况：大堆：321  小堆：45  那么中位数即：3 就是小堆堆顶
      12342 偶数情况：大堆：21  小堆：34  那么中位数即：（2+3）/2 就是大小堆堆顶求中位数
*/
class MedianFinder {
public:
	priority_queue<int> a;//默认大堆
	priority_queue<int, vector<int>, greater<int>> b;//建小堆
	void addNum(int num) {
		//直接加到大堆顶
		a.push(num);
        //平衡
		b.push(a.top());//将a中最大的放进b 则可以保证"小堆的数字永远大于大堆"
		a.pop();
		//维护两个堆的大小一致 
		if (a.size() < b.size()){
			a.push(b.top());
			b.pop();
		}
	}

	double findMedian() {
		//由于起始直接插入在大堆中 若为奇数则a.size()>b.size()且中位数一定在大堆顶 否则为两个堆顶元素求平均值
		return a.size()>b.size() ? (double)a.top() : (a.top() + b.top())*0.5;
	}
};
