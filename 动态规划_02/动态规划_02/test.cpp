#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
/*
һ��unique-paths
���ӣ�https://www.nowcoder.com/questionTerminal/166eaff8439d4cd898e3ba933fbc6358
��Դ��ţ����
һ����������m��n��С�ĵ�ͼ�����Ͻǣ���㣬��ͼ�еı�ǡ�start"��λ�ã���
������ÿ�����»������ƶ���������Ҫ�����ͼ�����½ǡ����յ㣬��ͼ�еı�ǡ�Finish"��λ�ã���
�����ж����ֲ�ͬ��·��������ߵ��յ㣿
*/

/*
˼·һ������ dfs
���޷�AC��ʱ�临�Ӷȹ��ߣ�
*/
class Solution {
public:
	int res = 0;
	bool check(int m,int n,int i,int j){
		if (i >= m ||i<0|| j >= n||j<0){
			return false;
		}
		return true;
	}
	void dfs(int m,int n,int i,int j){
		if (i == m - 1 && j == n - 1){
			++res;
			return;
		}
		//��
		dfs(m, n, i + 1, j);
		dfs(m, n, i, j + 1);
		
	}
	int uniquePaths(int m, int n) {
		dfs(m, n, 0, 0);
		return res;
	}
};

/*
˼·������̬�滮
f(i,j):�����ߵ���i,j�����ж�����·��
f(0,0) = 1;
f(0,1) = 1;
f(1,0) = 1;
f(1,1) = 2;
�ɴ˿ɵ�״̬ת�Ʒ���Ϊ��
	f(i,j) = f(i-1,j)+f(i,j-1)
	��ʼ״̬Ϊ��f(0,0) = 1
*/

