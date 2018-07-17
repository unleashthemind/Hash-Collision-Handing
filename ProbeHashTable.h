// File: ProbeHashTable.h
// Author: Anthony Littlefield
// CMSC 341 Spring 2018 Project 5
// 
#include <vector>
#include <iostream>
#ifndef PROBEHASHTABLE_H
#define PROBEHASHTABLE_H
#include "HashTable.h"
#include <stdexcept>

const int EMPTY = 0;
const int DELETED = -1;
const int FILLED = 1;

template <typename T>
class ProbeHashTable : public HashTable<T> { 
public:
   ProbeHashTable(unsigned int (*hashFunc)(const T&), int n = 101);
   virtual ~ProbeHashTable();
   ProbeHashTable (ProbeHashTable& other);
   const ProbeHashTable& operator= (ProbeHashTable& rhs);
   virtual bool insert(const T &data);
   virtual bool find(const T &data);
   virtual T remove(const T &data, bool &found);
   virtual void dump();
   virtual int at(int index, std::vector<T> &contents);
	
   class HashTableEntry{
   public:
      HashTableEntry(){
          m_flag = EMPTY;
	  m_orig_pos = 0;
      }
		  unsigned int m_orig_pos;
      int m_flag;
      T m_data;
   };
   friend std::ostream &operator<<(std::ostream&, const HashTableEntry& obj){
   	if(obj.m_flag == DELETED){
        	std::cout << "DELETED" << std::endl;
        } 
      	else if (obj.m_flag == EMPTY){
        	std::cout << "EMPTY" << std::endl;			
      	} 
      	else {
        	std::cout << obj.m_data << " (" << obj.m_orig_pos << ")" << std::endl;
      	}
   }
	
private:
   HashTableEntry* m_table;
   int m_size;
   int m_capacity;
};

#include "ProbeHashTable.cpp"
#endif
