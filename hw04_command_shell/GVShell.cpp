/* Shell class using c++
 * @Authors: Caleb Vredevoogd (chv5@students.calvin.edu) and Brian Goins (bmg23@students.calvin.edu)
 *
 *
 */

/*
XYShell - your shell class, with two public methods:
XYShell() - initialize your shell; and
void run() - execute your shell.
In addition to executing system programs (e.g., ls, ps, cat), your shell must also 	
handle cd, pwd, and exit as built-in commands (you may find the chdir() and getcwd() system calls to be useful for this).

*/


#include "GVShell.h"
//Project Files
#include "Path.cpp"
#include "Prompt.cpp"
#include "CommandLine.cpp"
#include <iostream>

using namespace std; 


class GVShell {
    public:
        GVShell(); 
        void run();
    private:
        Prompt prompt;
        Path path;     
};

GVShell::GVShell() {} //Constructor

void GVShell::run() {
    int status = 1;  
    
    //Shell Loop
    do {
        //Create Prompt
        cout << prompt.get() << "$ " << endl;
        CommandLine cmdl = CommandLine(cin); 
       
        //Look for command 
        //If command not found try to run a system call 
        //If command is not found and not a system call report back error.
        
        if(path.find(cmdl.getCommand()) != -1) {
            //Run command

            //Create a child process
            pid_t child = fork()

            //Check to see if the fork failed
            if (child < 0){
                cout << "Fork failed" << endl;
            }

            //If child succeeded, create process
            if (child == 0){
                int index = path.find();
                
            }

        } else {
            try {
                system(cmdl.getCommand()); 
            } catch (int e) {
                cout << "Command failed or not found!" << endl; 
            }
        }
        
        
    } while(status); 
    
}

//Main function
int main(){
    GVShell myShell;
    myShell.run();
}