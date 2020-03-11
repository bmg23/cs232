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
#include <stdexcept>
#include <dirent.h>
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
    
    string fullPath = ""; 

    while(pPath[i] != NULL)
	{
		char singleLetter = pPath[i]; 
        //Add paths, break in paths is :
        if(singleLetter == ':') {
            PATH.push_back(fullPath); 
            fullPath = ""; 
        } else {
            fullPath += singleLetter; 
        }

        //Increment the index
        ++i; 
	}
}

/* return the index of the directory containing 
*  program, or -1 if program is in no directory
*/ 
int Path::find(const string& program) {    
    int index = -1;
    DIR *dir;
    struct dirent *ent;
    for (int i = 0; i < PATH.size(); i++) {
        if ((dir = opendir(PATH[i].c_str())) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                if (ent->d_name == program) {
                    index = i;
                }
            }
            closedir(dir);
        }
    }
    return index;
}

// return the name of the directory whose index is i.
string Path::getDirectory(int i) const {
    if (i > PATH.size()) {
		throw range_error("Index is out of range.");
	}
	
    return PATH[i];
}