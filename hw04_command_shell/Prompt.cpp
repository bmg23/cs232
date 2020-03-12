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
        Prompt() { 
            Path = getcwd(buff, PATH_MAX + 1); 
            strcat(Path, "/GVShell");
        }; 
        string get() const { return Path; }

    // Private instance variables
    private:
        char* Path;
        char buff[PATH_MAX + 1];

}; 

