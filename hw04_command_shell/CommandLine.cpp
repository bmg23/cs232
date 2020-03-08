/*
* Command Line class
* @Author: Caleb Vredevoogd (chv5@students.calvin.edu)
*/

//note: how to get path: cwd, cast that to a string

using namespace std;

#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <bits/stdc++.h>


class CommandLine {
    int argc;
    char* argv[];

    public:

        //CommandLine constructor takes in iostream input and parses into argv while incrementing argc
        CommandLine(istream& in);
        char* getCommand() const;
        int getArgCount();
        char** getArgVector();
        char* getArgVector(int i);
        bool noAmpersand() const;



};

CommandLine::CommandLine(istream& in){
            //Read in the command from istream
            char *command;
            in >> command;

            //state keeps track of whether or not the loop is tracking a word
            int state = 0;
            int size = 0;
            //count both characters and words in the command
            while (*command){
                
                //If the next character is a separator, set the state to 0
                if (*command == ' ' || *command == '\n' || *command == '\t'){
                    state = 0;
                }

                //If state is 0, set state = 1 and increment argument counter
                else if (state == 0){
                    state = 1;
                    argc ++;
                }
                ++size;
                ++command;
            }

            //Allocate space for argv based on size of the command and number of arguments
            char* argv = (char*)calloc(argc, size);

            //Initialize variables for command tokenization
            int i;
            
            //Tokenize input command into argument vector
            char *token = strtok(command, " ");
            while (token != NULL){
                *token >> argv[i];
                token = strtok(NULL, " ");
                i++; 
            }
                       
}

//Return a pointer to the command portion of the command-line
char* CommandLine::getCommand() const { 
    return argv[0];
    }
//return the number of command line arguments on the command-line
int CommandLine::getArgCount(){
    return argc;
}

//Returns a pointer to the Argument Vector (argv)
char** CommandLine::getArgVector(){
    char* *arg;
    
    arg = argv;
    return arg;
}

//Return a pointer to the ith (zero relative) command-line 'word'
char* CommandLine::getArgVector(int i){
    return argv[i];
}

//TODO: Make this work through every argument in argv to look for and ampersand
//return true if and only if no ampersand was given on the command line
bool CommandLine::noAmpersand() const{
    char* andPtr = "&";
    for (int i = 0; i < argc; i++){
        if (argv[i] == )
    }
}

int main (){
    cout << "Enter command: ";
    CommandLine cmdl (cin);
    
}