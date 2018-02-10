#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <cassert> 
#include <cstddef>


template <typename T>
class Polygon {
    //a doubly-linked, circular list with Iterator interface
    //tail iterator is broken as it loops back to head iterator, 
    //thus size MUST be carefully maintained.
    public:

    bool empty() const;
  
    //returns the number of nodes in a polygon.
    int size() const;
  
    //MODIFIES: this
    //EFFECTS:  inserts datum into the back of the polygon
    void push_back(const T &datum);
  
  
    //deletes "last" node of polygon
    void pop_back();
  
    //CTOR
    //makes an empty polygon 
    Polygon();

    Polygon(int size_in);

    //COPY CTOR
    Polygon(const Polygon & other);
  
    //DESTRUCTOR
    ~Polygon();
  
    //override assignment to deep copy
    Polygon & operator= (const Polygon &rhs);
  
    private:
    int num_nodes;
    struct Node {
      Node *next;
      Node *prev;
      T datum;
    };

    //copies all nodes from other to this
    void copy_all(const Polygon<T> &other);
  
    //removes all nodes
    void pop_all();
  
    Node *first;   // points to first Node in polygon, or nullptr if polygon is empty
    Node *last;    // points to last Node in polygon, or nullptr if polygon is empty
  
    public:
    ////////////////////////////////////////
    class Iterator {
    friend class Polygon;
      //OVERVIEW: Iterator interface to List

      // You should add in a default constructor, destructor, copy constructor,
      // and overloaded assignment operator, if appropriate. If these operations
      // will work correctly without defining these, you can omit them. A user
      // of the class must be able to create, copy, assign, and destroy Iterators.
  
      // Your iterator should implement the following public operators: *,
      // ++ (prefix), default constructor, == and !=.
  
      public:
      //Constructor
      Iterator();
      
      // This operator will be used to test your code. Do not modify it.
      // Requires that the current element is dereferenceable.
      Iterator & operator--() {
        assert(node_ptr);
        node_ptr = node_ptr->prev;
        return *this;
      }
  
      //REQUIRES: we are not past the end 
      T & operator*() const;
  
      //REQUIRES: we are not past the end 
      Iterator & operator++();
  
      bool operator!=(Iterator rhs) const;
  
      bool operator==(Iterator rhs) const;
  
      private:
      Node *node_ptr; //current Iterator position is a List node
      // add any additional necessary member variables here
  
      // add any friend declarations here
  
      // construct an Iterator at a specific position
      Iterator(Node *p);
  
    };//List::Iterator
    ////////////////////////////////////////

    // return an Iterator pointing to the first element
    Iterator begin() const;
  
    // return an Iterator pointing to "past the end"
    Iterator end() const;

    //REQUIRES: i is a valid, dereferenceable iterator associated with this polygon
    //MODIFIES: this, may invalidate other polygon iterators
    //EFFECTS: Removes a single element from the polygon container
    void erase(Iterator i);
  
