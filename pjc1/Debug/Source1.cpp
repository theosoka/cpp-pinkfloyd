#include <iostream>
#include <string>

template<typename X>
struct node
{
	X val;
	node* next;

	void put(X a)
	{
		node* tmp = this;
		do
		{
			if (!tmp->next)
			{
				node* newest = tmp->next = new node();
				newest->val = a;
				return;
			}
		} while (tmp = tmp->next);
	}

	void transform(X(*func)(X)) {
		node* tmp = this;
		do
		{
			tmp->val = func(tmp->val);
		} while (tmp = tmp->next);
	}

	void print() {
		node* tmp = this;
		do
		{
			std::cout << tmp->val << " ";
		} while (tmp = tmp->next);
		std::cout << std::endl;
	}
};

double bar(double x)
{
	return x * x;
}

int main()
{
	node<double> root{ 5 };
	root.put(20);
	root.put(10);
	root.transform(bar);
	root.transform([](double x) {
		if ((int)x % 10) {
			return x;
		}
		return x * x;
		});
	root.print();
}
