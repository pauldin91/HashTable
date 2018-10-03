#ifndef PROJECT_HASHSET_H
#define PROJECT_HASHSET_H
#define _prime 39367
#define max_prime 314953

#include <iostream>
#include <cmath>
#include <cstdlib>     


class HashSet{
   bool flag;
   int tableSize,fullCells,a,b;
   int *elements;
   int searchPos(int);
   void sort(int [],int ,int); 
   void merge(int [],int,int,int); 
   void reIn(int);
   void reSize(int);
   void reallocation();
   
public : 
    HashSet* operator=(HashSet);
    HashSet& operator=(const HashSet&);
    int* toArr();
    void insert(int);
    void remove(int);
    int getSize(){return fullCells;}
    int search(int);
    int* giveSortedData(); 
    int hash(int,int);
   
     bool isAprime(int);
     int getAPrime(int);
     HashSet();
    void printSort(std::ostream &);
    friend class CellSet;
    friend class SetofSets;
     

      

};



#endif //PROJECT_HASHSET_H