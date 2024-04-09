#ifndef __CIRCOM_H
#define __CIRCOM_H

#include <map>
#include <gmp.h>
#include <mutex>
#include <condition_variable>
#include <thread>

#include "fr.hpp"

namespace CIRCUIT_NAME {

typedef unsigned long long u64;
typedef uint32_t u32;
typedef uint8_t u8;

//only for the main inputs
struct __attribute__((__packed__)) HashSignalInfo {
    u64 hash;
    u64 signalid; 
    u64 signalsize; 
};

struct IODef { 
    u32 offset;
    u32 len;
    u32 *lengths = nullptr;
};

struct IODefPair { 
    u32 len;
    IODef* defs = nullptr;
};

struct Circom_Circuit {
  //  const char *P;
  HashSignalInfo* InputHashMap = nullptr;
  u64* witness2SignalList = nullptr;
  FrElement* circuitConstants = nullptr;  
  std::map<u32,IODefPair> templateInsId2IOSignalInfo;

  ~Circom_Circuit() {

    delete[] InputHashMap;

    delete[] witness2SignalList;

    delete[] circuitConstants;

    for (auto &pair : templateInsId2IOSignalInfo) {
      auto *defs = pair.second.defs;
      if (defs != nullptr) {
        delete[] defs->lengths;
        free(defs);
      }
    }

  }
};


struct Circom_Component {
  u32 templateId;
  u64 signalStart;
  u32 inputCounter;
  std::string templateName;
  std::string componentName;
  u64 idFather; 
  u32* subcomponents = nullptr;
  bool* subcomponentsParallel = nullptr;
  bool *outputIsSet = nullptr;  //one for each output
  std::mutex *mutexes = nullptr;  //one for each output
  std::condition_variable *cvs = nullptr;
  std::thread *sbct = nullptr; //subcomponent threads

  Circom_Component()
	: subcomponents(0), subcomponentsParallel(0), outputIsSet(0), mutexes(0), cvs(0), sbct(0)
  {}

};

/*
For every template instantiation create two functions:
- name_create
- name_run

//PFrElement: pointer to FrElement

Every name_run or circom_function has:
=====================================

//array of PFrElements for auxiliars in expression computation (known size);
PFrElements expaux[];

//array of PFrElements for local vars (known size)
PFrElements lvar[];

*/

uint get_main_input_signal_start();
uint get_main_input_signal_no();
uint get_total_signal_no();
uint get_number_of_components();
uint get_size_of_input_hashmap();
uint get_size_of_witness();
uint get_size_of_constants();
uint get_size_of_io_map();

} //namespace
#endif  // __CIRCOM_H
