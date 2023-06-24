/*
    Student name: Phan Vinh Tien.
    
    Problem. 
        Define a integer sequence structure by using dynamic allocated 1-D array which has adding front, adding last, getting front, getting last, searching, and sorting operations. 
        Then define a set structure which has union, intersection, and difference operations. 
        In main funtion, enter 4 sets A, B, C, D; computing (A \cap B) \ (C \cup D).
*/

#include <bits/stdc++.h>

using namespace std;

// Sequence index starts from 0.
struct Sequence {
    int size;
    int capacity;
    int *array;

    Sequence() {}

    Sequence(int capacity) {
        this->size = 0;
        this->capacity = capacity;
        this->array = new int[capacity];
    }

    int sizeSequence();

    void insertFront(int data);
    void insertLast(int data);

    void removeFront();
    void removeLast();

    // Get the value, then remove this element.
    int getFront(); 
    int getLast(); 

    // Return first position if exist, else return -1.
    int searchSequence(int data); 
    
    // Sort in ascending order of data.
    void sortSequence();

    void printSequence();

    // Extra functions, which is used in below Set structure.
    //int at(int position); // Get the value at specific position.
    //bool remove(int data);
};

int Sequence::sizeSequence() {
    return size;
}

void Sequence::insertFront(int data) {
    if(size + 1 > capacity) return;
    else if(sizeSequence() == 0) {
        array[0] = data;
        ++size;
        return;
    }
    for(int index = sizeSequence() - 1; index >= 0; --index) array[index + 1] = array[index];
    array[0] = data;
    ++size;
}

void Sequence::insertLast(int data) {
    if(size + 1 > capacity) return;
    else if(sizeSequence() == 0) {
        array[0] = data;
        ++size;
        return;
    }
    array[sizeSequence()] = data;
    ++size;
}

void Sequence::removeFront() {
    if(sizeSequence() == 0) return;
    for(int index = 0; index < sizeSequence(); ++index) array[index] = array[index + 1];
    --size;
}

void Sequence::removeLast() {
    if(sizeSequence() == 0) return;
    --size;
}

int Sequence::getFront() {
    assert(sizeSequence() != 0);
    int temp = array[0];
    for(int index = 0; index < sizeSequence(); ++index) array[index] = array[index + 1];
    --size;
    return temp;
}

int Sequence::getLast() {
    assert(sizeSequence() != 0);
    int temp = array[size - 1];
    --size;
    return temp;
}

int Sequence::searchSequence(int data) {
    assert(sizeSequence() != 0);
    for(int index = 0; index < sizeSequence(); ++index) {
        if(array[index] == data) return index;
    }
    return -1;
}

void Sequence::sortSequence() {
    if(sizeSequence() == 0) return;
    for(int index = 0; index < sizeSequence(); ++index) {
        for(int _index = index + 1; _index < sizeSequence(); ++_index) {
            if(array[index] > array[_index]) swap(array[index], array[_index]);
        }
    }
}

void Sequence::printSequence() {
    if(sizeSequence() == 0) return;
    for(int index = 0; index < sizeSequence(); ++index) std::cout << array[index] << " ";
}

// Set index starts from 0.
struct Set {
    Sequence set;
    int size;

    Set(int capacity) {
        set.size = 0;
        set.capacity = capacity;
        set.array = new int[capacity];
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
    if(sizeSet() == 0) return 0;
    for(int index = 0; index < sizeSet(); ++index) {
        if(set.array[index] == data) return 1;
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
    Set *temp = new Set(sizeSet() + secondSet.sizeSet());
    for(int index = 0; index < sizeSet(); ++index) {
        temp->insert(set.array[index]);
    } 
    for(int index = 0; index < secondSet.sizeSet(); ++index) {
        temp->insert(secondSet.set.array[index]);
    } 
    return temp;
}

Set* Set::setIntersection(Set &secondSet) {
    Set *temp = new Set(min(sizeSet(), secondSet.sizeSet()));
    for(int index = 0; index < sizeSet(); ++index) {
        if(secondSet.contains(set.array[index])) temp->insert(set.array[index]);
    }
    return temp;
}

Set* Set::setDifference(Set &secondSet) {
    Set *temp = new Set(sizeSet());
    for(int index = 0; index < sizeSet(); ++index) {
        if(!secondSet.contains(set.array[index])) temp->insert(set.array[index]);
    }
    return temp;
}

int Set::sizeSet() {
    return size;
}

void Set::printSet() {
    set.printSequence();
}

int main () {
    int sizeA, sizeB, sizeC, sizeD;
    std::cout << "Enter the number of elements in set A (cardinality of set A): ";
    std::cin >> sizeA;
    std::cout << "Enter the number of elements in set B (cardinality of set B): ";
    std::cin >> sizeB;
    std::cout << "Enter the number of elements in set C (cardinality of set C): ";
    std::cin >> sizeC;
    std::cout << "Enter the number of elements in set D (cardinality of set D): ";
    std::cin >> sizeD;

    Set setA(sizeA), setB(sizeB), setC(sizeC), setD(sizeD);
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

    return 0;
}
