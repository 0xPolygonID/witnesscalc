#ifndef CIRCOM_CALCWIT_H
#define CIRCOM_CALCWIT_H

#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <memory>

#include "circom.hpp"
#include "fr.hpp"

#define NMUTEXES 12 //512

namespace CIRCUIT_NAME {

u64 fnv1a(std::string s);

class Circom_CalcWit {

  bool *inputSignalAssigned;
    unsigned int inputSignalAssignedCounter;

  Circom_Circuit *circuit;

public:

  FrElement *signalValues;
  Circom_Component* componentMemory;
  FrElement* circuitConstants; 
  std::map<u32,IODefPair> templateInsId2IOSignalInfo; 
  std::string* listOfTemplateMessages; 

  // parallelism
  std::mutex numThreadMutex;
  std::condition_variable ntcvs;
    unsigned int numThread;

    unsigned int maxThread;

  // Functions called by the circuit
  Circom_CalcWit(Circom_Circuit *aCircuit, unsigned int numTh = NMUTEXES);
  ~Circom_CalcWit();

  // Public functions
  void setInputSignal(u64 h, unsigned int i, FrElement &val);
  
  u64 getInputSignalSize(u64 h);

  inline unsigned int getRemaingInputsToBeSet() {
    return inputSignalAssignedCounter;
  }
  
  inline void getWitness(unsigned int idx, PFrElement val) {
    Fr_copy(val, &signalValues[circuit->witness2SignalList[idx]]);
  }

  std::string getTrace(u64 id_cmp);

  std::string generate_position_array(unsigned int* dimensions, unsigned int size_dimensions, unsigned int index);

private:
  
  unsigned int getInputSignalHashPosition(u64 h);

};

typedef void (*Circom_TemplateFunction)(unsigned int __cIdx, Circom_CalcWit* __ctx); 

} // namespace

#endif // CIRCOM_CALCWIT_H
