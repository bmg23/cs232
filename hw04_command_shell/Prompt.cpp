/* Prompt.cpp, CS232 Prof. Norman
 *
 * Author:  Brian Goins (bmg23@students.calvin.edu)
 * Date: Spring 2020 
 * 
 * Goal: A class to represent the command-line prompt
 */ 

#include <string>
#include <iostream>
#include <bits/stdc++.h>
 #include <stdlib.h> 
using namespace std; 

class Prompt {
    public: 
        Prompt(); 
        string get() const; 
};

//a constructor that builds a Prompt as the full path to the working directory
Prompt::Prompt() {

}

//an accessor that returns the current value of the Prompt
