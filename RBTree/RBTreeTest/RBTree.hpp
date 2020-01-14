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

			//找插入位置
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

			//插入新节点
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

			//新节点插入后进行调整，遵循性质3：不能有连在一起的红色节点
			while (RED == pParent->_color && pParent != _pHead)
			{
				//grandFather一定存在，因为pParent为红色，一定不是pRoot根节点，所以一定有双亲
				Node* grandFather = pParent->_pParent;

				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;

					if (uncle && RED == uncle->_color)
					{
						//情况一：pCur、pParent为红色，grandFather为黑色，uncle存在且为红色
						pParent->_color = uncle->_color = BLACK;
						grandFather->_color = RED;

						//更新调整后的PCur、pParent位置
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						//叔叔节点不存在、或者叔叔节点存在且为黑色
						//看是否满足情况二、情况三：即判断pCur节点是在pParent节点的内侧还是外侧 
						if (pCur == pParent->_pRight)
						{//在内侧，有“拐”,先转化为情况二
							//情况三：pCur、pParent为红色，grandFather为黑色，uncle不存在 或者 存在且为黑色
							_RotateLeft(pParent);
							std::swap(pParent, pCur);
						}

						//情况二 或 转化后的情况三：
						//pCur、pParent为红色，grandFather为黑色，uncle不存在 或者 存在且为黑色
						pParent->_color = BLACK;
						grandFather->_color = RED;
						_RotateRight(grandFather);
					}
				}
				else
				{
					//前面if体内三种情况的反情况：即镜像情况，处理方式相同
					Node* uncle = grandFather->_pLeft;

					if (uncle && RED == uncle->_color)
					{
						//情况一
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

		//始终保持红黑树头结点和根节点的性质
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
		{//空树也是红黑树
			return true;
		}

		//检测根节点是否满足情况
		if (BLACK != pRoot->_color)
		{
			std::cout << "违反红黑树性质二：根节点必须为黑色" << std::endl;
			return false;
		}

		//获取任意一条路径中黑色节点的个数,以最左路径为例
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

		//检测是否满足红黑树的性质，count用来记录路径中黑色节点的个数
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
				std::cout << "违反了性质4：每条路径中黑色节点个数必须相同" << std::endl;
				return false;
			}
			return true;
		}

#if 0
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (blackCount != count)
			{
				std::cout << "违反了性质4：每条路径中黑色节点个数必须相同" << std::endl;
				return false;
			}
		}
#endif

		//统计黑色节点个数
		if (BLACK == pRoot->_color)
		{
			count++;
		}

		//检测当前节点与其双亲是否都为红色
		Node* pParent = pRoot->_pParent;
		if (pParent && RED == pRoot->_color && RED == pParent->_color)
		{
			std::cout << "违反红黑树性质三：必须保证没有连在一起的红色节点" << std::endl;
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