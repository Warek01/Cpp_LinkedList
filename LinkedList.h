// Seminar work on linked lists
// Variable is being created as LinkedList<vartype>
// May have problems with swapping (unsufficient time for debugging)

#pragma once
#include <iostream>

template <typename T>
class LinkedList
{
private:

	struct Node
	{
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

	Node* m_firstNode = nullptr;
	Node* m_lastNode = nullptr;
	size_t m_size = 0;

	/////////////////////////////////////////////////
	// Private methods

	/* Return node by index */
	Node* m_getIndex(int index)
	{
		if (index < -1 || index > m_size - 1) throw std::invalid_argument("Invalid index");
		else if (index == -1) return m_lastNode;
		else
		{
			Node* node = m_firstNode;

			for (int i = 0; i < index; i++)
				node = node->next;

			return node;
		}
	}

	void m_swap(Node* a, Node* b)
	{
		if (m_firstNode == a) m_firstNode = b;
		else if (m_firstNode == b) m_firstNode = a;
		else if (m_lastNode == a) m_lastNode = b;
		else if (m_lastNode == b) m_lastNode = a;

		Node* n = a->next,
			* p = a->prev;

		a->next = b->next;
		if (a->next == b || b->prev == a)
		{
			b->next = a;
			a->prev = b;
		}
		else
		{
			a->prev = b->prev;
			b->next = n;
		}
		b->prev = p;
	}

public:
	/////////////////////////////////////////////////
	// Constructors
	LinkedList() { }

	/////////////////////////////////////////////////
	// Destructor
	~LinkedList() { empty(); }

	/////////////////////////////////////////////////
	// Methods

	/* Append data to list */
	LinkedList<T>& append(T data)
	{
		Node* node = new Node{ data, nullptr, m_lastNode };

		if (!m_firstNode)
		{
			m_firstNode = node;
			m_lastNode = node;
		}
		else
		{
			m_lastNode->next = node;
			m_lastNode = node;
		}

		m_size++;

		return *this;
	}

	/* Insert data on index to list */
	LinkedList<T>& insert(int index, T data)
	{
		if (index > m_size - 1 || index < -1) throw std::invalid_argument("Invalid index");

		Node* indexNode = m_getIndex(index),
			* node = new Node{ data, nullptr, nullptr };

		if (index == -1 || index == m_size - 1)
		{
			m_lastNode = node;
			indexNode->next = node;
			node->prev = indexNode;
		}
		else if (index == 0)
		{
			m_firstNode->prev = node;
			node->next = m_firstNode;
			m_firstNode = node;
		}
		else
		{
			node->next = indexNode->next;
			node->prev = indexNode;
			indexNode->next->prev = node;
			indexNode->next = node;
		}

		m_size++;

		return *this;
	}

	/* Remove element from a given index */
	LinkedList<T>& remove(int index)
	{
		Node* node = m_getIndex(index);

		if (index == -1 || index == m_size - 1)
		{
			node->prev->next = nullptr;
			m_lastNode = node->prev;
		}
		else if (index == 0)
		{
			m_firstNode = node->next;
			node->next->prev = nullptr;
		}
		else
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
		}

		delete node;
		m_size--;

		return *this;
	}

	/* First element */
	T getFirst()
	{
		return m_firstNode ? m_firstNode->data : NULL;
	}

	/* Last element */
	T getLast()
	{
		return m_lastNode ? m_lastNode->data : NULL;
	}

	/* Size of list */
	size_t size() { return m_size; }

	/* Sorting list (only work for comparable data types) */
	LinkedList<T>& sort()
	{
		Node* current = m_firstNode,
			* comparable = current->next;

		for (int i = 0; i < size() - 1; i++)
			for (int j = i + 1; j < size(); j++)
				if (m_getIndex(i)->data < m_getIndex(j)->data)
					m_swap(m_getIndex(i), m_getIndex(j));

		return *this;
	}

	/* Clear list */
	LinkedList<T>& empty()
	{
		if (m_size == 0) return *this;

		Node* node = m_firstNode;

		while (node != m_lastNode)
		{
			node = node->next;
			delete node->prev;
		}

		delete node;

		m_size = 0;
		m_firstNode = nullptr;
		m_lastNode = nullptr;

		return *this;
	}

	LinkedList<T>& swap(int i, int j)
	{
		if (i < 0 || j < 0 || i > size() - 1 || j > size() - 1) throw std::invalid_argument("Wrong index");

		m_swap(m_getIndex(i), m_getIndex(j));

		return *this;
	}

	/////////////////////////////////////////////////
	// Operators

	// Get Item by index
	/* Indexing operator */
	T operator[](int index)
	{
		return m_getIndex(index)->data;
	}

	// for std::cout << LinkedList
	/* Put operator */
	friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
	{
		Node* node = list.m_firstNode;

		while (node)
		{
			out << node->data << '\n';
			node = node->next;
		};

		return out;
	}
};
