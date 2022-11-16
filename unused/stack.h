#pragma once
#include<iostream>
#include<string>
using namespace std;

class Node
{
private:
	string data;
	Node* next;
public:
	Node(string x = "", Node* ptr = NULL);
	string get_data();
	Node* get_Next();
	void set_data(string y);
	void set_next(Node* ptr);

};

class Stack
{
public:
	Node* top;
public:
	Stack();
	~Stack();
	Node* get_top();
	void pushS(string x);
	string pop();
	boolean empty();
	string Top();
};

Node::Node(string x, Node* ptr)
{
	data = x;
	next = ptr;
}

string Node::get_data()
{
	return data;
}

Node* Node::get_Next()
{
	return next;
}

void Node::set_data(string x)
{
	data = x;
}

void Node::set_next(Node* ptr)
{
	next = ptr;
}

Stack::Stack()
{
	top = NULL;
}

Node* Stack::get_top()
{
	return top;
}

void Stack::pushS(string x)
{
	Node* topptr = new Node(x, top);
	top = topptr;
	//cout << x << " pushed!\n";
}

string Stack::pop()
{
	if (empty())
	{
		cout << "Stack is Empty!!" << endl;
	}
	else
	{
		Node* temp = get_top();
		top = top->get_Next();
		string z = temp->get_data();
		//cout << z << " is popped!\n";
		delete temp;
		return z;
	}
	return "";
}

boolean Stack::empty()
{
	return (get_top() == NULL);
}

string Stack::Top()
{
	return top->get_data();
}

Stack::~Stack()
{
	delete top;
}