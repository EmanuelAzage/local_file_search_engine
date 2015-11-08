// templated msort.h 
//requires a functor for T

#ifndef MSORT_H
#define MSORT_H

#include "lib/webpage.h"
#include <vector>
#include <iostream>


template <class T, class Comparator>
void useMergeSort (std::vector<T>& myArray, Comparator& comp);

template <class T, class Comparator>
void mergeSort(std::vector<T>& a, int l, int r, Comparator& comp);

template <class T, class Comparator>
void merge(std::vector<T>& a, int l, int r, int m, Comparator& comp);

template <class T, class Comparator>
void useMergeSort (std::vector<T>& myArray, Comparator& comp){
	mergeSort(myArray, 0, myArray.size()-1, comp);
}

template <class T, class Comparator>
void mergeSort(std::vector<T>& a, int l, int r, Comparator& comp){
	if(l<r){
		int m = (l + r)/2;
		mergeSort(a, l, m, comp);
		mergeSort(a, m+1, r, comp);
		merge(a, l, r, m, comp);
	}
}

template <class T, class Comparator>
void merge(std::vector<T>& a, int l, int r, int m, Comparator& comp){
	std::vector<T> temp(r+1-l);// initialize empty vector of string of size r=+1-l
  	// trace through the two subarrays, copying into a temporary one
  	int i = l, j = m+1, k = 0;
  	while (i <= m || j <= r) // at least one subarray contains another element
       {
        if(i <= m && (j > r || comp(a[i], a[j]) )){// next smallest element in left subarray
        	temp[k] = a[i]; 
        	i++; 
        	k++; 
        }
        else{// next smallest element in right subarray 
        	temp[k] = a[j]; 
        	j++;
        	k++; 
        }        
   	}
  	// now copy over the merged array into the original
  	for (k = 0; k < r+1-l; k ++){
		  a[k+l] = temp[k];
    }
}

#endif