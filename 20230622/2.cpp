/*
    Student name: Phan Vinh Tien.
    
    Problem. 
        Define a integer sequence structure by using linked list which has adding front, adding last, getting front, getting last, searching, and sorting operations. 
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
    Node *tail;
    int size;

    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }

    int sizeList();

    void insertFront(int data);
    void insertLast(int data);

    // Get the value, then remove this node.
    int getFront(); 
    int getLast(); 

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
        tail = newNode;
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
        tail = newNode;
        ++size;
        return;
    }

    tail->next = newNode;
    tail = newNode;
    ++size;
}

int LinkedList::getFront() {
    assert(head != NULL);

    Node *temp = head;
    int tempData = temp->data;
    head = temp->next;
    --size;
    delete temp;
    return tempData;
}

int LinkedList::getLast() {
    assert(head != NULL);

    Node *temp = head;
    if(temp->next == NULL) {
        int tempData = temp->data;
        head = NULL;
        --size;
        delete temp;
        return tempData;
    }

    else {
        while(temp->next->next != NULL) {
            temp = temp->next;
        }
        Node *last = temp->next;
        int lastData = last->data;
        temp->next = NULL;
        --size;
        delete last;
        return lastData;
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
    assert(head != NULL);

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
    if(head == NULL) return;
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

int main () {
    // Each time can insert 1 number. Howerver, unlimited number of entries and calculations until entering 0. 
    Set setA, setB, setC, setD, *iAB, *uCD, *answer;
    int temp;
    while(1) {
        std::cout << "---------------MENU---------------\n";
        std::cout << "0. Exit the program.\n";
        std::cout << "1. Enter element in set A.\n";
        std::cout << "2. Enter element in set B.\n";
        std::cout << "3. Enter element in set C.\n";
        std::cout << "4. Enter element in set D.\n";
        std::cout << "5. Compute (A \\cap B) \\setminus (C \\cup D).\n";
        std::cout << "----------------------------------\n";
        std::cout << "Enter your choice: ";

        int choice; std::cin >> choice;
        
        if(choice == 0) break;

        else if(choice == 1) {
            std::cout << "Enter element in set A: ";
            std::cin >> temp;
            setA.insert(temp);
            std::cout << "Elements of set A: ";
            setA.printSet(); std::cout << '\n';
        }

        else if(choice == 2) {
            std::cout << "Ente element in set B: ";
            std::cin >> temp;
            setB.insert(temp);
            std::cout << "Elements of set B: ";
            setB.printSet(); std::cout << '\n';
        }

        else if(choice == 3) {
            std::cout << "Enter element in set C: ";
            std::cin >> temp;
            setC.insert(temp);
            std::cout << "Elements of set C: ";
            setC.printSet(); std::cout << '\n';
        }

        else if(choice == 4) {
            std::cout << "Enter element in set D: ";
            std::cin >> temp;
            setD.insert(temp);
            std::cout << "Elements of set D: ";
            setD.printSet(); std::cout << '\n';
        }

        else if(choice == 5) {
            iAB = setA.setIntersection(setB);
            uCD = setC.setUnion(setD);
            answer = iAB->setDifference(*uCD);
            
            std::cout << "Elements of set A: ";
            setA.printSet(); std::cout << '\n';
            std::cout << "Elements of set B: ";
            setB.printSet(); std::cout << '\n';
            std::cout << "Elements of set C: ";
            setC.printSet(); std::cout << '\n';
            std::cout << "Elements of set D: ";
            setD.printSet(); std::cout << '\n';
            std::cout << "Elements of (A \\cap B) \\setminus (C \\cup D) are: ";
            answer->printSet(); std::cout << '\n';
        }

        else std::cout << "Wrong choice. Choose again.";
    }

    return 0;
}
