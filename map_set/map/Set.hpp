#pragma once

#include "RBTree.hpp"

namespace K_V
{
	//只需要封装一个红黑树即可
	template<class K>
	class set
	{
		typedef K ValueType;

		struct KeyOfValue
		{
			const K& operator()(const ValueType& data)
			{
				return data;
			}
		};

	public:
		//typename明确告诉编译器是一种类型，否则编译器会将iterator当做静态成员变量（都是通过类名::来访问）来处理
		typename typedef RBTree<ValueType, KeyOfValue>::iterator iterator;

	public:
		set()
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
			return _tree.Find(key);
		}

	private:
		RBTree<ValueType, KeyOfValue> _tree;
	};
}

void TestSet()
{
	K_V::set<std::string> m;
	m.insert("2222");
	m.insert("1111");
	m.insert("0000");
	std::cout << m.size() << std::endl;

	for (auto e : m)
	{
		std::cout << e << std::endl;
	}
	std::cout << std::endl;
}