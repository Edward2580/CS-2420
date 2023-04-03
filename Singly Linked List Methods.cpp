//Copyright 2022, Bradley Peterson, Weber State University, All rights reserved. (9/2022)
#include <sstream>
#include <chrono>
#include <iostream>
#include <set>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;
using std::set;

class DestructorTester {
public:
  static unsigned int getCount() {
    return count;
  }
  static unsigned int getTotalCopyCalls() {
    return totalCopyCalls;
  }
  DestructorTester() {
    count++;
  }
  DestructorTester(const DestructorTester& obj) {
    count++;
    totalCopyCalls++;
  }
  void operator=(const DestructorTester& obj) {
    // Not a constructor, so no new object is created here.  No need to increment count.
    totalCopyCalls++;
  }
  ~DestructorTester() {
    count--;
  }
private:
  static unsigned int count;
  static unsigned int totalCopyCalls;
};
unsigned int DestructorTester::count = 0;
unsigned int DestructorTester::totalCopyCalls = 0;

//******************
//The Node class
//******************
template <typename T>
class Node {
public:
  T data{};
  Node<T>* link{ nullptr };
};

//******************
// The linked list base class
//******************
template <typename T>
class LinkedListBase {
public:
  ~LinkedListBase();
  string getStringFromList();
  T getFifthElement() const { cerr << "Error: You didn't override this base class method yet" << endl; T temp{}; return temp; }
  void insertNewFifthElement(const T& data) { cerr << "Error: You didn't override this base class method yet" << endl; }
  void deleteFifthElement() { cerr << "Error: You didn't override this base class method yet" << endl; }
  void swapFifthAndSeventhElement() { cerr << "Error: You didn't override this base class method yet" << endl; }
  T getLast() const;
  void pushFront(const T& data);
  void pushBack(const T& data);
  void popFront();
  void popBack();

protected:
  Node<T>* head{ nullptr };
  Node<T>* tail{ nullptr };
  unsigned int count{ 0 };
};

template <typename T>
LinkedListBase<T>::~LinkedListBase() {
  Node<T>* temp = head;
  while (temp) {
    head = head->link;
    delete temp;
    temp = head;
  }
}
//This method helps return a string representation of all nodes in the linked list, do not modify.
template <typename T>
string LinkedListBase<T>::getStringFromList() {
  stringstream ss;
  if (!this->head) {
    ss << "The list is empty.";
  }
  else {

    Node<T>* currentNode = this->head;
    ss << currentNode->data;
    currentNode = currentNode->link;

    while (currentNode) {
      ss << " " << currentNode->data;
      currentNode = currentNode->link;
    };
  }
  return ss.str();
}

template <typename T>
T LinkedListBase<T>::getLast() const {
  if (this->tail) {
    return this->tail->data;
  }
  else {
    throw 1;
  }
}
template <typename T>
void LinkedListBase<T>::pushFront(const T& data) {

  if (!head) {
    // Scenario: The list is empty
    Node<T>* temp = new Node<T>();
    temp->data = data;
    this->head = temp;
    this->tail = temp;
    count++;
  }
  else {
    // Scenario: One or more nodes
    Node<T>* temp = new Node<T>();
    temp->data = data;
    temp->link = this->head;
    this->head = temp;
    count++;
  }
}

template <typename T>
void LinkedListBase<T>::pushBack(const T& data) {
  if (!head) {
    //Scenario: The list is empty
    Node<T>* temp = new Node<T>();
    temp->data = data;
    this->head = temp;
    this->tail = temp;
    count++;
  }
  else {
    Node<T>* temp = new Node<T>();
    temp->data = data;
    this->tail->link = temp;
    this->tail = temp;
    count++;
  }
}

template <typename T>
void LinkedListBase<T>::popFront() {

  if (!head) {
    // Scenario: The list is empty
    cout << "The list was already empty" << endl;
    return;
  }
  else if (this->head == this->tail) {
    // Scenario: One node list
    this->tail = nullptr;
    delete this->head;
    this->head = nullptr;
    count--;
  }
  else {
    // Scenario: General, at least two or more nodes
    Node<T>* temp = nullptr;
    temp = this->head->link;
    delete this->head;
    this->head = temp;
    count--;
  }
}

