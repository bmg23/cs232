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
        CommandLine & operator= (const CommandLine &CommandLine);
        char* getCommand() const;
        int getArgCount();
        char** getArgVector();
        char* getArgVector(int i);
        bool noAmpersand() const;

        ~CommandLine();

    private:
    //TODO: Maybe add bool for if ampersand is present?
    //TODO: Keep first arg separate?
        int argc = 0;
        char** argv;



};

//Default Constructor
CommandLine::CommandLine(){

}

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
    cout << cmnd[0] << endl;
    strcpy(cmnd, cmd);
    cout << cmnd[0] << endl;

    //DEBUG
    cout << "Argc: " << argc << endl;
   
    argv = (char**) calloc (argc+1, sizeof(char*));

    //tokenize the command into the argument vector
    char* p = strtok(cmnd, " ");
    //DEBUG
    cout << "value of p after first tokenize: " << p << endl;
    char* temp = p;

    int i = 0;
    while (p != NULL){
        argv[i] = (char*) calloc (64, sizeof(char*)); 
        argv[i] = p;
        
        p = strtok(NULL," ,\n,\t");

        //cout << "Tokenize: " << p << endl;

        i++;
    }

    //DEBUG
    /*cout << "Out of loop?" << endl;
    for(int n = 0; n < 4; n++) {
        cout << argv[n] << endl;
    }
    */
   //DEBUG
   // cout << "Check me for bugs!" << endl;            
}

//CommandLine Destructor
CommandLine::~CommandLine(){
    //DEBUG
    cout << "Calling Destructor..." << endl;
    free(argv);
}

//Assignment operator overload
CommandLine & CommandLine::operator= (const CommandLine &inCdl){
    argc = inCdl.argc;
    argv = inCdl.argv;

    return *this;
}

//Return a pointer to the command portion of the command-line
char* CommandLine::getCommand() const {
    //DEBUG
    //char* command = argv[0];

    //cout << "command from getCommand: " << command << endl;
    return argv[0];
    
    //return command;
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
    cout << "getArgVector..." << endl;
    return argv[i];
}

//return true if and only if no ampersand was given on the command line
bool CommandLine::noAmpersand() const{
    for (int i = 0; i < argc; i++){
        //Check if a lone argument is "&"
        if (argv[i] == "&"){
            cout << "Ampersand Present" << endl;
            return false;
        }
    }
    
    //Default return choice
    return true;
}
