#include<iostream>
using namespace std;
#include<deque>

template<class T, class Container = deque<T>>
class queue
{
public:
	queue()
		:con()
	{}
	void push(const T& x)
	{
		con.push_back(x);
	}
	void pop()
	{
		con.pop_front();
	}
	T& front()
	{
		return con.front();
	}
	const T& front()const
	{
		return con.front();
	}
	T& back()
	{
		return con.back();
	}
	const T& back()const
	{
		return con.back();
	}
	size_t size()const
	{
		return con.size();
	}
	bool empty()const
	{
		return con.empty();
	}
private:
	Container con;
};

void testQueue()
{
	queue<int> q;
	if (q.empty())
	{
		cout << q.size() << endl;
	}
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	cout << q.size() << endl;
	cout << q.front() << " --- " << q.back() << endl;

	q.pop();
	q.pop();
	cout << q.size() << endl;
	cout << q.front() << " --- " << q.back() << endl;
}

int main()
{
	testQueue();
	return 0;
}