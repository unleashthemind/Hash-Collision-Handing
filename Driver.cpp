/****************************************************************
 *
 * Driver1.cpp
 *
 * Tests Hashing techniques
 *
 ****************************************************************/

#include "ProbeHashTable.h"
#include "ChainHashTable.h"
#include "getCurrentCPU.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "words.h"

using namespace std;

struct cStr341 {
   const char *m_str;
   bool operator!=(const cStr341 &other) { 
      return strcmp(m_str, other.m_str); }
   bool operator==(const cStr341 &other) { 
      return !(*this != other); }

   friend ostream& operator<<(ostream& sout, const cStr341& data) {
      sout << data.m_str;
      return sout;
   }
};

unsigned int myHashFunction(const cStr341 &data) {
   const unsigned int hCoeff = 33 ;  // Suggested as good value in text
   unsigned int hCode = 0;

   for (const char *cp = data.m_str; *cp != '\0'; cp++) {
      hCode = hCode * hCoeff + *cp;
   }
   return hCode;
}

unsigned int myHashFunction(const int &data) {
   return (unsigned int) data * 149 + 47;
}

unsigned int myBadHashFunction(const int &data) {
   return (unsigned int) data;
}

void test1();
void test2();
void test3();

int main(int argc, char **argv) {
   test1();
   test2();
   test3();
   return 0;
	 
}

void test1() {
   int rm_data;
   bool found;
   clock_t startCPU, endCPU;
  
  
  
   ChainHashTable<int> chainHT(&myHashFunction);
   cout << "============================================================\n"
      << "= Initial chained hash table\n"
      << "============================================================"
      << endl;
   chainHT.dump();  // Should show empty table
    
   startCPU = getCurrentCPU();
   for (int i = 0; i < 1000; i++) {
      if (!chainHT.insert(i)) {
         cout << "insert(" << i << ") failed!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After 1000 insertions\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
   chainHT.dump();

   ProbeHashTable<int> probeHT(&myHashFunction);
   cout << "============================================================\n"
      << "= Initial probe hash table\n"
      << "============================================================"
      << endl;
   probeHT.dump();
   startCPU = getCurrentCPU();
   for (int i = 0; i < 2020; i += 20) {
      if (!probeHT.insert(i)) {
         cout << "insert(" << i << ") failed!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After 101 insertions (should see perfect hash)\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
   probeHT.dump();

   startCPU = getCurrentCPU();
   for (int i = 0; i < 2020; i += 20) {
      if (!probeHT.find(i)) {
         cout << "find(" << i << ") failed!" << endl;
      }
      rm_data = probeHT.remove(i, found);
      if (!found) {
         cout << "remove(" << i << ")--not found!" << endl;
      }
      else if (rm_data != i) {
         cout << "remove(" << i << ")--data does not match!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After 101 finds/removes (every bucket should be DELETED)\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
   probeHT.dump();

   startCPU = getCurrentCPU();
   for (int i = 0; i < 101; i++) {
      if (!probeHT.insert(rand())) {
         cout << "insert(" << i << ") failed!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After 101 random insertions\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
   probeHT.dump();

   ProbeHashTable<int> probeHT2(&myBadHashFunction, 100);
   for (int i = 0; i < 2000; i += 20) {
      if (!probeHT2.insert(i)) {
         cout << "insert(" << i << ") failed!" << endl;
      }
   }
   cout << "============================================================\n"
      << "= After 100 insertions w/bad hash table size and func\n"
      << "  (Should see lots of collisions)\n"
      << "============================================================"
      << endl;
   probeHT2.dump();
	 
}

void test2(){
   cStr341 data, rm_data;
   bool found;
   clock_t startCPU, endCPU;

   ChainHashTable<cStr341> chainHT(&myHashFunction);
    
   startCPU = getCurrentCPU();
   for (int i = 0; i < 80; i++) {
      data.m_str = words[i];
      if (!chainHT.insert(data)) {
         cout << "insert(" << data << ") failed!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After " << numWords << " insertions\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
    //chainHT.dump();

   ProbeHashTable<cStr341> probeHT2(&myHashFunction);
   ProbeHashTable<cStr341> probeHT(&myHashFunction, 70001);

   startCPU = getCurrentCPU();
   for (int i = 0; i < 80; i++) {
      data.m_str = words[i];
      if (!probeHT2.insert(data)) {
         cout << "insert(" << data << ") failed!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "[ProbeHashTable: Simple test]\n"
      << "= After " << 80 << " insertions\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
   probeHT2.dump();

   startCPU = getCurrentCPU();
   for (int i = 0; i < 80; i++) {
      data.m_str = words[i];
      if (!probeHT2.find(data)) {
         cout << "find(" << data << ") failed!" << endl;
      }
      rm_data = probeHT2.remove(data, found);
      if (!found) {
         cout << "remove(" << data << ")--not found!" << endl;
      }
      else if (rm_data != data) {
         cout << "remove(" << data << ")--data does not match!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After " << numWords << " finds/removes\n"
      << "  (~80% of buckets should be DELETED, rest EMPTY)\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
   probeHT2.dump();

    //
    // Now, big tests  (dumps turned off--too long)
    //
   startCPU = getCurrentCPU();
   for (int i = 0; i < numWords; i++) {
      data.m_str = words[i];
      if (!probeHT.insert(data)) {
         cout << "insert(" << data << ") failed!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "[ProbeHashTable: Full test]\n"
      << "= After " << numWords << " insertions\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
    //probeHT.dump();

   startCPU = getCurrentCPU();
   for (int i = 0; i < numWords; i++) {
      data.m_str = words[i];
      if (!probeHT.find(data)) {
         cout << "find(" << data << ") failed!" << endl;
      }
      rm_data = probeHT.remove(data, found);
      if (!found) {
         cout << "remove(" << data << ")--not found!" << endl;
      }
      else if (rm_data != data) {
         cout << "remove(" << data << ")--data does not match!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After " << numWords << " finds/removes\n"
      << "  (~80% of buckets should be DELETED, rest EMPTY)\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
    //probeHT.dump();

}

void test3(){
   int rm_data;
   bool found;
   clock_t startCPU, endCPU;

   ChainHashTable<int> chainHT(&myHashFunction);
   startCPU = getCurrentCPU();
   for (int i = 0; i < 100000; i++) {
      if (!chainHT.insert(i)) {
         cout << "insert(" << i << ") failed!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After 100000 insertions\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
    //chainHT.dump();  // uncomment for debugging, but will print out tons!

   ProbeHashTable<int> probeHT(&myBadHashFunction, 100000);
   startCPU = getCurrentCPU();
   for (int i = 0; i < 2000000; i += 20) {
      if (!probeHT.insert(i)) {
         cout << "insert(" << i << ") failed!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After 100000 insertions w/bad hash table size and func\n"
      << "  (Should see lots of collisions)\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
    //probeHT.dump();

   startCPU = getCurrentCPU();
   for (int i = 0; i < 2000000; i += 20) {
      if (!probeHT.find(i)) {
         cout << "find(" << i << ") failed!" << endl;
      }
      rm_data = probeHT.remove(i, found);
      if (!found) {
         cout << "remove(" << i << ")--not found!" << endl;
      }
      else if (rm_data != i) {
         cout << "remove(" << i << ")--data does not match!" << endl;
      }
   }
   endCPU = getCurrentCPU();
   cout << "============================================================\n"
      << "= After 100000 finds/removes (should be empty)\n"
      << "(" << (endCPU - startCPU) << " CPU ticks)\n"
      << "============================================================"
      << endl;
    //probeHT.dump();

}