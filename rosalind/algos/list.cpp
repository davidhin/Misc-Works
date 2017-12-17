#pragma once

#include <iostream>
#include <fstream>

// https://www.codementor.io/codementorteam/a-comprehensive-guide-to-implementation-of-singly-linked-list-using-c_plus_plus-ondlm5azr

struct node
{
	int data;
	node* next;
	bool visited = false;
	
	int degree()
	{
		int count = 0;
		node* cur = this;
		while (cur != NULL)
		{
				count++;
				cur = cur->next;
		}
		return count;
	}
};

class list
{
public:
	node *head, *tail;
	int level = -1;
	bool visited = false;
	bool pointed;

	list()
	{
		head=NULL;
		tail=NULL;
	}
	
	void createNode(int value)
	{
		node* temp = new node;
		temp->data = value;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}	
	
	void insert_start(int value)
	{
		node *temp = new node;
		temp->data = value;
		temp->next = head;
		head = temp;
	}

	void insert_position(int pos, int value)
	{
		node* pre = new node;
		node* cur = new node;
		node* temp = new node;
		cur = head;
		for (int i = 1; i < pos; i++)
		{
			pre = cur;
			cur = cur->next;
		}
		temp->data = value;
		pre->next = temp;
		temp->next = cur;	
	}

	void display()
	{
		node* temp = head;
		while (temp != NULL)
		{
			std::cout << temp << "\t" << temp->data << "\t" << temp->next << std::endl;
			temp = temp->next;
		}
	}

	void delete_first()
	{
		node* temp = new node;
		temp = head;
		head = head->next;
		delete temp;
	}

	void delete_last()
	{
		node* pre = new node;
		node* cur = new node;
		cur = head;
		while (cur->next != NULL)
		{
			pre = cur;
			cur = cur->next;
		}
		tail = pre;
		pre->next = NULL;
		delete cur;	
	}

	void delete_position(int pos)
	{
		node* cur = new node;
		node* pre = new node;
		cur = head;
		for (int i = 1; i < pos; i++)
		{
			pre = cur;
			cur = cur->next;
		}
		pre->next = cur->next;		
	}	
};
