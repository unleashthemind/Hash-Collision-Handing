// File: ProbeHashTable.cpp
// Author: Anthony Littlefield
// CMSC 341 Spring 2018 Project 5
// Implementation of ProbeHashTable

#include "ProbeHashTable.h"
#ifndef PROBEHASHTABLE_C
#define PROBEHASHTABLE_C

template <typename T>
ProbeHashTable<T>::ProbeHashTable(unsigned int (*hashFunc)(const T&), int n){
	m_size = 0;
	m_capacity = n;
	m_table = new HashTableEntry[n];
	this->hashFunc = hashFunc;
	
}

template <typename T>
ProbeHashTable<T>::~ProbeHashTable(){
	delete [] m_table;
}

template <typename T>
ProbeHashTable<T>::ProbeHashTable (ProbeHashTable& other){
	m_size = other.m_size;
	m_capacity = other.m_size;
	m_table = new HashTableEntry[m_size];
	for(int i = 0; i < m_capacity;i++){
		m_table[i].m_flag = other.m_table[i].m_flag;
		m_table[i].m_data = other.m_table[i].m_data;
		m_table[i].m_orig_pos = other.m_table[i].m_orig_pos;
	}
	this->hashFunc = other.hashFunc;
}

template <typename T>
const ProbeHashTable<T>& ProbeHashTable<T>::operator= (ProbeHashTable& rhs){
	delete [] m_table;
	m_size = rhs.m_size;
	m_capacity = rhs.m_size;
	m_table = new HashTableEntry[m_size];
	for(int i = 0; i < m_capacity;i++){
		m_table[i].m_flag = rhs.m_table[i].m_flag;
		m_table[i].m_data = rhs.m_table[i].m_data;
		m_table[i].m_orig_pos = rhs.m_table[i].m_orig_pos;
	}
	this->hashFunc = rhs.hashFunc;
}

template <typename T>
bool ProbeHashTable<T>::insert(const T &data){
	if(m_size < m_capacity){
		unsigned int pos = this->hashFunc(data);
		unsigned int origPos = pos % m_capacity;
		for(int i = 0;i < m_capacity;i++){
			pos = pos % m_capacity;
			if(m_table[pos].m_flag == EMPTY || m_table[pos].m_flag == DELETED){
				m_table[pos].m_data = data;
				m_table[pos].m_flag = FILLED;
				m_size++;
				m_table[pos].m_orig_pos = origPos;
				return true;
				break;
			} else{
				if(m_table[pos].m_data == data){
					return false;
				}
			}
			pos++;
		}
	}
	throw std::out_of_range("Capacity met");
}

template <typename T>
bool ProbeHashTable<T>::find(const T &data){
	unsigned int pos = this->hashFunc(data);	
	for(int i = 0;i < m_capacity;i++){
		pos = pos % m_capacity;
		if(m_table[pos].m_flag == FILLED){
			if(m_table[pos].m_data == data){
				return true;
			}
		}
		pos++;
	}
	return false;
}

template <typename T>
T ProbeHashTable<T>::remove(const T &data, bool &found){
	unsigned int pos = this->hashFunc(data);
	for(int i = 0;i < m_capacity;++i){
		pos = pos % m_capacity;
		if(m_table[pos].m_flag == FILLED && m_table[pos].m_data == data){
		   m_table[pos].m_flag = DELETED;
		   found = true;
		   m_size--;
		   return m_table[pos].m_data;
		}
		pos++;
	}
	found = false;
	return data;
}

template <typename T>
void ProbeHashTable<T>::dump(){
	for(int i = 0;i < m_capacity;i++){
		std::cout << "[" << i << "]: ";
		std::cout << m_table[i];
	}
   std::cout << "Total items: " << m_size << std::endl;
}

template <typename T>
int ProbeHashTable<T>::at(int index, std::vector<T> &contents){
	if(index >= 0 && index < m_capacity){
		if(m_table[index].m_flag == FILLED){
			contents.push_back(m_table[index].m_data);
			return 1;
		}
		return 0;
	}
	throw std::out_of_range("Pos out of range");
}

#endif