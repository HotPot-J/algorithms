#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<vector>
#include<queue>
#include <functional> 
using namespace std;


/*
1.如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。我们使用Insert()方法读取数据流，
使用GetMedian()方法获取当前读取数据的中位数。
*/

/*
思路：
1.建大小堆
2.维护大堆的所有值小于小堆
3.维护小堆的值大于大堆
(每次插入都用当前最大值给小堆插  当前最小值给大堆插入 保证插入第奇数个是先放进大堆再从大堆找最大插入min中
插入第偶数个 先放入小堆 从小堆最小的给大堆)
这样就保证了 大堆<小堆恒成立
总数为奇数个：中位数 = min.top()
偶数个：中位数= (max.top()+min.top())/2
*/
class Solution {
public:
	Solution()
		:flag(0)
	{}
	void Insert(int num)
	{
		if (flag % 2 == 0){
			max.push(num);
			//将大堆中的最大值给小堆
			min.push(max.top());
			max.pop();
		}
		else{
			min.push(num);
			//将小堆中最大的给大堆
			max.push(min.top());
			min.pop();
		}
		++flag;
	}

	double GetMedian()
	{
		if (flag % 2){
			return (double)min.top();
		}
		return (double)(max.top() + min.top()) / 2;
	}
private:
	int flag;
	priority_queue<int> max;
	priority_queue<int, vector<int>, greater<int>> min;
};


/*
题目描述：二叉搜索树的第k小节点
给定一棵二叉搜索树，请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8） 
中，按结点数值大小顺序第三小结点的值为4。
*/


struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};


/*
思路：
1、二叉搜索数的性质就是中序遍历有序（降序），将结果push
2、 k-1次就是第k小的值
3.注意：可能传进来的指针为空，或者k越界
*/

//递归中序遍历版本
class Solution {
public:
	void fun(TreeNode*cur, vector<TreeNode*>&s){
		if (cur == NULL){ return; }
		fun(cur->left, s);
		s.push_back(cur);
		fun(cur->right, s);
	}
	TreeNode* KthNode(TreeNode* pRoot, int k)
	{
		if (pRoot == NULL || k <= 0){ return NULL; }
		vector<TreeNode*> s;
		fun(pRoot, s);
		if (k>s.size()){
			return NULL;
		}
		return s[k - 1];
	}
};

//非递归中序遍历版本 利用栈 模拟递归的过程

class Solution {
public:

	void MidOrder(TreeNode* cur,stack<TreeNode*>& s,vector<TreeNode*>& res){
		while (cur || !s.empty){
			while (cur){
				s.push(cur);
				cur = cur->left;
			}
			TreeNode* top = s.top();
			s.pop();
			res.push_back(top);
			cur = top->right;
		}
	}

	TreeNode* KthNode(TreeNode* pRoot, int k)
	{
		if (pRoot == NULL || k <= 0){ return NULL; }
		vector<TreeNode*> res;
		stack<TreeNode*> s;
		MidOrder(pRoot, s, res);
		if (k > res.size()){ return NULL; }
		return res[k - 1];
	}
};