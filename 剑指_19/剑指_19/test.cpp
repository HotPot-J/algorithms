#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>


/*
��������˳��ʹ����λ��ż��ǰ��
����һ���������飬ʵ��һ�����������������������ֵ�˳��ʹ�����е�����λ�������ǰ�벿�֣�
���е�ż��λ������ĺ�벿�֣�����֤������������ż����ż��֮������λ�ò��䡣
*/
/*
˼·�����ò��������˼·���ҵ�������ǰ���ż�����󸲸ǣ����ղ�������
	ʱ�临�Ӷ�O��n^2��
	�ռ临�Ӷ�O��1��
*/
using namespace std;
class Solution1 {
public:
	void reOrderArray(vector<int> &array) {
		if (array.size() <= 1){ return; }
		int end = 0;
		for (int i = 0; i<array.size(); ++i){
			end = i;
			//�ҵ���һ������
			while (end<array.size() && array[end] % 2 == 0){ ++end; }
			if (end >= array.size()){ break; } //����û��������ֱ���˳�
			int tmp = array[end];
			//���ǰ����ż���͸���
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
				//����Ѱ��������Ƚ�
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