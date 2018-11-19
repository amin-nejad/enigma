#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include "utils.h"
#include "components.h"
#include "errors.h"

using namespace std;

const int MAX_CHARACTERS = 512;

int main(int argc, char** argv){

  // Assign the maximum number of characters we are prepared to encrypt/decrypt
  char input[MAX_CHARACTERS];
  char output[MAX_CHARACTERS];

  // Check if correct number of command line arguments are provided
  if ((argc < 3)||(argc == 4)) {
    cerr << "ERROR! There are an insufficient number of parameters.\n" <<
      "There needs to be at least: 1 Plugboard and 1 Reflector.\n" <<
      "If you have specified 1 or more Rotors, you need to also provide " <<
      "a Rotor configuration file." << endl;
    return (INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }

  /* Assign the command line file arguments to variables holding those file names
     and calculate the number of rotors supplied */
  string plugboard_file = argv[1];
  string reflector_file = argv[2];
  string rotor_file;
  string rotor_config_file;
  int number_of_rotors = 0;
  
  if (argc > 4) {
    number_of_rotors = argc - 4;
    rotor_config_file = argv[argc-1];
  }
  
  /* Now we must check the input files to make sure they are the right files. We will 
     place the constraint that they must be from their respective component folders and
     then check them in the order they are specified as outlined.*/
  
  if (plugboard_file.substr(0,11)!="plugboards/" || plugboard_file.length() < 12){
    cerr << "ERROR! Plugboard file must be within \"plugboards\" folder" <<
      " and must be the first file specified." << endl; 
    return (ERROR_OPENING_CONFIGURATION_FILE);
  }
  if (reflector_file.substr(0,11)!="reflectors/" || reflector_file.length() < 12){
    cerr << "ERROR! Reflector file must be within \"reflectors\" folder" <<
      " and must be the second file specified." << endl; 
    return (ERROR_OPENING_CONFIGURATION_FILE);
  }
  for (int i = 0; i < number_of_rotors; i++){
    rotor_file = argv[3+i];
    if (rotor_file.substr(0,7)!="rotors/" || rotor_file.length() < 8){
      cerr << "ERROR! Error with rotor file " << i+1 <<
	".\n All Rotor files must be within \"rotors\" folder." << endl; 
      return (ERROR_OPENING_CONFIGURATION_FILE);
    }
  }
  if (argc > 4 &&
      (rotor_config_file.substr(0,7)!="rotors/" || rotor_config_file.length() < 8)){
    cerr << "ERROR! Rotor config file must be within \"rotors\" folder" <<
      " and must be the last file specified" << endl; 
    return (ERROR_OPENING_CONFIGURATION_FILE);
  }

  /* Now that we have confirmed we have been given the right files as command line 
     arguments, we must effectively "sanity check" the contents of these files. As outlined
     in the rubric, this must be done in the order that the files are given on the 
     command line and once an error is encountered, no more processing should be done
     on the remaining configuration files. */

  try {
    int error_number = checkPlugboard(plugboard_file);
    if (error_number != 0) {
      if (error_number == 4){
	cerr << "ERROR! There is a non-numeric character in " << plugboard_file << endl;
	return (NON_NUMERIC_CHARACTER); 
      } else if (error_number == 3){
	cerr << "ERROR! There is an invalid number in " << plugboard_file <<
	  ".\n All numbers must be between 0 and 25." << endl;
	return (INVALID_INDEX);
      } else if (error_number == 5){
	cerr << "ERROR! There is an invalid plug cable connection in " << plugboard_file <<
	  ".\n You cannot connect a contact to itself or to multiple other contacts." << endl;
	return (IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
      } else if (error_number == 6) {
	cerr << "ERROR! There are an odd number of parameters in " << plugboard_file <<".\n" <<
	  "There must be an even number of parameters with each pair representing a plug cable"
	     << endl;
	return (INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
      }
    }
    
    error_number = checkReflector(reflector_file);
    if (error_number != 0) {
      if (error_number == 4){
	cerr << "ERROR! There is a non-numeric character in " << reflector_file << endl;
	return (NON_NUMERIC_CHARACTER); 
      } else if (error_number == 3){
	cerr << "ERROR! There is an invalid number in " << reflector_file <<
	  ".\n All numbers must be between 0 and 25." << endl;
	return (INVALID_INDEX);
      } else if (error_number == 9){
	cerr << "ERROR! There is an invalid connection in " << reflector_file <<
	  ".\n You cannot map an input to itself or pair each index with more than one other."
	     << endl;
	return (INVALID_REFLECTOR_MAPPING);
      } else if (error_number == 10) {
	cerr << "ERROR! Wrong number of parameters in " << reflector_file <<".\n" <<
	  "There must be exactly 13 pairs of numbers." <<
	  endl;
	return (INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
      }
    }
    
    for (int i = 0; i < number_of_rotors; i++){
      rotor_file = argv[3+i];
      error_number = checkRotor(rotor_file);
      if (error_number != 0) {
	if (error_number == 4){
	  cerr << "ERROR! There is a non-numeric character in " << rotor_file << endl;
	  return (NON_NUMERIC_CHARACTER); 
	} else if (error_number == 3){
	  cerr << "ERROR! There is an invalid number in " << rotor_file <<
	    ".\n All numbers must be between 0 and 25." << endl;
	  return (INVALID_INDEX);
	} else if (error_number == 7){
	  cerr << "ERROR! There is an invalid number in " << rotor_file <<
	    ".\n Numbers cannot repeat and each number in 0-25 must occur once. \n " <<
	    "After this, one or more notches must be specified." << endl;
	  return (INVALID_ROTOR_MAPPING);
	}
      }
    }

    if (argc > 4) {
      error_number = checkRotorConfig(rotor_config_file, number_of_rotors);
      if (error_number != 0) {
	if (error_number == 4){
	  cerr << "ERROR! There is a non-numeric character in " << rotor_config_file
	       << endl;
	  return (NON_NUMERIC_CHARACTER); 
	} else if (error_number == 3){
	  cerr << "ERROR! There is an invalid number in " << rotor_config_file <<
	    ".\n All numbers must be between 0 and 25." << endl;
	  return (INVALID_INDEX);
	} else if (error_number == 8){
	  cerr << "ERROR! There is a problem with  " << rotor_config_file <<
	    ".\n The number of rotor starting positions must match the number of rotors."
	       << endl;
	  return (NO_ROTOR_STARTING_POSITION);
	}
      }
    }
    
  } catch (const exception &e) {
    cerr << e.what() << endl;
    return (ERROR_OPENING_CONFIGURATION_FILE);
  }

  /* Now that we have ensured the command line arguments we have been given are 
     good, we can proceed with initialising our plugboard, reflector and rotor 
     components.

     Since there are a variable number of rotors and we cannot constrain this 
     variable we must deal with assigning the rotors differently using dynamic 
     arrays */

  
  Plugboard plugboard;
  Reflector reflector;

  reflector.setArray(reflector_file);
  plugboard.setArray(plugboard_file);  

  typedef Rotor* rotor_ptr;
  rotor_ptr* rotors = new rotor_ptr[number_of_rotors];

  if (number_of_rotors > 0) {

    int* rotor_starting_positions = NULL;
    countIntegers(rotor_config_file, rotor_starting_positions);
    parseFile(rotor_config_file, rotor_starting_positions);
  
    for (int i = 0; i < number_of_rotors ; i++){
      rotor_file = argv[3 + i];
      rotors[i] = new Rotor; 
      rotors[i]->setArray(rotor_file, *(rotor_starting_positions + i));
    }
  }

  // Now we can finally load the input file and check for invalid input characters

  try {
    loadInput(input);
  } catch (const exception &e) {
    cerr << e.what() << endl;
    return (INVALID_INPUT_CHARACTER);
  }

  /* Finally do the actual cryptography!!!
  
   Now we will do the actual cryptography which forms the core of the enigma machine.
   Firstly, we convert the input text into integers corresponding to the letters of
   the alphabet. Then, one by one, we send them through the plugboard, the rotors, the
   reflector, back through the rotors in the other direction and then back through the
   plugboard to its final number. Lastly this number is converted back to a character
   and returned as an array of characters once the cryptography is complete */
 
  unsigned i = 0;

  while (input[i]!='\0'){

    char character;
    int char_number;

    character = input[i];
    char_number = static_cast<int>(character) - 'A';

    char_number = plugboard.usePlugCable(char_number);

    if (number_of_rotors > 0){

      /* Rotors are rotated BEFORE circuit is complete
	 Only rightmost rotor is rotated unless any of them are on a notch */
      rotors[number_of_rotors - 1]->rotateRotor();
      
      for (int j = number_of_rotors - 1 ; j > 0; j--){
	if (rotors[j]->checkNotch()){
	  rotors[j-1]->rotateRotor();
	}
      }
      
      // Pass input through each rotor R->L
      for (int j = (number_of_rotors - 1); j > -1; j--){
	char_number = rotors[j]->mapForwards(char_number);
      }

      // Pass through reflector
      char_number = reflector.doReflection(char_number);

      // Pass input through each rotor L->R
      for (int j = 0; j < number_of_rotors; j++){
      	char_number = rotors[j]->mapBackwards(char_number);
      }
      
      // If there are no rotors, only pass through reflector
    } else {
      char_number = reflector.doReflection(char_number);
    }
    
    char_number = plugboard.usePlugCable(char_number);

    character = static_cast<char>(char_number) + 'A';
    output[i] = character;

    if (i == (strlen(input)-1)){
      output[i+1] = '\0';
    }
    
    i++;
  } 

  // Export the encrypted output to 'output.txt'
  
  exportOutput(output);

  // Free up memory on the heap before exiting the program

  if (number_of_rotors > 0){
    for (int i=0; i < number_of_rotors; i++){
      delete rotors[i];
    }
  }

  delete [] rotors;
  
  return 0;
}
