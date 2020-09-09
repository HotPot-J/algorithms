#pragma once
#include"RBTree.h"
#include<string>
namespace jxy{
	template<class K,class V>
	class _map{
	public:
		//仿函数 返回T（pair<K,V>中V的值）
		struct MapKeyOfT{
			const K& operator()(const pair<K, V>& _pair){
				return _pair.first;
			}
		};
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;
		iterator begin(){
			return _t.begin();
		}
		iterator end(){
			return _t.end();
		}
		
		pair<iterator, bool>  Insert(const pair<K, V>& kv){
			return _t.Insert(kv);
		}

		//利用插入重载[]：插入成功返回pair<iterator,true> 失败返回pair<itreator,true>
		V& operator[](const K& key){
			pair<iterator, bool> ret = _t.Insert(make_pair(key, V()));
			return (ret.first)->second;
		}
	private:
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};

	void test_map(){
		_map<int, int> m;
		m.Insert(make_pair(1, 1));
		m.Insert(make_pair(3, 3));
		m.Insert(make_pair(10, 10));
		m.Insert(make_pair(5, 5));
		m.Insert(make_pair(6, 6));
		_map<int, int>::iterator it = m.begin();
		while (it != m.end()){
			cout << it->first << ": " << it->second << endl;
			++it;
		}

		string strs[] = { "黄瓜", "香蕉", "葡萄", "黄瓜", "黄瓜" };
		_map<string, int> countMap;
		for (auto& str : strs){
			countMap[str]++;
		}

		for (auto e : countMap){
			cout << e.first << ": " << e.second << endl;
		}
	}
}