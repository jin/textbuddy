//
//  TaskManager.cpp
//  TextBuddy
//
//  Created by jin on 13/8/14.
//  Copyright (c) 2014 CryptApps. All rights reserved.
//

using namespace std;

#include <fstream>
#include <sstream>

#include "TaskManager.h"
#include "boost/tokenizer.hpp"

#define MESSAGE_PROMPT                 "command: "
#define MESSAGE_HELP                   "commands: help, add <task>, delete <task number>, display, clear, exit"
#define MESSAGE_COMMAND_NOT_RECOGNIZED "Command not recognized. Type \"help\" to see full list of commands."
#define MESSAGE_DELETED_ALL_TASKS      "Deleted all tasks."
#define MESSAGE_INVALID_TASK_NUMBER    "Invalid task number. Please try again."
#define MESSAGE_FILE_UNOPENABLE        "File cannot be opened."

#define INVALID_TASK_NUMBER -1

/**
    TaskManager constructor.
    @param the filename of the tasks file.
*/
TaskManager::TaskManager(string _filename) {
    filename = _filename;
    loadFromFile();
}

/**
    Begin the main IO loop.
*/
void TaskManager::init() {
    loop();
}

/**
    Tokenize and extract the command action from the command line. 
    Executes the action if it is one of the options, if not, prompt the user.
    @param the command line to be parsed
*/
void TaskManager::executeCommand(string commandLine) {
    vector<string> tokens = tokenize(commandLine);
    if (tokens.empty()) { return; }

    // std::string does not work well with switch case.
    // See http://stackoverflow.com/questions/650162/why-switch-statement-cannot-be-applied-on-strings 

    string command = tokens[0];
    if      (command == "display") { display(); } 
    else if (command == "clear")   { clear(); } 
    else if (command == "exit")    { exit(); } 
    else if (command == "add")     { add(extractTaskTitleFromTokens(tokens)); } 
    else if (command == "delete")  { del(extractTaskNumberFromTokens(tokens)); } 
    else if (command == "help")    { respondWithMessage(MESSAGE_HELP); } 
    else                           { respondWithMessage(MESSAGE_COMMAND_NOT_RECOGNIZED); }
}

int TaskManager::numberOfTasks() {
	return tasks.size();
}


// Private methods

/**
    The main IO loop of the program. 
*/
void TaskManager::loop() {
    string command;
    while (true) {
        cout << MESSAGE_PROMPT;
        getline(cin, command);
        executeCommand(command);
        writeToFile();
    }
}

/**
    This method allows the message to be forwarded to different outputs.

    @param the message string to be displayed to the user.
*/
void TaskManager::respondWithMessage(string message) {
    cout << message << endl;
}

/**
    Saves all the tasks in memory to the specified file, effectively
    overwriting the file.

    If there are unsaved changes in memory and this method is not called,
    the changes will be lost when the program exits, or when loadFromFile() 
    is called.
*/
void TaskManager::writeToFile() {
    ofstream o;
    o.open(filename);
    
    for (unsigned i = 0; i < tasks.size(); i++) {
        o << tasks[i].title << endl;
    }
    
    o.close();
}

/**
    Loads tasks from specified file, overwriting the tasks in memory.
*/
void TaskManager::loadFromFile() {
    ifstream i;
    i.open(filename);
    if (!i.is_open()) { cerr << MESSAGE_FILE_UNOPENABLE << endl; }
    
    string taskTitle;
    tasks.clear();
    while (getline(i, taskTitle)) {
        Task task;
        task.title = taskTitle;
        tasks.push_back(task);
    }
    
    i.close();

    respondWithMessage("Welcome to TextBuddy. " + filename + " is ready for use.");
}

/**
    @param the name of the task to be added
*/
void TaskManager::add(string title) {
    if (title.empty()) {
        respondWithMessage("Please enter a task.");
        return;
    }

    Task task;
    task.title = title;
    tasks.push_back(task);

    respondWithMessage("Added task to " + filename + ": " + task.title);
}

/**
    @param the number of the task to be deleted (1-index)
*/
void TaskManager::del(int taskNumber) {
    if (taskNumber == INVALID_TASK_NUMBER) {
        respondWithMessage(MESSAGE_INVALID_TASK_NUMBER);
        return;
    }
    respondWithMessage("Deleting task from " + filename + ": " + tasks[taskNumber].title);
    tasks.erase(tasks.begin() + taskNumber);
}

/**
    Delete all tasks from memory (not disk)
*/
void TaskManager::clear() {
    tasks.clear();
    respondWithMessage(MESSAGE_DELETED_ALL_TASKS);
}

/**
    Displays all tasks in memory in an ordered list, starting from 1.
*/
void TaskManager::display() {
    if (tasks.empty()) {
        respondWithMessage(filename + " is empty");
        return;
    } 

    // C++ array index begin with 0, but the display index begins from 1.
    int idx = 1;
    for (auto &i : tasks) {
        respondWithMessage(to_string(idx) + ": " + i.title);
        idx++;
    }
}

/**
    Prompt user to save changes before exit.
*/
void TaskManager::exit() {
    ::exit(0);
}

// Helper methods

/**
    Used by TaskManager::del()

    @param the tokenized command line
    @return an integer that represents a task number, or an INVALID_TASK_NUMBER if 
    it is not specified, or if it's out of range.
*/
int TaskManager::extractTaskNumberFromTokens(vector<string> tokens) {
    if (tokens.size() == 1) { return INVALID_TASK_NUMBER; } 


    int taskNumber = atoi(tokens[1].c_str()) - 1;
    if (taskNumber < 0 || taskNumber >= tasks.size()) {
        return INVALID_TASK_NUMBER;
    } else {
        return taskNumber;
    }
}

/**
    Used by TaskManager::add()

    Separate the task title from the tokenized command string.

    @param the tokenized command line
    @return a string that represents the title of the task. 
*/
string TaskManager::extractTaskTitleFromTokens(vector<string> tokens) {
    string taskTitle;

    // Join task words into a string
    for (unsigned i = 1; i < tokens.size(); i++) {
        taskTitle = taskTitle + tokens[i];
        if (i != tokens.size() - 1) { taskTitle = taskTitle + " "; }
    }

    return taskTitle;
}

/**
    Split a string into individual tokens. Separated by whitespace.

    @param the string to be tokenized
    @return the tokenized string 
*/
vector<string>TaskManager::tokenize(string s) {
    vector<string> tokens;
    boost::char_separator<char> sep(" ");
    boost::tokenizer<boost::char_separator<char>> tok(s, sep);
    for (const auto& t : tok) {
        tokens.push_back(t);
    }
    return tokens;
}