    //REQUIRES: i is a valid iterator associated with this polygon
    //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

template <typename T>
bool Polygon<T>::empty() const{
    return (first == nullptr);
}

template <typename T>
int Polygon<T>::size() const{
    return num_nodes;
    /*
    int i = 0;
    for (Node *ptr = first; ptr != nullptr; ptr=ptr->next) {
        ++i;
    }
    return i;
    */
}

/******************
template <typename T>
T & Polygon<T>::front(){
    assert(!empty());
    //returned by reference
    return first->datum;
}

template <typename T>
T & Polygon<T>::back(){
    assert(!empty());
    //returned by reference
    return last->datum;
}
*************************/

/*
template <typename T>
void Polygon<T>::push_front(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    p->next = nullptr;
    p->prev = nullptr;

    if (!empty()) {
        p->next = first;
        //p should be the old first's prev, and the new first
        first = first->prev = p;
    } else {    //empty
        p->next = first;
        last = first = p;
    }
}
*/

template <typename T>
void Polygon<T>::push_back(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    p->next = nullptr;
    p->prev = nullptr;

    if (!empty()) {
        p->prev = last;
		p->next = first;
        //p should have the old last as prev, be the next of old last, 
        //and be the new last
        last = last->next = p;
        first->prev = last;
    } else {    //empty
        p->prev = last;
        first = last = p;
    }
}

template <typename T>
void Polygon<T>::pop_front(){
    assert(!empty());
    Node *victim = first;

    if (size() != 1) {
        first = victim->next;
        first->prev = nullptr;
    } else {    //singleton
        first = victim->next;
        last = nullptr;
    }

    delete victim;
}

template <typename T>
void Polygon<T>::pop_back(){
    assert(!empty());
    Node *victim = last;

    if (size() != 1) {
        last = victim->prev;
        //last->next = nullptr;
    } else {    //singleton
        last = victim->prev;
        //so the first should point nowhere
        first = nullptr;
    }

    delete victim;
}

template <typename T>
Polygon<T>::Polygon() 
    : num_nodes(0), first(nullptr), last(nullptr) {}

template <typename T>
Polygon<T>::Polygon(int size_in) 
    : num_nodes(size_in), first(nullptr), last(nullptr) {}

template <typename T>
Polygon<T>::Polygon(const Polygon & other)
    : first(nullptr) {
        copy_all(other);
}

template <typename T>
Polygon<T>::~Polygon(){
    pop_all();
}

template <typename T>
Polygon<T> & Polygon<T>::operator= (const Polygon &rhs){
    if (this == &rhs) return *this;
    pop_all();
    copy_all(rhs);
    return *this;
}

template <typename T>
void Polygon<T>::copy_all(const Polygon<T> &other){
    for (Node *ptr = other.first; ptr != nullptr; ptr=ptr->next) {
        push_back(ptr->datum);
    }
}

template <typename T>
void Polygon<T>::pop_all(){
    int i = num_nodes;
    while (i > 0) {
        pop_back();
        i--;
    }
    /*
    while (!empty()) {
        pop_back();
    }
    */
}

template <typename T>
Polygon<T>::Iterator::Iterator()
    : node_ptr(nullptr) {}

template <typename T>
T & Polygon<T>::Iterator::operator* () const{
    assert(node_ptr != nullptr);
    return node_ptr->datum;
}

template <typename T>
typename Polygon<T>::Iterator & Polygon<T>::Iterator::operator++(){
    assert(node_ptr != nullptr);
    node_ptr = node_ptr->next;
    return *this;
}

template <typename T>
bool Polygon<T>::Iterator::operator!=(Iterator rhs) const{
    return node_ptr != rhs.node_ptr;
}

template <typename T>
bool Polygon<T>::Iterator::operator==(Iterator rhs) const{
    return node_ptr == rhs.node_ptr;
}

template <typename T>
Polygon<T>::Iterator::Iterator(Node *p)
    : node_ptr(p) {}

template <typename T>
typename Polygon<T>::Iterator Polygon<T>::begin() const{
    return Iterator(first);
}

template <typename T>
typename Polygon<T>::Iterator Polygon<T>::end() const{
    return Iterator();
}

template <typename T>
void Polygon<T>::erase(Iterator i){
    //note we don't have equality for iterators but we can pull a 
    //not not equal
    if (i == begin()) {
        pop_front();
    } else if ((i.node_ptr)->next == nullptr) {
        pop_back();
    } else {
    //else we can safely assume there is a node to either side of that
    //being pointed to by our iterator
        ((i.node_ptr)->prev)->next = (i.node_ptr)->next;
        ((i.node_ptr)->next)->prev = (i.node_ptr)->prev;
        delete i.node_ptr;
    }
}
  

template <typename T>
void Polygon<T>::insert(Iterator i, const T &datum){
    //note we don't have equality for iterators but we can pull a 
    //not not equal
    if (i == begin()) {
        push_front(datum);
    } else if ((i.node_ptr)->next == nullptr) {
        push_back(datum);
    } else {
    //else we can safely assume there is a node to either side of that
    //being pointed to by our iterator
        Node *p = new Node;
        p->datum = datum;
        // i.prev <-> p <-> i
        p->next = i.node_ptr;
        p->prev = (i.node_ptr)->prev;
        ((i.node_ptr)->prev)->next = p;
        (i.node_ptr)->prev = p;
    }
}


#endif

