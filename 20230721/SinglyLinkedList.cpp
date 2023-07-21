#include <bits/stdc++.h>
#include "SinglyLinkedList.hpp"

using namespace std;

/*
    Constructor of LinkedList class.
*/

template<typename T>
LinkedList<T>::LinkedList() {
    this->head = NULL;
    this->tail = NULL;
    m_count = 0;
}

/*
    Fetch an item in LinkedList class.
    It will return the node of the selected index or NULL if the selected index is out of bounds.
*/
template<typename T>
Node<T>* LinkedList<T>::get(int index) {
    // Check if the index is out of bound.
    if(index < 0 || index > m_count) return NULL;

    // Start from head.
    Node<T> *node = head;

    // Iterate through the linked list elements until it finds the selected index.
    for(int i = 0; i < index; ++i) node = node->next;

    return node;
}

/*
    Insert an item in the LinkedList class. There are 4 cases for this operation (linked list has n elements and index is counted from 0).
    1. The new item is inserted at the beginning of the linked list (index = 0) so it becomes the new head.
    2. The new item is inserted at the ending of the linked list (index = n - 1) so it becomes the new tail.
    3. The new item is inserted to an empty linked list. Thus, both head and tail will point to this item.
    4. The new item is inserted in the other position of the linked list, where index = 1, 2,..., n - 2.

    Time complexity: O(n). The best case is O(1) when inserting at front and last.
*/
template<typename T>
void LinkedList<T>::insertFront(T value) {
    // Create a new node.
    Node<T> *node = new Node<T>(value);

    // The current head will no longer become of head so the next pointer of the new node will point to the current head.
    node->next = head;

    // The new node now becomes the head.
    head = node;

    // If the linked list is empty, the tail is also the head.
    if(m_count == 0) tail = head;

    // One element is added.
    ++m_count;
} // Solve case 1 and 3.

template<typename T>
void LinkedList<T>::insertLast(T value) {
    // If the linked list is empty, we invoke insertFront().
    if(m_count == 0) {
        insertFront(value);
        return;
    }

    // Create a new node.
    Node<T> *node = new Node<T>(value);

    // The current tail will no longer become of tail so the next pointer of the current tail will point to the new node.
    tail->next = node;

    // The new node now becomes the tail.
    tail = node;

    // One element is added.
    ++m_count;
} // Solve case 2.

template<typename T>
void LinkedList<T>::insertMiddle(T value, int index) {
    // Check if the index is out of bound.
    if(index < 0 || index > m_count - 1) return;

    // If inserting a new head.
    if(index == 0) {
        insertFront(value);
        return;
    }

    // If inserting a new tail.
    else if(index == m_count - 1) {
        insertLast(value);
        return;
    } 

    // Find previous of target node from the head.
    Node<T> *prevNode = head;

    // Traverse the elements until the selected index is found.
    for(int i = 0; i < index - 1; ++i) prevNode = prevNode->next;

    // Create the next node which is the element after previous node.
    Node<T> *nextNode = prevNode->next;

    // Create a new node.
    Node<T> *node = new Node<T>(value);

    // Insert this new node between the previous node and the next node.
    node->next = nextNode;
    prevNode->next = node;

    // One element is added.
    ++m_count;
} // Solve case 4.

/*
    Getting the index of the selected item in the linked list.
    We traverse the linked list elements until the select value is matched, the method will return its current position index.
*/

template<typename T>
int LinkedList<T>::search(T value) {
    // If the linked list is empty, just return NOT_FOUND.
    if(m_count == 0) return -1;

    // Need to count the index.
    int index = 0;

    // Traverse from the head.
    Node<T> *node = head;

    // Travese until the selected value is matched with the value of the current position.
    while(node->value != value) {
        ++index;
        node = node->next;
        
        // This will happen if the selected value is NOT_FOUND.
        if(node == NULL) return -1;
    }
    
    return index;
}

/*
    Remove an item from the linked list. There are 3 cases:
    1. The removed item is in the head (index = 0).
    2. The removed item is in the tail (index = n - 1).
    3. The remove item is in the other posiion of the linked list, where index = 1, 2,..., n - 2.
*/

template<typename T>
void LinkedList<T>::removeFront() {
    // Do nothing if the linked list is empty.
    if(m_count == 0) return;

    // Save the current head to a new node.
    Node<T> *node = head;

    // Point the head pointer to the elements next to the current head.
    head = head->next;

    // Now, it is safe to remove the first element.
    delete node;

    // One element is removed.
    --m_count;
} // Solve case 1.

template<typename T>
void LinkedList<T>::removeLast() {
    // Do nothing if the linked list is empty.
    if(m_count == 0) return;

    // If list element is only one, call removeFront().
    if(m_count == 1) {
        removeFront();
        return;
    }

    // Find previous node of tail from the head.
    Node<T> *prevNode = head;

    // This is the candidate of removed items which is the elements next to the prevNode.
    Node<T> *node = head->next;

    // Traverse the elements until the last element.
    while(node->next != NULL) {
        prevNode = prevNode->next;
        node = node->next;
    }

    // The prevNode now becomes tail so the next pointer of the prevNode point to NULL.
    prevNode->next = NULL;
    tail = prevNode;

    // Now it is safe to remove the last element.
    delete node;

    // One element is removed.
    --m_count;    
} // Solve case 2.

/*
    Print all elements of the linked list.
*/

template<typename T>
void LinkedList<T>::print() {
    if(m_count == 0) return;

    Node<T> *node = head;
    while(node != NULL) {
        cout << node->value << " ";
        node = node->next;
    }
}

int main() {
    LinkedList<float> list;
    list.insertFront(5.2);
    list.insertLast(10.0);
    list.print();

    return 0;
}
