
#include <sstream>
#include <map>
#include <chrono>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;

//************************************************************************
//A class I designed to help keep track of how much memory you allocate
//Do not modify, this is not part of your assignment, it just helps test it.
//For this to work, a class needs to inherit off of this one. 
//Then this does the rest of the work, since it 
//overloads new, new[], delete, and delete[].
//************************************************************************
class ManageMemory {
public:

  static std::size_t getTotalSize() {
    std::size_t total = 0;
    std::map<void*, std::size_t>::iterator iter;
    for (iter = mapOfAllocations.begin(); iter != mapOfAllocations.end(); ++iter) {
      total += iter->second;
    }
    return total;
  }

  //I overloaded the new and delete keywords so I could manually track allocated memory.
  void* operator new(std::size_t x) {
    void* ptr = ::operator new(x);
    mapOfAllocations[ptr] = x;
    return ptr;
  }
  void* operator new[](std::size_t x) {
    void* ptr = ::operator new[](x);
    mapOfAllocations[ptr] = x;
    return ptr;
  }
    void operator delete(void* x) {
    mapOfAllocations.erase(x);
    ::operator delete(x);
  }
  void operator delete[](void* x) {
    mapOfAllocations.erase(x);
    ::operator delete[](x);
  }
private:
  static std::map<void*, std::size_t> mapOfAllocations;
};
std::map<void*, std::size_t> ManageMemory::mapOfAllocations;

//******************
//The node class
//******************
template <typename T>
class Node : public ManageMemory {
public:
  T data{};
  Node<T>* backward{ nullptr };
  Node<T>* forward{ nullptr };

};


//******************
//The linked list base class
//This contains within it a class declaration for an iterator
//******************
template <typename T>
class BaseDoublyLinkedList : public ManageMemory {
public:

  //public members of the DoublyLinkedList class
  ~BaseDoublyLinkedList();
  string getListAsString();
  string getListBackwardsAsString();
  void pushFront(const T&);
  void pushBack(const T&);
  T get(const unsigned int index) const { cerr << "Error: You didn't override this base class method yet" << endl; T temp{}; return temp; }
  T& operator[](const unsigned int index) const { cerr << "Error: You didn't override this base class method yet" << endl; T temp{}; return temp; }
  void insert(const unsigned int index, const T& value) { cerr << "Error: You didn't override this base class method yet" << endl; }
  void remove(const unsigned int index) { cerr << "Error: You didn't override this base class method yet" << endl; }
  void removeAllInstances(const T& value) { cerr << "Error: You didn't override this base class method yet" << endl; }

protected:

  Node<T>* first{ nullptr };
  Node<T>* last{ nullptr };

};

template <typename T>// destructor
BaseDoublyLinkedList<T>::~BaseDoublyLinkedList() {
  Node<T>* temp = this->first;

  while (first) {
    first = first->forward;
    delete temp;
    temp = first;
  }
}

template <typename T>
void BaseDoublyLinkedList<T>::pushFront(const T& item) {
  Node<T>* temp = new Node<T>();

  temp->data = item;
  if (!first) {
    // Scenario: List is empty
    last = temp;
  }
  else {
    first->backward = temp;
    temp->forward = first;
  }
  first = temp;
}

template <typename T>
void BaseDoublyLinkedList<T>::pushBack(const T& item) {
  Node<T>* temp = new Node<T>();

  temp->data = item;
  if (!first) {
    // Scenario: List is empty
    first = temp;
  }
  else {
    last->forward = temp;
    temp->backward = last;
  }
  last = temp;
}


//This method helps return a string representation of all nodes in the linked list, do not modify.
template <typename T>
string BaseDoublyLinkedList<T>::getListAsString() {
  stringstream ss;
  if (!first) {
    ss << "The list is empty.";
  }
  else {

    Node<T>* currentNode{ first };
    ss << currentNode->data;
    currentNode = currentNode->forward;

    while (currentNode) {
      ss << " " << currentNode->data;
      currentNode = currentNode->forward;
    };
  }
  return ss.str();
}

//This method helps return a string representation of all nodes in the linked list, do not modify.
template <typename T>
string BaseDoublyLinkedList<T>::getListBackwardsAsString() {
  stringstream ss;
  if (!first) {
    ss << "The list is empty.";
  }
  else {

    Node<T>* currentNode{ last };
    ss << currentNode->data;
    currentNode = currentNode->backward;

    while (currentNode) {
      ss << " " << currentNode->data;
      currentNode = currentNode->backward;
    };
  }
  return ss.str();
}

