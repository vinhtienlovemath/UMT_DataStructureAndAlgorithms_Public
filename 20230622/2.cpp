/*
    Student name: Phan Vinh Tien.
    
    Problem. 
        Define a integer sequence structure by using linked list. 
        Then define a set structure which has union, intersection, and difference operations. 
        In main funtion, enter 4 sets A, B, C, D; computing (A \cap B) \ (C \cup D).
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *next;

    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

// LinkedList index starts from 1.
struct LinkedList {
    Node *head;
    int size;

    LinkedList() {
        this->head = NULL;
        this->size = 0;
    }

    int sizeList();

    void insertFront(int data);
    void insertLast(int data);

    // Get the value, then remove this node.
    void getFront(); 
    void getLast(); 

    // Return first position if exist, else return -1.
    int searchList(int data); 
    
    // Sort in ascending order of data.
    void sortList();

    void printList();

    // Extra functions, which is used in below Set structure.
    int at(int position); // Get the value at specific position.
    bool remove(int data);
};

int LinkedList::sizeList() {
    return size;
}

void LinkedList::insertFront(int data) {
    Node *newNode = new Node(data);
    
    if(head == NULL) {
        head = newNode;
        ++size;
        return;
    }

    newNode->next = head;
    head = newNode;
    ++size;
}

void LinkedList::insertLast(int data) {
    Node *newNode = new Node(data);

    if(head == NULL) {
        head = newNode;
        ++size;
        return;
    }

    Node *temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    ++size;
}

void LinkedList::getFront() {
    if(head == NULL) return;

    Node *temp = head;
    head = temp->next;
    --size;
    delete temp;
}

void LinkedList::getLast() {
    if(head == NULL) return;

    Node *temp = head;
    if(temp->next == NULL) {
        head = NULL;
        --size;
        delete temp;
    }

    else {
        while(temp->next->next != NULL) {
            temp = temp->next;
        }
        Node *last = temp->next;
        temp->next = NULL;
        --size;
        delete last;
    }
}

void LinkedList::printList() {
    if(head == NULL) return;

    Node *temp = head;
    while(temp != NULL) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
}

int LinkedList::searchList(int data) {
    if(head == NULL) return -1;

    Node *temp = head;
    int returnIndex = 1;
    for(int index = 1; index <= sizeList(); ++index) {
        if(temp->data == data) return returnIndex;
        temp = temp->next;
        ++returnIndex;
    }
    return -1;
}

void LinkedList::sortList() {
    for(Node *index = head; index != NULL; index = index->next) {
        for(Node *_index = index->next; _index != NULL; _index = _index->next) {
            if(index->data > _index->data) {
                int temp = index->data;
                index->data = _index->data;
                _index->data = temp;
            } 
        }
    }
}

int LinkedList::at(int position) {
    Node *temp = head;
    for(int index = 1; index < position; ++index) {
        if(temp->next == NULL) exit(1);
        temp = temp->next;
    }
    return temp->data;
}

// Set index starts from 1.
struct Set {
    LinkedList set;
    int size;

    Set() {
        set.head = NULL;
        set.size = 0;
        size = set.size;
    }

    bool contains(int data);
    bool insert(int data);

    Set* setUnion(Set &secondSet);
    Set* setIntersection(Set &secondSet);
    Set* setDifference(Set &secondSet);

    int sizeSet();
    void printSet();   
};


bool Set::contains(int data) {
    if(set.head == NULL) return 0;
    Node *temp = set.head;
    for(int index = 1; index <= sizeSet(); ++index) {
        if(temp->data == data) return 1;
        temp = temp->next;
    }
    return 0;
}

bool Set::insert(int data) {
    if(contains(data)) return 0;
    else {
        set.insertLast(data);
        ++size;
        return 1;
    }
}

Set* Set::setUnion(Set &secondSet) {
    Set *temp = new Set();
    for(int index = 1; index <= sizeSet(); ++index) {
        temp->insert(set.at(index));
    } 
    for(int index = 1; index <= secondSet.sizeSet(); ++index) {
        temp->insert(secondSet.set.at(index));
    } 
    return temp;
}

Set* Set::setIntersection(Set &secondSet) {
    Set *temp = new Set();
    for(int index = 1; index <= sizeSet(); ++index) {
        if(secondSet.contains(set.at(index))) temp->insert(set.at(index));
    }
    return temp;
}

Set* Set::setDifference(Set &secondSet) {
    Set *temp = new Set();
    for(int index = 1; index <= sizeSet(); ++index) {
        if(!secondSet.contains(set.at(index))) temp->insert(set.at(index));
    }
    return temp;
}

int Set::sizeSet() {
    return size;
}

void Set::printSet() {
    set.printList();
}

void input(Set &setA, Set &setB, Set &setC, Set &setD) {
    int sizeA, sizeB, sizeC, sizeD;
    std::cout << "Enter the number of elements in set A (cardinality of set A): ";
    std::cin >> sizeA;
    std::cout << "Enter the number of elements in set B (cardinality of set B): ";
    std::cin >> sizeB;
    std::cout << "Enter the number of elements in set C (cardinality of set C): ";
    std::cin >> sizeC;
    std::cout << "Enter the number of elements in set D (cardinality of set D): ";
    std::cin >> sizeD;

    std::cout << "Enter " << sizeA << " elements in set A: ";
    for(int index = 1; index <= sizeA; ++index) {
        int temp; 
        std::cin >> temp;
        setA.insert(temp);
    }
    std::cout << "Enter " << sizeB << " elements in set B: ";
    for(int index = 1; index <= sizeB; ++index) {
        int temp; 
        std::cin >> temp;
        setB.insert(temp);
    }
    std::cout << "Enter " << sizeC << " elements in set C: ";
    for(int index = 1; index <= sizeC; ++index) {
        int temp; 
        std::cin >> temp;
        setC.insert(temp);
    }
    std::cout << "Enter " << sizeD << " elements in set D: ";
    for(int index = 1; index <= sizeD; ++index) {
        int temp; 
        std::cin >> temp;
        setD.insert(temp);
    }
}

void output(Set setA, Set setB, Set setC, Set setD) {
    Set *iAB = setA.setIntersection(setB);
    Set *uCD = setC.setUnion(setD);
    Set *answer = iAB->setDifference(*uCD);
    
    std::cout << "Elements of set A: ";
    setA.printSet(); std::cout << '\n';
    std::cout << "Elements of set B: ";
    setB.printSet(); std::cout << '\n';
    std::cout << "Elements of set C: ";
    setC.printSet(); std::cout << '\n';
    std::cout << "Elements of set D: ";
    setD.printSet(); std::cout << '\n';
    std::cout << "Elements of (A \\cap B) \\setminus (C \\cup D) are: ";
    answer->printSet();
}

int main () {
    Set setA, setB, setC, setD;
    input(setA, setB, setC, setD);
    output(setA, setB, setC, setD);

    return 0;
}
