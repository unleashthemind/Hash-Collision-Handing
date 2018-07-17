// File: ChainHashTable.h
// Author: Anthony Littlefield
// CMSC 341 Spring 2018 Project 5
// 

#include <vector>
#include <list>
#ifndef CHAINHASHTABLE_H
#define CHAINHASHTABLE_H
#include <stdexcept>

template <typename T>
class ChainHashTable : public HashTable<T> {
public:
	ChainHashTable(unsigned int (*hashFunc)(const T&), int n=101);
	virtual ~ChainHashTable();
	ChainHashTable (ChainHashTable& other);
	const ChainHashTable& operator= (ChainHashTable& rhs);
	virtual bool insert(const T &data);
	virtual bool find(const T &data);
	virtual T remove(const T &data, bool &found);
	virtual void dump();
   	virtual int at(int index, std::vector<T> &contents);
private:
	std::list<T>* m_table;
	int m_size;
	int m_capacity;
};


#include "ChainHashTable.cpp"
#endif
