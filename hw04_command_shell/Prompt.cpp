/* Prompt.cpp, CS232 Prof. Norman
 *
 * Author:  Brian Goins (bmg23@students.calvin.edu)
 * Date: Spring 2020 
 * 
 * Goal: A class to represent the command-line prompt
 */ 
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <unistd.h>
using namespace std;

class Prompt {
  // Method declarations
    public:
        Prompt();
        string get() const;

    // Private instance variables
    private:
        char* curr_Path;
        char buff[PATH_MAX + 1];

}; 

//a constructor that builds a Prompt as the full Path to the working directory
Prompt::Prompt() {
    curr_Path = getcwd(buff, PATH_MAX + 1);
	strcat(curr_Path, "/GVShell");

}

string Prompt::get() const {
	return curr_Path;
}

