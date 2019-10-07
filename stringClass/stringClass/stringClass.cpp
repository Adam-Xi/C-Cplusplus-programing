#include<iostream>
using namespace std;
#include<assert.h>

class String
{
public:
	typedef char* iterator;
public:
	String(const char* str = "") //���캯��
	{
		_size = strlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}
	String(const String& str)  //�������캯��
		:_str(nullptr)
		, _capacity(0)
		, _size(0)
	{
		String tmp(str);
		this->Swap(tmp);
	}
	void Swap(String& str)  //���������е���Դ
	{
		swap(_str, str._str);
		swap(_capacity, str._capacity);
		swap(_size, str._size);
	}
	~String()  //��������
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
			_capacity = 0;
			_size = 0;
		}
	}
	String& operator=(String str)
	{
		this->Swap(str);
		return *this;
	}
	iterator begin()  //������
	{
		return _str;
	}
	iterator end()  
	{
		return _str + _size;
	}
	String& operator+=(char c)
	{
		if (_size == _capacity)
		{
			Reserve(_capacity * 2);
		}
		_str[_size++] = c;
		_str[_size] = '\0';
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




private:
	char* _str;
	size_t _capacity;
	size_t _size;
};

int main()
{

	return 0;
}