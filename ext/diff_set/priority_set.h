#ifndef PRIORITY_SET_H
#define PRIORITY_SET_H

#include "rice/Object.hpp"
#include "rice/Array.hpp"
#include "rice/Hash.hpp"
using namespace Rice;

#include <boost/random.hpp>
#include <boost/heap/fibonacci_heap.hpp>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>

#include <sys/time.h>
#include <limits>

#include "random_set.h"

class PrioritySet {
public:
  struct element {
    int id;
    double priority;
    double random;
    bool enabled;
    
    element(int id, double priority, double random) {
      enabled = true;
      this->id = id;
      this->priority = priority;
      this->random = random;
    }
  };
  
  struct comparator {
    bool operator()(const element &a, const element &b) const {
      return (a.priority < b.priority) || (a.priority == b.priority && a.random < b.random);
    }
  };
  
  PrioritySet();
  void add(int id, double priority = 0.0);
  void remove(int id);
  Array sample(int limit);
  bool includes(int id);
  Array subtract(RandomSet &other, size_t limit);
  Array to_a();
  Hash to_h();
  size_t size();
protected:
  typedef boost::heap::fibonacci_heap<element, boost::heap::compare<comparator> > fibonacci_heap;
  typedef fibonacci_heap::handle_type element_handle;
  fibonacci_heap heap;
  boost::unordered_map<int, element_handle > element_handles;
  boost::unordered_set<int> element_set;
  boost::random::mt19937 rng;
};

#endif
