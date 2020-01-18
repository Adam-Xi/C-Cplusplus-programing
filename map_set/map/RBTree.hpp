#pragma once 

#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

enum Color { RED, BLACK};

template<class Type>
struct RBTreeNode
{
	RBTreeNode(const Type& data = Type(), Color color = RED)
		: _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _color(color)
	{}

	RBTreeNode<Type>* _pLeft;
	RBTreeNode<Type>* _pRight;
	RBTreeNode<Type>* _pParent;
	Type _data;
	Color _color;
};

template<class Type>
struct RBTreeIterator
{
	typedef RBTreeNode<Type> Node;
	typedef RBTreeIterator<Type> Self;

public:
	RBTreeIterator(Node* pNode = nullptr)
		: _pNode(pNode)
	{}

	//ʹ����ָ�����
	Type& operator*()
	{
		return _pNode->_data;
	}

	Type* operator->()
	{
		return &(operator*());
	}

	//�����ƶ�
	Self& operator++()
	{
		Increasement();
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(*this);
		Increasement();
		return tmp;
	}

	Self& operator--()
	{
		DeIncreasement();
		return *this;
	}

	Self operator--(int)
	{
		Self tmp(*this);
		DeIncreasement();
		return tmp;
	}

	bool operator==(const Self& obj)const
	{
		return _pNode == obj._pNode;
	}

	bool operator!=(const Self& obj)const
	{
		return _pNode != obj._pNode;
	}

private:
	void Increasement()
	{
		if (_pNode->_pRight)
		{
			//����������ʱ��������������ڵ�
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
			{
				_pNode = _pNode->_pLeft;
			}
		}
		else
		{
			//������������ʱ�����汲�ڵ���
			Node* pParent = _pNode->_pParent;
			while (pParent->_pRight == _pNode)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}

			//���ڵ�û�������������ҵ������պ��ڸ��ڵ�λ��
			if (_pNode->_pRight != pParent)
			{
				_pNode = pParent;
			}
			_pNode = pParent;
		}
	}

	void DeIncreasement()
	{
		if (_pNode->_pParent->_pParent == _pNode && RED == _pNode->_color)
		{
			_pNode = _pNode->_pRight;
		}
		else if (_pNode->_pLeft)
		{
			//����������ʱ�������������ҽڵ�
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
			{
				_pNode = _pNode->_pRight;
			}
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pLeft)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}

			_pNode = pParent;
		}
	}
private:
	Node* _pNode;
};

struct KeyOfValue
{
	int operator()(int data)
	{
		return data;
	}
};

template<class Type, class KOFV>
class RBTree
{
	typedef RBTreeNode<Type> Node;
public:
	typedef RBTreeIterator<Type> iterator;

public:
	RBTree()
		: _size(0)
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	iterator begin()
	{
		return iterator(_pHead->_pLeft);
	}

	iterator end()
	{
		return iterator(_pHead);
	}

	std::pair<iterator, bool> Insert(const Type& data)
	{
		Node*& pRoot = GetRoot();
		Node* pNewNode = nullptr;
		if (nullptr == pRoot)
		{
			pNewNode = pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
		}
		else
		{
			//���ն����������������ҵ�������ڵ��ں�����е�λ��
			Node* pCur = pRoot;
			Node* pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (KOFV()(data) < KOFV()(pCur->_data))
				{
					pCur = pCur->_pLeft;
				}
				else if (KOFV()(data) > KOFV()(pCur->_data))
				{
					pCur = pCur->_pRight;
				}
				else
				{
					return std::make_pair(iterator(), false);
				}
			}

			//�����½ڵ�
			pNewNode = pCur = new Node(data);
			if (KOFV()(data) < KOFV()(pParent->_data))
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;

			//����½ڵ������Ƿ�������һ��ĺ�ɫ�ڵ�
			while (RED == pParent->_color && pParent != _pHead)
			{
				Node* grandFather = pParent->_pParent;
				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;
					//���һ������ڵ���ڣ���Ϊ��
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						if (pCur == pParent->_pRight)
						{
							//�������
							RotateLeft(pParent);
							std::swap(pParent, pCur);
						}
						//�������
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateRight(grandFather);
					}
				}
				else
				{
					Node* uncle = grandFather->_pLeft;
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						if (pCur == pParent->_pLeft)
						{
							RotateRight(pParent);
							std::swap(pParent, pCur);
						}

						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateLeft(grandFather);
					}
				} // end while()
			} // end else
		} // end function()

		//ȷ����ʼ���Ǻ�ɫ��
		_size++;
		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return std::make_pair(iterator(pNewNode), true);
	}
	void Inorder()
	{
		_InOrder(GetRoot());
		std::cout << std::endl;
	}

	bool IsValidRBTree()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			return true;
		}
		if (pRoot->_color != BLACK)
		{
			std::cout << "Υ������1�����ڵ���ɫ����Ϊ��ɫ" << std::endl;
			return false;
		}

		//��ȡһ��·���нڵ�ĸ���
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (pCur->_color == BLACK)
			{
				blackCount++;
			}
			pCur = pCur->_pLeft;
		}

		size_t pathBalck = 0;
		return _IsValidRBTree(pRoot, blackCount, pathBalck);
	}

	bool Empty()const
	{
		return nullptr == _pHead->_pParent;
	}
	size_t size()const
	{
		return _size;
	}

	iterator find(const Type& data)const
	{
		Node* pCur = _pHead->_pParent;
		while (pCur)
		{
			if (KOFV()(data) == KOFV()(pCur->_data))
			{
				return iterator(pCur);
			}
			else if (KOFV()(data) < KOFV()(pCur->_data))
			{
				pCur = pCur->_pLeft;
			}
			else
			{
				pCur = pCur->_pRight;
			}
		}
		return end();
	}
