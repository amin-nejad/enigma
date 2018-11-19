#include <string>
#include <iostream>
#include "components.h"
#include "utils.h"
#include "errors.h"

using namespace std;

const int SIZE_OF_ALPHABET = 26;

Rotor::Rotor(){

  rot_ptr = NULL;
  notch_ptr = NULL;
  number_of_notches = 0;
  offset_from_zero = 0;
}

Rotor::~Rotor(){

  if (!(rot_ptr == NULL)){
    delete [] rot_ptr;
  }
}

void Rotor::setArray(string &filename, int starting_position){

  offset_from_zero = starting_position;
  number_of_notches = countIntegers(filename, rot_ptr) - SIZE_OF_ALPHABET;
  notch_ptr = rot_ptr + SIZE_OF_ALPHABET;
  parseFile(filename, rot_ptr);
}

int Rotor::checkOffset(int offset){

  if (offset > 25){
    offset = offset % 26;
  } else if (offset < 0){
    offset = (offset % 26) + 26;
  }
  return offset;
}

void Rotor::rotateRotor(){

  offset_from_zero++;
  offset_from_zero = checkOffset(offset_from_zero);
}

bool Rotor::checkNotch(){

  for (int i = 0; i < number_of_notches; i++){
    if ( *(notch_ptr + i) == offset_from_zero){
      return true;
    }
  }
  return false;
}

int Rotor::mapForwards(int position){

  int temp_position;
  
  temp_position = checkOffset(position + offset_from_zero);
  position = *(rot_ptr + temp_position);
  position = checkOffset(position);

  return position;
}

int Rotor::mapBackwards(int position){

  int temp_position;

  temp_position = position;

  for (int i = 0; i < SIZE_OF_ALPHABET; i++){
    if ( *(rot_ptr + i) == temp_position){
      position = i - offset_from_zero;
    }
  }
  position = checkOffset(position);

  return position;
}


//////////////////////////////////////////////////////////////////////////////

Plugboard::Plugboard(){

  pb_ptr = NULL;
  pb_length = 0;
}

Plugboard::~Plugboard(){

  if (!(pb_ptr == NULL)){
    delete [] pb_ptr;
  }
}

void Plugboard::setArray(string &filename){
  
  pb_length = countIntegers(filename, pb_ptr);
  parseFile(filename, pb_ptr);
}

int Plugboard::usePlugCable(int position){

  for (int i=0; i < pb_length; i++){
    if (*(pb_ptr + i) == position){
      if (i % 2 == 0){
	position = *(pb_ptr + i + 1);
	return position;
      } else {
	position = *(pb_ptr + i - 1);
	return position;
      }
    }
  }
  return position;
}
  

//////////////////////////////////////////////////////////////////////////

Reflector::Reflector(){

  rf_ptr = NULL;
  rf_length = 0;
}

Reflector::~Reflector(){

  if (!(rf_ptr == NULL)){
    delete [] rf_ptr;
  }
}

void Reflector::setArray(string &filename){
  
  rf_length = countIntegers(filename, rf_ptr);
  parseFile(filename, rf_ptr);
}

int Reflector::doReflection(int position){

  for (int i=0; i < rf_length; i++){
    if (*(rf_ptr + i) == position){
      if (i % 2 == 0){
	position = *(rf_ptr + i + 1);
	return position;
      } else {
	position = *(rf_ptr + i - 1);
	return position;
      }
    }
  }
  return position;
}