class Solution1 {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp;
		dp.resize(m);
		for (int i = 0; i < m; ++i){
			dp[i].resize(n, 0);
		}
		for (int i = 0; i < m; ++i){
			for (int j = 0; j < n; ++j){
				if (i == 0 && j == 0){
					//��ʼ״̬
					dp[i][j] = 1;
				}
				else if (i == 0){
					//��һ��ֻ������
					dp[i][j] = dp[i][j - 1];
				}
				else if (j == 0){
					//��һ��ֻ������
					dp[i][j] = dp[i - 1][j];
				}
				else{
					//��ͨ�������/�ң�
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		return dp[m - 1][n - 1];
	}
};

//int main(){
//	Solution1 a;
//	a.uniquePaths(1, 2);
//	return 0;
//}

/*
����unique-paths-ii
���ӣ�https://www.nowcoder.com/questionTerminal/3cdf08dd4e974260921b712f0a5c8752
��Դ��ţ����
�ȶ�ָ����14177ʱ�����ƣ�C/C++ 1�룬��������2��ռ����ƣ�C/C++ 32M����������64M
�㷨֪ʶ��Ƶ����
����˼����Ŀ"Unique Paths":
�����ͼ�м�����һЩ�ϰ����ж��ٲ�ͬ��·����
�ֱ���0��1�����������ϰ�
����
��ͼ��ʾ��һ���ϰ���3*3��ͼ���롣
[
[0,0,0],
[0,1,0],
[0,0,0]
]
��2����ͬ��·��
��ע��m��n������100.
*/

/*
˼·:��̬�滮
f(i,j):�ߵ�(i,j)λ�õ�·������
״̬ת�Ʒ��̣�
f(i,j) = f(i-1,j)+f(i,j-1)
��ʼ״̬��
���ӣ�
0 0 0 1 0
1
0
0
��Ҫ�ߵ�(0,4)��λ����Ҫ��֤��֮ǰ��·����û���ϰ� ���� map[0][4]==0&&map[0][i] i<4 
��Ҫ�ߵ�(3,0)��λ����Ҫ��֤��֮ǰ��·����û���ϰ� ���� map[3][0]==0&&map[i][0] i<3
�ܽ��ʼ��״̬��Ҫ���������:
	i = 0: map[0][i]==0 && map[0][j]==0 &&(j<i)
	i = 0: map[i][0]==0 && map[j][0]==0 &&(j<i)
*/
class Solution3{
public:
	int uniquePathsWithObstacles(vector<vector<int> >& obstacleGrid) {
		if (obstacleGrid.empty()||obstacleGrid[0][0]==1){ return 0; }
		int row = obstacleGrid.size(), col = obstacleGrid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
	/*	dp.resize(row);
		for (int i = 0; i < row; ++i){
			dp[i].resize(col, 0);
		}*/
		//��ʼ��״̬
		for (int i = 0; i < col; ++i){
			//��һ��
			if (obstacleGrid[0][i] == 0) {
				dp[0][i] = 1;
			}
			else break;
		}
		for (int i = 0; i < row; ++i){
			//��һ��
			if (obstacleGrid[i - 1][0] == 0){
				dp[i][0] = 1;
			}
			else break;
		}
		for (int i = 1; i < row; ++i){
			for (int j = 1; j < col; ++j){
				if (obstacleGrid[i][j] == 0){
					//��ǰ�㲢��·��
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		return  dp[row - 1][col - 1];
	}
};

/*
������Ȩֵ����С·����
���ӣ�https://www.nowcoder.com/questionTerminal/23462ed010024fcabb7dbd3df57c715e
��Դ��ţ����
����һ���ɷǸ���������m x n�Ķ�ά���飬����Ҫ�Ӷ�ά��������Ͻ��ߵ����½ǣ����ҳ�·���ϵ���������֮����С��·����
ע�⣺��ÿ��ֻ�����»������ƶ���
ʾ��1
����
[[1,2],[5,6],[1,1]]
���
8
*/
/*
˼·:
״̬ f(i,j)����ʾ��i,j����ǰ���Ȩֵ��
����ֻ�������ƶ�(��ʼ״̬)��
	i = 0  f(0,j) = f(0,j-1)+arr[0,j] 
	j = 0  f(i,0) = f(i-1,0)+arr[i,0]
��ͨ״̬:
	f(i,j) = min(f(i-1,j),f(i,j-1))+arr[i,j]
*/

class Solution12{
public:
	int minPathSum(vector<vector<int> >& grid) {
		if (grid.empty()){ return 0; }
		int row = grid.size(), col = grid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		//��ʼ״̬
		dp[0][0] = grid[0][0];
		for (int i = 1; i < col; ++i){
			//��һ��
			dp[0][i] = dp[0][i - 1] + grid[0][i];
		}
		for (int i = 1; i < row; ++i){
			dp[i][0] = dp[i - 1][0] + grid[i][0];
		}
		for (int i = 1; i < row; ++i){
			for (int j = 1; j < col; ++j){
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
			}
		}
		return dp[row - 1][col - 1];
	}
};

/*
�ġ���������
��N����Ʒ��һ������ΪV�ı�������i����Ʒ�ļ�ֵ��C[i]��������W[i]����⽫��Щ��Ʒװ�뱳����ʹ��ֵ�ܺ����
���ӣ�https://www.nowcoder.com/questionTerminal/3ee42c9155c340588729995561ace594
��������:
�����һ���� N V (1 <=N <=500) (1<= V <= 10000)
���� N�� �������� ���� C W (1 <= C <= 50000, 1 <= W <=10000)
�������:
�������ֵ
��:
5 10
8 6
10 4
4 2
5 4
5 3
���
19
*/

/*
˼·:
	Ŀ��: ������СΪVʱ����n����Ʒ����ѡ��ʹ����Ʒ�ܼ�ֵ���
	״̬��������Ӱ�����ս���������������Ʒ��ֵc����Ʒ�Ĵ�Сw
	f(i,j)��ʾ���ڿ��ǵ�i����Ʒʱ��������СΪjʱ������ֵ
	���ۣ�
		������뵱ǰ��Ʒ��
			1.w[i]<=j ���ԷŽ�ȥ���ó�֮ǰһ������Ʒ�õ�ǰ��Ʒ�Ž�ȥ��
			2.w[i]>j  ���ܷŽ�ȥ
	���ԣ�                           ����        �ţ���ζ�ſ����ó�֮ǰ�Ĳ�����Ʒ��
	   ��w[i]<=jʱ ��f(i,j) = max( f(i-1,j) , f(i-1,j-w[i])+c[i] ) (�ӷţ�������Ҫȡ��֮ǰ�Ĳ�����Ʒ���ټ��ϵ�ǰ��Ʒ��ֵ���Ͳ�����ѡ��һ����ֵ�ϴ��)
	   ��w[i]>jʱ  ��f(i,j) = f(i-1,j)   ��ֻ�в��ŵ������
		
*/

//int main(){
//	int N = 0, V = 0;
//	while (cin >> N >> V){
//		vector<vector<int>> store(N + 1, vector<int>(2, 0));
//		int c = 0, w = 0;//��ֵ������
//		for (int i = 1; i <= N; ++i){
//			cin >> c >> w;
//			store[i][0] = c; //��ֵ
//			store[i][1] = w; //����
//		}
//		vector<vector<int>> dp(N + 1, vector<int>(V + 1, 0));
//		//i����ڼ�����Ʒ j����ǰ����
//		for (int i = 1; i <= N; ++i){
//			for (int j = 1; j <= V; ++j){
//				if (store[i][1] <= j){
//					//��ǰ��Ʒ�������ԷŽ�����
//					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - store[i][1]] + store[i][0]);
//				}
//				else{
//					//��ǰ��Ʒ���������ԷŽ�����
//					dp[i][j] = dp[i - 1][j];
//				}
//			}
//		}
//		cout << dp[N][V] << endl;
//	}
//	return 0;
//}

/*
�塢palindrome-partitioning-ii 
  ��һ���ַ���s���ָ�sʹ�÷ָ����ÿһ���Ӵ����ǻ��Ĵ�
  ���㽫�ַ���s�ָ�ɻ��ķָ�������С�и���
  ����:�����ַ���s="aab",
  ����1����Ϊ���ķָ���["aa","b"]���и�һ�����ɵġ�
*/

/*
(ע�⣺ţ����ʹ��strsub�����и�Ĳ����ַ��������ܽ������ô��ݸ���������)
˼·:
	f(i):��ǰλ���п���ǰi���ַ��Ƿ��ܹ��ɻ��Ĵ�
	����: aaba
	f(0): |aaba 0
	f(1)  a|aba  a�ǻ��� 1
	f(2)  f(1)|a|ba �� 2   aa|ba ��1   min(2,1) = 1
	f(3)  ����f(1)�Ľ�� a|ab|a�������ɻ��ģ�   f(2)|b|a ���ɻ��ģ�f(2)+1 = 2
	f(4)  f(1)|aba:1   f(2)|ba|�������ɻ��ģ�   f(3)|b|a| f(3)+1 = 3   min(1,3) = 1
���ƹ�ʽ:
	f(i) = (j<i)&&f(j)&&[j+1,i]+1)
*/
class Solution100{
public:
	bool isPalindrome(string s){
		string tmp = s;
		reverse(tmp.begin(), tmp.end());
		if (strcmp(tmp.c_str(), s.c_str()) == 0){
			return true;
		}
		return false;
	}
	int minCut(string s) {
		if (s.empty()){ return 0; }
		int len = s.size();
		vector<int>dp(len, 0);
		for (int i = 0; i < len; ++i){
			if (isPalindrome(s.substr(0, i + 1))){
				//����������һ�����Ĵ��Ͳ����и�
				dp[i] = 0;
			}
			else{
				//���岻�Ǿ���Ҫ�õ�֮ǰ��״̬
				int min = INT_MAX;
				for (int j = i - 1; j >= 0; --j){
					if (isPalindrome(s.substr(j + 1, i - j))){
						//[j+1,i]��һ�����Ĵ���ά��min
						if (dp[j] + 1 < min){
							min = dp[j] + 1;
						}
					}
				}
				dp[i] = min;
			}
		}
		return dp[len - 1];
	}
};

//int main(){
//	string s("aaba");
//	Solution100 a;
//	a.minCut(s);
//	return 0;
//}

/*
aaba
��������ʱ�临�ӶȽϸߣ����ǿ��Խ�ÿ�������Ƿ�Ϊ���Ĵ���״̬���������������Ż�
����:����[i,j]�Ƿ�Ϊ���Ĵ�
״̬��f(i,j)������[i,j]�Ƿ�Ϊ���Ĵ�
   ͨ���ж�һ���ַ����Ƿ�Ϊ���ģ�������ײָ��ķ�������
   f(i,j)�Ƿ�Ϊ���ģ�ֻ��Ҫ���㣺f(i+1,j-1)Ϊ����&&s[i]==[j]
   ����״̬ת�Ʒ���Ϊ��
   f(i,j):f(i-1,j-1)&&s[i]==s[j]
  ��ʼ״̬��
   ����������ַ���f(i,j):s[i]==s[j]
   �����ַ���f(i,i) ��true
*/

vector<vector<bool>> isPal(string& s){
	int len = s.size();
	vector<vector<bool>> pMat(len, vector<bool>(len, false));
	for (int i = len-1; i >=0 ; ++i){
		for (int j = i; j < len; ++j){
			if (i == j){
				pMat[i][j] = true; //���ַ�����
			}
			else if (i + 1 == j){
				pMat[i][j] = s[i] == s[j];//˫�ַ�����
			}
			else{
				pMat[i][j] = pMat[i + 1][j - 1] && (s[i] == s[j]);
			}
		}
	}
	return pMat;
}

