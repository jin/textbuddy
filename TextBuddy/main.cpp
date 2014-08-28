// main.cpp
// TextBuddy

// Created by jin on 13/8/14.
// Copyright (c) 2014 CryptApps. All rights reserved.

// This program lets you manage your TODO tasks in the command line interface.
//
// No installation is required to run the program.
//
// Building dependencies: 
// 1) c++ boost library in include path.
//
// Usage:
// TextBuddy.exe tasks.txt 
// TextBuddy.exe C:\\Users\foo\Desktop\todo.txt
//
// The only argument is the location of the plaintext file where the tasks are saved. 
//
// At startup, tasks from the file are loaded into memory, one by one.
//
// The prompt will change from "command:" to "command *:" if there are unsaved changes.
//
// Commands:
// 
// - help
// Show the list of available commands.
//
// Example:
// command: help
// available commands: help, add <task>, delete <task number>, display, clear, exit, save, reload
//
//-------------------------------------
//
// - display
// Shows all tasks that are loaded in memory. 
//
// Example:
// command: display
// 1: buy milk
// 2: walk the dog
//
//-------------------------------------
//
// - add <task>
// Add a task to memory.
//
// Example:
// command: add walk the dog
// Added task to Tasks.txt: walk the dog 
//
//-------------------------------------
//
// - delete <task number>
// Delete a task from memory specified by the task number, starting from 0.
//  
// Example: 
// command: delete 1
// Deleting task: buy milk
//
//-------------------------------------
// - clear 
// Clears all tasks in the memory 
//
// Example:
// command: clear
// all content deleted from Tasks.txt
//
//-------------------------------------
//
// - save
// Saves tasks in memory to the file on disk. This overwrites the file contents.
//
// Example:
// command: save
// Saved!
//
//-------------------------------------
//
// - reload
// Overwrites the tasks in memory with the tasks from the specified file.
//
// Example:
// command: reload 
// Loaded!
//
// -------------------------------------
// 
// - exit  
// Exits the application.

#include <iostream>
#include <fstream>
#include <string>

#include "TaskManager.h"

using namespace std;

/**
    Create an empty file to store the tasks on disk.
    @param path to file.
*/
void createTaskFile(string filename){
    cout << "Creating file: " << filename << "\n";
    
    fstream f;
    f.open(filename, fstream::out);
    f << flush;
    f.close();
    
    cout << "File created." << endl;
}

/**
    @param path to file.
    @return true if file with filename exists, false otherwise.
*/
bool isFileCreated(string filename){
    ifstream i(filename);

    // Assign the value to a variable instead of returning i.good()
    // is to allow the closing of ifstream i.
    bool isCreated = i.good();
    i.close();

    return isCreated;
}

/**
    @param integer representing number of arguments
*/
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
    
    TaskManager taskManager = TaskManager(filename);
    taskManager.init();
    
    return 0;
}