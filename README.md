# enigma
C++ Coursework 2

This coursework provides an implementation for an enigma machine. 

The executable can be called as follows:
```
./enigma plugboards/IV.pb reflectors/I.rf rotors/II.rot rotors/I.pos < input.txt > output.txt
```
Output.txt will contain an encrypted version of the text contained inside input.txt. Passing the encrypted version as 
input.txt with the same command line parameters will then decrpyt the text to its original state.