private:
	Node*& GetRoot()
	{
		return _pHead->_pParent;
	}

	Node* LeftMost()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			return _pHead;
		}

		Node* pCur = pRoot;
		while (pCur->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur;
	}

	Node* RightMost()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			return _pHead;
		}

		Node* pCur = pRoot;
		while (pCur->_pRight)
		{
			pCur = pCur->_pRight;
		}
		return pCur;
	}

	void RotateLeft(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		Node* ppParent = pParent->_pParent;

		pParent->_pRight = pSubRL;
		pSubR->_pLeft = pParent;

		if (pSubRL)
		{
			pSubRL->_pParent = pParent;
		}
		pParent->_pParent = pSubR;
		pSubR->_pParent = ppParent;

		if (ppParent == _pHead)
		{
			GetRoot() = pSubR;
		}
		else
		{
			if (ppParent->_pLeft == pParent)
			{
				ppParent->_pLeft = pSubR;
			}
			else
			{
				ppParent->_pRight = pSubR;
			}
		}
	}

	void RotateRight(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		Node* ppParent = pParent->_pParent;

		pParent->_pLeft = pSubLR;
		pSubL->_pRight = pParent;

		if (pSubLR)
		{
			pSubLR->_pParent = pParent;
		}
		pParent->_pParent = pSubL;
		pSubL->_pParent = ppParent;

		if (ppParent == _pHead)
		{
			GetRoot() = pSubL;
		}
		else
		{
			if (ppParent->_pLeft == pParent)
			{
				ppParent->_pLeft = pSubL;
			}
			else
			{
				ppParent->_pRight = pSubL;
			}
		}
	}
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			std::cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	bool _IsValidRBTree(Node* pRoot, size_t blackCount, size_t pathBlack)
	{
		if (nullptr == pRoot)
		{
			return true;
		}

		if (pRoot->_color == BLACK)
		{
			pathBlack++;
		}

		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead && pParent->_color == RED && pRoot->_color == RED)
		{
			std::cout << "Υ��������3������������һ��ĺ�ɫ�ڵ�" << std::endl;
		}

		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (blackCount != pathBlack)
			{
				std::cout << "Υ��������4��ÿ��·���к�ɫ�ڵ����������ͬ" << std::endl;
			}
		}

		return _IsValidRBTree(pRoot->_pLeft, blackCount, pathBlack) && 
			   _IsValidRBTree(pRoot->_pRight, blackCount, pathBlack);
	}
private:
	Node* _pHead;
	size_t _size;  //��¼���������Ч�ڵ�ĸ���
};

void TestRBTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int, KeyOfValue> tree;
	for (auto e : array)
	{
		tree.Insert(e);
	}
	tree.Inorder();
	if (tree.IsValidRBTree())
	{
		std::cout << "Is a valid RBTree" << std::endl;
	}
	else
	{
		std::cout << "Is a Invalid RBTree" << std::endl;
	}

	RBTree<int, KeyOfValue>::iterator it = tree.begin();
	while (it != tree.end())
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}