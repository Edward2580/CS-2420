

#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

template <typename T> class DoublyLinkedList;

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::stringstream;
using std::iter_swap;
using std::vector;


//******************
//The Node class
//******************
template <typename T>
class Node {
public:
    T data{};
    Node<T>* backward{ nullptr };
    Node<T>* forward{ nullptr };
};

//******************
//The Iterator class
//******************
template <typename T>
class Iterator {
  friend class DoublyLinkedList<T>;
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = int;
  using pointer = T*;
  using reference = T&;

  // TODO: Implement the following:
  //operator*
  T& operator*() const;

  //operator++ prefix  ends with return *this;
  Iterator<T> operator++();

  //operator++ postfix  starts with auto temp = *this;  advances the "this"...;   return temp;
  Iterator<T> operator++(int);

  //operator-- prefix
  Iterator<T> operator--();

  //operator!=
  bool operator!=(const Iterator<T>& rhs);

  //operator==
  bool operator==(const Iterator<T>& rhs);

private:

  // TODO: supply two data members
  
  // You need a pointer to a node
    Node<T>* currAddr{ nullptr };

  // You need a boolean pastTheEnd, initialized to false.
    bool pastTheEnd{ false };

};

//***********************************
//The Iterator class methods
//***********************************

// TODO: code the definitions for all the iterator methods.
template <typename T>
T& Iterator<T>::operator*() const {
    return currAddr->data;
}

template <typename T>
Iterator<T> Iterator<T>::operator++() {
    if (currAddr->forward == nullptr) {
        pastTheEnd = true;
        return *this;
    }

    else if (!currAddr) {
        return *this;
    }

    else {
        currAddr = currAddr->forward;
        return *this;
    }
}

template <typename T>
Iterator<T>  Iterator<T>::operator++(int) {
    auto copyOfItself = *this;

    if (currAddr->forward == nullptr) {
        pastTheEnd = true;
        return copyOfItself;
    }

    else if (pastTheEnd == true) {
        return copyOfItself;
    }

    else {
        currAddr = currAddr->forward;
        return copyOfItself;
    }
};

template <typename T>
Iterator<T> Iterator<T>::operator--(){

    if (!currAddr) {
        return *this;
    }
    else if (pastTheEnd == true) {
        pastTheEnd = false;
    }

    else if (this->currAddr->backward == nullptr) {
        return *this;
    }

    else{
        currAddr = currAddr->backward;
        return *this;
    }

}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) {

    if (!currAddr) {
        return false;
    }
    else if(currAddr->data == rhs.currAddr->data && pastTheEnd == rhs.pastTheEnd) {
        return false;
    }
    else {
        return true;
    }
};

template <typename T>
bool  Iterator<T>::operator==(const Iterator<T>& rhs) {
    if (currAddr->data == rhs.currAddr->data && pastTheEnd == rhs.pastTheEnd) {
        return true;
    }
    else {
        return false;
    }
};

//****************************
//The DoublyLinkedList class
//****************************
template <typename T>
class DoublyLinkedList {

public:

  //public members of the DoublyLinkedList class
  DoublyLinkedList();
  ~DoublyLinkedList();

  void pushFront(const T&);
  void pushBack(const T&);
  // TODO: Implement a begin() and end() method.  They each return an Iterator<T> object
  Iterator<T> begin();
  Iterator<T> end();

protected:

  Node<T>* first{ nullptr };
  Node<T>* last{ nullptr };

};

template< typename T>
DoublyLinkedList<T>::DoublyLinkedList() {

}

template <typename T>// destructor
DoublyLinkedList<T>::~DoublyLinkedList() {
  Node<T>* temp = this->first;

  while (first) {
    first = first->forward;
    delete temp;
    temp = first;
  }
}

