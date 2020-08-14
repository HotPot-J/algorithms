#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;

/*
��Ŀ���� ��ת�������С����
��һ�������ʼ�����ɸ�Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת��
����һ���ǵݼ�����������һ����ת�������ת�������СԪ�ء�
��������{3,4,5,1,2}Ϊ{1,2,3,4,5}��һ����ת�����������СֵΪ1��
NOTE������������Ԫ�ض�����0���������СΪ0���뷵��0��
*/

/*
˼·һ���ռ临�Ӷ�0(1) ʱ�临�Ӷ�0(N)
1.���������ҵ���һ���ǵ�����λ�ã�����
2.�������������ǵ����ģ���ôֱ�ӷ��ص�һ�����ּ��ɣ�˵��û��ת��
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
˼·:���ֲ��ҿռ临�Ӷ�O(1) ʱ�临�Ӷ�(logN)
1.��������ָ��ָ������left�������ң�right��
2.��Ȼ���ҵ���һ���ǵ�����λ��
*/

class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.size() == 0){ return 0; }
		//�����ߴ����ұߣ����䲻���ڣ����ڼ��ǵ�һ���ǵ�����λ�ã�
		int left = 0, right = rotateArray.size() - 1, mid = -1;
		while (rotateArray[left] >= rotateArray[right]){
			if (right - left == 1){
				mid = right;
				break;
			}
			mid = left + (right - left) / 2;
			if (rotateArray[mid] >= rotateArray[left]){
				//˵��left��mid���ǵ����� ����left�ִ���right
				left = mid;
			}
			if (rotateArray[mid] <= rotateArray[right]){
				//˵��mid��right�ǵ����ģ�����left�ִ���right
				//���Ȼ����ת����ģ�����rightֱ�ӵ�mid��λ��
				right = mid;
			}
		}
		return rotateArray[mid];
	}
};

/*
��Ŀ���� ���θ���
���ǿ�����2*1��С���κ��Ż�������ȥ���Ǹ���ľ��Ρ�������n��2*1��С�������ص��ظ���һ��2*n�Ĵ���Σ��ܹ��ж����ַ�����

����n=3ʱ��2*3�ľ��ο���3�ָ��Ƿ�����
*/

/*
˼·����쳲���������д���ˣ��ÿռ任ʱ��....
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