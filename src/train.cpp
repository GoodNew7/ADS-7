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
    first = newCar;
  }
}

int Train::getLength() {
  if (!first) return 0;
  if (first->next == first) return 1;

  countOp = 0;
  Car* current = first;
  unsigned int countCar = 1;

  if (!current->light) {
    current->light = true;
  }

  current = current->next;
  countOp += 2;

  while (!current->light) {
    current = current->next;
    countOp += 2;
    countCar++;
  }

  current->light = false;

  if (!first->light) {
    return countCar;
  }

  while (true) {
    current = first;
    countCar = 1;

    if (!current->light) {
      current->light = true;
    }

    current = current->next;
    countOp += 2;

    while (!current->light) {
      current = current->next;
      countOp += 2;
      countCar++;
    }

    current->light = false;

    if (!first->light) {
      return countCar;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}

Train::~Train() {
  if (!first) return;

  if (first->next == first) {
    delete first;
    first = nullptr;
    return;
  }

  Car* current = first->next;
  while (current != first) {
    Car* temp = current;
    current = current->next;
    delete temp;
  }

  delete first;
  first = nullptr;
}
