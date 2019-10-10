#pragma warning(disable:4996)
#include<iostream>
using namespace std;
#include<assert.h>
#include<string.h>

class String
{
public:
	typedef char* iterator;
public:
	String(const char* str = "") //构造函数
	{
		_size = strlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}
	String(const String& str)  //拷贝构造函数
		:_str(nullptr)
		, _capacity(0)
		, _size(0)
	{
		String tmp(str);
		this->Swap(tmp);
	}
	~String()  //析构函数
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
			_capacity = 0;
			_size = 0;
		}
	}
	String& operator=(String str)  //赋值运算符重载 
	{
		this->Swap(str);
		return *this;
	}
	iterator begin()  //迭代器
	{
		return _str;
	}
	iterator end()  
	{
		return _str + _size;
	}
	void PushBack(char c)  //尾插一个字符c
	{
		if (_size == _capacity)
		{
			Reserve(_capacity * 2);
		}
		_str[_size++] = c;
		_str[_size] = '\0';
	}
	String& operator+=(char c)
	{
		PushBack(c);
		return *this;
	}
	void Append(const char* str)  //尾接一个字符串
	{
		if ((_size + strlen(str)) >= _capacity)
		{
			Reserve(_capacity + strlen(str));
		}
		strcat(_str, str);
		_size += strlen(str);
		_str[_size] = '\0';
	}
	String& operator+=(const char* str)
	{
		Append(str);
		return *this;
	}
	void Clear()  //清空
	{
		_size = 0;
		_str[_size] = '\0';
	}
	void Swap(String& str)  //交换对象中的资源
	{
		swap(_str, str._str);
		swap(_capacity, str._capacity);
		swap(_size, str._size);
	}
	const char* C_Str()const
	{
		return _str;
	}
	String& Reserve(size_t newCapacity)
	{
		if (newCapacity > _capacity)
		{
			char* str = new char[newCapacity + 1];
			strcpy(str, _str);

			delete[] _str;
			_str = str;
			_capacity = newCapacity;
		}
	}
	String& Resize(size_t newSize, char c = '\0')
	{
		if (newSize > _size)
		{
			if (newSize > _capacity)
			{
				Reserve(newSize);
			}
			memset(_str + _size, c, newSize - _size);
		}
		_size = newSize;
		_str[newSize] = '\0';
	}
	char& operator[](size_t index)
	{
		assert(index < _size);
		return _str[_size];
	}
	const char& operator[](size_t index)const
	{
		assert(index < _size);
		return _str[_size];
	}
	
	bool operator<(const String& s)
	{
		if (strcmp(_str, s._str) < 0)
		{
			return true;
		}
		return false;
	}
	bool operator<=(const String& s)
	{
		if (strcmp(_str, s._str) <= 0)
		{
			return true;
		}
		return false;
	}
	bool operator>(const String& s)
	{
		if (strcmp(_str, s._str) > 0)
		{
			return true;
		}
		return false;
	}
	bool operator>=(const String& s)
	{
		if (strcmp(_str, s._str) >= 0)
		{
			return true;
		}
		return false;
	}
	bool operator==(const String& s)
	{
		if (strcmp(_str, s._str) == 0)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const String& s)
	{
		if (!(*this == s))
		{
			return true;
		}
		return false;
	}

	size_t Find(char c, size_t pos = 0)const //返回c在string中第一次出现的位置
	{
		for (size_t i = pos; i < _size; ++i)
		{
			if (_str[i] == c)
			{
				return i;
			}
		}
		return -1;
	}
	size_t Find(const char* s, size_t pos = 0)const //返回子串s在string中第一次出现的位置
	{
		/*
		assert(s != nullptr);
		char* str = strstr(_str, s);
		if (str != nullptr)
		{
			return str - s;
		}
		*/
		size_t len = strlen(s);
		int flag = 1;
		for (size_t i = pos; i < _size - len; ++i)
		{
			i = this->Find(s[i], i);
			for (size_t j = 0; j <= len; ++j)
			{
				if (_str[i + j] != s[j])
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				return i;
			}
			flag = 1;
		}
		return -1;
	}
	String& Insert(size_t pos, char c) //在pos位插入字符c，并返回该字符的位置
	{
		if (_size == _capacity)
		{
			Reserve(_capacity * 2);
		}
		for (size_t i = _size + 1; i > pos; --i) //从结束符'\0'位置开始后移一个位置
		{
			_str[i] = _str[i - 1];
		}
		_str[pos] = c;

		return *this;
	}
	String& Insert(size_t pos, const char* str) //在pos位插入字符串str，并返回该子串的首元素位置
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			Reserve(_size + len);
		}
		for (size_t i = _size + len; i > pos; --i) //从结束符'\0'位置开始后移len位置
		{
			_str[i] = _str[i - len];
		}
		for (size_t i = pos, j = 0; i <= len; ++i, ++j)
		{
			_str[i] = str[j];
		}
		return *this;
	}
	String& Erase(size_t pos, size_t len) //删除pos位置的元素
	{
		for (size_t i = pos; i < _size; ++i)
		{
			_str[i] = _str[i + 1];
		}
		_size--;
		return *this;
	}

private:
	char* _str;
	size_t _capacity;
	size_t _size;
};

void TestString()
{

}

int main()
{

	return 0;
}