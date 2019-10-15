#include<iostream>
using namespace std;
#include<assert.h>

template<class T> 
struct ListNode
{
	ListNode(const T& data = T())
		:_pNext(nullptr)
		, _pPrev(nullptr)
		, _data(data)
	{}

	ListNode* _pNext;
	ListNode* _pPrev;
	T _data;
};

template<class T>
struct List_iterator
{
	typedef ListNode<T> Node;
	typedef List_iterator<T> Self;

	List_iterator(Node* pCur)
		:_pCur(pCur)
	{}

	T& operator*()
	{
		return _pCur->_data;
	}
	T* operator->()
	{
		return &(_pCur->_data);
	}

	Self& operator++()
	{
		_pCur = _pCur->_pNext;
		return *this;
	}
	Self operator++(int)
	{
		Self temp(*this);
		_pCur = _pCur->_pNext;
		return temp;
	}
	Self& operator--()
	{
		_pCur = _pCur->_pPrev;
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		_pCur = _pCur->_pPrev;
		return temp;
	}
	bool operator==(const Self& l)
	{
		return _pCur == l._pCur;
	}
	bool operator!=(const Self& l)
	{
		return _pCur != l._pCur;
	}
	Node* _pCur;
};

template<class Iterator, class T>
struct List_reverse_iterator
{
	typedef ListNode<T> Node;
	typedef List_reverse_iterator<Iterator, T> Self;

	List_reverse_iterator(Iterator it)
		:_it(it)
	{}
	T& operator*()
	{
		Iterator temp = _it;
		--temp;
		return *temp;
	}
	T* operator->()
	{
		return &(operator*());
	}
	Self& operator++()
	{
		--_it;
		return *this;
	}
	Self operator++(int)
	{
		Self temp(*this);
		_it--;
		return temp;
	}
	Self& operator--()
	{
		++_it;
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		_it++;
		return temp;
	}
	bool operator!=(const Self& l)
	{
		return _it != l._it;
	}
	bool operator==(const Self& l)
	{
		return _it == l._it;
	}

	Iterator _it;
};

template<class T>
class List
{
	typedef ListNode<T> Node;
public:
	typedef List_iterator<T> iterator;
	typedef List_reverse_iterator<iterator, T> reverse_iterator;

public:
	List()
	{
		CreatHead();
	}
	List(int n, const T& val = T())
	{
		CreatHead();
		if (_pHead)
		{
			for (int i = 0; i < n; ++i)
			{
				Push_Back(val);
			}
		}
	}
	List(const List<T>& l)
	{
		CreatHead();
		Node* pCur = l._pHead->_pNext;
		while (pCur != l._pHead)
		{
			Push_Back(pCur->_data);
			pCur = pCur->_pNext;
		}
	}
	template<class Iterator>
	List(Iterator first, Iterator last)
	{
		CreatHead();
		while (first != last)
		{
			Push_Back(*first);
			++first;
		}
	}
	~List()
	{
		clear();
		delete _pHead;
	}

	List<T>& operator=(const List<T>& l)
	{
		//if (this != &l)
		//{
		//	clear();
		//	Node* pCur = l._pHead->_pNext;
		//	while (pCur != l._pHead)
		//	{
		//		Push_Back(pCur->_data);
		//		pCur = pCur->_pNext;
		//	}
		//}
		Swap(l);
		return *this;
	}
	iterator begin()const
	{
		return iterator(_pHead->_pNext);
	}
	iterator end()const
	{
		return iterator(_pHead);
	}
	reverse_iterator rbegin()const
	{
		return end();
	}
	reverse_iterator rend()const
	{
		return begin();
	}


	size_t Size()const
	{
		size_t count = 0;
		iterator it = begin();
		while (it != end())
		{
			count++;
			it++;
		}
		return count;
	}
	bool Empty()
	{
		return _pHead->_pNext == _pHead && _pHead->_pPrev == _pHead;
	}

	T& front()
	{
		return _pHead->_pNext->_data;
	}
	const T& front()const
	{
		return _pHead->_pNext->_data;
	}
	T& back()
	{
		return _pHead->_pPrev->_data;
	}
	const T& back()const
	{
		return _pHead->_pPrev->_data;
	}

	void Push_Back(const T& val)
	{
		Insert(end(), val);
	}
	void Pop_Back()
	{
		Earse(--end());
	}
	void Push_Front(const T& val)
	{
		Insert(begin(), val);
	}
	void Pop_Front()
	{
		Earse(begin());
	}
	iterator Insert(iterator pos, const T& val)
	{
		Node* pNewNode = new Node(val);
		Node* pCur = pos._pCur;

		pNewNode->_pPrev = pCur->_pPrev;
		pNewNode->_pNext = pCur;
		pCur->_pPrev->_pNext = pNewNode;
		pCur->_pPrev = pNewNode;

		return iterator(pNewNode);
	}
	iterator Earse(iterator pos)
	{
		Node* pDelNode = pos._pCur;
		if (pDelNode == _pHead)
		{
			return end();
		}

		Node*  pRet = pDelNode->_pNext;
		pDelNode->_pPrev->_pNext = pDelNode->_pNext;
		pDelNode->_pNext->_pPrev = pDelNode->_pPrev;
		delete pDelNode;

		return iterator(pRet);
	}
	void clear()
	{
		Node* pCur = _pHead->_pNext;

		while (pCur != _pHead)
		{
			_pHead->_pNext = pCur->_pNext;
			delete pCur;
			pCur = _pHead->_pNext;
		}
		
		_pHead->_pNext = _pHead;
		_pHead->_pNext = _pHead;
	}
	void Swap(List<T>& l)
	{
		swap(_pHead, l._pHead);
	}

private:
	void CreatHead()
	{
		_pHead = new Node;
		_pHead->_pNext = _pHead;
		_pHead->_pPrev = _pHead;
	}

private:
	Node* _pHead;
};

template<class T>
void print(const List<T>& list)
{
	auto it = list.begin();
	while (it != list.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

template<class T>
void reverse_print(const List<T>& list)
{
	auto rit = list.rbegin();
	while (rit != list.rend())
	{
		cout << *rit << " ";
		++rit;
	}
}
#include <vector>

void TestList1()
{
	List<int> list1;
	List<int> list2(10, 5);
	
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	List<int> list3(v.begin(), v.end());

	List<int> list4(list3);

	print(list1);
	print(list2);
	print(list3);
	reverse_print(list4);

}
#include<string>
void TestList2()
{
	List<string> list;
	list.Push_Back("aaaa");
	list.Push_Back("xxxx");
	list.Push_Back("zzzz");
	list.Push_Back("yyyy");
	print(list);

	list.Pop_Back();
	list.Pop_Back();
	print(list);

	list.Push_Front("iiii");
	list.Push_Front("lllll");
	list.Push_Front("y");
	list.Push_Front("!!!");
	print(list);

	list.Pop_Front();
	print(list);

	list.clear();
	print(list);

	cout << " test over" << endl;
}

int main()
{
	// TestList1();
	TestList2();
	return 0;
}