template <typename T>
void DoublyLinkedList<T>::pushFront(const T& item) {
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
void DoublyLinkedList<T>::pushBack(const T& item) {
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




//***********************************
//The DoublyLinkedList class methods
//***********************************
// TODO: implement the  the definitions for the begin() and end() methods.  They each return an Iterator<T> object
template <typename T>
Iterator<T> DoublyLinkedList<T>::begin() {
    //checks to see if the list is empty
    if (!first) {

        Iterator<T> retVal;

        retVal.pastTheEnd = true;

        return retVal;
   }
    //otherwise assign the pointer to the first item on the list
    else {
        Iterator<T> retVal;

        retVal.currAddr = this->first;

        return retVal;
    }
}


template <typename T>
Iterator<T> DoublyLinkedList<T>::end() {

    if (!first) {

        Iterator<T> retVal;

        retVal.pastTheEnd = true;

        return retVal;
    }
    else {
        //creating the iterator object
        Iterator<T> retVal;

        //setting the past the end to true
        retVal.pastTheEnd = true;

        retVal.currAddr = this->last;

        return retVal;
    }
}



//***********************************
// TODO: complete the assignmentReverse function.
// Note that begin and end here are are iterators (The T is just saying it can be any kind of iterator).
// Your tools are ***ONLY**: ++, --, !=, ==, *,
// For example, these three lines do a swap:
 // auto temp = *end;
 // *end = *begin;
 // *begin = temp;
 // Also, this comes in handy : iter_swap(begin, end);  //Swaps the values pointed at by two iterators.  
template <typename T>
void assignmentReverse(T begin, T end) {

    --end;  // Get the container off its past-the-end state so its "pointing" at the last value in the container.  
    
    while (begin != end) {
        iter_swap(begin, end);

        auto temp = *end;

        --end;
        ++begin;

        if (*begin == temp) {
            return;
        }
   }


}

//----------------------------------------------------------------------------------------------------------------------------------------
//Copyright 2021, Bradley Peterson, Weber State University, All rights reserved. (Oct 2021)
//This helps with testing, do not modify.
bool checkTest(string testName, const string whatItShouldBe, const string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
    exit(1);
  }
}

template <typename T>
bool checkTest(string testName, const T whatItShouldBe, const T whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
    exit(1);
  }
}


//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "  There are " << whatItIs << " bytes of memory yet to be reclaimed!" << endl;
    return false;
    exit(1);
  }
}


//This helps with testing, do not modify.
void testIteratorFundamentals() {
//  //cout << "|||### You need to comment in testIteratorIncrement() when it's ready and remove this ###|||" << endl;
//  //cout << "|||### I strongly advise commenting in tests one at a time and testing those.  It's harder to try and do all tests at once.###|||" << endl;

  DoublyLinkedList<int> d;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 20; i += 2) {
    d.pushBack(i);
  }

  ////Get an iterator which points at the beginning of the list
  Iterator<int> iter = d.begin();

  ////Test the operator* operator
  checkTest("testIteratorFundamentals #1", 2, *iter);

  ////Test the ++ prefix increment opreator
  ++iter;
  checkTest("testIteratorFundamentals #2", 4, *iter);

  ////Test the != operator
  ////reset them back to the start
  iter = d.begin();
  Iterator<int> anotherIter = d.begin();
  if (iter != anotherIter) {
    cout << "****** Failed testIteratorFundamentals #3 ****** " << endl << "     The two iteraters held the same data." << endl;
  }
  else {
    cout << "Passed testIteratorFundamentals #3" << endl;
  }

  //Again test the != operator
  ++iter;
  if (iter != anotherIter) {
    cout << "Passed testIteratorFundamentals #4" << endl;
  }
  else {
    cout << "****** Failed testIteratorFundamentals #4 ****** " << endl << "     The two iteraters held different data." << endl;
  }

  //Test the ++postfix increment
  iter = d.begin(); //reset it back to the start
  anotherIter = iter++;  //anotherIter should be at the data 2

  checkTest("testIteratorFundamentals #5", 4, *iter);
  checkTest("testIteratorFundamentals #6", 2, *anotherIter);

  // TODO:
  // We have !=, *, ++, and .begin() tested by this point.  Now test .end().  Do that with a for loop.  
  stringstream ss;
  cout << "testIteratorFundamentals test #7, this should display 2 4 6 8 10 12 14 16 18 20." << endl;
  for (auto item : d) {
    cout << item << " ";
    ss << item << " ";
  }
  cout << endl;


  checkTest("testIteratorFundamentals test #7", "2 4 6 8 10 12 14 16 18 20 ", ss.str());
  ss.str("");
}

//This helps with testing, do not modify.
void testIteratorIncrement() {
  //cout << "|||### You need to comment in testIteratorIncrement() when it's ready and remove this ###|||" << endl;
  DoublyLinkedList<int>* d = new DoublyLinkedList<int>;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 20; i += 2) {
    d->pushBack(i);
  }

  //Get an iterator which points at the beginning of the list
  Iterator<int> iter = d->begin();

  //Test that it does point to the first
  checkTest("testIteratorsIncrement #1", 2, *iter);

  //Test that our Iterator can move forward;
  ++iter;
  checkTest("testIteratorsIncrement #2", 4, *iter);


  //Test that our Iterator can move forward again;
  ++iter;
  checkTest("testIteratorsIncrement #3", 6, *iter);

  //move it some more
  for (int i = 0; i < 6; i++) {
    ++iter;
  }
  checkTest("testIteratorsIncrement #4", 18, *iter);

  //Hit the end
  ++iter;
  checkTest("testIteratorsIncrement #5", 20, *iter);

  ////Verify we move the iterator past the end without crashing
  ++iter;
  string didntCrash = "did not crash";
  checkTest("testIteratorsIncrement #6", didntCrash, didntCrash);


  delete d;
}

