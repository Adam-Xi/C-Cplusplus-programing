#pragma once

#include "BitSet.hpp"

// BloomFilter：位图 + 多个哈希函数
template<class Type, class HF1 = Str2INT1, class HF2 = Str2INT2, class HF3 = Str2INT3, class HF4 = Str2INT4, class HF5 = Str2INT5>
class BloomFilter
{
public:
	BloomFilter(size_t size = 10)
		: _bt(10 * size)
		, _size(0)
	{}

	bool Insert(const Type& data)
	{
		//通过不同的哈希函数计算出待插入元素的所有地址
		size_t index1 = HF1()(data) % _bt.size();
		size_t index2 = HF2()(data) % _bt.size();
		size_t index3 = HF2()(data) % _bt.size();
		size_t index4 = HF2()(data) % _bt.size();
		size_t index5 = HF2()(data) % _bt.size();

		//将计算出来的各个地址位置为1
		_bt.set(index1);
		_bt.set(index2);
		_bt.set(index3);
		_bt.set(index4);
		_bt.set(index5);

		_size++;
		return true;
	}

	bool IsIn(const Type& data)
	{
		//通过不同的哈希函数计算出待插入元素的所有地址
		size_t index1 = HF1()(data) % _bt.size();
		if (!_bt.test(index1))
		{
			return false;
		}
		size_t index2 = HF2()(data) % _bt.size();
		if (!_bt.test(index2))
		{
			return false;
		}
		size_t index3 = HF2()(data) % _bt.size();
		if (!_bt.test(index3))
		{
			return false;
		}
		size_t index4 = HF2()(data) % _bt.size();
		if (!_bt.test(index4))
		{
			return false;
		}
		size_t index5 = HF2()(data) % _bt.size();
		if (!_bt.test(index5))
		{
			return false;
		}

		return true;
	}

	size_t Size()const
	{
		return _size;
	}
private:
	xi::bitset _bt;
	size_t _size;
};


void TestBloomFilter()
{
	BloomFilter<std::string> bf;
	bf.Insert("妲己");
	bf.Insert("凯");
	bf.Insert("上官婉儿");

	std::cout << bf.Size() << std::endl;

	if (bf.IsIn("孙策"))
	{
		std::cout << "Has existed" << std::endl;
	}
	else
	{
		std::cout << "Hasn't existed" << std::endl;
	}
	if (bf.IsIn("凯"))
	{
		std::cout << "Has existed" << std::endl;
	}
	else
	{
		std::cout << "Hasn't existed" << std::endl;
	}
}