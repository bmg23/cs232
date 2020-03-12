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
//#include <stdlib.h>
#include <string>
#include <bits/stdc++.h>


class CommandLine {
    

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

    private:
        int argc = 0;
        char** argv;



};

//CommandLine Constructor takes in istream
CommandLine::CommandLine(istream& in){
    
//Read in input
    argc = 1;
    string command;
    getline (in, command);

    //Turn command into a char array
    const char * cmd = command.c_str();
    
    //Get number of arguments
    for(const char *c = cmd; *c; ++c) {
        if (*c == ' ' || *c=='t' || *c == '\n'){
            argc++;
        }
    }

    //Copy command into non const char array cmnd
    char cmnd[sizeof(cmd)];
    strcpy(cmnd, cmd);

    //DEBUG
    cout << argc << endl;
   
    argv = (char**) calloc (argc+1, sizeof(char*));

    //tokenize the command into the argument vector
    char* p = strtok(cmnd, " ");
    char* temp = p;

    int i = 0;
    while (p != NULL){
        argv[i] = (char*) calloc (64, sizeof(char*)); 
        argv[i] = p;
        cout << argv[i] << endl;
        p = strtok(NULL," ,\n,\t");

        i++;
    }

    //DEBUG
    /*cout << "Out of loop?" << endl;

    for(int n = 0; n < 4; n++) {
        cout << argv[n] << endl;
    }
    */

                       
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
