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
      
    for(int i = 0; PATH.size(); ++i) {
        string currentPath = PATH[i];
        if(currentPath.find(program) != string::npos) {
            return i; 
        }
    }
}

// return the name of the directory whose index is i.
string Path::getDirectory(int i) const {
    return PATH[i];
}

//Main Tester
int main() {
    Path path; 

    //Test Paths
    string p1 = "WINDOWS"; 
    string p2 = "VSCode"; 
    string p3 = "npm"; 

    int index1, index2, index3;  

    index1 = path.find(p1); 
    index2 = path.find(p2); 
    index3 = path.find(p3); 

    cout << index1 << "\n"
         << index2 << "\n"
         << index3 << "\n"; 
    
    cout << path.getDirectory(index1) << "\n"
         << path.getDirectory(index2) << "\n"
         << path.getDirectory(index3) << "\n"; 

}
