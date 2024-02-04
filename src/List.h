#pragma once
#include <iostream>

// Header-only, templated Doubly Linked List class

// Supports: AddFront, AddBack, AddAt, DeleteFront, DeleteBack, DeleteAt, ReadList, FindAt, FindIndex, DoesExist, IsEmpty, GetSize

template<typename type>
class List 
{
public:
    List()
    {
        m_Head = new Node(type());
        m_Tail = new Node(type());
        m_Head->m_Next = m_Tail;
        m_Tail->m_Prev = m_Head;
        m_Size = 0;
    }
    ~List()
    {
        while (m_Head != nullptr)
        {
            Node* temp = m_Head;
            m_Head = m_Head->m_Next;
            delete temp;
        }
    }
public:
    // Add methods
    void AddFront(const type& m_Data) 
    {
        Node* newNode = new Node(m_Data);
        newNode->m_Next = m_Head->m_Next;
        newNode->m_Prev = m_Head;
        m_Head->m_Next->m_Prev = newNode;
        m_Head->m_Next = newNode;
        m_Size++;
    }
    void AddBack(const type& m_Data) 
    {
        Node* newNode = new Node(m_Data);
        newNode->m_Prev = m_Tail->m_Prev;
        newNode->m_Next = m_Tail;
        m_Tail->m_Prev->m_Next = newNode;
        m_Tail->m_Prev = newNode;
        m_Size++;
    }
    void AddAt(const type& m_Data, const int& _Index)
    {
        if (_Index > m_Size || _Index < 0) return;

        Node* temp = m_Head; // no need for head->next here because we add at that index
        for (int i = 0; i < _Index; i++)
        {
            if (temp->m_Next == m_Tail) break;
            temp = temp->m_Next;
        }

        Node* newNode = new Node(m_Data);
        newNode->m_Next = temp->m_Next;
        newNode->m_Prev = temp;
        temp->m_Next->m_Prev = newNode;
        temp->m_Next = newNode;
        m_Size++;
    }
public:
    // Delete methods
    void DeleteFront() 
    {
        if (m_Head->m_Next == m_Tail) // if there is nothing to delete
            return;

		// Adjust previous and next pointers
        Node* temp = m_Head->m_Next;
        m_Head->m_Next = temp->m_Next;
        temp->m_Next->m_Prev = m_Head;

		delete temp; // delete element
        m_Size--;
    }
    void DeleteBack() 
    {
        if (m_Tail->m_Prev == m_Head) // if there is nothing to delete
            return;

		// Adjust previous and next pointers
        Node* temp = m_Tail->m_Prev;
        m_Tail->m_Prev = temp->m_Prev;
        temp->m_Prev->m_Next = m_Tail;

		delete temp; // delete element
        m_Size--;
    }
    void Delete(type m_Data)
    {
        // if there is nothing to find
        if (m_Size == 0)
            throw std::out_of_range("List is empty");

        // find that element 
        Node* temp = m_Head->m_Next;
        for (int i = 0; i < m_Size; i++)
        {
            if (m_Data == temp->m_Data)
                break;
            temp = temp->m_Next;
        }

        if (temp == m_Tail)
            throw std::out_of_range("Element not found"); // if index is out of range

        // Adjust previous and next pointers
        temp->m_Prev->m_Next = temp->m_Next;
        temp->m_Next->m_Prev = temp->m_Prev;

        delete temp;  // delete element
        m_Size--;
    }
    void DeleteAt(int _Index)
    {
        if (m_Size == 0) // if there is nothing to delete
            return;

        // find element with that index
        Node* temp = m_Head->m_Next;
        for (int i = 0; i < m_Size; i++) 
        {
            if (i == _Index) break;
            temp = temp->m_Next;
        }

		if (temp == m_Tail) 
            return; // if index is out of range

		// Adjust previous and next pointers
        temp->m_Prev->m_Next = temp->m_Next;
        temp->m_Next->m_Prev = temp->m_Prev;

		delete temp;  // delete element
        m_Size--;
    }
public:
	// Find methods
    type& Find(type _Data)
	{
		// if there is nothing to find
		if (m_Size == 0)
			throw std::out_of_range("List is empty");

        // find that element 
        Node* temp = m_Head->m_Next;
        for (int i = 0; i < m_Size; i++)
        {
            if (_Data == temp->m_Data) return temp->m_Data;
            temp = temp->m_Next;
        }

        throw std::out_of_range("Index out of bounds");

    }
    type& FindAt(int _Index)
    {
        // if indecies are small, brute force way // 30% faster
        if (_Index == 0) return m_Head->m_Next->m_Data;
        if (_Index == 1) return m_Head->m_Next->m_Next->m_Data;
        if (_Index == 2) return m_Head->m_Next->m_Next->m_Next->m_Data;
        if (_Index == 3) return m_Head->m_Next->m_Next->m_Next->m_Next->m_Data;
        if (_Index == 4) return m_Head->m_Next->m_Next->m_Next->m_Next->m_Next->m_Data;

        // if index is out of bounds
        if (_Index < 0 || _Index >= m_Size)
			throw std::out_of_range("Index out of bounds");

        // if they are bigger, this way
        Node* temp = m_Head->m_Next;
        for (int i = 0; i < _Index; i++)
        {
            temp = temp->m_Next;
        }
        return temp->m_Data;
    }
    int FindIndex(type _Data)
    {
        // if there is nothing to find 
        if (m_Size == 0) 
            throw std::out_of_range("List is empty");

        Node* temp = m_Head->m_Next;
        for (int i = 0; i < m_Size; i++)
        {
            if (_Data == temp->m_Data) return i;
            temp = temp->m_Next;
        }
		return -1;
    }
public:
	// Other methods
    inline int GetSize()
    {
        return m_Size;
    }
    bool DoesExist(type m_Data)
    {
        // if there is nothing to find
        if (m_Size == 0)
            return false;

        Node* temp = m_Head->m_Next;
        while (temp != m_Tail)
        {
            if (m_Data == temp->m_Data)
            {
                return true; // if element exists
            }
            temp = temp->m_Next;
        }
        return false; // if element doesn't exist
    }
    inline bool IsEmpty()
    {
        if (m_Size <= 0) 
            return true;
        else
            return false;
    }
    void ReadList() {
        // if there is nothing to read
        if (m_Size == 0)
        {
			std::cout << "List is empty" << std::endl;
            return;
        }

        Node* temp = m_Head->m_Next;
        std::cout << "Elements of List are: " << std::endl;
        while (temp != m_Tail) 
        {
            std::cout << temp->m_Data << " ";
            temp = temp->m_Next;
        }
        std::cout << std::endl;
    }
private:
	// Data structure
    struct Node
    {
        type m_Data;
        Node* m_Next;
        Node* m_Prev;

        Node(const type& _data) : m_Data(_data), m_Next(nullptr), m_Prev(nullptr) {}
    };
    Node* m_Head;
    Node* m_Tail;
    int m_Size;
};