#pragma once
#include <string>
#include <sstream>
#include <stdexcept>
#include "assert.h"
#include "LinkedListInterface.h"

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T> {

private:
	struct Node {
		Node(T val) {
			value = val;
			next = NULL;
		}
		
		T value;
		Node *next;
	};
	
	int numItems = 0;
	Node *tail;
	Node *head;

public:

	LinkedList(void) {
		head = NULL;
	}
	
	~LinkedList(void) {
		clear();
	}

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	void insertHead(T value) {
		// should check for duplicates (need to add code)
		if (!find(value)) {
			Node *n = new Node(value);
			n->next = head;
			head = n;
			numItems++;
		}
	}
	
	bool find(T val) {
		Node *fakeItr = head;
		while (fakeItr != NULL) {
			if (fakeItr->value == val)
				return true;
			fakeItr = fakeItr->next;
		}
		
		return false;
	}

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(T value) {
		if (find(value)) {
			return;
		}

		if (head == NULL) {
			insertHead(value);
			return;
		}

		Node *last = new Node(value);
		Node *fake = head;

		while (fake->next != NULL) {
			fake = fake->next;
		}
		
		fake->next = last;
		numItems++;
	}

	/*
	insertAfter

	A node with the given value should be inserted immediately after the node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(T value, T insertionNode) {
		if (find(value)) {
			return;
		}
		if (!find(insertionNode)) {
			return;
		}
		Node *n = new Node(value); 
		Node *fake = head;
		while (fake->value != insertionNode) {
			fake = fake->next;
		}
		n->next = fake->next;
		fake->next = n;
		numItems++;
	}

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	void remove(T val) {
		if (!find(val)) {
			return;
		}

		if (head->value == val) {
			Node *placeholder1 = head;
			head = head->next;
			delete placeholder1;
		}
		else {
			Node *placeholder2 = head;
			Node *previous = NULL;
			while (placeholder2 != NULL && 
				   placeholder2->value != val) {
				previous = placeholder2;
				placeholder2 = placeholder2->next;
			}
			previous->next = placeholder2->next;
			delete placeholder2;
		}
		numItems--;
	}

	/*
	clear

	Remove all nodes from the list.
	*/
	void clear() {
		while (head != NULL) {
			remove(head->value);
		}
		numItems = 0;
	}

	/*
	at

	Returns the value of the node at the given index. The list begins at index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index) {
		if ((index < 0) || (index >= size())) {
    		throw out_of_range("out of range");
		}

		Node *fake = head;
		int indexCounter = 0;
		while(fake != NULL) {
			if (indexCounter == index) {
				return fake->value;
			}
			indexCounter++;
			fake = fake->next;
		}
		assert (0);
	}

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size() {
		return numItems;
	}

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	string toString() {
		stringstream ss;
		
		Node *fakeItr = head;
		while (fakeItr != NULL) {
			if (fakeItr->next == NULL) {
				ss << fakeItr->value;
			}
			else {
				ss << fakeItr->value << " ";
			}
			fakeItr = fakeItr->next;
		}
		
		return ss.str();
	}

};