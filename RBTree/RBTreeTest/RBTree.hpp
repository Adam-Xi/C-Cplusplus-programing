#pragma once 

#include <iostream>
#include <algorithm>  //reverse

enum Color{ RED, BLACK };

template<class Type>
struct RBTreeNode
{
	RBTreeNode(const Type& data = Type(), Color color = RED)
		: _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _color(color)
		, _data(data)
	{}

	RBTreeNode<Type>* _pLeft;
	RBTreeNode<Type>* _pRight;
	RBTreeNode<Type>* _pParent;
	Color _color;
	Type _data;
};

template<class Type>
class RBTree
{
	typedef RBTreeNode<Type> Node;

public:
	RBTree()
	{
		_pHead = new Node();
		_pHead->_pLeft = _pHead->_pRight = _pHead;
	}

	bool Insert(const Type& data)
	{
		Node*& pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
		}
		else
		{
			Node* pCur = pRoot;
			Node* pParent = nullptr;

			//�Ҳ���λ��
			while (pCur)
			{
				pParent = pCur;
				if (data < pCur->_data)
				{
					pCur = pCur->_pLeft;
				}
				else if (data > pCur->_data)
				{
					pCur = pCur->_pRight;
				}
				else
				{
					return false;
				}
			}

			//�����½ڵ�
			pCur = new Node(data);
			if (data < pParent->_data)
			{
				pParent->_pLeft = pCur;
			}
			else
			{
				pParent->_pRight = pCur;
			}
			pCur->_pParent = pParent;

			//�½ڵ�������е�������ѭ����3������������һ��ĺ�ɫ�ڵ�
			while (RED == pParent->_color && pParent != _pHead)
			{
				//grandFatherһ�����ڣ���ΪpParentΪ��ɫ��һ������pRoot���ڵ㣬����һ����˫��
				Node* grandFather = pParent->_pParent;

				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;

					if (uncle && RED == uncle->_color)
					{
						//���һ��pCur��pParentΪ��ɫ��grandFatherΪ��ɫ��uncle������Ϊ��ɫ
						pParent->_color = uncle->_color = BLACK;
						grandFather->_color = RED;

						//���µ������PCur��pParentλ��
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						//����ڵ㲻���ڡ���������ڵ������Ϊ��ɫ
						//���Ƿ����������������������ж�pCur�ڵ�����pParent�ڵ���ڲ໹����� 
						if (pCur == pParent->_pRight)
						{//���ڲ࣬�С��ա�,��ת��Ϊ�����
							//�������pCur��pParentΪ��ɫ��grandFatherΪ��ɫ��uncle������ ���� ������Ϊ��ɫ
							_RotateLeft(pParent);
							std::swap(pParent, pCur);
						}

						//����� �� ת������������
						//pCur��pParentΪ��ɫ��grandFatherΪ��ɫ��uncle������ ���� ������Ϊ��ɫ
						pParent->_color = BLACK;
						grandFather->_color = RED;
						_RotateRight(grandFather);
					}
				}
				else
				{
					//ǰ��if������������ķ���������������������ʽ��ͬ
					Node* uncle = grandFather->_pLeft;

					if (uncle && RED == uncle->_color)
					{
						//���һ
						pParent->_color = uncle->_color = BLACK;
						grandFather->_color = RED;

						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						if (pCur == pParent->_pLeft)
						{
							_RotateRight(pParent);
							std::swap(pParent, pCur);
						}

						pParent->_color = BLACK;
						grandFather->_color = RED;
						_RotateLeft(grandFather);
					}
				} // end else
			} //end while
		} // end if (nullptr == pRoot) else...

		//ʼ�ձ��ֺ����ͷ���͸��ڵ������
		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

	void InOrder()
	{
		_InOrder(GetRoot());
		std::cout << std::endl;
	}

	bool IsValidRBTree()
	{
		Node* pRoot = GetRoot();

		if (nullptr == pRoot)
		{//����Ҳ�Ǻ����
			return true;
		}

		//�����ڵ��Ƿ��������
		if (BLACK != pRoot->_color)
		{
			std::cout << "Υ����������ʶ������ڵ����Ϊ��ɫ" << std::endl;
			return false;
		}

		//��ȡ����һ��·���к�ɫ�ڵ�ĸ���,������·��Ϊ��
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
			{
				blackCount++;
			}
			pCur = pCur->_pLeft;
		}

		//����Ƿ��������������ʣ�count������¼·���к�ɫ�ڵ�ĸ���
		size_t count = 0;
		return _IsValidRBTree(pRoot, count, blackCount);
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

	void _RotateLeft(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		Node* ppParent = pParent->_pParent;

		pSubR->_pLeft = pParent;
		pParent->_pRight = pSubRL;

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
			if (pParent == ppParent->_pLeft)
			{
				ppParent->_pLeft = pSubR;
			}
			else
			{
				ppParent->_pRight = pSubR;
			}
		}
	}

	void _RotateRight(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		Node* ppParent = pParent->_pParent;

		pSubL->_pRight = pParent;
		pParent->_pLeft = pSubLR;

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

	void _InOrder(Node* pCur)
	{
		if (pCur)
		{
			_InOrder(pCur->_pLeft);
			std::cout << pCur->_data << " ";
			_InOrder(pCur->_pRight);
		}
	}

	bool _IsValidRBTree(Node* pRoot, size_t count, const size_t blackCount)
	{
		if (nullptr == pRoot)
		{
			if (blackCount != count)
			{
				std::cout << "Υ��������4��ÿ��·���к�ɫ�ڵ����������ͬ" << std::endl;
				return false;
			}
			return true;
		}

#if 0
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (blackCount != count)
			{
				std::cout << "Υ��������4��ÿ��·���к�ɫ�ڵ����������ͬ" << std::endl;
				return false;
			}
		}
#endif

		//ͳ�ƺ�ɫ�ڵ����
		if (BLACK == pRoot->_color)
		{
			count++;
		}

		//��⵱ǰ�ڵ�����˫���Ƿ�Ϊ��ɫ
		Node* pParent = pRoot->_pParent;
		if (pParent && RED == pRoot->_color && RED == pParent->_color)
		{
			std::cout << "Υ������������������뱣֤û������һ��ĺ�ɫ�ڵ�" << std::endl;
			return false;
		}

		return _IsValidRBTree(pRoot->_pLeft, count, blackCount) && 
			   _IsValidRBTree(pRoot->_pRight, count, blackCount);
	}
private:
	Node* _pHead;
};

void TestRBTree()
{
	//int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int> tree;
	for (auto e : array)
	{
		tree.Insert(e);
	}
	tree.InOrder();

	
	if (tree.IsValidRBTree())
	{
		std::cout << "Is a valid RBTree" << std::endl;
	}
	else
	{
		std::cout << "Is a invalid RBTree" << std::endl;
	}
	
}