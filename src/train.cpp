// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};

  if (!first) {
    first = newCar;
    newCar->next = newCar;
    newCar->prev = newCar;
  } else {
    Car* last = first->prev;
    newCar->next = first;
    newCar->prev = last;
    first->prev = newCar;
    last->next = newCar;
  }
}

int Train::getLength() {
  if (!first) return 0;
  if (first->next == first) return 1;

  countOp = 0;
  Car* current = first;
  bool initialLight = current->light;
  current->light = !current->light;
  int steps = 0;

  do {
    current = current->next;
    countOp++;
    steps++;
    if (current == first) {
      if (current->light == initialLight) {
        current->light = !current->light;
      }
    } else {
      current->light = !current->light;
    }
  } while (!(current == first && current->light != initialLight));

  return steps;
}

int Train::getOpCount() {
  return countOp;
}