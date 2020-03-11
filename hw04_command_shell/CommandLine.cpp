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
    int argc = 0;
    char* argv[];

    public:

        //CommandLine constructor takes in istream input and parses into argv while incrementing argc
        CommandLine();
        CommandLine(istream& in);
        char* getCommand() const;
        int getArgCount();
        char** getArgVector();
        char* getArgVector(int i);
        bool noAmpersand() const;
        ~CommandLine();



};

//CommandLine Constructor takes in istream
CommandLine::CommandLine(istream &cmd){
            //Read in the command from istream
            char *command = cmd;
            cout << "CommandLine input: " << command << flush;

            //state keeps track of whether or not the loop is tracking a word
            int size = 0;
            //count both characters and words in the command
            
            while (command != NULL){
                
                argv[argc] = command;
                command = strtok(NULL, " ,\n,\t");

                //Increment size and argument counter
                argc++;
                size++;
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

//CommandLine Destructor
CommandLine::~CommandLine(){
    free(argv);
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
//Unclear: Do we want to check every character in argv or every word?
//return true if and only if no ampersand was given on the command line
bool CommandLine::noAmpersand() const{
    for (int i = 0; i < argc; i++){
        //Check if a lone argument is "&"
        if (argv[i] == "&"){
            return false;
        }
    }
    
    //Default return choice
    return true;
}