template <typename T>
void LinkedListBase<T>::popBack() {
  if (!this->head) {
    // Scenario: The list is empty
    cout << "The list was already empty" << endl;
    return;
  }
  else if (this->head == this->tail) {
    // Scenario: One node list
    this->tail = nullptr;
    delete this->head;
    this->head = nullptr;
    count--;
  }
  else {
    // Scenario: General, at least two or more nodes
    Node<T>* temp = nullptr;
    temp = head;

    while (temp->link != this->tail) {
      temp = temp->link; // This is like i++;
    }

    // temp is now at the second to tail node
    delete this->tail;
    this->tail = temp;
    this->tail->link = nullptr;
    count--;
  }
}


//**********************************
//Write your code below here
//**********************************

template <typename T>
class SinglyLinkedList : public LinkedListBase<T> {
public:
    T getFifthElement() const;
    void insertNewFifthElement(const T& data);
    void deleteFifthElement();
    void swapFifthAndSeventhElement();
};

//TODO: Define your methods here.
template <typename T>
T SinglyLinkedList<T>::getFifthElement()const {

    //error check, if linked list then 5 then there is no fifth element
    if (this->count < 5) {
        throw std::out_of_range("No fifth element");
    }
    else {
        // will count how many spaces it moved
        int index = 0;

        //setting the temp node equal to the head node
        Node<T>* temp = this->head;

        //moving only 4 spaces because the 4th node links to the 5th node
        while (index < 4) {
              //everytime it iterates, it moves the node down the linked list
              temp = temp->link;
              index++;
         }
        //how ot return the data of the desired node
         return temp->data;
         }
    
    }

template <typename T>
void SinglyLinkedList<T>::insertNewFifthElement(const T& data) {
    if (this->count < 4) {
        //throw std::out_of_range("error");
        cout << "error";
    }

    //if there is only 4 items, push back the last one to make it 5
    else if (this->count == 4) {

        Node<T>* temp = new Node<T>();

        temp->data = data;

        this->tail->link = temp;

        this->tail = temp;
    }
    else if (this->count == 5) {
        //holding the 4th node for the link
        Node<T>* temp4 = this->head;

        //creating the fifth node
        Node<T>* temp5 = new Node<T>;

        //holding the new sixth node so that the 5th node can link to it
        Node<T>* temp6 = this->head;
        int index = 0;

        while (index < 3) {

            //everytime it iterates, it moves the node down the linked list
            temp4 = temp4->link;
            index++;
        }

        index = 0;
        while (index < 4) {
            temp6 = temp6->link;
            index++;
        }

        //putting the data into the temp node
        temp5->data = data;

        temp4->link = temp5;

        temp5->link = temp6;

     
    }
    //any number greater than 5
    else if(this->count > 5){
        //holds the value of the 4th spot
        Node<T>* temp4 = this->head;
        
        //new node to put in
        Node<T>* temp5 = new Node<T>;

        //the orginal 5th element turned 6th to allow the new 5th element to point to it
        Node<T>* temp6 = this->head;

        int index = 0;

        while (index < 3) {
            //everytime it iterates, it moves the node down the linked list
            temp4 = temp4->link;
            index++;
        }

        index = 0;

        while (index < 4) {
            temp6 = temp6->link;
            index++;
        }

        temp5->data = data;

        temp4->link = temp5;

        temp5->link = temp6;

    }
};