template <typename T>
class DoublyLinkedList : public BaseDoublyLinkedList<T> {

public:
  T get(const unsigned int index) const;
  T& operator[](const unsigned int index) const;
  void insert(const unsigned int index, const T& value);
  void remove(const unsigned int index);
  void removeAllInstances(const T& value);
private:

};

template <typename T>
T DoublyLinkedList<T>::get(const unsigned int index) const {

    
  

    //error check if the index is less than 0, dont have to run the loop 
    if(index < 0) {
        throw std::out_of_range("Index out of range");
    }

    Node<T>* temp1 = this->first;

    int count{ 1 };

    //running the loop to count how many items in the linked list
    while (temp1->forward != NULL) {
        temp1 = temp1->forward;
        count++;
    };

    //error checking if the index is greater than count
     if (index > count) {
         throw std::out_of_range("Index out of range");
    }

     //initilalize the second temp to first
     Node<T>* temp2 = this->first;

     //if the index is 0, return first which is the first item
      if (index == 0) {
         return this->first->data;
     }
     //if the index is == to count return the last

     else if (index == count) {
         return this->last->data;
     }
     //all other scenarios involving numbers in between
     else {
         for (unsigned int i = 0; i < index; i++) {
             temp2 = temp2->forward;
         }
         return temp2->data;
     }
}

template <typename T>
T& DoublyLinkedList<T>::operator[](const unsigned int index) const {
    //same as the previous code for get
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }

    int count{ 1 };

    Node<T>* temp1 = this->first;
   

    while (temp1->forward != NULL) {
        temp1 = temp1->forward;
        count++;
    };

    Node<T>* temp2 = this->first;

    if (index > count) {
        throw std::out_of_range("Index out of range");
    }

    else if (index == 0) {
        return this->first->data;
    }

    else if (index == count) {
        return this->last->data;
    }
    else {
        for (unsigned int i = 0; i < index; i++) {
            temp2 = temp2->forward;
        }
        return temp2->data;
    }
}
template <typename T>

void DoublyLinkedList<T>::insert(const unsigned int index, const T& value) {
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }

    unsigned int count{ 0 };

    if (this->first == NULL) {
        Node<T>* temp = new Node<T>;

        temp->data = value;

        this->first = temp;

        this->last = temp;

        return;
    }

    

    //holds the count
    Node<T>* temp1 = this->first;

    //unsigned int count{ 1 };

    count++;

    //loops through the linked list to get the count
    while (temp1->forward != NULL) {
        temp1 = temp1->forward;
        count++;
    };

    //error check if the index is too high
    if (index > count){
        cout << "Index out of range";
      }

    

    //if the number being inputed is at the start of the linked list just use the first node
    else if (index == 0) {

        //holding the value to be inputed
        Node<T>* temp = new Node<T>();

        temp->data = value;

        //making the new node point to the 1st node
        temp->forward = this->first;

        //having the previous first node point to the last node
        this->first->backward = temp;

        //assign the first node its original spot
        this->first = temp;

  
        
    }
   // if the number being inputed is at the end of the linked list just use the tail
    else if (index == count) {

        //holds the main value being inserted in the spot
        Node<T>* temp = new Node<T>();

        temp->data = value;

        //will hold the previous node from the intented node
        temp->backward = this->last;

        this->last->forward = temp;

        this->last = temp;
    }
    else {
        Node<T>* temp = new Node<T>();

        temp->data = value;

        //holding the previous node to the index
        Node<T>* temp2 = this->first;

        //holding the node after the index
        Node<T>* temp3 = this->first;


        for (unsigned int i = 0; i < index-1; i++) {
            temp2 = temp2->forward;
        }


        for (unsigned int i = 0; i < index; i++) {
            temp3 = temp3->forward;
        }

        //pointing previous node to the new node
        temp2->forward = temp;

        //point the next node to the new previous node
        temp3->backward = temp;

        //pointing the new node to the next node
        temp->forward = temp3;

        //pointing the new node to the previous node
        temp->backward = temp2;

    }

}
template <typename T>

