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
#include "cstdlib"
#include "Prompt.cpp"
#include "CommandLine.cpp"
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std; 


class GVShell {
    public:
        GVShell(); 
        void run();
    private:
        Prompt prompt;
        Path path;
        CommandLine cmd;


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

        //Use of assignment operator should solve values changing
        cmd = cmdl; 

        //DEBUG
        //cout << "\nCommandLine initialized\n" << flush;

        //DEBUG
        //cout << "Current Command: " << cmdl.getCommand() << endl;
        //path.find might be a problem
        if(path.find(cmd.getArgVector(0)) != NULL) {
            //DEBUG
            cout << "Running command\n" << flush;
            //Run command

            //Create a child process
            pid_t child = fork(); 

            //Check to see if the fork failed
            if (child < 0){
                cout << "Fork failed" << endl;
            }

            //If child succeeded, create process
            else if (child == 0){

                execvp(cmd.getCommand(), cmd.getArgVector()); 
            }

            //Otherwise it's a parent
            else {
                int stat;
                //Check for ampersand in command. If there is none present, wait for the child
                //DEBUG
                cout << "Checking if ampersand present" << endl;
                if(cmd.noAmpersand()){
                    pid_t cldpid = waitpid(child, &stat, 0);
                    while (!WIFEXITED(stat)){
                        wait(NULL);
                    }
                    if (WIFEXITED(stat))
                        printf("Child %d terminated with status: %d\n", cldpid, WEXITSTATUS(stat));
                }
                //If there is an ampersand present, don't wait for child to exit and
                //continue back to the top of the loop
                else{
                    continue;
                }

                

            }

        } 

        cmd.~CommandLine(); 
        cout << "Out of if else." << endl; 
        
    } while(status); 
    
}

//Main function
int main(){
    GVShell myShell;
    myShell.run();
}