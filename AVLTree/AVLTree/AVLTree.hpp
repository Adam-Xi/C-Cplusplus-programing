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

//约定：AVL树中各个节点的值都是唯一的
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

		//找插入位置
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

		//插入节点
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

		//更新平衡因子
		while (pParent)
		{
			//检测插入位置是在双亲的左侧还是右侧
			if (pCur == pParent->_pLeft)
			{
				pParent->_bf--;
			}
			else
			{
				pParent->_bf++;
			}
			//判断当前双亲的平衡因子是否需要调整
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
				//pParent 的节点已经违反AVL树的性质了 pParent->_bf = 2 | -2
				//此时需要进行旋转处理以调整
				if (pParent->_bf == 2)
				{
					//pParent的右子树高
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
					//pParent的左子树高
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

	//左单旋：将新节点插入到较高右子树的右侧
	void RotateLeft(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		Node* ppParent = pParent->_pParent;

		//更新子树指针域
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

		//更新双亲
		if (pSubRL)
		{
			pSubRL->_pParent = pParent;
		}
		pParent->_pParent = pSubR;
		pSubR->_pParent = ppParent;

		//更新平衡因子
		pParent->_bf = pSubR->_bf = 0;
	}

	//右单旋：将新节点插入到较高左子树地左侧
	void RotateRight(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		Node* ppParent = pParent->_pParent;

		//更新子树指针域
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

		//更新双亲
		if (pSubLR)
		{//避免左单支子树的情况PSubLR为空
			pSubLR->_pParent = pParent;
		}
		pParent->_pParent = pSubL;
		pSubL->_pParent = ppParent;

		//更新平衡因子
		pParent->_bf = pSubL->_bf = 0;
	}

	//先左单旋再右单旋
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

	//先右单旋再左单旋
	void RotateRL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;

		RotateRight(pParent->_pRight);
		RotateLeft(pParent);

		//调整部分节点的平衡因子
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