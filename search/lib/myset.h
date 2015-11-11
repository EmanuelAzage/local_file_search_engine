#ifndef MYSET_H
#define MYSET_H

#include <set> 


// avoid circular reference
//class WebPage;

template <class T>
class MySet : public std::set<T>
{
public:
  MySet();
  MySet<T> set_intersection(const MySet<T>& other);
  MySet<T> set_union(const MySet<T>& other);
};

template <class T>
MySet<T>::MySet() : std::set<T>() {}

//returns a set containing all the elements that exist in both sets
template <class T>
MySet<T> MySet<T>::set_intersection(const MySet<T>& other) {

	MySet<T> set_intersect;

	//for each element in this set, if the element is in the other set, insert 
	//the element into our insertion set
	typename std::set<T>::iterator it;
    for(it = this->begin(); it != this->end(); ++it) {
    	if(other.count(*it)){
    		set_intersect.insert(*it);
    	}
    }

    return set_intersect;
}

// Returns a set of all the elements from each set
template <class T>
MySet<T> MySet<T>::set_union(const MySet<T>& other) {
	
	MySet<T> set_union;

	// add all the elements from this set to the union set
	typename std::set<T>::iterator it;
    for(it = this->begin(); it != this->end(); ++it) {
    	set_union.insert(*it);
    }

    // add all the elements of other set to the union set
    for(it = other.begin(); it != other.end(); ++it) {
    	set_union.insert(*it);
    }

    return set_union;
}


#endif