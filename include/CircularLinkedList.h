#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <iostream>

template <typename T>
class Node
{
public:
    T data;
    Node *next;

    Node(T value) : data(value), next(nullptr) {}
};



template <typename T>
class CircularLinkedList;

template <typename T>
class CircularIterator
{
public:
    CircularIterator(Node<T> *node, Node<T> *head) : current(node), head(head) {}

    T &operator*()
    {
        return current->data;
    }

    CircularIterator &operator++()
    {
        if (current)
        {
            current = current->next;
        }
        return *this;
    }

    bool operator!=(const CircularIterator &other) const
    {
        return current != other.current;
    }

    bool isEnd() const
    {
        return current->next == head;
    }

private:
    Node<T> *current;
    Node<T> *head;
};

template <typename T>
class CircularLinkedList
{
public:
    Node<T> *head;

    CircularLinkedList() : head(nullptr) {}

    void append(T value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (!head)
        {
            head = newNode;
            newNode->next = head; 
        }
        else
        {
            Node<T> *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }
    void remove(T value)
    {
        if (!head)
            return;

        Node<T> *current = head;
        Node<T> *previous = nullptr;

        do
        {
            if (current->data == value)
            {
                if (current == head)
                {

                    if (head->next == head)
                    { 
                        delete head;
                        head = nullptr;
                    }
                    else
                    {
                        Node<T> *tail = head;
                        while (tail->next != head)
                        {
                            tail = tail->next;
                        }
                        tail->next = head->next; 
                        Node<T> *temp = head;
                        head = head->next; 
                        delete temp;
                    }
                }
                else
                {
                    previous->next = current->next;
                    delete current;
                }
                return;
            }
            previous = current;
            current = current->next;
        } while (current != head);
    }
    CircularIterator<T> begin()
    {
        return CircularIterator<T>(head, head); 
    }
    CircularIterator<T> end()
    {
        return CircularIterator<T>(nullptr, head);
    }
    ~CircularLinkedList()
    {
        if (!head)
            return;

        Node<T> *current = head;
        Node<T> *nextNode;

        do
        {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);

        head = nullptr;
    }
};


#endif