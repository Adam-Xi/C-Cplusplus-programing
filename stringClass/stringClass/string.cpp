//#pragma warning(disable:4996)
//#include<iostream>
//using namespace std;
//#include<assert.h>
//#include<string.h>
//
//namespace simulation
//{
//	class string
//	{
//	public:
//		typedef char* iterator;
//		typedef const char* const_iterator;
//	public:
//		string(const char* str = "")
//		{
//			_size = strlen(str);
//			_capacity = _size;
//			_str = new char[_capacity + 1];
//			strcpy(_str, str);
//		}
//		string(const string& s)
//			:_str(nullptr)
//			, _size(0)
//			, _capacity(0)
//		{
//			string temp(s._str);
//			Swap(temp);
//		}
//		~string()
//		{
//			if (_str)
//			{
//				delete[] _str;
//				_str = nullptr;
//			}
//		}
//
//		iterator begin()  //指向字符串的开头
//		{
//			return _str;
//		}
//		const_iterator begin()const
//		{
//			return _str;
//		}
//		iterator end()  //指向字符串最后一个元素的下一个位置
//		{
//			return _str + _size;
//		}
//		const_iterator end()const
//		{
//			return _str + _size;
//		}
//
//		string& operator=(string& s)
//		{
//			Swap(s);
//			return *this;
//		}
//		void push_back(char c)
//		{
//			if (_size == _capacity)
//			{
//				Reserve(_capacity * 2);
//			}
//			_str[_size] = c;
//			_str[++_size] = '\0';
//		}
//		void Append(const char* str)
//		{
//			size_t len = strlen(str);
//			if (_size + len > _capacity)
//			{
//				Reserve(_size + len);
//			}
//			strcat(_str, str);
//			_size += len;
//		}
//		string& insert(size_t pos, char c)
//		{
//			if (_size == _capacity)
//			{
//				Reserve(_capacity * 2);
//			}
//			iterator it = end();
//			iterator start = _str + pos;
//			while (it > start)
//			{
//				--it;
//				*(it + 1) = *it;
//			}
//			_str[pos] = c;
//			_str[++_size] = '\0';
//		}
//		string& insert(size_t pos, const char* str)
//		{
//			size_t len = strlen(str);
//			if (_size + len > _capacity)
//			{
//				Reserve(_size + len);
//			}
//			iterator it = end();
//			iterator start = _str + pos;
//			while (it > start)
//			{
//				--it;
//				*(it + len) = *it;
//			}
//			for (size_t i = 0; i < len; ++i)
//			{
//				*it++ = str[i];
//			}
//			_size += len;
//			_str[_size] = '\0';
//			return *this;
//		}
//
//
//		string& operator+=(char c)
//		{
//			push_back(c);
//			return *this;
//		}
//		string& operator+=(const char* str)
//		{
//			Append(str);
//			return *this;
//		}
//		void Swap(string& s)
//		{
//			swap(_str, s._str);
//			swap(_size, s._size);
//			swap(_capacity, s._capacity);
//		}
//
//
//		void clear()
//		{
//			_size = 0;
//			_str[_size] = '\0';
//		}
//		const char* c_str()const
//		{
//			return _str;
//		}
//		size_t Size()const
//		{
//			return _size;
//		}
//		size_t Capacity()const
//		{
//			return _capacity;
//		}
//		bool empty()const
//		{
//			if (_str[0] == '\0' && _size == 0)
//			{
//				return true;
//			}
//			return false;
//		}
//		void Resize(size_t newSize, char c = '\0')
//		{
//			if (newSize > _size)
//			{
//				if (newSize > _capacity)
//				{
//					Reserve(newSize);
//				}
//				memset(_str + _size, c, newSize - _size);
//			}
//			_size = newSize;
//			_str[_size] = '\0';
//		}
//		void Reserve(size_t newCapacity)
//		{
//			if (newCapacity > _capacity)
//			{
//				char* str = new char[newCapacity + 1];
//				strcpy(str, _str);
//
//				if (_str != nullptr)
//				{
//					delete[] _str;
//					_str = str;
//					_capacity = newCapacity;
//				}
//			}
//		}
//
//
//		char& operator[](size_t index)
//		{
//			assert(index < _size);
//			return _str[index];
//		}
//		const char& operator[](size_t index)const
//		{
//			assert(index < _size);
//			return _str[index];
//		}
//		bool operator>(const string& s)
//		{
//			return strcmp(_str, s._str) > 0;
//		}
//		bool operator>=(const string& s)
//		{
//			return strcmp(_str, s._str) >= 0;
//		}
//		bool operator<(const string& s)
//		{
//			return strcmp(_str, s._str) < 0;
//		}
//		bool operator<=(const string& s)
//		{
//			return strcmp(_str, s._str) <= 0;
//		}
//		bool operator==(const string& s)
//		{
//			return strcmp(_str, s._str) == 0;
//		}
//		bool operator!=(const string& s)
//		{
//			return strcmp(_str, s._str) != 0;
//		}
//		size_t find(char c, size_t pos = 0)const
//		{
//			iterator it = _str + pos;
//			while (it != '\0')
//			{
//				if (*it == c)
//				{
//					return it - _str;
//				}
//				++it;
//			}
//			if (it == '\0')
//			{
//				return -1;
//			}
//		}
//		size_t find(const char* str, size_t pos = 0)const
//		{
//			size_t len = strlen(str);
//			int flag = 1;
//			for (size_t i = pos; i < _size; ++i)
//			{
//				for (size_t j = 0; j < len; ++j)
//				{
//					if (_str[i + j] != str[j])
//					{
//						flag = 0;
//						break;
//					}
//				}
//				if (flag == 1)
//				{
//					return i;
//				}
//				flag = 1;
//			}
//			return -1;
//		}
//		string& erase(size_t pos, size_t len)
//		{
//			for (size_t i = pos; i < _size; ++i)
//			{
//				_str[i] = _str[i + 1];
//			}
//			_size--;
//			return *this;
//		}
//	private:
//		friend ostream& operator<<(ostream& _cout, const simulation::string& s);
//
//	private:
//		char* _str;
//		size_t _size;
//		size_t _capacity;
//	};
//}
//ostream& simulation::operator<<(ostream& _cout, const simulation::string& s)
//{
//	cout << s._str;
//	return _cout;
//}
//
//void TestString1()
//{
//	simulation::string s1;
//	simulation::string s2("hello world!");
//	simulation::string s3(s2);
//	simulation::string s4 = s3;
//	s1.Append("i love you!");
//	s2.push_back('!');
//	s2.erase(5, 1);
//	s3 += "end";
//	s3 += '!';
//	s4.clear();
//}
//
//int main()
//{
//	TestString1();
//	return 0;
//}