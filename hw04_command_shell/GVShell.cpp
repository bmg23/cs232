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
        cout << prompt.get() << "$ ";
        
        //Debug stuff - This ended up using the input and so the CommandLine constructor call got nothing
        //string input; 
        //cin >> input;
        //cout << input << flush; 

        CommandLine cmdl = CommandLine(cin); 

        //Debug stuff
        cout << "\nCommandLine initialized\n" << flush;


        if(path.find(cmdl.getCommand()) != -1) {
            cout << "Running command\n" << flush;
            //Run command

            //Create a child process
            pid_t child = fork(); 

            //Check to see if the fork failed
            if (child < 0){
                cout << "Fork failed" << endl;
            }

            //If child succeeded, create process
            if (child == 0){
                execvp(cmdl.getCommand(), cmdl.getArgVector()); 
                
            }

        } else {

            cout << "Trying System Call: " << cmdl.getCommand() << endl;
            const char * command = cmdl.getCommand(); 
                
            system(command); 
            /*
            try {
                
            } catch (int e) {
                cout << "Command failed or not found!" << endl; 
            }
            */
        }

        cmdl.~CommandLine(); 
        cout << "Out of if else." << endl; 
        
    } while(status); 
    
}

//Main function
int main(){
    GVShell myShell;
    myShell.run();
}