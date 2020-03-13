/*
* Command Line class
* @Author: Caleb Vredevoogd (chv5@students.calvin.edu), Brian Goins (bmg23@students.calvin.edu)
*/

//note: how to get path: cwd, cast that to a string

using namespace std;

#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
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
        int argc;
        char** argv;
        char* cmdArg;
        bool noAmp;
        vector<string> argvVector;

};

//CommandLine Constructor takes in istream
CommandLine::CommandLine(istream& in){

    argc = 0;
	noAmp = true;

	string command;
	getline(in, command);

	istringstream commandStream (command);

	string temp;
	while (commandStream >> temp) {
		if (strcmp(temp.c_str(), "&") == 0) {
			noAmp = false;
		} else {
			argvVector.push_back(temp);
			argc++;
		}
	}

	argv = new char*[argvVector.size()];

	for (size_t i = 0; i < argvVector.size(); i++) {
		argv[i] = new char[argvVector[i].size() + 1];
		strcpy(argv[i], argvVector[i].c_str());
	}

}

//CommandLine Destructor
CommandLine::~CommandLine(){
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
    return argv[0];
}

//return the number of command line arguments on the command-line
int CommandLine::getArgCount(){
    return argc;
}

//Returns a pointer to the Argument Vector (argv)
char** CommandLine::getArgVector(){
    return argv;
}

//Return a pointer to the ith (zero relative) command-line 'word'
char* CommandLine::getArgVector(int i){
    return argv[i];
}

//return true if and only if no ampersand was given on the command line
bool CommandLine::noAmpersand() const{
    return noAmp;
}
