// File: ChainHashTable.cpp
// Author: Anthony Littlefield
// CMSC 341 Spring 2018 Project 5
// Implementation of ChainHashTable

#include "ChainHashTable.h"
#ifndef CHAINHASHTABLE_C
#define CHAINHASHTABLE_C

template <typename T>
ChainHashTable<T>::ChainHashTable(unsigned int (*hashFunc)(const T&), int n){
	m_size = 0;
	m_capacity = n;
	m_table = new std::list<T>[m_capacity];
	this->hashFunc = hashFunc;
}

template <typename T>
ChainHashTable<T>::~ChainHashTable(){
	delete [] m_table;
}

template <typename T>
ChainHashTable<T>::ChainHashTable (ChainHashTable& other){
	m_size = other.m_size;
	m_capacity = other.m_size;
	m_table = new std::list<T>[m_capacity];
	for(int i = 0;i < m_capacity;i++){
		for(typename std::list<T>::iterator j = other.m_table[i].begin();j != other.m_table[i].end();++j){
			m_table[i].push_back(*j);
		}
	}
	this->hashFunc = other.hashFunc;
}

template <typename T>
const ChainHashTable<T>& ChainHashTable<T>::operator= (ChainHashTable& rhs){
	delete [] m_table;
	m_size = rhs.m_size;
	m_capacity = rhs.m_size;
	m_table = new std::list<T>[m_capacity];
	for(int i = 0;i < m_capacity;i++){
		for(typename std::list<T>::iterator j = rhs.m_table[i].begin();j != rhs.m_table[i].end();++j){
			m_table[i].push_back(*j);
		}
	}
	this->hashFunc = rhs.hashFunc;
}

template <typename T>
bool ChainHashTable<T>::insert(const T &data){
	int place = this->hashFunc(data) % m_capacity;
	//Check for duplicate
	for(typename std::list<T>::iterator j = m_table[place].begin();j != m_table[place].end();++j){
		if(*j == data){
			return false;
		}
	}
	m_table[place].push_front(data);
	m_size++;
	return true;
}

template <typename T>
bool ChainHashTable<T>::find(const T &data){
	int pos = this->hashFunc(data); // Find place to traverse
	pos = pos % m_capacity;
	//Traverse table
	for(typename std::list<T>::iterator j = m_table[pos].begin();j != m_table[pos].end();++j){
		if(*j == data){
			return true;
		}
	}
	return false;
}

template <typename T>
T ChainHashTable<T>::remove(const T &data, bool &found){
	int pos = this->hashFunc(data) % m_capacity;	
	for(typename std::list<T>::iterator j = m_table[pos].begin();j != m_table[pos].end();++j){
		if(*j == data){
			found = true;
			m_table[pos].erase(j);
      			m_size--;
			return data;
		}
	}
	found = false;
	return data;
}

template <typename T>
void ChainHashTable<T>::dump(){
	for (int i = 0; i < m_capacity;++i)
   {
		std::cout << "[" << i << "]: ";
		//Check if empty
		if(!m_table[i].empty()){
			for(typename std::list<T>::iterator j = m_table[i].begin();j != m_table[i].end();++j){
				std::cout << *j << ", ";
			}
			std::cout << "\n";
			} else {
				std::cout << "\n";
			}
   }
   std::cout << "Total items: " << m_size << std::endl;
}

template <typename T>
int ChainHashTable<T>::at(int index, std::vector<T> &contents){
	if(index >= 0 && index < m_capacity){
		int sum = 0;
		for(typename std::list<T>::iterator j = m_table[index].begin();j != m_table[index].end();++j){
			contents.push_back(*j);
			sum++;
		}
		return sum;
	}
		throw std::out_of_range("Pos out of range");
}

#endif
