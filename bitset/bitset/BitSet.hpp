#pragma once

#include <iostream>
#include <vector>

namespace xi
{
	class bitset
	{
	public:
		bitset(size_t bitCount)
			: _set(bitCount / 8 + 1)
			, _bitCount(bitCount)
		{}

		//置1
		void set(size_t which)
		{
			if (which >= _bitCount)
			{
				return;
			}
			//计算对应的字节
			size_t index = which >> 3;
			size_t pos = which % 8;

			_set[index] |= (1 << pos);
		}

		//置0
		void reset(size_t which)
		{
			if (which >= _bitCount)
			{
				return;
			}
			//计算对应的字节
			size_t index = which >> 3;  // <---> which / 8
			size_t pos = which % 8;

			_set[index] &= ~(1 << pos);
		}

		//检测which比特位是否为1
		bool test(size_t which)
		{
			if (which >= _bitCount)
			{
				return false;
			}
			//计算对应的字节
			size_t index = which >> 3;
			size_t pos = which % 8;

			return 0 != (_set[index] & (1 << pos));
		}

		//返回总的比特位的个数
		size_t size()
		{
			return _bitCount;
		}

		//返回所有比特位为1的个数
		size_t count()
		{
			int bitCnttable[256] = {
				0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
				3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
				3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
				4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
				3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
				6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
				4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
				6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
				3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
				4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
				6, 7, 6, 7, 7, 8 };

			size_t szcount = 0;
			for (size_t i = 0; i < _set.size(); i++)
			{
				szcount += bitCnttable[_set[i]];
			}
			return szcount;
		}

	private:
		std::vector<unsigned char> _set;
		size_t _bitCount;
	};
}

void TestBitSet()
{
	xi::bitset bt(100);
	bt.set(10);
	bt.set(20);
	bt.set(30);
	bt.set(40);
	bt.set(41);
	std::cout << bt.size() << std::endl;
	std::cout << bt.count() << std::endl;

	if (bt.test(40))
	{
		std::cout << "40th bit is 1" << std::endl;
	}
	else
	{
		std::cout << "40th bit isn't 1" << std::endl;
	}

	bt.reset(40);
	std::cout << bt.count() << std::endl;

	if (bt.test(40))
	{
		std::cout << "40th bit is 1" << std::endl;
	}
	else
	{
		std::cout << "40th bit isn't 1" << std::endl;
	}
}