//This helps with testing, do not modify.
void testIteratorDecrement() {
  cout << "|||### You need to comment in testIteratorDecrement() when it's ready and remove this###|||" << endl;

  DoublyLinkedList<int>* d = new DoublyLinkedList<int>;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 20; i += 2) {
    d->pushBack(i);
  }

  //Get an Iterator which points at the end of the list    (Not on the last item, but on the "end" state)
  Iterator<int> iter = d->end();

  --iter;  // We have to do a decrement otherwise the iterator is in the past-the-end state and isn't pointing at a value
           // Don't comment out this line, even if it makes your test #2 pass.  It will make later tests fail.
           // If you comment out this line and later contact me for help, then I will drive up to your residence, 
           // ring your doorbell, and stare at you angrily.  

  //Test that it does point to the first
  checkTest("testIteratorsDecrement #1", 20, *iter);

  ////Test that our Iterator can move forward;
  --iter;
  checkTest("testIteratorsDecrement #2", 18, *iter);

  //move it some more
  for (int i = 0; i < 7; i++) {
    --iter;
  }

  checkTest("testIteratorsDecrement #3", 4, *iter);

  //Hit the end
  --iter;
  checkTest("testIteratorsDecrement #4", 2, *iter);

  //Now go back forward
  ++iter;
  checkTest("testIteratorsDecrement #5", 4, *iter);

  delete d;
}

//This helps with testing, do not modify.
void testIterationTricky() {

  cout << "|||### You need to comment in testIterationTricky() when it's ready and remove this###|||" << endl;

  DoublyLinkedList<int> myListOneNode;

  myListOneNode.pushBack(42);
  cout << "TestIterationTricky test #1, the next line should display 42" << endl;
  stringstream ss;
  //see if we can just iterator through one item.
  for (auto i : myListOneNode) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("TestIterationTricky test #1", "42 ", ss.str());
  ss.str("");

  DoublyLinkedList<int> myListEmpty;
  cout << "TestIterationTricky test #2, the next line shouldn't display anything" << endl;
  //see if we can just iterator through one item.
  for (auto i : myListEmpty) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("TestIterationTricky test #2", "", ss.str());
  ss.str("");
}



//This helps with testing, do not modify.
void testAlgorithms() {
  cout << "|||### You need to comment in testAlgorithms() when it's ready and remove this###|||" << endl;

  DoublyLinkedList<int> myList;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 6; i += 2) {
    myList.pushBack(i);
  }
  myList.pushBack(100);
  for (int i = 8; i <= 12; i += 2) {
    myList.pushBack(i);
  }
  myList.pushBack(100);
  for (int i = 14; i <= 20; i += 2) {
    myList.pushBack(i);
  }
  stringstream ss;
  cout << "testAlgorithms test #1, this should display 2 4 6 100 8 10 12 100 14 16 18 20." << endl;
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #1", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
  ss.str("");

  //Test the STL reverse algorithm on our iterator
  cout << "testAlgorithms test #2, this should display 20 18 16 14 100 12 10 8 100 6 4 2." << endl;
  std::reverse(myList.begin(), myList.end());
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #2", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
  ss.str("");

  //Get it back in ascending order using the STL reverse algorithm
  std::reverse(myList.begin(), myList.end());
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #3", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
  ss.str("");

  // Try a custom assignmentReverse function

  assignmentReverse(myList.begin(), myList.end());
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #4", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
  ss.str("");

  //Get it back in ascending order using the STL reverse algorithm
  assignmentReverse(myList.begin(), myList.end());
  for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;

  checkTest("testAlgorithms test #5", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
  ss.str("");

  // Test assignmentReverse on an STL container:


  list<int> stlList;

  //Our test data should have all even numbers from 2 to 20
  for (int i = 2; i <= 6; i += 2) {
    stlList.push_back(i);
  }
  stlList.push_back(100);
  for (int i = 8; i <= 12; i += 2) {
    stlList.push_back(i);
  }
  stlList.push_back(100);
  for (int i = 14; i <= 20; i += 2) {
    stlList.push_back(i);
  }
  for (auto i : stlList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #6", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
  ss.str("");

  // Try a custom assignmentReverse function

  assignmentReverse(stlList.begin(), stlList.end());
  for (auto i : stlList) {
    cout << i << " ";
    ss << i << " ";
  }
  cout << endl;
  checkTest("testAlgorithms test #7", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
  ss.str("");


}

void pressAnyKeyToContinue() {
  cout << "Press enter to continue...";
  cin.get();
}

int main() {

    cout << "This first test can run forever until you get operators *, != and ++ implemented." << endl;
    pressAnyKeyToContinue();

    testIteratorFundamentals();
    pressAnyKeyToContinue();

    testIteratorIncrement();
    pressAnyKeyToContinue();

    testIteratorDecrement();
    pressAnyKeyToContinue();

    testIterationTricky();
    pressAnyKeyToContinue();

    testAlgorithms();
    pressAnyKeyToContinue();

    return 0;
}
