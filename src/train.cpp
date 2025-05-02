// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  if (!first) {
    first = new Car{light, nullptr, nullptr};
    return;
  }
  if (!first->next) {
    Car* car = new Car{light, nullptr, nullptr};
    first->next = car;
    first->prev = car;
    car->next = first;
    car->prev = first;
    return;
  }
  Car* car = new Car{light, nullptr, nullptr};
  Car* last = first->prev;
  last->next = car;
  car->prev = last;
  car->next = first;
  first->prev = car;
}

int Train::getOpCount() {
  return countOp;
}

int Train::getLength() {
  countOp = 0;
  Car* cur = first;
  int len = 1;
  while (true) {
    cur = first;
    len = 1;
    if (!cur->light)
      cur->light = true;
    cur = cur->prev;
    countOp++;
    while (!cur->light) {
      cur = cur->prev;
      countOp++;
      len++;
    }
    cur->light = false;
    if (!first->light)
      return len;
  }
}

Train::~Train() {
  if (!first)
    return;
  if (!first->next) {
    delete first;
    first = nullptr;
    return;
  }
  Car* cur = first->next;
  while (cur != first) {
    Car* nxt = cur->next;
    delete cur;
    cur = nxt;
  }
  delete first;
  first = nullptr;
}