void DoublyLinkedList<T>::remove(const unsigned int index) {
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }
    if (this->first == NULL) {
        cout << "List is empty";
        return;
    }

    
    unsigned int count{ 0 };

    //holds the count
    Node<T>* temp1 = this->first;

    count++;
    
   

    //loops through the linked list to get the count
    while (temp1->forward != NULL) {
        temp1 = temp1->forward;
        count++;
    };

    if (index == 0 && count == 1) {

        Node<T>* temp = this->first;

        this->first = NULL;

        delete temp;

        return;
    }

    if (index > count ) {
        cout << ("Index out of range");
    }

    else if (index == 1 && count == 1){
        cout << ("Index out of range");
    }

    
    //moving the first node forward node and deleting the previous one
    else if (index == 0 && count != 0) {

        //creating a node that holds the first one
        Node<T>* temp = this->first;

        //moving the first node forward 1
        this->first = temp->forward;

        this->first->backward = nullptr;


        //deleting previous node
        delete temp;

    }
    //moving the last node backwards and then deleting the node
    else if (index == count-1) {
        //creating a node to hold the last node
        Node<T>* temp = this->last;

        //moving the last node backwards 1
        this->last = temp->backward;

        this->last->forward = nullptr;

        //deleting the last node
        delete temp;
    }

    else {
        //holds the vlaue to be deleted
        Node<T>* temp1 = this->first;

        //holds the value previous of the value to be deleted
        Node<T>* temp2 = this->first;

        //holds the value forward of the value to be deleted
        Node<T>* temp3 = this->first;

        for (unsigned int i = 0; i < index; i++) {
            temp1 = temp1->forward;
        }

        for (unsigned int i = 0; i < index - 1; i++) {
            temp2 = temp2->forward;
        }

        for (unsigned int i = 0; i < index + 1; i++) {
            temp3 = temp3->forward;
        }

        temp2->forward = temp3;

        temp3->backward = temp2;

        delete temp1;

    }
}

template <typename T>
void DoublyLinkedList<T>::removeAllInstances(const T& value) {
    if (this->first == NULL) {
        cout << "linked list is empty";
        return;
    }

    

    //will hold the place in line for the node (temp2) doing the deleting
    Node<T>* temp = this->first;

    //will delete nodes and then come back in line via the first temp
    Node<T>* temp2 = this->first;


    while (temp->forward != NULL) {
        if (temp == this->first && temp->data == value) {

            temp2 = temp;

            this->first = this->first->forward;

            this->first->backward = NULL;

            temp = temp->forward;

            delete temp2;

            Node<T>* temp2 = temp;
        
        }
       
        else if (temp->data == value && temp != this->last && temp != this->first) {

            //this code is here so that when the code does multiple pass throughs, it can make the temp2 value catch up again to the temp value
            temp2 = temp;

            //having the next backwards node point to backward node of the to be deleted node
            temp2->forward->backward = temp2->backward;

            //having the backwards node point to the next node ahead of the to be deleted node
            temp2->backward->forward = temp2->forward;

            temp = temp->forward;

            delete temp2;

            Node<T>* temp2 = temp;

        }
        else {
            temp = temp->forward;
        }
    }

   

    if (temp == this->last && temp->data == value && temp != this->first) {

        this->last = this->last->backward;

        this->last->forward = NULL;

        delete temp;

        return;
    }

    if (temp->forward == NULL && temp->data == value) {
        delete temp;

        this->first = NULL;

        this->last = NULL;

    }

   
}


//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "  You lost track of " << whatItIs << " bytes in memory!" << endl;
    return false;
  }
}

//This helps with testing, do not modify.
void testGet() {
  DoublyLinkedList<int>* d = new DoublyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    d->pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testGet #1", "10 11 12 13 14 15 16 17 18 19", d->getListAsString());
  checkTest("testGet #2", "19 18 17 16 15 14 13 12 11 10", d->getListBackwardsAsString());

  //Test retrieving items. 
  int item = d->get(0);
  checkTest("testGet #3", 10, item);

  item = d->get(5);
  checkTest("testGet #4", 15, item);

  item = d->get(9);
  checkTest("testGet #5", 19, item);

  //Make sure the list was undisturbed during this time
  checkTest("testGet #6", "10 11 12 13 14 15 16 17 18 19", d->getListAsString());

  //Try to access out of bounds.  
  string caughtError = "";
  try {
    int item = d->get(-1);
  }
  catch (std::out_of_range& orr) {
    caughtError = "caught";
  }
  checkTest("testGet #7", "caught", caughtError);

  try {
    int item = d->get(100);
  }
  catch (std::out_of_range& orr) {
    caughtError = "caught";
  }
  checkTest("testGet #8", "caught", caughtError);

  delete d;

  d = new DoublyLinkedList<int>;
  d->pushBack(18);
  item = d->get(0);
  checkTest("testGet #9", 18, item);
  delete d;
}

