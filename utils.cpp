#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include "utils.h"
#include "errors.h"
#include "components.h"

using namespace std;

int checkPlugboard(string &filename){

  string input;
  int input_number;
  int count = 0;
  vector<int> number_array;
  
  char* c_filename = const_cast<char*>(filename.c_str());
  ifstream in_stream(c_filename);

  if(in_stream.fail()){
    throw runtime_error("ERROR! " + filename +
			" cannot be opened. Please provide another file.");
  }
  
  in_stream >> ws >> input;
  
  while(!in_stream.eof()){

    count++;
    
    for (char& character : input) {
      if (!isdigit(character)){
	return (NON_NUMERIC_CHARACTER);
      }
    }
    
    stringstream input_ss(input);
    input_ss >> input_number;
    if ((input_number < 0) || (input_number > 25)){
      return (INVALID_INDEX);
    }
    
    for (unsigned i=0; i < number_array.size(); i++) {
      if (number_array.at(i)==input_number) {
	return (IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
      }
    }
    
    number_array.push_back(input_number);
    in_stream >> ws >> input;
  }
  
  if (count % 2 != 0) {
    return (INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
  }
  
  return 0;
}

int checkReflector(string &filename){

  string input;
  int input_number;
  int count = 0;
  vector<int> number_array;
  
  char* c_filename = const_cast<char*>(filename.c_str());
  ifstream in_stream(c_filename);

  if(in_stream.fail()){
    throw runtime_error("ERROR! " + filename +
			" cannot be opened. Please provide another file.");
  }
  
  in_stream >> ws >> input;
  
  while(!in_stream.eof()){

    count++;
    
    for (char& character : input) {
      if (!isdigit(character)){
	return (NON_NUMERIC_CHARACTER);
      }
    }
    
    stringstream input_ss(input);
    input_ss >> input_number;
    if ((input_number < 0) || (input_number > 25)){
      return (INVALID_INDEX);
    }
    
    for (unsigned i=0; i < number_array.size(); i++) {
      if (number_array.at(i)==input_number) {
	return (INVALID_REFLECTOR_MAPPING);
      }
    }
    
    number_array.push_back(input_number);
    in_stream >> ws >> input;
  }
  
  if (count != 26) {
    return (INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }
  
  return 0;
}

int checkRotor(string &filename){

  string input;
  int input_number;
  int count = 0;
  vector<int> number_array;
  
  char* c_filename = const_cast<char*>(filename.c_str());
  ifstream in_stream(c_filename);

  if(in_stream.fail()){
    throw runtime_error("ERROR! " + filename +
			" cannot be opened. Please provide another file.");
  }
  
  in_stream >> ws >> input;

  /* The first 26 numbers must comprise of the numbers 0-25, each appearing once.
     The code below ensures this is the case by preventing any repeating numbers 
     After the first 26 numbers, one or more notches must be specified */
  while(!in_stream.eof()){

    count++;
    
    for (char& character : input) {
      if (!isdigit(character)){
	return (NON_NUMERIC_CHARACTER);
      }
    }
    
    stringstream input_ss(input);
    input_ss >> input_number;
    if ((input_number < 0) || (input_number > 25)){
      return (INVALID_INDEX);
    }
    
    for (unsigned i=0; i < number_array.size(); i++) {
      if (number_array.at(i)==input_number) {
	return (INVALID_ROTOR_MAPPING);
      }
    }
    
    number_array.push_back(input_number);
    
    // reset the vector array of numbers after first 26 numbers to allow them to repeat
    if (count == 26) {
      number_array.clear();
    }
    in_stream >> ws >> input;
  }

  // at least one notch must be specified
  if (count < 27) {
    return (INVALID_ROTOR_MAPPING);
  }
  
  return 0;
}

int checkRotorConfig(string &filename, int &number_of_rotors){
  
  string input;
  int input_number;
  int count = 0;
  
  char* c_filename = const_cast<char*>(filename.c_str());
  ifstream in_stream(c_filename);

  if(in_stream.fail()){
    throw runtime_error("ERROR! " + filename +
			" cannot be opened. Please provide another file.");
  }
  
  in_stream >> ws >> input;
  
  while(!in_stream.eof()){

    count++;
    
    for (char& character : input) {
      if (!isdigit(character)){
	return (NON_NUMERIC_CHARACTER);
      }
    }
    
    stringstream input_ss(input);
    input_ss >> input_number;
    if ((input_number < 0) || (input_number > 25)){
      return (INVALID_INDEX);
    }
    
    in_stream >> ws >> input;
  }
  
  if (count != number_of_rotors) {
    return (NO_ROTOR_STARTING_POSITION);
  }
  
  return 0;
}

void parseFile(string &filename, int* file_array) {

  int number;
  int i = 0;
  
  char* c_filename = const_cast<char*>(filename.c_str());
  ifstream in_stream(c_filename);

  in_stream >> number;

  while(!in_stream.eof()){
    *(file_array + i) = number;
    in_stream >> number;
    i++;
  }
}

int countIntegers(string &filename, int* &file_array) {

  int number;
  int count = 0;
  
  char* c_filename = const_cast<char*>(filename.c_str());
  ifstream in_stream(c_filename);

  in_stream >> number;

  while(!in_stream.eof()){
    count++;
    in_stream >> number;
  }

  file_array = new int[count];

  return count;
}
  

void loadInput(char* input) {

  char character;
  int i = 0;
  cin >> ws >> character;

  while(!cin.eof()){   
    if ((character <'A')||(character > 'Z')){
      throw logic_error("ERROR! All input characters must be ASCII uppercase letters.");
    }
    input[i] = character;
    i++;
    cin >> ws >> character;
  }
  input[i]='\0';
}

void exportOutput(char* output) {
  cout << output << endl;
}
