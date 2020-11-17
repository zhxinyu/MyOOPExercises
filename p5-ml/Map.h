#ifndef MAP_H
#define MAP_H
/* Map.h
 *
 * Abstract data type representing a map of key-value pairs with
 * unique keys. A subset of the std::map interface
 * http://www.cplusplus.com/reference/map/map/
 * Project UID db1f506d06d84ab787baf250c265e24e
 *
 * By Andrew DeOrio <awdeorio@umich.edu>
 *    Amir Kamil    <akamil@umich.edu>
 *    James Juett   <jjuett@umich.edu>
 * Updated
 *   2016-11-23
 *
 * DO NOT modify the public interface. Modify anything else you need to.
 */

#include "BinarySearchTree.h"
#include <cassert>  //assert
#include <utility>  //pair

template <typename Key_type, typename Value_type,
          typename Key_compare=std::less<Key_type> // default argument
         >
class Map {

private:
  // Type alias for an element, the combination of a key and mapped
  // value stored in a std::pair.
  // See http://www.cplusplus.com/reference/utility/pair/

  using Pair_type = std::pair<Key_type, Value_type>;
  // A custom comparator
  class PairComp {
  public:
      Key_compare comp;
      bool operator()(const Pair_type & a, const Pair_type & b)const{
        return comp(a.first,b.first);
          //return Key_compare(a.first,b.first);
      }
  };

public:

  // OVERVIEW: Maps are associative containers that store elements
  // formed by a combination of a key value and a mapped value,
  // following a specific order.
  //
  // NOTE: This Map should be represented using a BinarySearchTree that
  //       stores (key, value) pairs. See Pair_type above. You will
  //       also need to define an appropriate comparator type (PairComp) for the
  //       BinarySearchTree to use in comparing elements, so that they
  //       are compared based on the key stored in the first member of
  //       the pair, rather than the built-in behavior that compares the
  //       both the key and the value stored in first/second of the pair.

  // Type alias for iterator type. It is sufficient to use the Iterator
  // from BinarySearchTree<Pair_type> since it will yield elements of Pair_type
  // in the appropriate order for the Map.
  using Iterator = typename BinarySearchTree<Pair_type, PairComp>::Iterator;

  // You should add in a default constructor, destructor, copy
  // constructor, and overloaded assignment operator, if appropriate.
  // If these operations will work correctly without defining them,
  // you should omit them. A user of the class must be able to create,
  // copy, assign, and destroy Maps.

    Map():BST(BinarySearchTree<Pair_type,PairComp>()) {std::cout<<"Default Constructor declaration here."<<std::endl;}
    Map(const Map &other):BST(other.BST){std::cout<<"Customized Copy Constructor declaration here."<<std::endl;}
    Map & operator=(const Map &rhs){
      std::cout<<"Equal  Assignment Operator here."<<std::endl;
        if (this==&rhs){return *this;}
        BST = rhs.BST;
        return *this;
    }
    //~Map();
    
    
  // EFFECTS : Returns whether this Map is empty.
  bool empty() const;

  // EFFECTS : Returns the number of elements in this Map.
  // NOTE : size_t is an integral type from the STL
  size_t size() const;

  // EFFECTS : Searches this Map for an element with a key equivalent
  //           to k and returns an Iterator to the associated value if found,
  //           otherwise returns an end Iterator.
  //
  // HINT: Since Map is implemented using a BinarySearchTree that stores
  //       (key, value) pairs, you'll need to construct a dummy value
  //       using "Value_type()".
  Iterator find(const Key_type& k) const;

  // MODIFIES: this
  // EFFECTS : Returns a reference to the mapped value for the given
  //           key. If k matches the key of an element in the
  //           container, the function returns a reference to its
  //           mapped value. If k does not match the key of any
  //           element in the container, the function inserts a new
  //           element with that key and a value-initialized mapped
  //           value and returns a reference to the mapped value.
  //           Note: value-initialization for numeric types guarantees the
  //           value will be 0 (rather than memory junk).
  //
  // HINT:     In the case the key was not found, and you must insert a
  //           new element, use the expression {k, Value_type()} to create
  //           that element. This ensures the proper value-initialization is done.
  //
  // HINT: http://www.cplusplus.com/reference/map/map/operator[]/
  Value_type& operator[](const Key_type& k);

  // MODIFIES: this
  // EFFECTS : Inserts the given element into this Map if the given key
  //           is not already contained in the Map. If the key is
  //           already in the Map, returns an iterator to the
  //           corresponding existing element, along with the value
  //           false. Otherwise, inserts the given element and returns
  //           an iterator to the newly inserted element, along with
  //           the value true.
  std::pair<Iterator, bool> insert(const Pair_type &val);

  // EFFECTS : Returns an iterator to the first key-value pair in this Map.
  Iterator begin() const;

  // EFFECTS : Returns an iterator to "past-the-end".
  Iterator end() const;

private:
    BinarySearchTree<Pair_type, PairComp> BST;
  // Add a BinarySearchTree private member HERE.
};

// You may implement member functions below using an "out-of-line" definition
// or you may simply define them "in-line" in the class definition above.
// If you choose to define them "out-of-line", here is an example.
// (Note that we're using K, V, and C as shorthands for Key_type,
// Value_type, and Key_compare, respectively - the compiler doesn't
// mind, and will just match them up by position.)
//    template <typename K, typename V, typename C>
//    typename Map<K, V, C>::Iterator Map<K, V, C>::begin() const {
//      // YOUR IMPLEMENTATION GOES HERE
//    }
template <typename Key_type, typename Value_type,typename Key_compare>
bool Map<Key_type,Value_type,Key_compare>::empty() const{
    if (BST.empty()){return true;}
    return false;
}
template <typename Key_type, typename Value_type,typename Key_compare>
size_t Map<Key_type,Value_type,Key_compare>::size() const{
    return BST.size();
}



template <typename Key_type, typename Value_type,typename Key_compare>
typename Map<Key_type,Value_type,Key_compare>::Iterator Map<Key_type,Value_type,Key_compare>::begin() const{
  return BST.begin();
}

template <typename Key_type, typename Value_type,typename Key_compare>
typename Map<Key_type,Value_type,Key_compare>::Iterator Map<Key_type,Value_type,Key_compare>::end() const{
    return BST.end();
}

template <typename Key_type, typename Value_type,typename Key_compare>
typename Map<Key_type,Value_type,Key_compare>::Iterator Map<Key_type,Value_type,Key_compare>::find(const Key_type &k) const{
 Pair_type tmp;
 tmp.first = k;
 tmp.second = Value_type();
 return BST.find(tmp);
}

template <typename Key_type, typename Value_type,typename Key_compare>
Value_type & Map<Key_type,Value_type,Key_compare>::operator[](const Key_type &k){
  Pair_type tmp;
  tmp.first = k;
  tmp.second = Value_type();
  Iterator it = BST.find(tmp);
  if (it==end()){ return (*BST.insert({k,Value_type()})).second;}
  else {return (*it).second; }
}

template <typename Key_type, typename Value_type,typename Key_compare>
 std::pair< typename Map<Key_type,Value_type,Key_compare>::Iterator, bool > Map<Key_type,Value_type,Key_compare>::insert(const Pair_type &val) {
     if (find(val.first)==end()){return {BST.insert(val),true};}
  else return {find(val.first),false};

  }



#endif // DO NOT REMOVE!!!
