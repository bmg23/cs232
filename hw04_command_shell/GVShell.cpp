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


};

GVShell::GVShell() {} //Constructor




void GVShell::run() {
    int status = 1;  
    
    //Shell Loop
    do {
        //Create Prompt
        cout << prompt.get() << "$ ";
        CommandLine cmdl = CommandLine(cin);

 
        if(strcmp(cmdl.getCommand(), "pwd") == 0) {
            cout << path.getCWD() << endl; 
        }
        else if(strcmp(cmdl.getCommand(), "exit") == 0) {
            cout << "...Leaving" << endl; 
            exit(0); 
        }
        else if(strcmp(cmdl.getCommand(), "cd") == 0) {

            //Get command and arguments 
            string command; 
            char** args = cmdl.getArgVector(); 

            //Add arguments to command string 
            for(int i = 0; i < cmdl.getArgCount(); ++i) { 
                command += args[i];
                command += " ";   
            }


            //try to run system call. 
            try {
                system(command.c_str());  
            } catch(int e) {
                cout << "System call failed." << endl; 
            }

        } else {
            //Create a child process
            pid_t child = fork(); 

            //Check to see if the fork failed
            if (child < 0){
                cout << "Fork failed" << endl;
            }

            //If child succeeded, create process
            else if (child == 0){
                execve(cmdl.getCommand(), cmdl.getArgVector(), NULL); 
            }

            //Otherwise it's a parent
            else {
                int stat;
                //Check for ampersand in command. If there is none present, wait for the child
                //DEBUG
                cout << "Checking if ampersand present" << endl;
                if(cmdl.noAmpersand()){
                    pid_t chldpid = waitpid(child, &stat, 0);
                    while (!WIFEXITED(stat)){
                        wait(NULL);
                    }
                    /*
                    if (WIFEXITED(stat))
                        printf("Child %d terminated with status: %d\n", chldpid, WEXITSTATUS(stat));
                    */
                }
                //If there is an ampersand present, don't wait for child to exit and
                //continue back to the top of the loop
                else{
                    continue;
                }
            }

        } 
        
    } while(status); 
    
}

//Main function
int main(){
    GVShell myShell;
    myShell.run();
}