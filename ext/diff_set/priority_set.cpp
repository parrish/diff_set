#include "priority_set.h"

PrioritySet::PrioritySet() {
  timeval time;
  gettimeofday(&time, NULL);
  long millis = (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
  this->rng.seed((uint)millis);
}

void PrioritySet::add(int id, double priority) {
  if(includes(id)) {
    element_handle handle = this->element_handles[id];
    (*handle).priority = priority;
    this->heap.update(handle);
    return;
  }
  
  static boost::uniform_01<boost::random::mt19937> dist(this->rng);
  element_handle handle = this->heap.push(element(id, priority, dist()));
  this->element_handles.insert(std::make_pair<int, element_handle>(id, handle));
  this->element_set.insert(id);
}

void PrioritySet::remove(int id) {
  boost::unordered_set<int>::iterator set_it = this->element_set.find(id);
  
  if(set_it != this->element_set.end()) {
    this->element_set.erase(set_it);
    element_handle handle = this->element_handles[id];
    (*handle).priority = std::numeric_limits<int>::min();
    (*handle).enabled = false;
    this->heap.decrease(handle);
  }
}

Array PrioritySet::sample(int limit) {
  Array sampled;
  fibonacci_heap::ordered_iterator it;
  
  for(it = this->heap.ordered_begin(); it != this->heap.ordered_end(); it++) {
    if(it->enabled) {
      sampled.push(it->id);
      if(sampled.size() >= (size_t)limit) {
        break;
      }
    }
  }
  
  return sampled;
}

bool PrioritySet::includes(int id) {
  boost::unordered_set<int>::const_iterator it;
  it = this->element_set.find(id);
  return it != this->element_set.end();
}

Array PrioritySet::subtract(RandomSet &other, size_t limit) {
  Array diff;
  fibonacci_heap::ordered_iterator it;
  boost::unordered_set<int>::const_iterator in_other;
  
  for(it = this->heap.ordered_begin(); it != this->heap.ordered_end(); it++) {
    if(it->enabled && other.element_set.find(it->id) == other.element_set.end()) {
      diff.push(it->id);
      if(diff.size() >= limit) {
        break;
      }
    }
  }
  
  return diff;
}

Array PrioritySet::to_a() {
  Array array;
  fibonacci_heap::ordered_iterator it;
  for(it = this->heap.ordered_begin(); it != this->heap.ordered_end(); it++) {
    if(it->enabled) {
      array.push(it->id);
    }
  }
  return array;
}

Hash PrioritySet::to_h() {
  Hash hash;
  fibonacci_heap::ordered_iterator it;
  for(it = this->heap.ordered_begin(); it != this->heap.ordered_end(); it++) {
    if(it->enabled) {
      hash[it->id] = it->priority;
    }
  }
  return hash;
}

size_t PrioritySet::size() {
  return this->element_set.size();
}
