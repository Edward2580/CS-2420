
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void pressAnyKeyToContinue();


vector<bool> destructTracker;

class Int {
public:
  int val{ -1 };
  void operator=(const Int& objToClone) {
    if (this != &objToClone) {
      destructTracker[val] = true;
      this->val = objToClone.val;
    }
  }
  ~Int() {
    destructTracker[val] = true;
  }
private:

};

class DestructorTester {
public:
  DestructorTester() {
    index.val = destructTracker.size();
    destructTracker.push_back(false);
  }
  ~DestructorTester() {
    destructTracker[index.val] = true;
  }
private:
  //int index{ -1 };
  Int index;
};


//This base class helps the assignment compile and run without any changes.  
//Dot not modify it.  You will instead override the methods in the derived classes below.
template <typename T>
class BaseQueue {
public:
  BaseQueue() { }
  void push_back(const T& item) { cout << "This push_back() method is filler, override it in the derived class" << endl; }
  void pop_front() { cout << "This pop_front() method is filler, override it in the derived class" << endl; }
  T front() { cout << "This front() method is filler, override it in the derived class" << endl; T temp{}; return temp; }
  T back() { cout << "This back() method is filler, override it in the derived class" << endl; T temp{}; return temp; }
  const unsigned int size() const { cout << "This size() method is filler, override it in the derived class" << endl; return 0; }

  // This just disables the copy/move constructors/assignments
  BaseQueue(const BaseQueue<T>& objToCopy) { cout << "This copy constructor is filler, override it in the derived class" << endl; }
  const BaseQueue<T>& operator=(const BaseQueue<T>& objToCopy) { cout << "This operator= is filler, override it in the derived class" << endl; return *this; };
  BaseQueue(BaseQueue<T>&& objToCopy) = delete;  // Disable link shortener
  BaseQueue<T>& operator=(BaseQueue<T>&& objToCopy) = delete;  // Disable link shortener
  // Assignment solution key: https://tinyurl.com/4j8mjhcz
protected:
  T* arr{ nullptr };

};

//**********************************
//Write your code below here
//**********************************
template <typename T>
class QueueForCS2420 : public BaseQueue<T> {
public:
  // TODO: Complete constructor, copy constructor, copy assignment, and destructor, and all other needed methods
  QueueForCS2420(const unsigned int capacity);
  QueueForCS2420(const QueueForCS2420& objToCopy);
  const QueueForCS2420<T>& operator=(const QueueForCS2420<T>& objToCopy);
  ~QueueForCS2420();
  void push_back(const T& item);
  void pop_front();
  T front();
  T back();
  const unsigned int size() const;

private:

  // TODO: Supply the 4 needed data members
    unsigned int capacity{ 0 };
    unsigned int quantity{ 0 };

    unsigned int head{ 0 };
    unsigned int tail{ 0 };

};


template <typename T>
QueueForCS2420<T>::QueueForCS2420(const unsigned int capacity) {
    this->capacity = capacity;
    this->arr = new T[capacity];

}
  // TODO: Complete this
//copy
template <typename T>
QueueForCS2420<T>::QueueForCS2420(const QueueForCS2420<T>& objToCopy) {
    //copying 
    this->capacity = objToCopy.capacity;
    this->quantity = objToCopy.quantity;
    this->head = objToCopy.head;
    this->tail = objToCopy.tail;
    this->arr = new T[this->capacity];

    for (unsigned int i = 0; i < this->capacity; i++) {
        this->arr[i] = objToCopy.arr[i];
    }

}
//copy assignment
template <typename T>
const QueueForCS2420<T>& QueueForCS2420<T>::operator=(const QueueForCS2420<T>& objToCopy) {
    if (this != &objToCopy) {

        if (this->arr) {
            //Resetting the pointer
            delete[] this->arr;
            this->arr = nullptr;
            this->capacity = 0;
        }

        //copying once again
        this->capacity = objToCopy.capacity;
        this->quantity = objToCopy.quantity;
        this->head = objToCopy.head;
        this->tail = objToCopy.tail;
        this->arr = new T[this->capacity];
        for (unsigned int i = 0; i < this->capacity; i++) {
            this->arr[i] = objToCopy.arr[i];
        }
    }
    return *this;
}

template <typename T>
QueueForCS2420<T>::~QueueForCS2420(){
        delete[] this->arr;
}

template <typename T>
const unsigned int QueueForCS2420<T>::size() const {
    return quantity;
}

template <typename T>
void QueueForCS2420<T>::push_back(const T& item) {
    if (quantity == capacity) {
        cout << ("error");
    }
    else if (tail >= capacity) {
        tail = 0;
        this->arr[tail] = item;
        tail++;
        quantity++;
    }
    else {
        this->arr[tail] = item;
        tail++;
        quantity++;
    }
}

template <typename T>
void QueueForCS2420<T>::pop_front() {
    if (quantity == 0) {
        throw(1);
    }
    else if(head >= capacity){
        head = 0;
        head++;
        quantity--;
    }
    else {
        head++;
        quantity--;
    }
}

