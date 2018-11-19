// Perform all the error checks on the plugboard file integer by integer
int checkPlugboard(std::string &filename);

// Perform all the error checks on the reflector file integer by integer
int checkReflector(std::string &filename);

// Perform all the error checks on all the rotor files (if any) integer by integer
int checkRotor(std::string &filename);

// Perform all the error checks on the rotor config file (if specified) integer by integer
int checkRotorConfig(std::string &filename, int &number_of_rotors);

/* Once all the error checks have been done, this function takes a component file, counts
   the number of integers in the file and then creates an array of the right size  */
int countIntegers(std::string &filename, int* &file_array);

/* This function parses the component file and returns an array populated with the integers
   present in the input file after having been given an array of the right size */
void parseFile(std::string &filename, int* file_array);

/* This function parses the text in the input.txt file and creates an array of characters
   removing whitespace in the process and throws an error if it encounters an invalid 
   character*/
void loadInput(char* input);

// This function simply outputs the encrypted final text
void exportOutput (char* output);
