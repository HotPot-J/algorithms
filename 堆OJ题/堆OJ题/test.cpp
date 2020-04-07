#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<functional>
#include<queue>
using namespace std;

/*
������40. ��С��k����
������������ arr ���ҳ�������С�� k ���������磬����4��5��1��6��2��7��3��8��8�����֣�
����С��4��������1��2��3��4��
ʾ�� 1��
���룺arr = [3,2,1], k = 2
�����[1,2] ���� [2,1]
ʾ�� 2��
���룺arr = [0,1,2,1], k = 1
�����[0]
����
0 <= k <= arr.length <= 10000
0 <= arr[i] <= 10000
*/
//˼·��С��
//����һ������STL�е�priority_queueȥ��С��
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


//����������дС�� ʵ��pop���� ����ǰk���ɣ�˼·���ϱ�һ�£�ֻ�����Լ�ʵ����С�Ѻ�pop������
class Solution2 {
public:
	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		creatheap(arr);//����С��
		vector<int> ret;
		for (int i = 0; i < k; ++i){
			ret.push_back(_popheap(arr));
		}
		return ret;
	}
private:
	////_swap��������
	//template<typename T>
	//void _Swap(T& left, T& right)
	//{
	//	T temp = left;
	//	left = right;
	//	right = temp;
	//}
	//���µ����㷨 ��С�ѣ�
	void adjustdwon(vector<int>& arr,int root){
		int parents = root;
		//��Ĭ�����ӱȽ�С ����Һ��Ӹ���++child����
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
	//��С��
	void creatheap(vector<int>& arr){
		//С�ѱ���Ҫ��֤������������ΪС�� �������Ǵ����һ����㿪ʼ����
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


//�������� ʵ�ֶ����� ֱ��ѡȡtopk����
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
	//���µ��� ���򽨴��
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
	//����
	void creatheap(vector<int>& arr){
		for (int i = (arr.size() - 1 - 1) / 2; i >= 0; --i){
			adjustdown(arr, arr.size(),i);
		}
	}
	//������
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
������41. �������е���λ��
��εõ�һ���������е���λ����������������ж�����������ֵ����ô��λ������������ֵ����֮��λ���м����ֵ��
������������ж���ż������ֵ����ô��λ������������ֵ����֮���м���������ƽ��ֵ��
���磬
[2,3,4] ����λ���� 3
[2,3] ����λ���� (2 + 3) / 2 = 2.5
���һ��֧���������ֲ��������ݽṹ��
void addNum(int num) - �������������һ�����������ݽṹ�С�
double findMedian() - ����Ŀǰ����Ԫ�ص���λ����
ʾ�� 1��

���룺
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
�����[null,null,null,1.50000,null,2.00000]
*/

/*˼·��ʹ�ô�С������� �ô�Ѵ洢һ���������е����� С�������洢һ���������е��Ұ�� ��Զ���������ѵĴ�Сһ��
���磺12345 �����������ѣ�321  С�ѣ�45  ��ô��λ������3 ����С�ѶѶ�
      12342 ż���������ѣ�21  С�ѣ�34  ��ô��λ��������2+3��/2 ���Ǵ�С�ѶѶ�����λ��
*/
class MedianFinder {
public:
	priority_queue<int> a;//Ĭ�ϴ��
	priority_queue<int, vector<int>, greater<int>> b;//��С��
	void addNum(int num) {
		//ֱ�Ӽӵ���Ѷ�
		a.push(num);
        //ƽ��
		b.push(a.top());//��a�����ķŽ�b ����Ա�֤"С�ѵ�������Զ���ڴ��"
		a.pop();
		//ά�������ѵĴ�Сһ�� 
		if (a.size() < b.size()){
			a.push(b.top());
			b.pop();
		}
	}

	double findMedian() {
		//������ʼֱ�Ӳ����ڴ���� ��Ϊ������a.size()>b.size()����λ��һ���ڴ�Ѷ� ����Ϊ�����Ѷ�Ԫ����ƽ��ֵ
		return a.size()>b.size() ? (double)a.top() : (a.top() + b.top())*0.5;
	}
};
