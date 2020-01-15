#pragma once 
#include <iostream>

template<class T>
struct AVLTreeNode
{
	AVLTreeNode(const T& data = T())
		: _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _bf(0)
	{}
	AVLTreeNode<T>* _pLeft;
	AVLTreeNode<T>* _pRight;
	AVLTreeNode<T>* _pParent;
	T _data;
	int _bf;
};

//Լ����AVL���и����ڵ��ֵ����Ψһ��
template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;

public:
	AVLTree()
		: _pRoot(nullptr)
	{}

	bool Insert(const T& data)
	{
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(data);
			return true;
		}

		//�Ҳ���λ��
		Node* pCur = _pRoot;
		Node* pParent = nullptr;
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

		//����ڵ�
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

		//����ƽ������
		while (pParent)
		{
			//������λ������˫�׵���໹���Ҳ�
			if (pCur == pParent->_pLeft)
			{
				pParent->_bf--;
			}
			else
			{
				pParent->_bf++;
			}
			//�жϵ�ǰ˫�׵�ƽ�������Ƿ���Ҫ����
			if (0 == pParent->_bf)
			{
				return true;
			}
			else if (-1 == pParent->_bf || 1 == pParent->_bf)
			{
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{
				//pParent �Ľڵ��Ѿ�Υ��AVL���������� pParent->_bf = 2 | -2
				//��ʱ��Ҫ������ת�����Ե���
				if (pParent->_bf == 2)
				{
					//pParent����������
					if (pCur->_bf == 1)
					{
						RotateLeft(pParent);
					}
					else
					{
						RotateRL(pParent);
					}
				}
				else
				{
					//pParent����������
					if (pCur->_bf == -1)
					{
						RotateRight(pParent);
					}
					else
					{
						RotateLR(pParent);
					}
				}
				break;
			} //end else
		} //end while

		return true;
	} //end function()

	void InOrder()
	{
		_InOrder(_pRoot);
	}
	
	bool IsValidAVLTree()
	{
		return _IsValidAVLTree(_pRoot);
	}

private:
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			std::cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	bool _IsValidAVLTree(Node* pRoot)
	{
		if (nullptr == pRoot)
		{
			return true;
		}

		int leftHeight = Height(pRoot->_pLeft);
		int rightHeight = Height(pRoot->_pRight);
		int bf = rightHeight - leftHeight;

		if (abs(bf) > 1 || bf != pRoot->_bf)
		{
			return false;
		}

		return _IsValidAVLTree(pRoot->_pLeft) && _IsValidAVLTree(pRoot->_pRight);
	}

	int Height(Node* pRoot)
	{
		if (nullptr == pRoot)
		{
			return 0;
		}

		int leftHeight = Height(pRoot->_pLeft);
		int rightHeight = Height(pRoot->_pRight);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	//���������½ڵ���뵽�ϸ����������Ҳ�
	void RotateLeft(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		Node* ppParent = pParent->_pParent;

		//��������ָ����
		pSubR->_pLeft = pParent;
		pParent->_pRight = pSubRL;
		if (ppParent)
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
		else
		{
			_pRoot = pSubR;
		}

		//����˫��
		if (pSubRL)
		{
			pSubRL->_pParent = pParent;
		}
		pParent->_pParent = pSubR;
		pSubR->_pParent = ppParent;

		//����ƽ������
		pParent->_bf = pSubR->_bf = 0;
	}

	//�ҵ��������½ڵ���뵽�ϸ������������
	void RotateRight(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		Node* ppParent = pParent->_pParent;

		//��������ָ����
		pSubL->_pRight = pParent;
		pParent->_pLeft = pSubLR;
		if (ppParent)
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
		else
		{
			_pRoot = pSubL;
		}

		//����˫��
		if (pSubLR)
		{//������֧���������PSubLRΪ��
			pSubLR->_pParent = pParent;
		}
		pParent->_pParent = pSubL;
		pSubL->_pParent = ppParent;

		//����ƽ������
		pParent->_bf = pSubL->_bf = 0;
	}

	//���������ҵ���
	void RotateLR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;

		RotateLeft(pParent->_pLeft);
		RotateRight(pParent);

		if (bf == 1)
		{
			pParent->_bf = -1;
		}
		else if (bf == -1)
		{
			pSubL->_bf = 1;
		}
	}

	//���ҵ���������
	void RotateRL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;

		RotateRight(pParent->_pRight);
		RotateLeft(pParent);

		//�������ֽڵ��ƽ������
		if (bf == 1)
		{
			pParent->_bf = -1;
		}
		else if (bf == -1)
		{
			pSubR->_bf = 1;
		}
	}

private:
	Node* _pRoot;
};

void TestAVLTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16};
	//int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	AVLTree<int> tree;

	for (auto e : array)
	{
		tree.Insert(e);
	}

	tree.InOrder();
	std::cout << std::endl;

	if (tree.IsValidAVLTree())
	{
		std::cout << "tree is a valid AVLTree" << std::endl;
	}
	else
	{
		std::cout << "tree is not a valid AVLTree" << std::endl;
	}
}