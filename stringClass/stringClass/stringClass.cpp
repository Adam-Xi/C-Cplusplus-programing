#include<iostream>
using namespace std;
#include<assert.h>

class String
{
public:
	String(const char* str = "")
	{
		_size = strlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}
	String(const String& str)
		:_str(nullptr)
		, _capacity(0)
		, _size(0)
	{
		String tmp(str);
		this->Swap(tmp);
	}
	void Swap(String& str)
	{
		swap(_str, str._str);
		swap(_capacity, str._capacity);
		swap(_size, str._size);

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