template <typename T>
void SinglyLinkedList<T>::deleteFifthElement() {
    if (this->count < 5) {
        cout << "error";
    }
    else if (this->count == 5) {
        Node<T>* temp4 = this->head;
        Node<T>* temp5 = this->head;

        int index = 0;

        while (index < 3) {
            temp4 = temp4->link;
            index++;
        }

        index = 0;


        while (index < 4) {
            temp5 = temp5->link;
            index++;
        }

        index = 0;

        temp4->link = nullptr;

        this->tail = temp4;

        delete temp5;
   }

    else if (this->count >= 5) {
        Node<T>* temp4 = this->head;
        Node<T>* temp5 = this->head;

        int index = 0;

        while (index < 3) {
            temp4 = temp4->link;
            index++;
        }

        index = 0;


        while (index < 4) {
            temp5 = temp5->link;
            index++;
        }

        temp4->link = temp5->link;

        delete temp5;
 
    }

}
template <typename T>
void SinglyLinkedList<T>::swapFifthAndSeventhElement(){

    if (this->count > 7) {
        Node<T>* temp4 = this->head;
        Node<T>* temp5 = this->head;
        Node<T>* temp6 = this->head;
        Node<T>* temp7 = this->head;
        Node<T>* temp8 = this->head;

            int index = 0;

        while (index < 3) {
            temp4 = temp4->link;
            index++;
        }

        index = 0;


        while (index < 4) {
            temp5 = temp5->link;
            index++;
        }

        index = 0;


        while (index < 5) {
            temp6 = temp6->link;
            index++;
        }

        index = 0;


        while (index < 6) {
            temp7 = temp7->link;
            index++;
        }

        index = 0;


        while (index < 7) {
            temp8 = temp8->link;
            index++;
        }

        temp4->link = temp7;

        temp7->link = temp6;

        temp6->link = temp5;

        temp5->link = temp8;
    }
    else if (this->count == 7) {

        Node<T>* temp4 = this->head;
        Node<T>* temp5 = this->head;
        Node<T>* temp6 = this->head;
        Node<T>* temp7 = this->head;

        int index = 0;

        while (index < 3) {
            temp4 = temp4->link;
            index++;
        }

        index = 0;


        while (index < 4) {
            temp5 = temp5->link;
            index++;
        }

        index = 0;


        while (index < 5) {
            temp6 = temp6->link;
            index++;
        }

        index = 0;


        while (index < 6) {
            temp7 = temp7->link;
            index++;
        }

        temp4->link = temp7;

        temp7->link = temp6;

        temp6->link = temp5;

        temp5->link = nullptr;

        this->tail = temp5;
    }
}
//**********************************
//Write your code above here
//**********************************


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
void testGetFifthElement() {
  SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testGetFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test retrieving item. 
  int item = si->getFifthElement();
  checkTest("testGetFifthElement #2", 14, item);
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->pushBack(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testGetFifthElement #3", "10 11 12 13 14", si->getStringFromList());

  //Test retrieving item. 
  item = si->getFifthElement();
  checkTest("testGetFifthElement #4", 14, item);
  delete si;


  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 14; i++) {
    si->pushBack(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testGetFifthElement #5", "10 11 12 13", si->getStringFromList());

  //Try to access out of bounds.  
  string caughtError = "";
  try {
    item = si->getFifthElement();
  }
  catch (std::out_of_range& oor) {
    caughtError = "caught";
  }
  checkTest("testGetFifthElement #6", "caught", caughtError);
  delete si;

  SinglyLinkedList<string>* ss = new SinglyLinkedList<string>;
  ss->pushBack("Multi Pass");
  ss->pushBack("Lelu Dallas");
  ss->pushBack("BIG BADA BOOM");
  ss->pushBack("Bruce Willis");
  ss->pushBack("Fried Chicken");
  ss->pushBack("EEEAAAAAAAeeeaaaaaEEeeAAAEEaaaaAA");
  checkTest("testGetFifthElement #7", "Fried Chicken", ss->getFifthElement());
  delete ss;

  SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
  for (int i = 0; i < 10; i++) {
    dt->pushBack(DestructorTester());
  }
  dt->getFifthElement();
  if (DestructorTester::getCount() == 10) {
    cout << "Passed testGetFifthElement #8" << endl;
  }
  else {
    cout << "***Failed test testGetFifthElement #8 *** " << endl << "   You have a memory leak. " << endl;
  }

  delete dt;
  if (DestructorTester::getCount() == 0) {
    cout << "Passed testGetFifthElement #9" << endl;
  }
  else {
    cout << "***Failed test testGetFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
  }
}


//This helps with testing, do not modify.
void testInsertNewFifthElement() {

  SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testInsertNewFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #2", "10 11 12 13 97 14 15 16 17 18 19", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->pushBack(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testInsertNewFifthElement #3", "10 11 12 13 14", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #4", "10 11 12 13 97 14", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 14; i++) {
    si->pushBack(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testInsertNewFifthElement #5", "10 11 12 13", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #6", "10 11 12 13 97", si->getStringFromList());
  checkTest("testInsertNewFifthElement #7", 97, si->getLast());
  delete si;



  // Now test inserting an invalid option
  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 13; i++) {
    si->pushBack(i);
  }
  si->insertNewFifthElement(1000);
  //Test just to make sure the data didn't go in at all and didn't crash.
  checkTest("testInsertNewFifthElement #8", "10 11 12", si->getStringFromList());

  delete si;

  SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
  for (int i = 0; i < 10; i++) {
    dt->pushBack(DestructorTester());
  }
  dt->insertNewFifthElement(DestructorTester());
  if (DestructorTester::getCount() == 11) {
    cout << "Passed testInsertNewFifthElement #9" << endl;
  }
  else {
    cout << "***Failed test testInsertNewFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
  }

  delete dt;
  if (DestructorTester::getCount() == 0) {
    cout << "Passed testInsertNewFifthElement #10" << endl;
  }
  else {
    cout << "***Failed test testInsertNewFifthElement #10 *** " << endl << "   You have a memory leak. " << endl;
  }

}

//This helps with testing, do not modify.
void testDeleteFifthElement() {
  // Note from the instructor: Please do not delete the actual movie.  It's very good and shouldn't be removed.

  SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testDeleteFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #2", "10 11 12 13 15 16 17 18 19", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 16; i++) {
    si->pushBack(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testDeleteFifthElement #3", "10 11 12 13 14 15", si->getStringFromList());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #4", "10 11 12 13 15", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->pushBack(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testDeleteFifthElement #5", "10 11 12 13 14", si->getStringFromList());
  checkTest("testDeleteFifthElement #6", 14, si->getLast());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #7", "10 11 12 13", si->getStringFromList());
  checkTest("testDeleteFifthElement #8", 13, si->getLast());
  delete si;

  SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
  for (int i = 0; i < 10; i++) {
    dt->pushBack(DestructorTester());
  }
  dt->deleteFifthElement();
  if (DestructorTester::getCount() == 9) {
    cout << "Passed testDeleteFifthElement #9" << endl;
  }
  else {
    cout << "***Failed test testDeleteFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
  }

  delete dt;
  if (DestructorTester::getCount() == 0) {
    cout << "Passed testDeleteFifthElement #10" << endl;
  }
  else {
    cout << "***Failed test testDeleteFifthElement #10 *** " << endl << "   You have a memory leak. " << endl;
  }

}

//This helps with testing, do not modify.
void testSwapFifthAndSeventhElement() {
  // Note from the instructor: Please do not delete the actual movie.  
  // It's very good and shouldn't be removed.

  SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testSwapFifthAndSeventhElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test swapping an item
  si->swapFifthAndSeventhElement();
  checkTest("testSwapFifthAndSeventhElement #2", "10 11 12 13 16 15 14 17 18 19", si->getStringFromList());

  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 17; i++) {
    si->pushBack(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testSwapFifthAndSeventhElement #3", "10 11 12 13 14 15 16", si->getStringFromList());

  //Test swapping an item
  si->swapFifthAndSeventhElement();
  checkTest("testSwapFifthAndSeventhElement #4", "10 11 12 13 16 15 14", si->getStringFromList());
  checkTest("testSwapFifthAndSeventhElement #5", 14, si->getLast());
  delete si;


  SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
  for (int i = 0; i < 10; i++) {
    dt->pushBack(DestructorTester());
  }
  unsigned int beforeTotalCopyCalls = DestructorTester::getTotalCopyCalls();
  dt->swapFifthAndSeventhElement();
  unsigned int afterTotalCopyCalls = DestructorTester::getTotalCopyCalls();
  if (beforeTotalCopyCalls == afterTotalCopyCalls) {
    cout << "Passed testSwapFifthAndSeventhElement #6" << endl;
  }
  else {
    cout << "***Failed test testSwapFifthAndSeventhElement #6 *** " << endl << "   You didn't move the pointers around, you copied values " << (afterTotalCopyCalls - beforeTotalCopyCalls) << " times." << endl;
  }

  if (DestructorTester::getCount() == 10) {
    cout << "Passed testSwapFifthAndSeventhElement #7" << endl;
  }
  else {
    cout << "***Failed test testSwapFifthAndSeventhElement #7 *** " << endl << "   You have a memory leak. " << endl;
  }

  delete dt;
  if (DestructorTester::getCount() == 0) {
    cout << "Passed testSwapFifthAndSeventhElement #8" << endl;
  }
  else {
    cout << "***Failed test testSwapFifthAndSeventhElement #8 *** " << endl << "   You have a memory leak. " << endl;
  }

}


void pressAnyKeyToContinue() {
  cout << "Press enter to continue...";

  cin.get();

}


int main() {

  testGetFifthElement();

  testInsertNewFifthElement();

  pressAnyKeyToContinue();

  testDeleteFifthElement();

  testSwapFifthAndSeventhElement();

  pressAnyKeyToContinue();

  return 0;
}