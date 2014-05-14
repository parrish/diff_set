#include "random_set.h"

RandomSet::RandomSet() {
  timeval time;
  gettimeofday(&time, NULL);
  long millis = (time.tv_sec * 1000.0) + (time.tv_usec / 1000.0);
  this->rng.seed((uint)millis);
}

void RandomSet::add(int element, double priority) {
  this->element_set.insert(element);
  this->elements.push_back(element);
}

void RandomSet::remove(int element) {
  boost::unordered_set<int>::iterator set_it = this->element_set.find(element);
  
  if(set_it != this->element_set.end()) {
    this->element_set.erase(set_it);
    
    std::vector<int>::iterator it = iterator_to(element);
    if(it != this->elements.end()) {
      this->elements.erase(it);
    }
  }
}

Array RandomSet::sample(int limit) {
  Array sampled;
  int swapIndex;
  int tmp;
  int upper_bound = (int)this->elements.size() - 1;
  boost::random::uniform_int_distribution<> dist;
  
  for(int i = 0; i < limit && i < (int)this->elements.size(); i++) {
    dist = boost::random::uniform_int_distribution<>(std::min(i + 1, upper_bound), upper_bound);
    swapIndex = dist(rng);
    tmp = this->elements[i];
    this->elements[i] = this->elements[swapIndex];
    this->elements[swapIndex] = tmp;
    sampled.push(this->elements[i]);
  }
  
  return sampled;
}

bool RandomSet::includes(int element) {
  boost::unordered_set<int>::const_iterator it;
  it = this->element_set.find(element);
  return it != this->element_set.end();
}

std::vector<int>::iterator RandomSet::iterator_to(int element) {
  std::vector<int>::iterator it;
  for(it = this->elements.begin(); it != this->elements.end(); it++) {
    if(element == *it) {
      return it;
    }
  }
  
  return this->elements.end();
}

Array RandomSet::subtract(RandomSet &other, size_t limit) {
  Array diff;
  int element;
  int swapIndex;
  int tmp;
  int upper_bound = (int)this->elements.size() - 1;
  
  boost::unordered_set<int>::const_iterator in_other;
  boost::random::uniform_int_distribution<> dist;
  
  for(int i = 0; i < (int)this->elements.size(); i++) {
    dist = boost::random::uniform_int_distribution<>(std::min(i + 1, upper_bound), upper_bound);
    swapIndex = dist(rng);
    tmp = this->elements[i];
    this->elements[i] = this->elements[swapIndex];
    this->elements[swapIndex] = tmp;
    
    element = this->elements[i];
    in_other = other.element_set.find(element);
    
    if(in_other == other.element_set.end()) {
      diff.push(element);
      if(diff.size() >= limit) {
        break;
      }
    }
  }
  
  return diff;
}

Array RandomSet::to_a() {
  Array array;
  
  std::vector<int>::iterator it;
  for(it = this->elements.begin(); it != this->elements.end(); it++) {
    array.push(*it);
  }
  
  return array;
}

size_t RandomSet::size() {
  return this->elements.size();
}
