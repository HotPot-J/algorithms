#pragma once
#include<iostream>
#include<vector>
using namespace std;
/*
1.红黑树的性质:
（1）根节点为黑色
（2）最长路径不超过最短路径的一半
例子:
最长路径：黑红黑红（一黑一红）
最短路径: 黑  黑（全黑）
（3）没有连续的红结点
（4）每条路径都有相同数量的黑结点
（AVL树由于平衡因子的存在，其更加平衡
而红黑树靠着颜色和特殊规则保持平衡，没有AVL树效率高
但是AVL树插入数据时发生的旋转太多）
*/

enum Colour{
	BLACK,
	RED,
};

template<class T>
struct RBTreeNode{
	//三叉链
	RBTreeNode<T>* left;
	RBTreeNode<T>* right;
	RBTreeNode<T>* parent;
	//颜色
	Colour _col;
	//数据
	T _data;
	//构造函数
	RBTreeNode(const T& data)
		:left(nullptr)
		, right(nullptr)
		, parent(nullptr)
		, _col(RED)
		, _data(data)
	{}
};


//对应map的迭代器
template<class T>
class _iterator{
	typedef _iterator<T> self;
	typedef RBTreeNode<T> node;
public:
	_iterator(node* a)
		:_node(a)
	{}
	//对应map重载->   (因为map中的T为pair类型)
	T* operator->(){
		return &_node->_data;
	}

	T& operator*(){
		return _node->_data;
	}
	//重载前置++  (采用中序遍历)
	/*
	进行中序遍历++，分为两种情况:（复习时建议画图理解二叉树的中序遍历）
		1.当前节点的右不为空，说明其右还未访问，去寻找其右子树的左，则是中序遍历的下一个位置
		2.当前节点的右为空，说明当前结点已经访问完毕。
			a.若当前结点为其父节点的左，则下一个++位置就是其父节点。
			b.若当前节点为其父结点的右，则下一个++位置并非其父节点，而是把其父结点作为右子树的结点
			综上，当右为空时，应当寻找把当前结点当作左子树的祖先结点
	*/
	self& operator++(){
		if (_node->right){
			node* cur = _node->right;
			while (cur&&cur->left){
				cur = cur->left;
			}
			_node = cur;
		}
		else{
			node* cur = _node;
			node* father = cur->parent;
			while (father&&father->right == cur){
				cur = cur->parent;
				father = father->parent;
			}
			_node = father;
		}
		return *this;
	}
	bool operator!=(const self& s){
		return _node != s._node;
	}
private:
	node* _node;
};


template<class K, class T, class KofV>  //K,代表插入元素的k值，T（可以是pair<K,V>,也可以是K）
//KofV,是一个仿函数，重载()，对应set返回K，对应map返回pair中的K(键值)
class RBTree{
	typedef  RBTreeNode<T> node;
public:
	typedef _iterator<T> iterator;
	iterator begin(){
		node* cur = _root;
		while (cur&&cur->left){
			cur = cur->left;
		}
		return iterator(cur);
	}

	iterator end(){
		return iterator(nullptr);
	}

