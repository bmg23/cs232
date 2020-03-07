/* Path.cpp, CS232 Prof. Norman
 *
 * Author:  Brian Goins (bmg23@students.calvin.edu)
 * Date: Spring 2020 
 * 
 * Goal: A class to represent the directories in which 
 *         your shell searches for executable programs.  
 */ 

#include <string>
#include <iostream>
#include <bits/stdc++.h>
 #include <stdlib.h> 
using namespace std; 

class Path {
    public:
        //Private or Public?
        Path();  
        vector<string> PATH;
        int find(const string& program); 
        string getDirectory(int i) const;

};

Path::Path() {
    char* pPath;
    
    pPath = getenv ("PATH");
    int i = 0; 
    int pathIndex = 0; 
    
    while(pPath[i] != NULL)
	{
		
        ++i; 
	}
    
    if (pPath!=NULL)
        printf ("The current path is: %s",pPath);

}

/* return the index of the directory containing 
*  program, or -1 if program is in no directory
*/ 
int Path::find(const string& program) {
    //Get end of path. 
    
    //If end of path 
    if(1) {

    } else {
        return -1; 
    }
}

// return the name of the directory whose index is i.
string Path::getDirectory(int i) const {
    return "hey"; 
}

//Main Tester
int main() {
    Path path; 
  
}
