#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

/*
22. ��������
���� n �����������ŵĶ������������һ�������������ܹ��������п��ܵĲ��� ��Ч�� ������ϡ�
ʾ����
���룺n = 3
�����[
"((()))",
"(()())",
"(())()",
"()(())",
"()()()"
]
*/

/*
˼·�����ݷ� ͨ��left��right�ֱ��жϵ�ǰ�������ŵķ�����������left<n �ſɷ���(   ��right<left�ſɷ��� )
ͨ������ȥѰ�Ҹ��ֿ��ܽ�
*/
//class Solution {
//public:
//	vector<string> res;
//	string tmp;
//	vector<string> generateParenthesis(int n) {
//		fun(0, 0, n);
//		return res;
//	}
//	void fun(int left, int right, int n){
//		if (left == n&&right == n){
//			res.push_back(tmp);
//			return;
//		}
//		if (left < n){
//			tmp += '(';
//			fun(left + 1, right, n);
//			tmp.pop_back();
//		}
//		if (right < left){
//			tmp += ')';
//			fun(left, right + 1, n);
//			tmp.pop_back();
//		}
//	}
//};

//int main(){
//	Solution a;
//	a.generateParenthesis(3);
//	return 0;
//}

/*
89. ���ױ���
���ױ�����һ������������ϵͳ���ڸ�ϵͳ�У�������������ֵ����һ��λ���Ĳ��졣
����һ�����������λ���ķǸ����� n����ӡ����ױ������С���ʹ�ж����ͬ�𰸣���Ҳֻ��Ҫ��������һ�֡�
���ױ������б����� 0 ��ͷ��
ʾ�� 1:
����: 2
���: [0,1,3,2]
����:
00 - 0
01 - 1
11 - 3
10 - 2
���ڸ����� n������ױ������в���Ψһ��
���磬[0,2,3,1] Ҳ��һ����Ч�ĸ��ױ������С�
00 - 0
10 - 2
11 - 3
01 - 1
ʾ�� 2:
����: 0
���: [0]
����: ���Ƕ�����ױ������б����� 0 ��ͷ��
����������λ��Ϊ n �ĸ��ױ������У��䳤��Ϊ 2^n���� n = 0 ʱ������Ϊ 2^0 = 1��
��ˣ��� n = 0 ʱ������ױ�������Ϊ [0]��
*/

/*
˼·��  ����������ϵĴ��� ����ⷨ��ʵ�Լ�û�����
  �� nn �׸����뼯��Ϊ G(n)G(n)���� G(n+1)G(n+1) �׸�����Ϊ��
�� G(n)G(n) �׸�����ÿ��Ԫ�ض�������ʽǰ����� 00���õ� G'(n)G ��(n)��
�� G(n)G(n) ���ϵ��򣨾���Ϊ R(n)R(n)���� R(n)R(n) ÿ��Ԫ�ض�������ʽǰ����� 11���õ� R'(n)R ��(n)��
G(n+1) = G'(n) �� R'(n)G(n+1)=G ��(n)��R ��(n) ƴ���������ϼ��ɵõ���һ�׸����롣
�������Ϲ��ɣ��ɴ� 00 �׸������Ƶ����κν׸����롣

n = 0  �� 0
n = 1  �� 0                 1
n = 2  �� 00  01            11 10
n = 3  �� 000 001 011       111 101 100
*/
class Solution {
public:
	vector<int> grayCode(int n) {
		vector<int> res;
		res.push_back(0);
		int head = 1;
		for (int i = 0; i < n; ++i){
			for (int j = res.size() - 1; j >= 0; --j){ //�������
				//Ϊ����λ���1
				int tmp = res[j] | head;
				res.push_back(tmp);
			}
			head <<= 1; //head�Ŵ�һλ  
		}
		return res;
	}
};

