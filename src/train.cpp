// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  Car* car = new Car{light, nullptr, nullptr};
  if (!first) {
    first = car;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = car;
    car->prev = last;
    car->next = first;
    first->prev = car;
  }
}

int Train::getOpCount() {
  return countOp;
}

int Train::getLength() {
  if (!first) {
    return 0;
  }
  countOp = 0;
  Car* cur = first;
  int len = 0;
  do {
    if (!cur->light) {
      cur->light = true;
      len = 1;
      Car* start = cur;
      cur = cur->prev;
      countOp++;
      while (!cur->light && cur != start) {
        cur = cur->prev;
        countOp++;
        len++;
      }
      cur->light = false;
      if (cur == first && !first->light) {
        return len;
      }
    } else {
      cur = cur->prev;
      countOp++;
    }
  } while (cur != first);
  return len;
}

Train::~Train() {
  if (!first) {
    return;
  }
  Car* last = first->prev;
  last->next = nullptr;
  first->prev = nullptr;
  Car* cur = first;
  while (cur) {
    Car* next = cur->next;
    delete cur;
    cur = next;
  }
  first = nullptr;
}