	//插入
	pair<iterator,bool> Insert(const T& data){
		node* newNode = new node(data); //先造个红黑树结点出来
		if (_root == nullptr){
			//如果插入的结点为第一个结点（根节点）
			_root = newNode;
			_root->_col = BLACK; //满足红黑树的特性，根节点为黑色
			return make_pair(iterator(_root),true);
		}
		//不是第一个节点，则需要用二叉搜索树的规则进行插入
		node* cur = _root;
		node* pre = nullptr; //记录cur上一个结点，以在合适的地方插入
		KofV kf;  //定义一个仿函数类型的变量
		while (cur){
			if (kf(data) < kf(cur->_data)){
				pre = cur;
				cur = cur->left;

			}
			else if (kf(data)>kf(cur->_data)){
				pre = cur;
				cur = cur->right;
			}
			else{
				return make_pair(iterator(cur),false); //由于实现的是set和map 不允许有相等K值出现
			}
		}
		//找到合适的位置了
		if (kf(data) < kf(pre->_data)) {
			pre->left = newNode;
		}
		else{
			pre->right = newNode;
		}
		newNode->parent = pre;
		/*将新插入结点的颜色置为红，有可能打破：不能有连续两个红色结点的特性，从而去进行调整
		 为什么部置为黑色呢？ 红黑树中，有关于黑色结点的性质是：每条路径的黑色结点个数相等，如果这样，几乎每次插入
		 都会打破平衡进行调整，效率变低。
		*/
		newNode->_col = RED;
		//判断是否需要调整
		/*
		  红黑树的调整主要是看其uncle结点的颜色，分为3中情况：
			1.父节点（father）和uncle结点均为红色，那么此时其父节点与uncle结点的祖先结点（grand）必为黑色（因为再插入之前，整棵树是平衡的）
			 这种情况下我们只需要将，father和uncle变为黑色，grand变为红色。
			 但是grand变为红色右分为两种情况：
				（1）grand为根节点：那么直接将grand再变黑，则整棵树符合红黑树特性
				（2）grand不是根节点，那么将其变红，可能会打破grand上一层的平衡，我们需要迭代去处理
			2.不存在uncle和存在uncle为黑，针对grand，father和uncle满足左左/右右（具体见当前目录下画图板）
			3.不能存在uncle和存在uncle为黑，针对grand，father和uncle满足左右/右左（具体见当前目录下画图板）
			2，3情况均需要做旋转处理
		*/
			while (pre&&pre->_col==RED){
				node* grand = pre->parent;
				if (pre == grand->left){
					//左
					node* uncle = grand->right;
					//情况一
					if (uncle&&uncle->_col == RED){
						uncle->_col = BLACK;
						pre->_col = BLACK;
						grand->_col = RED;
						//继续向上迭代处理
						newNode = grand;
						pre = newNode->parent;
					}
					else {
						//由于情况二可能由情况三转变而来，先处理情况三
						if (newNode = pre->right){
							rotateL(pre);
							swap(pre, newNode);
						}
						//第三种情况
						rotateR(grand);
						grand->_col = RED;
						pre->_col = BLACK;
						break;
						/*
						可以直接break的原因是：这里经过旋转，将pre的位置旋转到grand的位置上且将pre置为BLACK，
						对红黑树的性质并无影响，可直接break
						*/
					}
				}
				else{
					//右
					node* uncle = grand->left;
					//情况一
					if (uncle&&uncle->_col == RED){
						uncle->_col = BLACK;
						pre->_col = BLACK;
						grand->_col = RED;
						//继续向上迭代处理
						newNode = grand;
						pre = newNode->parent;
					}
					else {
						//由于情况二可能由情况三转变而来，先处理情况三
						if (newNode = pre->left){
							rotateR(pre);
							swap(pre, newNode);
						}
						//第三种情况
						rotateL(grand);
						grand->_col = RED;
						pre->_col = BLACK;
						break;
					}
				}
			}
			_root->_col = BLACK;//保证根一定为黑色
			return make_pair(iterator(newNode), true);
		}

	//左旋
	void rotateL(node* cur){
		node* curR = cur->right;
		node* curRL = curR->left;
		node* father = cur->parent;

		cur->right = curRL;
		if (curRL){ curRL->parent = cur; }

		curR->left = cur;
		cur->parent = curR;

		if (cur == _root){  //cur为根节点
			_root = curR;
			curR->parent = nullptr;
		}
		else{
			if (father->left == cur){
				father->left = curR;
			}
			else{
				father->right = curR;
			}
			curR->parent = father;
		}
	}
	//右旋
	void rotateR(node* cur){
		node* curL = cur->left;
		node* curLR = curL->right;
		node* father = cur->parent;

		cur->left = curLR;
		if (curLR){ curLR->parent = cur; }

		curL->right = cur;
		cur->parent = curL;

		if (cur == _root){
			_root = curL;
			cur->parent = nullptr;
		}
		else{
			if (father->left == cur){
				father->left = curL;
			}
			else{
				father->right = curL;
			}
			curL->parent = father;
    	}
	}

private:
	node* _root = nullptr;
};