//This helps with testing, do not modify.
void testSquareBrackets() {
  DoublyLinkedList<int> d;
  for (int i = 10; i < 20; i++) {
    d.pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testSquareBrackets #1", "10 11 12 13 14 15 16 17 18 19", d.getListAsString());
  checkTest("testSquareBrackets #2", "19 18 17 16 15 14 13 12 11 10", d.getListBackwardsAsString());

  //Test retrieving items. 
  int item = d[0];

  checkTest("testSquareBrackets #3", 10, item);

  item = d[5];
  checkTest("testSquareBrackets #4", 15, item);

  item = d[9];
  checkTest("testSquareBrackets #5", 19, item);

  //Make sure the list was undisturbed during this time
  checkTest("testSquareBrackets #6", "10 11 12 13 14 15 16 17 18 19", d.getListAsString());
  checkTest("testSquareBrackets #7", "19 18 17 16 15 14 13 12 11 10", d.getListBackwardsAsString());

  //now test the return by reference
  d[1] = 1000;

  checkTest("testSquareBrackets #8", "10 1000 12 13 14 15 16 17 18 19", d.getListAsString());
  checkTest("testSquareBrackets #9", "19 18 17 16 15 14 13 12 1000 10", d.getListBackwardsAsString());

  //Try to access out of bounds.  
  string caughtError = "";
  try {
    int item = d[-1];
  }
  catch (std::out_of_range& oor) {
    caughtError = "caught";
  }
  checkTest("testSquareBrackets #10", "caught", caughtError);

  try {
    int item = d[100];
  }
  catch (std::out_of_range& oor) {
    caughtError = "caught";
  }
  checkTest("testSquareBrackets #11", "caught", caughtError);

}

//This helps with testing, do not modify.
void testInsert() {
  DoublyLinkedList<int>* s = new DoublyLinkedList<int>();
  for (int i = 10; i < 20; i++) {
    s->pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testInsert #1", "10 11 12 13 14 15 16 17 18 19", s->getListAsString());
  checkTest("testInsert #2", "19 18 17 16 15 14 13 12 11 10", s->getListBackwardsAsString());

  s->insert(3, 33);

  checkTest("testInsert #3", "10 11 12 33 13 14 15 16 17 18 19", s->getListAsString());
  checkTest("testInsert #4", "19 18 17 16 15 14 13 33 12 11 10", s->getListBackwardsAsString());

  s->insert(5, 55);

  checkTest("testInsert #5", "10 11 12 33 13 55 14 15 16 17 18 19", s->getListAsString());
  checkTest("testInsert #6", "19 18 17 16 15 14 55 13 33 12 11 10", s->getListBackwardsAsString());


  s->insert(0, 9);

  checkTest("testInsert #7", "9 10 11 12 33 13 55 14 15 16 17 18 19", s->getListAsString());
  checkTest("testInsert #8", "19 18 17 16 15 14 55 13 33 12 11 10 9", s->getListBackwardsAsString());

  s->insert(13, 20);

  checkTest("testInsert #9", "9 10 11 12 33 13 55 14 15 16 17 18 19 20", s->getListAsString());
  checkTest("testInsert #10", "20 19 18 17 16 15 14 55 13 33 12 11 10 9", s->getListBackwardsAsString());

  delete s;

  s = new DoublyLinkedList<int>();

  s->insert(0, 42);
  checkTest("testInsert #11", "42", s->getListAsString());
  checkTest("testInsert #12", "42", s->getListBackwardsAsString());

  s->insert(1, 82);
  checkTest("testInsert #13", "42 82", s->getListAsString());
  checkTest("testInsert #14", "82 42", s->getListBackwardsAsString());

  delete s;

}

//This helps with testing, do not modify.
void testRemove() {
  DoublyLinkedList<int>* d = new DoublyLinkedList<int>;
  for (int i = 10; i < 17; i++) {
    d->pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testRemove #1", "10 11 12 13 14 15 16", d->getListAsString());
  checkTest("testRemove #2", "16 15 14 13 12 11 10", d->getListBackwardsAsString());

  //Test deleting first items. 
  d->remove(0);
  checkTest("testRemove #3", "11 12 13 14 15 16", d->getListAsString());
  checkTest("testRemove #4", "16 15 14 13 12 11", d->getListBackwardsAsString());

  d->remove(0);
  checkTest("testRemove #5", "12 13 14 15 16", d->getListAsString());
  checkTest("testRemove #6", "16 15 14 13 12", d->getListBackwardsAsString());

  //Test deleting a middle item
  d->remove(2);
  checkTest("testRemove #7", "12 13 15 16", d->getListAsString());
  checkTest("testRemove #8", "16 15 13 12", d->getListBackwardsAsString());

  //Test deleting last itmes
  d->remove(3);
  checkTest("testRemove #9", "12 13 15", d->getListAsString());
  checkTest("testRemove #10", "15 13 12", d->getListBackwardsAsString());

  d->remove(2);
  checkTest("testRemove #11", "12 13", d->getListAsString());
  checkTest("testRemove #12", "13 12", d->getListBackwardsAsString());

  //Test deleting a Kth element that doesn't exist.
  d->remove(500);
  checkTest("testRemove #13", "12 13", d->getListAsString());
  checkTest("testRemove #14", "13 12", d->getListBackwardsAsString());

  //Test deleting a last item
  d->remove(1);
  checkTest("testRemove #15", "12", d->getListAsString());
  checkTest("testRemove #16", "12", d->getListBackwardsAsString());

  //Test deleting item that doesn't exist
  d->remove(1);
  checkTest("testRemove #17", "12", d->getListAsString());
  checkTest("testRemove #18", "12", d->getListBackwardsAsString());

  //Test deleting item on the first
  d->remove(0);
  checkTest("testRemove #19", "The list is empty.", d->getListAsString());

  //Test attempting to delete from an empty list
  d->remove(0);
  checkTest("testRemove #20", "The list is empty.", d->getListAsString());

  delete d;
}


//This helps with testing, do not modify.
void testRemoveAllInstances() {

  DoublyLinkedList<int>* d = new DoublyLinkedList<int>;

  d->pushBack(4);
  d->pushBack(2);
  d->pushBack(6);
  d->pushBack(5);
  d->pushBack(6);
  d->pushBack(9);

  //Do a delete, test it.
  d->removeAllInstances(6);
  checkTest("testRemoveAllInstances #1", "4 2 5 9", d->getListAsString());
  checkTest("testRemoveAllInstances #2", "9 5 2 4", d->getListBackwardsAsString());

  delete d;
  d = new DoublyLinkedList<int>;
  d->pushBack(4);
  d->pushBack(2);
  d->pushBack(3);
  d->pushBack(4);
  d->pushBack(4);
  d->pushBack(4);
  d->pushBack(9);
  d->removeAllInstances(4);
  checkTest("testRemoveAllInstances #3", "2 3 9", d->getListAsString());
  checkTest("testRemoveAllInstances #4", "9 3 2", d->getListBackwardsAsString());

  delete d;
  d = new DoublyLinkedList<int>;
  d->pushBack(3);
  d->pushBack(3);
  d->pushBack(3);
  d->pushBack(8);
  d->pushBack(2);
  d->pushBack(3);
  d->pushBack(3);
  d->pushBack(3);
  d->removeAllInstances(3);
  checkTest("testRemoveAllInstances #5", "8 2", d->getListAsString());
  checkTest("testRemoveAllInstances #6", "2 8", d->getListBackwardsAsString());

  delete d;
  d = new DoublyLinkedList<int>;
  d->pushBack(9);
  d->pushBack(9);
  d->pushBack(4);
  d->pushBack(2);
  d->pushBack(9);
  d->pushBack(9);
  d->pushBack(5);
  d->pushBack(1);
  d->pushBack(9);
  d->pushBack(2);
  d->pushBack(9);
  d->pushBack(9);

  //Do a delete, test it.
  d->removeAllInstances(9);
  checkTest("testRemoveAllInstances #7", "4 2 5 1 2", d->getListAsString());
  checkTest("testRemoveAllInstances #8", "2 1 5 2 4", d->getListBackwardsAsString());

  //Test deleting something that doesn't exist
  d->removeAllInstances(7);
  checkTest("testRemoveAllInstances #9", "4 2 5 1 2", d->getListAsString());
  checkTest("testRemoveAllInstances #10", "2 1 5 2 4", d->getListBackwardsAsString());

  //A few more tests
  d->removeAllInstances(2);
  checkTest("testRemoveAllInstances #11", "4 5 1", d->getListAsString());
  checkTest("testRemoveAllInstances #12", "1 5 4", d->getListBackwardsAsString());

  d->removeAllInstances(4);
  checkTest("testRemoveAllInstances #13", "5 1", d->getListAsString());
  checkTest("testRemoveAllInstances #14", "1 5", d->getListBackwardsAsString());

  d->removeAllInstances(5);
  checkTest("testRemoveAllInstances #15", "1", d->getListAsString());

  d->removeAllInstances(1);
  checkTest("testRemoveAllInstances #16", "The list is empty.", d->getListAsString());

  //retest deleting something that doesn't exist.
  d->removeAllInstances(7);
  checkTest("testRemoveAllInstances #17", "The list is empty.", d->getListAsString());
  delete d;

  //Now ramp it up and do some huge tests.  Start by timing how long a smaller approach takes.
  d = new DoublyLinkedList<int>;
  //Fill the list with a pattern of
  //1 2 2 3 3 3 4 4 4 4 1 2 2 3 3 3 4 4 4 4 ...
  cout << endl << "Preparing for testRemoveAllInstances #18, placing 50,000 numbers into the linked list to see how long things take." << endl;
  for (int i = 0; i < 20000; i++) {
    for (int j = 0; j < i % 4 + 1; j++) {
      d->pushBack(i % 4 + 1);
    }
  }
  cout << "    Calling removeAllInstances to remove 15,000 3s in the list." << endl;
  //delete all the 3s.
  auto start = std::chrono::high_resolution_clock::now();
  d->removeAllInstances(3);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> diff = end - start;
  double benchmarkTime = diff.count() / 1000.0;
  cout << "    Removing 15,000 3s took " << benchmarkTime << " milliseconds." << endl;
  cout << "    So we will assume removing 30,000 3s then should be double that..." << endl;
  cout << "	 about " << benchmarkTime << " * 2 = " << (benchmarkTime * 2) << " milliseconds if done correctly." << endl;
  delete d;

  cout << "Starting testRemoveAllInstances #18, filling in 100,000 numbers into the linked list to get it started." << endl;
  d = new DoublyLinkedList<int>;
  //Fill the list with a pattern of
  //1 2 2 3 3 3 4 4 4 4 1 2 2 3 3 3 4 4 4 4 ...
  for (int i = 0; i < 40000; i++) {
    for (int j = 0; j < i % 4 + 1; j++) {
      d->pushBack(i % 4 + 1);
    }
  }
  cout << "    Finished inserting 100,000 numbers." << endl;
  cout << "    Calling removeAllInstances to remove 30,000 3s.  This should take about " << (benchmarkTime * 2) << " milliseconds." << endl;
  //delete all the 3s.
  start = std::chrono::high_resolution_clock::now();
  d->removeAllInstances(3);
  end = std::chrono::high_resolution_clock::now();
  diff = end - start;
  double actualTime = diff.count() / 1000.0;
  if (actualTime < (benchmarkTime * 2 * 1.5)) { //The 1.5 gives an extra 50% wiggle room
    cout << "Passed testRemoveAllInstances #18, completed removeAllInstances in " << actualTime << " milliseconds." << endl;

  }
  else {
    cout << "*** Failed testRemoveAllInstances #18, removeAllInstances took " << actualTime
      << " milliseconds." << endl;
    cout << "*** This which is much worse than the expected " << (benchmarkTime * 2) << " milliseconds." << endl;
  }
  delete d;

}

void pressAnyKeyToContinue() {
  cout << "Press enter to continue...";
  cin.get();
}


int main() {

  //For your assignment, write the code to make these three methods work
  //You should not modify the code here in main.

  testGet();


  pressAnyKeyToContinue();

  testSquareBrackets();

  pressAnyKeyToContinue();

  testInsert();

  pressAnyKeyToContinue();

  testRemove();

  pressAnyKeyToContinue();

  testRemoveAllInstances();

  pressAnyKeyToContinue();

  return 0;
}
