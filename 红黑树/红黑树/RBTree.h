#pragma once
#include<iostream>
#include<vector>
using namespace std;
/*
1.�����������:
��1�����ڵ�Ϊ��ɫ
��2���·�����������·����һ��
����:
�·�����ں�ں죨һ��һ�죩
���·��: ��  �ڣ�ȫ�ڣ�
��3��û�������ĺ���
��4��ÿ��·��������ͬ�����ĺڽ��
��AVL������ƽ�����ӵĴ��ڣ������ƽ��
�������������ɫ��������򱣳�ƽ�⣬û��AVL��Ч�ʸ�
����AVL����������ʱ��������ת̫�ࣩ
*/

enum Colour{
	BLACK,
	RED,
};

template<class T>
struct RBTreeNode{
	//������
	RBTreeNode<T>* left;
	RBTreeNode<T>* right;
	RBTreeNode<T>* parent;
	//��ɫ
	Colour _col;
	//����
	T _data;
	//���캯��
	RBTreeNode(const T& data)
		:left(nullptr)
		, right(nullptr)
		, parent(nullptr)
		, _col(RED)
		, _data(data)
	{}
};


//��Ӧmap�ĵ�����
template<class T>
class _iterator{
	typedef _iterator<T> self;
	typedef RBTreeNode<T> node;
public:
	_iterator(node* a)
		:_node(a)
	{}
	//��Ӧmap����->   (��Ϊmap�е�TΪpair����)
	T* operator->(){
		return &_node->_data;
	}

	T& operator*(){
		return _node->_data;
	}
	//����ǰ��++  (�����������)
	/*
	�����������++����Ϊ�������:����ϰʱ���黭ͼ�������������������
		1.��ǰ�ڵ���Ҳ�Ϊ�գ�˵�����һ�δ���ʣ�ȥѰ�����������������������������һ��λ��
		2.��ǰ�ڵ����Ϊ�գ�˵����ǰ����Ѿ�������ϡ�
			a.����ǰ���Ϊ�丸�ڵ��������һ��++λ�þ����丸�ڵ㡣
			b.����ǰ�ڵ�Ϊ�丸�����ң�����һ��++λ�ò����丸�ڵ㣬���ǰ��丸�����Ϊ�������Ľ��
			���ϣ�����Ϊ��ʱ��Ӧ��Ѱ�Ұѵ�ǰ��㵱�������������Ƚ��
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


template<class K, class T, class KofV>  //K,�������Ԫ�ص�kֵ��T��������pair<K,V>,Ҳ������K��
//KofV,��һ���º���������()����Ӧset����K����Ӧmap����pair�е�K(��ֵ)
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

	//����
	pair<iterator,bool> Insert(const T& data){
		node* newNode = new node(data); //����������������
		if (_root == nullptr){
			//�������Ľ��Ϊ��һ����㣨���ڵ㣩
			_root = newNode;
			_root->_col = BLACK; //�������������ԣ����ڵ�Ϊ��ɫ
			return make_pair(iterator(_root),true);
		}
		//���ǵ�һ���ڵ㣬����Ҫ�ö����������Ĺ�����в���
		node* cur = _root;
		node* pre = nullptr; //��¼cur��һ����㣬���ں��ʵĵط�����
		KofV kf;  //����һ���º������͵ı���
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
				return make_pair(iterator(cur),false); //����ʵ�ֵ���set��map �����������Kֵ����
			}
		}
		//�ҵ����ʵ�λ����
		if (kf(data) < kf(pre->_data)) {
			pre->left = newNode;
		}
		else{
			pre->right = newNode;
		}
		newNode->parent = pre;
		/*���²��������ɫ��Ϊ�죬�п��ܴ��ƣ�����������������ɫ�������ԣ��Ӷ�ȥ���е���
		 Ϊʲô����Ϊ��ɫ�أ� ������У��й��ں�ɫ���������ǣ�ÿ��·���ĺ�ɫ��������ȣ��������������ÿ�β���
		 �������ƽ����е�����Ч�ʱ�͡�
		*/
		newNode->_col = RED;
		//�ж��Ƿ���Ҫ����
		/*
		  ������ĵ�����Ҫ�ǿ���uncle������ɫ����Ϊ3�������
			1.���ڵ㣨father����uncle����Ϊ��ɫ����ô��ʱ�丸�ڵ���uncle�������Ƚ�㣨grand����Ϊ��ɫ����Ϊ�ٲ���֮ǰ����������ƽ��ģ�
			 �������������ֻ��Ҫ����father��uncle��Ϊ��ɫ��grand��Ϊ��ɫ��
			 ����grand��Ϊ��ɫ�ҷ�Ϊ���������
				��1��grandΪ���ڵ㣺��ôֱ�ӽ�grand�ٱ�ڣ������������Ϻ��������
				��2��grand���Ǹ��ڵ㣬��ô�����죬���ܻ����grand��һ���ƽ�⣬������Ҫ����ȥ����
			2.������uncle�ʹ���uncleΪ�ڣ����grand��father��uncle��������/���ң��������ǰĿ¼�»�ͼ�壩
			3.���ܴ���uncle�ʹ���uncleΪ�ڣ����grand��father��uncle��������/���󣨾������ǰĿ¼�»�ͼ�壩
			2��3�������Ҫ����ת����
		*/
			while (pre&&pre->_col==RED){
				node* grand = pre->parent;
				if (pre == grand->left){
					//��
					node* uncle = grand->right;
					//���һ
					if (uncle&&uncle->_col == RED){
						uncle->_col = BLACK;
						pre->_col = BLACK;
						grand->_col = RED;
						//�������ϵ�������
						newNode = grand;
						pre = newNode->parent;
					}
					else {
						//��������������������ת��������ȴ��������
						if (newNode = pre->right){
							rotateL(pre);
							swap(pre, newNode);
						}
						//���������
						rotateR(grand);
						grand->_col = RED;
						pre->_col = BLACK;
						break;
						/*
						����ֱ��break��ԭ���ǣ����ﾭ����ת����pre��λ����ת��grand��λ�����ҽ�pre��ΪBLACK��
						�Ժ���������ʲ���Ӱ�죬��ֱ��break
						*/
					}
				}
				else{
					//��
					node* uncle = grand->left;
					//���һ
					if (uncle&&uncle->_col == RED){
						uncle->_col = BLACK;
						pre->_col = BLACK;
						grand->_col = RED;
						//�������ϵ�������
						newNode = grand;
						pre = newNode->parent;
					}
					else {
						//��������������������ת��������ȴ��������
						if (newNode = pre->left){
							rotateR(pre);
							swap(pre, newNode);
						}
						//���������
						rotateL(grand);
						grand->_col = RED;
						pre->_col = BLACK;
						break;
					}
				}
			}
			_root->_col = BLACK;//��֤��һ��Ϊ��ɫ
			return make_pair(iterator(newNode), true);
		}

	//����
	void rotateL(node* cur){
		node* curR = cur->right;
		node* curRL = curR->left;
		node* father = cur->parent;

		cur->right = curRL;
		if (curRL){ curRL->parent = cur; }

		curR->left = cur;
		cur->parent = curR;

		if (cur == _root){  //curΪ���ڵ�
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
	//����
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