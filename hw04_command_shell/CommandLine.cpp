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
#include <string>
#include <bits/stdc++.h>


class CommandLine {
    int argc;
    char* argv[];

    public:
        CommandLine(istream& in);
        char* getCommand() const;



} cmdl;

//CommandLine constructor takes in iostream input and parses into argv while incrementing argc
CommandLine::CommandLine(istream& in){
    
    //Read in the command from istream
    string command;
    in >> command;

    //Initialize variables for command tokenization
    stringstream strm(command);
    string interm;
    int i = 0;
    //Tokenize input command into argument vector and increment argument counter
    while(getline(strm, interm, ' ')){
        *CommandLine::argv[i].push_back(interm);
        argc++;    
    }

    //Allocate memory to hold command 
    calloc(argc, command.length());

}

char* getCommand() const { 
    return argv[0];
    }

int main (){
    cout << "Enter command: ";
    CommandLine cmdl (cin);
}