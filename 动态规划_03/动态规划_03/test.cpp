#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;     

/*
һ��edit-distance
���ӣ�https://www.nowcoder.com/questionTerminal/81d7738f954242e5ade5e65ec40e5027
��Դ��ţ����

������������word1��word2������㽫word1ת��Ϊword2������Ҫ���ٲ�������
����Զ�һ������ִ������3�ֲ�����
a���ڵ����в���һ���ַ�
b��ɾ�������е�һ���ַ�
c���滻�����е�һ���ַ�
-------------
ʾ��1
����
"b",""
���
1
-------------
ʾ��2
����
"ab","bc"
���
2
*/
/*
˼·:
s1:ab --> s2:cdab

״̬f(i,j)��ʾs1ǰi���ַ�ת����s2ǰj���ַ�����Ҫ�Ĳ���
f(1,1):����a->c ��Ҫ1�� ���滻��
f(1,2):����a->cd ����f(1,1)��״̬���ٲ���d����
f(1,3):����a->cda ����f(1,2)��״̬���ٲ���a����...
f(2,2):����ab->cd ����f(1,1)��״̬���ٽ�b�滻Ϊb����
f(2,1):����ab->c  ����f(1,1)��״̬���ٽ�bɾ��
...

�ɵ�״̬ת�Ʒ���:
	s1[i]==s2[i]: f(i,j) = min(dp[i-1][j-1],dp[i-1][j],dp[i][j])
	s1[i]!=s2[i]: f(i,j) = min(dp[i-1][j-1],dp[i-1][j],dp[i][j])
*/
class Solution {
public:
	int _min(int a, int b, int c){
		int tmp = min(a, b);
		return min(tmp, c);
	}
	int minDistance(string word1, string word2) {
		if (word1.empty() && word2.empty()){ return 0; }
		if (word1.empty()){ return word2.size(); }
		if (word2.empty()){ return word1.size(); }
		int len1 = word1.size(), len2 = word2.size();
		vector<vector<int>> dp(len1+1, vector<int>(len2+1, 0));
		
		for (int i = 1; i <= len1; ++i){
				if (word1[i-1] == word2[0]){
					dp[i][1] = dp[i - 1][1];
				}
				else{
					dp[i][1] = dp[i - 1][1]+1; 
				}
		}

		for (int j = 1; j <= len2; ++j){
			if (word1[0] == word2[j-1]){
				dp[1][j] = dp[1][j-1];
			}
			else{
				dp[1][j] = dp[1][j-1]+1;
			}
		}

		for (int i = 2; i <= len1; ++i){
			for (int j = 2; j <= len2; ++j){
				if (word1[i-1] == word2[j-1]){
					dp[i][j] = _min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]);
				}
				else{
					dp[i][j] = _min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]) + 1;
				}
			}
		}
		return dp[len1][len2];
	}
};

//int main(){
//	string s1 = "ab";
//	string s2 = "cdab";
//	Solution a;
//	a.minDistance(s1, s2);
//	return 0;
//}

