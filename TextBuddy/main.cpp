//
//  main.cpp
//  TextBuddy
//
//  Created by jin on 13/8/14.
//  Copyright (c) 2014 CryptApps. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

#include "TaskManager.h"

using namespace std;

// Create an empty file with filename
void createTaskFile(string filename){
    cout << "Creating file: " << filename << "\n";
    
    fstream f;
    f.open(filename, fstream::out);
    f << flush;
    f.close();
    
    cout << "File created." << endl;
}

// Check if file with filename is created
bool isFileCreated(string filename){
    ifstream i(filename);
    return i.good();
}

void exitIfNoArguments(int argCount) {
    if (argCount < 2) {
        cerr << "Please input the name of the task file" << endl;
		exit(1);
    }
}

int main(int argc, const char * argv[]){
	exitIfNoArguments(argc);
    
    string filename = argv[1];
    if (isFileCreated(filename) == 0) { createTaskFile(filename); }
    
	// Loop begins at the end of TaskManager initialization
    TaskManager taskManager = TaskManager(filename);
    
    return 0;
}