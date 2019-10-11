#include<iostream>
using namespace std;

//vector�ĵײ�ṹΪ�ɴ���������͵Ķ�̬˳���
//���ڿɴ���������ͣ�������ģ��������ģ��ʵ��
template <class T> 
class Vector
{
public:
	//Vector�ĵ�����ʵ�ʾ���һ��ԭ��ָ̬��
	typedef T* iterator;
	typedef const T* const_iterator;

public:
	////////////////////////////////////////////////////////////
	//��������������
	Vector()  //�޲ι��캯��
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{}

	Vector(size_t n, const T& val = T())  //���ι��캯������n��val���
		:_start(new T[n])
	{
		for (size_t i = 0; i < n; ++i)
		{
			_start[i] = val;
		}
		_finish = _start + n;
		_endOfStorage = _finish;
	}

	Vector(const Vector& v)  //��������
		:_start(nullptr)
		, _finish(nullptr)
		, _endOfStorage(nullptr)
	{
		//���ٿռ䣬��ֹǳ����
		Reserve(v.Capacity());

		//����Ԫ��
		iterator it = begin();
		const_iterator const_it = const_begin();
		while (const_it != v.const_end())
		{
			*it++ = *const_it++;
		}

		//����ָ���ָ��
		_finish = _start + v.Size();
		_endOfStorage = _start + v.Capacity();
	}

	//���ʹ��iterator�����������ᵼ�³�ʼ���ĵ���������[first, last)ֻ����vector�ĵ�����
	//��������������������������[first, last)���������������ĵ�����
	template<class InputIterator>
	Vector(InputIterator first, InputIterator last)  //���乹��
	{
		Reserve(last - first);
		while (first != last)
		{
			Push_Back(*first);
			++first;
		}
	}

	~Vector()  //��������
	{
		if (_start)
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_endOfStorage = nullptr;
		}
	}

	////////////////////////////////////////////////////////////
	//������
	iterator begin()
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	const_iterator const_begin()
	{
		return _start;
	}

	const_iterator const_end()
	{
		return _finish;
	}

	////////////////////////////////////////////////////////////
	//�ռ���������
	size_t Size()
	{
		return _finish - _start;
	}

	size_t Capacity()
	{
		return _endOfStorage - _start;
	}

	bool Empty()
	{
		if (_start == _finish)
		{
			return true;  //��
		}
		return false;  
	}

	void Resize(size_t newSize, const T& val = T())  //���¹涨�ռ���Ԫ�صĸ��������涨�����δװ��Ԫ�صĿռ䣬��val���
	{
		//���´�С С�� �ɵĴ�С��ֱ�Ӹ���_finish�����أ� ����Ҫ��δװ��Ԫ�صĿռ���и�ֵ
		if (newSize < size())
		{
			_finish = _start + newSize;
			return;
		}
		//���´�С����������������
		if (newSize > Capacity())
		{
			Reserve(newSize);
		}
		//��δװ��Ԫ�صĿռ丳ֵval
		iterator it = _finish;  //���þɵ�β��Ϊ�µı���ͷ
		iterator _finish = _start + newSize;  //�ٸ��� �µ�β��������Ϊ�������յ�
		while (it != _finish)
		{
			*it++ = val;
		}
	}

	void Reserve(size_t newCapacity)  //����
	{
		if (newCapacity > Capacity())
		{
			//-----1�������¿ռ�
			T* temp = new T[newCapacity];
			//-----2����Դ����
			size_t n = size();
			if (_start) //���_startָ��Ŀռ����ʱ
			{
				for (size_t i = 0; i < n; ++i)
				{
					temp[i] = _start[i];
				}
				//-----3���ͷžɿռ�
				delete[] _start;
			}
			//����ָ���ָ��
			_start = temp;
			_finish = _start + n;
			_endOfStorage = _start + newCapacity;
		}
		else
		{
			_finish = _start + newCapacity;
		}
	}

	////////////////////////////////////////////////////////////
	//��ɾ���
	void Push_Back(const T& c)  //β��һ��Ԫ��c
	{
		Insert(end(), c);
	}

	void Pop_Back()  //ɾ�����һ��Ԫ��
	{
		Earse(--end());
	}

	iterator Earse(iterator pos)  //ɾ��posλ�õ�Ԫ�أ�����ɾ��λ��
	{
		//�ж�ɾ��λ�õĺϷ���
		assert(pos >= begin() && pos < end());

		iterator it = pos;
		while (it != end() - 1)
		{
			*it = *(it + 1);
			++it;
		}
		--_finish;

		return pos;
	}

	iterator Insert(iterator pos, const T& c)  //����һ��Ԫ�أ������������λ�õĵ�ַ
	{
		//���ԣ��������λ���Ƿ�Ϸ�
		assert(pos >= begin() && pos < end());

		//�ж��Ƿ���Ҫ����
		if (_finish == _endOfStorage)
		{
			size_t size = size();
			size_t newCapacity = (0 == capacity()) ? 1 : capacity() * 2;
			//������������Ŀռ��ַ�����仯��������Ҫ����pos
			pos = _start + size;
		}
		//��posλ���Ժ��Ԫ��ȫ������ƶ�һλ
		iterator it = end();
		while (it >= pos)
		{
			--it;
			*it = *(it - 1);
		}
		//posλ����c
		*pos = c;
		//����_finish
		++_finish;

		return pos;
	}

	////////////////////////////////////////////////////////////
	//
private:
	iterator _start;  //ָ��˳����ڵ�һ��Ԫ��
	iterator _finish;  //ָ��˳��������һ��Ԫ�ص�ĩβ(��һ��λ��)
	iterator _endOfStorage;  //ָ��ÿռ��е�ĩβ(���һ��λ��)
};


int main()
{
	return 0;
}