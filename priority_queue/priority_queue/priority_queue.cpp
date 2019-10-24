//优先级队列
#include<iostream>
using namespace std;

template<class T, class Container = vector<T>, class Compare = less<T>>
class priority_queue
{
public:
	priority_queue()
		:con()
	{}

	template<class Iterator>
	priority_queue(Iterator first, Iterator last)
		: con(first, last)
	{
		int rear = con.size();
		int node = ((rear - 2) >> 1);
		for (; node >= 0; --node)
		{
			AdjustDown(node);
		}
	}

	void push(const T& x)
	{
		con.push_back(x);
		AdjustUp(con.size() - 1);
	}

	void pop()
	{
		if (con.empty())
		{
			return;
		}
		swap(con.front(), con.back());
		con.pop_back();
		AdjustDown(0);
	}

	bool empty()
	{
		return con.empty();
	}
	size_t size()
	{
		return con.size();
	}
	size_t size()const
	{
		return con.size();
	}
	T& top()
	{
		return con.front();
	}
private:
	void AdjustUp(int child)
	{
		size_t parent = (child - 1) >> 1;
		while (child !=	0)
		{
			if (cmp(con[parent], con[child]))
			{
				swap(con[child], con[parent]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
			{
				return;
			}
		}
	}
	void AdjustDown(int parent)
	{
		size_t child = parent * 2 + 1;
		while (child < con.size())
		{
			if (child + 1 < con.size() && cmp(con[child + 1], con[child]))
			{
				child += 1;
			}
			if (cmp(con[parent], con[child]))
			{
				swap(con[child], con[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				return;
			}
		}
	}

private:
	Container con;
	Compare cmp;
};
#include<vector>
#include<functional>
void TestPQ()
{
	// 8  1  9  3  6  4  5  0  2  7
	int array[] = { 8, 1, 9, 3, 6, 4, 5, 0, 2, 7 };
	priority_queue<int> q(array, array + sizeof(array) / sizeof(array[0]));

	q.pop();

	priority_queue<int, vector<int>, less<int>> q2;
	q2.push(5);
	q2.push(0);
	q2.push(9);
	q2.push(3);
	q2.push(4);
}

int main()
{
	TestPQ();
	return 0;
}