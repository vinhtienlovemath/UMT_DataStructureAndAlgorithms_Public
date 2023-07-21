/*
    Filename: SinglyLinkedList.h
*/

template<typename T>
class Node {
    public:
        T value;
        Node<T> *next;

        Node(T value): value(value), next(NULL) {}
};

template<typename T>
class LinkedList {
    private:
        int m_count;

    public:
        // The first node in the list or NULL if empty.
        Node<T> *head;

        // The last node in the list or NULL if empty.
        Node<T> *tail;

        // Constructor.
        LinkedList(): head(NULL), tail(NULL), m_count(0) {}

        // get() operation.
        Node<T> *get(int index);

        // insert() operation.
        void insertFront(T value);
        void insertLast(T value);
        void insertMiddle(T value, int index);

        // remove() operation.
        void removeFront();
        void removeLast();
        void removeMiddle(int index);

        // Additional operations.
        int size(); 
        void print();
        int search(T value);
};

