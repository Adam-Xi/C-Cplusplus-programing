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
	String& operator=(String str)  //��ֵ��������� 
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
	void PushBack(char c)  //β��һ���ַ�c
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
	void Append(const char* str)  //β��һ���ַ���
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
	void Clear()  //���
	{
		_size = 0;
		_str[size] = '\0';
	}
	void Swap(String& str)  //���������е���Դ
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
				Reverse(newSize);
			}
			memset(_str + _size, c, newSize - _size);
		}
		_size = newSize;
		_str[newSize] = '\0';
	}
	char& operator[](size_t index)
	{

	}
	const char& operator[](size_t index)const
	{

	}
	
	bool operator<(const String& s)
	{

	}
	bool operator<=(const String& s)
	{

	}
	bool operator>(const String& s)
	{

	}
	bool operator>=(const String& s)
	{

	}
	bool operator==(const String& s)
	{
		
	}
	bool operator!=(const String& s)
	{

	}

	size_t Find(char c, size_t pos = 0)const
	{

	}
	size_t Find(const char* s, size_t pos = 0)const
	{

	}
	String& Insert(size_t pos, char c)
	{

	}
	String& Insert(size_t pos, const char* str)
	{

	}
	String& Erase(size_t pos, size_t len)
	{

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