template<typename T>
T QueueForCS2420<T>::front() {
    if (quantity != 0) {
        if (head >= capacity) {
            head = 0;
            return this->arr[head];
        }
        return this->arr[head];
    }

    else {
        throw(1);
    }
}

template<typename T>
T QueueForCS2420<T>::back() {
    if (quantity != 0) {
        return this->arr[tail-1];
    }
    else {
        throw(1);
    }
}
//**********************************
//Write your code above here
//**********************************

//This helps with testing, do not modify.

//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    if (whatItShouldBe == "") {
      cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
    }
    else {
      cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    }
    exit(1);
    return false;
  }
}

template <typename T, typename U>
bool checkTest(string testName, T whatItShouldBe, U whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
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
    cout << "***Failed test " << testName << " *** " << endl << ".  ";
    cout << "You are manually managing " << whatItIs << " bytes in memory, but it should be " << whatItShouldBe << " bytes." << endl;
    return false;
    exit(1);
  }
}



void testQueueForCS2420() {

  string result;
  string caughtError;
  {
    QueueForCS2420<string> pQueue(5);

    // Tests push_back
    string item = "penny";
    pQueue.push_back(item);
    item = "nickel";
    pQueue.push_back(item);
    item = "dime";
    pQueue.push_back(item);
    item = "quarter";
    pQueue.push_back(item);

    checkTest("testQueueForCS2420 #1", 4, pQueue.size());

    checkTest("testQueueForCS2420 #2", "penny", pQueue.front());
    checkTest("testQueueForCS2420 #3", "quarter", pQueue.back());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #4", 3, pQueue.size());

    checkTest("testQueueForCS2420 #5", "nickel", pQueue.front());
    checkTest("testQueueForCS2420 #6", "quarter", pQueue.back());

    pQueue.pop_front();
    checkTest("testQueueForCS2420 #7", "dime", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #8", "quarter", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #9", 0, pQueue.size());

    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (int) {
      caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #10", "caught", caughtError);

    caughtError = "not caught";
    try {
      result = pQueue.back();
    }
    catch (int) {
      caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #11", "caught", caughtError);

    checkTest("testQueueForCS2420 #12", 0, pQueue.size());

    item = "penny";
    pQueue.push_back(item);
    checkTest("testQueueForCS2420 #13", "penny", pQueue.front());
    pQueue.push_back("nickel");
    pQueue.push_back("dime");
    pQueue.push_back("quarter");

    checkTest("testQueueForCS2420 #14", "penny", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("half dollar");
    pQueue.push_back("silver dollar");

    // It should be full, no more room to add more.
    pQueue.push_back("million dollar bill");

    // Because of so many tests, pause for a bit on the screen.
    pressAnyKeyToContinue();

    // Take a look at what is coming next.
    checkTest("testQueueForCS2420 #15", "nickel", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #16", "dime", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #17", "quarter", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #18", "half dollar", pQueue.front());
    pQueue.pop_front();
    checkTest("testQueueForCS2420 #19", "silver dollar", pQueue.front());
    pQueue.pop_front();
    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (int) {
      caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #20", "caught", caughtError);

    // Test adding and removing back and forth
    pQueue.push_back("penny");
    checkTest("testQueueForCS2420 #21", "penny", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("nickel");
    checkTest("testQueueForCS2420 #22", "nickel", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("dime");
    checkTest("testQueueForCS2420 #23", "dime", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("quarter");
    checkTest("testQueueForCS2420 #24", "quarter", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("half dollar");
    checkTest("testQueueForCS2420 #25", "half dollar", pQueue.front());
    pQueue.pop_front();
    pQueue.push_back("silver dollar");
    checkTest("testQueueForCS2420 #26", 1, pQueue.size());

    checkTest("testQueueForCS2420 #27", "silver dollar", pQueue.front());
    pQueue.pop_front();
    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (int) {
      caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #28", "caught", caughtError);
  }
  {
    QueueForCS2420<int> iQueue(3); // A queue of 3 items

    iQueue.push_back(1);
    iQueue.push_back(2);
    iQueue.pop_front();
    iQueue.push_back(3);
    iQueue.pop_front();
    checkTest("testQueueForCS2420 #29", 3, iQueue.front());
    checkTest("testQueueForCS2420 #30", 3, iQueue.back());
    iQueue.push_back(4);
    iQueue.push_back(5);
    checkTest("testQueueForCS2420 #31", 3, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueForCS2420 #32", 4, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueForCS2420 #33", 5, iQueue.front());
  }

}

void testQueueClone() {

  string result;
  string caughtError;

  // Test copy constructor
  {
    QueueForCS2420<int> iQueue(5);
    iQueue.push_back(10);
    iQueue.push_back(20);
    iQueue.push_back(30);
    iQueue.push_back(40);
    iQueue.push_back(50);

    QueueForCS2420<int> iCopy(iQueue);
    checkTest("testQueueClone #1", 5, iQueue.size());
    checkTest("testQueueClone #2", 5, iCopy.size());
    checkTest("testQueueClone #3", 10, iQueue.front());
    checkTest("testQueueClone #4", 10, iCopy.front());

    iCopy.pop_front();
    checkTest("testQueueClone #5", 4, iCopy.size());
    checkTest("testQueueClone #6", 20, iCopy.front());
    checkTest("testQueueClone #7", 10, iQueue.front());
  }

  // Test operator=
  {
    QueueForCS2420<int> iQueue(5);
    iQueue.push_back(10);
    iQueue.push_back(20);
    iQueue.push_back(30);
    iQueue.push_back(40);
    iQueue.push_back(50);

    QueueForCS2420<int> iCopy(5);
    iCopy.push_back(1111);
    iCopy = iQueue;
    checkTest("testQueueClone #8", 5, iQueue.size());
    checkTest("testQueueClone #9", 5, iCopy.size());
    checkTest("testQueueClone #10", 10, iQueue.front());
    checkTest("testQueueClone #11", 10, iCopy.front());

    iCopy.pop_front();
    checkTest("testQueueClone #12", 4, iCopy.size());
    checkTest("testQueueClone #13", 20, iCopy.front());
    checkTest("testQueueClone #14", 10, iQueue.front());
  }

  // Test an attempted cloning an object onto itself (obviously it shouldn't attempt to clone it)
  {
    QueueForCS2420<int> iQueue(5);
    iQueue.push_back(10);
    iQueue.push_back(20);
    iQueue.push_back(30);
    iQueue.push_back(40);
    iQueue.push_back(50);

    iQueue = iQueue;
    checkTest("testQueueClone #15", 5, iQueue.size());
    checkTest("testQueueClone #16", 10, iQueue.front());
    iQueue.pop_front();
    checkTest("testQueueClone #17", 20, iQueue.front());
  }
}

void testDestructor() {

  // Test that it destroys everything 
  // (It's a queue of DestructorTestor objects.  Each time a Destructor tester object is created
  // it will append a new false value to a global destructTracker vector.  Each time a Destructor object is
  // destructed, it will set its corresponding false value to true.)

  {
    QueueForCS2420< DestructorTester > dQueue(5); // <--- Constructor invokes here
  }  // <--- Destructor should invoke here.

  bool everythingDestructed{ true };
  if (destructTracker.size() != 5) {
    everythingDestructed = false;
  }
  else {
    for (int i = 0; i < 5; i++) {
      if (!destructTracker[i]) {
        everythingDestructed = false;
      }
    }
  }
  if (everythingDestructed) {
    cout << "Passed testDestructor #1" << endl;
  }
  else {
    cout << "***Failed test testDestructor #1 *** " << endl << "   You are missing a destructor, or your destructor didn't work. " << endl;
  }

  destructTracker.clear();

  {
    QueueForCS2420< DestructorTester > dQueue(3);
    QueueForCS2420< DestructorTester > dClone(dQueue);
  }  // <--- Destructor should invoke here.

  everythingDestructed = true;
  if (destructTracker.size() != 6) {
    everythingDestructed = false;
  }
  else {
    for (auto destructed : destructTracker) {
      if (!destructed) {
        everythingDestructed = false;
      }
    }
  }

  // If this test fails, then your resize() method likely didn't call delete[] on the original this->arr.  
  if (everythingDestructed) {
    cout << "Passed testDestructor #2" << endl;
  }
  else {
    cout << "***Failed test testDestructor #2 *** " << endl << "   You are missing a destructor, or your destructor didn't work. " << endl;
  }

 destructTracker.clear();

  {
    QueueForCS2420< DestructorTester > dQueue(3);
    QueueForCS2420< DestructorTester > dClone(3);
    dQueue = dClone;
  }  // <--- Destructor should invoke here.

  everythingDestructed = true;
  if (destructTracker.size() != 9) {
    everythingDestructed = false;
  }
  else {
    for (auto destructed : destructTracker) {
      if (!destructed) {
        everythingDestructed = false;
      }
    }
  }

  // If this test fails, then your resize() method likely didn't call delete[] on the original this->arr.  
  if (everythingDestructed) {
    cout << "Passed testDestructor #3" << endl;
  }
  else {
    cout << "***Failed test testDestructor #3 *** " << endl << "   You are missing a destructor, or your destructor didn't work. " << endl;
  }

  destructTracker.clear();

}


void pressAnyKeyToContinue() {
  cout << "Press enter to continue...";

  //Linux and Mac users with g++ don't need this
  //But everyone else will see this message.
  cin.get();

}

int main() {

  {
    testQueueForCS2420();
    pressAnyKeyToContinue();
    testQueueClone();
    pressAnyKeyToContinue();
    testDestructor();
    pressAnyKeyToContinue();
  }
  cout << "Shutting down the program" << endl;
  return 0;
}