/*
����distinct-subsequences����ͬ�����и�����
���ӣ�https://www.nowcoder.com/questionTerminal/ed2923e49d3d495f8321aa46ade9f873
��Դ��ţ����

���������ַ���S��T������S�����е���T�Ĳ�ͬ�����и����ж��ٸ���
�ַ���������������ԭ�����ַ���ɾ��һЩ�ַ���Ҳ���Բ�ɾ�����ڲ��ı����λ�õ�����µ�ʣ���ַ�
�����磬"ACE"is a subsequence of"ABCDE"����"AEC"���ǣ�
���磺
S ="rabbbit", T ="rabbit"
����3
*/
/*
˼·��
Ŀ�꣺Ѱ��S�����е���T�Ĳ�ͬ�����и����ж��ٸ�
״̬��f(i,j) = sǰi-1���ַ� �� j-1���ַ���ͬ���Ӵ�����
���ӣ� s:rabbbit t:rabbit
^        ^
i        j
��s[i]==t[i]��
�Ե�ǰi j��ָ���b��Ϊ��β��������Ҫ�ҵ�s��ǰi-1���ַ�����ra����f(i-1,j-1)
��s[i-1]��Ӧ��b��β��������Ҫ�ҵ�s��ǰi-1���ַ�����rab��:f��i-1��j��
�������������b��ͬ�������ǲ�ͬ�������������Ӧ�����:
f(i,j) = f(i-1,j-1)+f(i-1,j)
��s[i]!=t[i]
����Ӧ��Ѱ��s��ǰi-1���ַ�����Ӧ��tǰj���ַ�����f(i-1,j)
f(i,j) = f(i-1,j-1)
��ʼ״̬��
f(i,0):��s��ǰi���ַ���Ѱ�����Ӵ�������ַ�����ȣ��ռ� ���ܹ��ҵ�-��1
f(0,j):�ӿմ���Ѱ���Ӵ�����ǿմ���ȣ��Ҳ���-��0

*/

class Solution {
public:
	int numDistinct(string S, string T) {
		int len1 = S.size(), len2 = T.size();
		//��ʼ��dp
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		for (int i = 0; i <= len1; ++i){
			dp[i][0] = 1;
		}
		for (int i = 1; i <= len1; ++i){
			for (int j = 1; j <= len2; ++j){
				if (S[i - 1] == T[j - 1]){
					dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
				}
				else{
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
		return dp[len1][len2];
	}
};
//int main(){
//	Solution2 a;
//	a.numDistinct("b", "b");
//	return 0;
//}

//�氲�ű��ԣ���������̬�滮�⣩
/*
����
��˾��һ��¥�ݣ�ͬ����ÿ����̫����������ʱ��һ����һ��̨�ף���ʱ��һ��������̨�ס�
���������n��̨�ף�ͬ���ж�������¥�ݵķ�����?(Ϊ�˲���ͬ��̫�ۣ����36��̨��)
*/
/*
˼·����̬�滮
f(i) = f(i-1)+f(i-2)
*/
int main(){
	int n = 0;
	while (cin >> n){
		if (n <= 0){
			cout << 0 << endl;
		}
		else{
			vector<int> dp(n + 1, 0);
			//��ʼ״̬
			dp[0] = 1;
			dp[1] = 1;//�����һ��̨��ֻ��һ�ַ���
			for (int i = 2; i <= n; ++i){
				dp[i] = dp[i - 1] + dp[i - 2];
			}
			cout << dp[n] << endl;
		}
	}
	return 0;
}

/*
һ�����иĽ�����һ�ŷ�����Ҫ��Ǩ������������Ҫ��������׷��ӡ�
Ҫ��:
    1.��֤ÿ��ס����������һ�׷���
	2.���ڷ��ӣ������ס��������ķ�������Ҫ����ס�������ٵķ��ӡ�
	3.�����Ƿ����ڣ�������ͬ�ķ��ӣ����䵽�ķ����������Բ�ͬ��
*/
/*
˼·����̬�滮��
��arr[i-1]<arr[i]: f(i) = f(i-1)+1
��arr[i-1]>arr[i]: s) = f(i)+1
��ʼ״̬��ÿ�����ȷ�һ�׷��� ��֤���ٷ�һ��
*/
class Solution {
public:
	int house(int* person, int personLen) {
		if (personLen == 0 || person == NULL){ return 0; }
		if (personLen == 1){ return 1; }
		vector<int>dp(personLen + 1, 1);
		for (int i = 2; i <= personLen; ++i){
			if (person[i - 1] == 0){
				dp[i] = 0;
			}
			else if (person[i - 2] < person[i - 1]){
				dp[i] = dp[i - 1] + 1;
			}
			else if (person[i - 2] > person[i - 1]){
				dp[i - 1] = dp[i] + 1;
			}
		}
		long res = 0;
		for (int i = 1; i <= personLen; ++i){
			res += dp[i];
		}
		return res;
	}
};