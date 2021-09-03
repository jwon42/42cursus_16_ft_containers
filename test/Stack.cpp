#include "main.hpp"

static void constructors(void)
{
	print_header("Constructor");
	ft::stack<int> s1;
	std::stack<int> s2;
	check("s1.size() == s2.size()", s1.size() == s2.size());
	check("s1.empty() == s2.empty()", s1.empty() == s2.empty());
}

static void front_back(void)
{
	print_header("Front / Back / Push / Pop");
	ft::stack<int> s1;
	std::stack<int> s2;
	s1.push(0);
	s1.push(1);
	s1.push(2);
	s2.push(0);
	s2.push(1);
	s2.push(2);
	check("s1.size() == s2.size()", s1.size() == s2.size());
	check("s1.empty() == s2.empty()", s1.empty() == s2.empty());
	check("s1.top() == s2.top()", s1.top(), s2.top());
	s1.pop();
	s2.pop();
	check("s1.size() == s2.size()", s1.size() == s2.size());
	check("s1.top() == s2.top()", s1.top(), s2.top());
}

void test_stack(void)
{
	print_header("stack", true);

	constructors();
	front_back();
}