#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<string>
#include<stdio.h>
using namespace std;
/*
�����㷨�Ļ���ģ��:
  
int check(����)
{
    if(��������)
        return 1;
    return 0;
}
 
void dfs(int step)
{
        �жϱ߽�
        {
            ��Ӧ����
        }
        ����ÿһ�ֿ���
        {
               ����check����
               ���
               ������һ��dfs(step+1)
               �ָ���ʼ״̬�����ݵ�ʱ��Ҫ�õ���
        }
} 
*/
/*
784. ��ĸ��Сдȫ����
����һ���ַ���S��ͨ�����ַ���S�е�ÿ����ĸת���Сд�����ǿ��Ի��һ���µ��ַ������������п��ܵõ����ַ������ϡ�
ʾ��:
����: S = "a1b2"
���: ["a1b2", "a1B2", "A1b2", "A1B2"]
����: S = "3z4"
���: ["3z4", "3Z4"]
����: S = "12345"
���: ["12345"]
ע�⣺
S �ĳ��Ȳ�����12��
S �������ֺ���ĸ��ɡ�
*/
//a-z 97-122  A-Z 65-90
/*
  С���ۣ���A��a���32  A^32 = a   a^32 = A
 ���ӣ�
  1 1 1 1   15 ��10����5
  0 1 0 1
���
  1 0 1 0  8+2 = 10   
*/

//class Solution {
//public:
//	vector<string> ans;
//	vector<string> letterCasePermutation(string S) {
//		dfs(S, 0);
//		return ans;
//	}
//	void dfs(string& S, int index){
//		//���������� ��Ϊ�����޸��Ժ�Ļ�������ȥѰ������������
//		if (index == S.size()){
//			ans.push_back(S);
//			return;
//		}
//		dfs(S, index + 1);
//		//�ж����Ƿ�Ϊ��ĸ 
//		if (isalpha(S[index])){
//			//�ı����Сд
//			S[index] = S[index] ^ 32;
//			//�Ӹ�λ��������֧���б���
//			dfs(S, index+1);
//		}
//	}
//};

//int main(){
//	Solution a;
//	string s("abcd");
//	a.letterCasePermutation(s);
//	return 0;
//}


/*
401. �������ֱ�
�������ֱ����� 4 �� LED ����Сʱ��0-11�����ײ��� 6 �� LED ������ӣ�0-59����
ÿ�� LED ����һ�� 0 �� 1�����λ���Ҳࡣ
���磬����Ķ������ֱ��ȡ ��3:25����
����һ���Ǹ����� n ����ǰ LED ���ŵ��������������п��ܵ�ʱ�䡣
����:
����: n = 1
����: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
ע������:
�����˳��û��Ҫ��
Сʱ�������㿪ͷ������ ��01:00�� �ǲ�����ģ�ӦΪ ��1:00����
���ӱ�������λ����ɣ����ܻ����㿪ͷ������ ��10:2�� ����Ч�ģ�ӦΪ ��10:02����
*/

//�ⷨһ��˫��ѭ���ҳ����н⣨λ���㣩
//��ʽ��һ���ַ���ʹ�ã�sprint()
//class Solution {
//public:
//	vector<string> readBinaryWatch(int num) {
//		vector<string> res ;
//		char s[10];
//		for (int i = 0; i < 12; ++i){
//			for (int j = 0; j < 60; ++j){
//				if (count_one_bits(i)+count_one_bits(j) == num){
//					sprintf(s, "%d:%02d", i, j);
//					res.push_back(s);
//				}
//			}
//		}
//		return res;
//	}
//	int count_one_bits(unsigned int value)
//	{
//		//����һ�����ֵĶ������м���1
//		int count = 0; // ����1�ĸ���
//		for (int i = 0; i < 32; i++){
//			if ((value >> i) & 1){
//				count++;
//			}
//		}
//		return count;
//	}
//};

//�ⷨ�� �����ݷ�
class Solution {
public:
	vector<string> res;
	char tmp[10];
	int flag1 = 0, flag2 = 0;
	vector<string> readBinaryWatch(int num) {
		int arr[10] = { 1, 2, 4, 8, 1, 2, 4, 8, 16, 32 };
		int map[10] = { 0 };
		dfs(num, 0, arr, map);
		return res;
	}
	int check(int* m){
		int flag = 0;
		for (int i = 0; i < 10; ++i){
			if (!m[i]){
				++flag;
			}
		}
		return flag;
	}
	void dfs(int num, int index, int* arr, int*map){
		if (index == 10){
			//������һ��
			if (check(map) == num){
				//��������
				for (int i = 0; i < 4; ++i){
					if (!map[i]){
						flag1 += arr[i];
					}
				}
				for (int j = 4; j < 10; ++j){
					if (!map[j]){
						flag2 += arr[j];
					}
				}
				if (flag1<12 && flag2<60){
					sprintf(tmp, "%d:%02d", flag1, flag2);
					res.push_back(tmp);
				}

				flag1 = 0;
				flag2 = 0;
			}
			return;
		}
		if (map[index] == 0){
			map[index] = 1;
		}
		dfs(num, index + 1, arr, map);
		map[index] = 0;
		dfs(num, index + 1, arr, map);
	}
};


int main(){
	Solution a;
	a.readBinaryWatch(1);
	return 0;
}