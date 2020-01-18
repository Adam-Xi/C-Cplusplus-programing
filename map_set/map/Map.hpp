#pragma once

#include "RBTree.hpp"

namespace K_V
{
	//只需要封装一个红黑树即可
	template<class K, class V>
	class map
	{
		typename typedef std::pair<K, V> ValueType;

		struct KeyOfValue
		{
			const K& operator()(const ValueType& data)
			{
				return data.first;
			}
		};

	public:
		//typename明确告诉编译器是一种类型，否则编译器会将iterator当做静态成员变量（都是通过类名::来访问）来处理
		typename typedef RBTree<ValueType, KeyOfValue>::iterator iterator;
		
	public:
		map()
			: _tree()
		{}

		iterator begin()
		{
			return _tree.begin();
		}

		iterator end()
		{
			return _tree.end();
		}

		std::pair<iterator, bool> insert(const ValueType& data)
		{
			return _tree.Insert(data);
		}

		size_t size()const
		{
			return _tree.size();
		}

		bool empty()const
		{
			return _tree.Empty();
		}

		iterator find(const K& key)
		{
			return _tree.Find(std::make_pair(key, V()));
		}

		V& operator[](const K& key)
		{
			return (*((this->insert(std::make_pair(key, V()))).first)).second;
		}
	private:
		RBTree<ValueType, KeyOfValue> _tree;
	};
}

void TestMap()
{
	K_V::map<std::string, std::string> m;
	m.insert(std::pair<std::string, std::string>("2222", "2222"));
	m.insert(std::make_pair("1111", "1111"));
	m["0000"] = "0000";
	std::cout << m.size() << std::endl;

	for (auto e : m)
	{
		std::cout << e.first << " " << e.second << std::endl;
	}
	std::cout << std::endl;
}