#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  List();
  ~List();
  List(const List<T>& other);
  //EFFECTS:  returns true if the list is empty
  bool empty() const;
  List<T>& operator=(const List<T>& other);


  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:

  Iterator():node_ptr(nullptr){}
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator& operator++() {
        assert(node_ptr != nullptr); 
        node_ptr = node_ptr->next;
        return *this;
    }

    T& operator*() const {
    assert(node_ptr != nullptr);
    return node_ptr->datum;
    }

    bool operator==(const Iterator& other) const {
        return node_ptr == other.node_ptr;
    }

    bool operator!=(const Iterator& other) const {
        return node_ptr != other.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List<T>;
    // construct an Iterator at a specific position
    Iterator(Node *p):node_ptr(p){}
    

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    assert(i.node_ptr != nullptr);
    Node* toErase = i.node_ptr;
    if (toErase == first && toErase == last) {
        first = last = nullptr;
    } else if (toErase == first) {
        first = first->next;
        first->prev = nullptr;
    } else if (toErase == last) {
        last = last->prev;
        last->next = nullptr;
    } else {
        toErase->prev->next = toErase->next;
        toErase->next->prev = toErase->prev;
    }
    delete toErase;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    Node* newNode = new Node{nullptr, nullptr, datum};
    Node* current = i.node_ptr;

    if (current == nullptr) {
        newNode->prev = last;
        if (last != nullptr) {
            last->next = newNode;
        } else {
            first = newNode;
        }
        last = newNode;
    } else if (current == first) {
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    } else {
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
    }

  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

template <typename T>
List<T>::List() : first(nullptr), last(nullptr) {}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
List<T>::List(const List<T>& other) : first(nullptr), last(nullptr) {
    copy_all(other);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        clear(); // Clear the current list
        copy_all(other); // Copy elements from 'other' list
    }
    return *this;
}






template <typename T>
bool List<T>::empty() const {
  return first == nullptr;
}

template <typename T>
int List<T>::size() const {
  int c=0;
  Node * cur = first;
  while (cur !=nullptr) {
    c++;
    cur=cur->next;
  }
  return c;
}

template <typename T>
T& List<T>::front() {
  return first->datum;
} 

template <typename T>
T& List<T>::back() {
  return last->datum;
}

template <typename T>
void List<T>::push_front(const T& datum) {
  Node* n= new Node;
  n->prev = nullptr;
  n->next = first;
  n->datum = datum;
  if(empty()) {
    first = n;
    last = n;
  } else {
    first ->prev=n;
    first = n;
  }
}

template <typename T>
void List<T>::push_back(const T& datum) {
  Node* n= new Node;
  n->prev = last;
  n->next = nullptr;
  n->datum = datum;
  if(empty()) {
    first = n;
    last = n;
  } else {
    last ->next =n;
    last = n;
  }
}

template <typename T>
void List<T>::pop_front() {

  Node* temp = first;
  first = first->next;
  if (first == nullptr) {
    last = nullptr;
  } else {
    first->prev = nullptr;
  }
  delete temp;
}

template <typename T>
void List<T>::pop_back() {
  Node* temp = last;
  last = last->prev;
  if (last == nullptr) {
    first = nullptr;
  } else {
    last->next = nullptr;
  }
  delete temp;
}

template <typename T>
void List<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
void List<T>::copy_all(const List<T>& other) {
  for (Node* current = other.first; current != nullptr; current = current->next) {
    push_back(current->datum);
  }
}







#endif // Do not remove this. Write all your code above this line.
