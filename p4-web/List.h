#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
    //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
    
    //EFFECTS:  returns true if the list is empty
    bool empty() const{
        if ((first==nullptr)&(last==nullptr)){
            return true;
        }
        else{
            return false;
        }
    }
    
    //EFFECTS: returns the number of elements in this List
    int size() const{
        int size = 0;
        Node *tmp = first;
        while(tmp!=nullptr){
            size++;
            tmp=tmp->next;
        }
        return size;
    }
    
    //REQUIRES: list is not empty
    //EFFECTS: Returns the first element in the list by reference
    T & front(){
        assert((first!=nullptr)&(last!=nullptr));
        return first->datum;
    }
    
    //REQUIRES: list is not empty
    //EFFECTS: Returns the last element in the list by reference
    T & back(){
        assert((first!=nullptr)&(last!=nullptr));
        return last->datum;
    }
    
    //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum){
        Node *tmp = new Node;
        tmp->datum = datum;
        tmp->prev  = nullptr;
        if ((first ==nullptr) | (last ==nullptr)){
            tmp->next = nullptr;
            first = tmp;
            last = tmp;
            
        }
        else {
            tmp->next  = first;
            first->prev = tmp;
            first = first->prev;
        }
    }
    
    //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum){
        Node * tmp= new Node;
        //std::cout<<"here"<<std::endl;
        tmp->datum =datum;
        tmp->next  = nullptr;
        if ((first ==nullptr) | ((last ==nullptr))){
            tmp->prev = nullptr;
            first = tmp;
            last = tmp;
        }
        else {
            tmp->prev = last;
            last->next=tmp;
            last = last->next;
        }
    }
    
    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the front of the list
    void pop_front(){
        assert(size()>0);
        Node * tmp = first;
        tmp = tmp->next;
        delete first;
        first = tmp;
        if (first == nullptr){
            last = nullptr;
            return;}
        first->prev= nullptr;
    }
    
    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the back of the list
    void pop_back() {
        assert(size()>0);
        Node * tmp = last;
        tmp = tmp->prev;
        delete last;
        last = tmp;
        if (last==nullptr){
            first = nullptr;
            return;}
        last->next = nullptr;
        
    }
    List(){
        std::cout<<"Native constructor here."<<std::endl;
        first = nullptr;
        last  = nullptr;
    }
    
    List(const List<T> & obj){
        std::cout<<"Copy constructor here."<<std::endl;
        if ( (obj.first ==nullptr)| (obj.last ==nullptr)){
            first = nullptr;
            last  = nullptr;
        }
        else{
            copy_all(obj);
            // *this = obj;
        }
    }
    
    List & operator=(const List<T> & obj){
        std::cout<<"Equal assignment here."<<std::endl;
        if (this == &obj) {return *this;}
        else{
//            std::cout<<(first==nullptr)<<(last==nullptr)<<std::endl;
//            assert(false);
            if((first!=nullptr)|(last!=nullptr)){
                pop_all();}
            
            copy_all(obj);
            return *this;}
    }
    ~List(){pop_all();}
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
    void copy_all(const List<T> &other){
//        first = nullptr;
//        last = nullptr;
        Node * tmp = other.first;
        while(tmp!= nullptr){
            push_back(tmp->datum);
            tmp = tmp->next;
        }
    }
    
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes all nodes
    void pop_all() {
        Node *tmp = first;
        while(tmp!=nullptr)
        {   //std::cout<<tmp1->datum<<std::endl;
            tmp = tmp->next;
            //std::cout<<"Here."<<std::endl;
            delete first;
            first = tmp;
        }
        first = nullptr;
        last = nullptr;
        
    }
    
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
        Iterator(){
            node_ptr = nullptr;
        }
        Iterator(const Iterator & obj){
            node_ptr= obj.node_ptr;
        }
        ~Iterator(){}
        // This operator will be used to test your code. Do not modify it.
        // Requires that the current element is dereferenceable.
//        Iterator& operator--() {
//            assert(node_ptr);
//            node_ptr = node_ptr->prev;
//            return node_ptr->datum;
//        }
        Iterator& operator--() {
            assert(node_ptr);
            node_ptr = node_ptr->prev;
            return *this;
        }
        Iterator& operator++() {
            assert(node_ptr);
            node_ptr = node_ptr->next;
            return *this;
        }
        
        T & operator*() const{
            assert(node_ptr);
            return node_ptr->datum;
        }
        bool operator==(const Iterator & obj) const{
            //assert(node_ptr);
            return node_ptr==obj.node_ptr;
        }
        bool operator!=(const Iterator & obj) const{
            //assert(node_ptr);
            return node_ptr!=obj.node_ptr;
        }
        
        Node * get_ptr(){
            return node_ptr;
        }
        
        
        


    private:
        Node *node_ptr; //current Iterator position is a List node
        // add any additional necessary member variables here
        
        // add any friend declarations here
        friend class List;
//        friend Iterator begin();
//        friend Iterator end();
//        friend void erase(Iterator i);
//        friend void insert(Iterator i, const T &datum);
        // construct an Iterator at a specific position
        Iterator(Node *p){
            node_ptr = p;
        }
        
    };//List::Iterator
    ////////////////////////////////////////
    
    // return an Iterator pointing to the first element
    Iterator begin() const {
        return Iterator(first);
    }
    
    // return an Iterator pointing to "past the end"
    Iterator end() const{
        if (last==nullptr) {return Iterator(last);}
        return Iterator(last->next);
    }
    
    //REQUIRES: i is a valid, dereferenceable iterator associated with this list
    //MODIFIES: may invalidate other list iterators
    //EFFECTS: Removes a single element from the list container
    void erase(Iterator i){
        assert(i.get_ptr());
        if (i.get_ptr() ==first){
            pop_front();
        }
        else if (i.get_ptr() ==last){
            pop_back();
        }
        else{
        Node *tmp = i.get_ptr()->prev;
        tmp->next =tmp->next->next;
        delete i.get_ptr();}
    }
    
    //REQUIRES: i is a valid iterator associated with this list
    //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum){
        if (i.get_ptr()==nullptr | i.get_ptr()==first) {
            push_front(datum);
        }
        else{
            Node * tmp = new Node;
            tmp->datum = datum;
            tmp->prev = (--i).get_ptr()->prev;
            i.get_ptr()->next = tmp;
            tmp->next = (++i).get_ptr();
            i.get_ptr()->prev = tmp;}
    }
    
    
};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
