#pragma once
#include <iostream>

// Templated Doubly Linked List class
// for primitive types only

// Supports: AddFront, AddBack, AddAt, DeleteFront, DeleteBack, DeleteAt, 
//  ReadList, NodeAt, FindIndex, DoesExist, IsEmpty, GetSize

template<typename type>
class List {
private:
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

    void AddAt(const type& m_Data, const int& index) 
    {
        if (index > m_Size || index < 0) return;

        Node* temp = m_Head; // no need for head->next here because we add at that index
        for (int i = 0; i < index; i++)
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

    // Delete methods

    void DeleteFront() 
    {
        // if there is nothing to delete
        if (m_Head->m_Next == m_Tail) 
            return;

        Node* temp = m_Head->m_Next;
        m_Head->m_Next = temp->m_Next;
        temp->m_Next->m_Prev = m_Head;

        delete temp;
        m_Size--;
    }

    void DeleteBack() 
    {
        // if there is nothing to delete
        if (m_Tail->m_Prev == m_Head) 
            return;

        Node* temp = m_Tail->m_Prev;
        m_Tail->m_Prev = temp->m_Prev;
        temp->m_Prev->m_Next = m_Tail;

        delete temp;
        m_Size--;
    }

    void DeleteAt(int index) 
    {
		// if there is nothing to delete
        if (m_Head->m_Next == m_Tail || index >= m_Size || index < 0) 
            return;

        Node* temp = m_Head->m_Next;
        for (int i = 0; i < index; i++)
        {
            if (temp->m_Next == m_Tail) break;
            temp = temp->m_Next;
        }
        temp->m_Prev->m_Next = temp->m_Next;
        temp->m_Next->m_Prev = temp->m_Prev;

        delete temp;
        m_Size--;
    }

	// Read methods

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

    type& NodeAt(int index)
    {
        // if indecies are small, brute force way // 30% faster
        if (index == 0) return m_Head->m_Next->m_Data;
        if (index == 1) return m_Head->m_Next->m_Next->m_Data;
        if (index == 2) return m_Head->m_Next->m_Next->m_Next->m_Data;
        if (index == 3) return m_Head->m_Next->m_Next->m_Next->m_Next->m_Data;
        if (index == 4) return m_Head->m_Next->m_Next->m_Next->m_Next->m_Next->m_Data;

        // if index is out of bounds
		type ErrorReturn = type(); 
        if (index < 0 || index >= m_Size) return ErrorReturn;

        // if they are bigger, this way
        Node* temp = m_Head->m_Next;
        for (int i = 0; i < index; i++)
        {
            temp = temp->m_Next;
        }
        return temp->m_Data;
    }

    int FindIndex(type m_Data)
    {
        // if there is nothing to find 
        if (m_Size == 0) 
            return -1; // returns invalid index

        Node* temp = m_Head->m_Next;
        for (int i = 0; i < m_Size; i++)
        {
            if (m_Data == temp->m_Data) return i;
            temp = temp->m_Next;
        }
    }

	// Check methods

    bool DoesExist(type m_Data)
    {
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

	// Get methods

    inline int GetSize()
    {
        return m_Size;
    }

};