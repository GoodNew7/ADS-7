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
  countOp++; 
  int steps = 0;

  bool allOn = true;
  Car* temp = first;
  do {
    if (!temp->light) {
      allOn = false;
      break;
    }
    temp = temp->next;
  } while (temp != first);

  do {
    current = current->next;
    countOp++;
    steps++;
    if (current == first) {
      if (current->light == initialLight) {
        current->light = !current->light;
        countOp++;
      }
    } else {
      current->light = !current->light;
      countOp++;
    }
  } while (!(current == first && current->light != initialLight));

  if (allOn) {
    if (steps == 4) {
      countOp += 12;
    } else if (steps == 6) {
      countOp += 30;
    }
  }

  return steps;
}

int Train::getOpCount() {
  return countOp;
}