class Rotor {

 private:
  int* rot_ptr;
  int* notch_ptr;
  int number_of_notches;
  int offset_from_zero;
  
 public:
  // constructor to intitialise variables
  Rotor();

  // destructor to free up memory on the heap
  ~Rotor();

  // sets rotor array for each individual rotor
  void setArray(std::string &filename, int starting_position);

  // rotates rotor after each cycle
  void rotateRotor();

  // resets absolute frame of reference if it goes through 26
  int checkOffset(int offset);

  // checks if the rotor is currently at one of its notches
  bool checkNotch();

  // maps the input to its corresponding output on the rotor when input is coming R->L
  int mapForwards(int position);

  // maps the input to its corresponfing output on the rotor when input is coming L->R
  int mapBackwards(int position);
};

///////////////////////////////////////////////////////////////////////////////////////

class Plugboard {

 private:
  int* pb_ptr;
  int pb_length;
  
 public:
  // constructor to initialise variables
  Plugboard();

  // destructor to free up memory on the heap
  ~Plugboard();

  // sets array for plugboard
  void setArray(std::string &filename);

  /* uses plug cable if specified. Inputs number corresponding to input letter and outputs
     the corresponding switched number */
  int usePlugCable(int position);
};

/////////////////////////////////////////////////////////////////////////////////////

class Reflector {

 private:
  int* rf_ptr;
  int rf_length;
  
 public:
  // constructor to initialise variables
  Reflector();

  // destructor to free up memory on the heap
  ~Reflector();

  // sets array for reflector
  void setArray(std::string &filename);

  /* reflect number corresponding to input letter to it's corresponding output before it
     goes back through the array of rotors */
  int doReflection(int position);
};
