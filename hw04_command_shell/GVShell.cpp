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
        cout << path.getCWD() << "/GVShell$ ";
        CommandLine cmdl = CommandLine(cin);

 
        if(strcmp(cmdl.getCommand(), "pwd") == 0) {
            cout << path.getCWD() << endl; 
        }
        else if(strcmp(cmdl.getCommand(), "exit") == 0) {
            cout << "...Leaving" << endl; 
            exit(0); 
        }
        else if(strcmp(cmdl.getCommand(), "cd") == 0) {

            //Get the desired path 
            string path; 
            char** args = cmdl.getArgVector(); 

            path = args[1]; 

    
            //try to run system call. 
            try {
                chdir(path.c_str()); 
            } catch(int e) {
                cout << "Change in directory failed." << endl; 
            }

        } else {

            if(path.find(cmdl.getCommand()) == -1) {
                cout << "Command not found" << endl; 
                continue;
            }

            //Create a child process
            pid_t child = fork(); 

            //Check to see if the fork failed
            if (child < 0){
                cout << "Fork failed" << endl;
            }

            //If child succeeded, create process
            else if (child == 0){ 
                int index = path.find(cmdl.getCommand()); 
                
                string directory_to_path = path.getDirectory(index); 
                directory_to_path += "/";
                directory_to_path += cmdl.getCommand(); 

                char ** argVec = cmdl.getArgVector(); 
                argVec[cmdl.getArgCount()] = NULL; 
                cout << endl; 
                execve(directory_to_path.c_str(), argVec, NULL); 
            } else {
                int stat;
                //Check for ampersand in command. If there is none present, wait for the child
                if(cmdl.noAmpersand()){
                    pid_t chldpid = waitpid(child, &stat, 0);
                    while (!WIFEXITED(stat)){
                        wait(NULL);
                    }
                    kill(child, SIGKILL); 
                    /*
                    if (WIFEXITED(stat))
                        printf("Child %d terminated with status: %d\n", chldpid, WEXITSTATUS(stat));
                    */
                } else {
                    cout << endl; 
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