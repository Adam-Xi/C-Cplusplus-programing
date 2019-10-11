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
		String tmp(str._str);
		this->Swap(tmp);
	}
	//string(const string& s)
	//	: _size(s._size)
	//	, _capacity(s._size)
	//{
	//	_str = new char[_capacity + 1];
	//	strcpy(_str, s._str);
	//}
	~String()  //��������
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
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
		_str[_size] = '\0';
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
		return *this;
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
		return *this;
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

	size_t Find(char c, size_t pos = 0)const //����c��string�е�һ�γ��ֵ�λ��
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
	size_t Find(const char* s, size_t pos = 0)const //�����Ӵ�s��string�е�һ�γ��ֵ�λ��
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
		for (size_t i = pos; i < _size; ++i)
		{
			for (size_t j = 0; j < len; ++j)
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
	String& Insert(size_t pos, char c) //��posλ�����ַ�c
	{
		if (_size == _capacity)
		{
			Reserve(_capacity * 2);
		}
		for (size_t i = _size; i > pos; --i) //�ӽ�����'\0'λ�ÿ�ʼ����һ��λ��
		{
			_str[i] = _str[i - 1];
		}
		_str[pos] = c;
		_str[++_size] = '\0';
		return *this;
	}
	String& Insert(size_t pos, const char* str) //��posλ�����ַ���str
	{
		size_t len = strlen(str);
		if (_size + len > _capacity) //���Ƿ���Ҫ����
		{
			Reserve(_size + len);
			_size = _size + len;
		}
		for (size_t i = _size; i >= pos + len; --i) //�ӽ�����'\0'λ��(_str[_size]λ��)��ʼ����lenλ��
		{
			_str[i] = _str[i - len];
		}
		for (size_t i = pos, j = 0; j < len; ++i, ++j)
		{
			_str[i] = str[j];
		}
		return *this;
	}
	String& Erase(size_t pos, size_t len) //ɾ��posλ�õ�Ԫ��
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

void TestString1()
{
	String s1;
	String s2("helloWorld");
	String s3(s2);
	String s4("school");
	s1 = s4;
	s2.PushBack('!');
	s3 += '!';
	s3 += " great!";
	s4.Append(" great");
	s1.Clear();
}
void TestString2()
{
	String s1("abcdefabdmn");
	size_t res = s1.Find('a');
	res = s1.Find('a', 3);
	res = s1.Find("abd");
	res = s1.Find("mn");
}
void TestString3()
{
	String s1("abcdefabdmn");
	s1.Insert(1, 'a');
	s1.Insert(3, 'a');
	s1.Insert(1, "abcd");
	s1.Insert(3, "xzy");
}
int main()
{
	//TestString1();
	//TestString2();
	TestString3();
	return 0;
}