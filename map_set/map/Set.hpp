#pragma once

#include "RBTree.hpp"

namespace K_V
{
	//ֻ��Ҫ��װһ�����������
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
		//typename��ȷ���߱�������һ�����ͣ�����������Ὣiterator������̬��Ա����������ͨ������::�����ʣ�������
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