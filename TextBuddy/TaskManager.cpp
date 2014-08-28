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

#define HELP_MESSAGE "available commands: help, add <task>, delete <task number>, display, clear, exit, save, reload"


TaskManager::TaskManager(string _filename) {
    filename = _filename;
    loadFromFile();
    loop();
}

// This is the main IO loop.
// Gets an input line, splits them up into tokens, 
// and passes the tokens into executeCommand()
void TaskManager::loop() {
    string command;
    vector<string> tokens;
    while (true) {
        cout << "command: ";
        getline(cin, command);
		tokens = tokenize(command);
		executeCommand(tokens);
    }
}

void TaskManager::executeCommand(vector<string> tokens) {
	if (tokens.size() == 0) {
		return;
	}

	string command = tokens[0];
	if (command == "display") {
		display();
	} else if (command == "clear") {
		clear();
	} else if (command == "exit") {
		exit();
	} else if (command == "save") {
		writeToFile();
	} else if (command == "reload") {
		loadFromFile();
	} else if (command == "add") {
		add(extractTaskFromTokens(tokens));
	} else if (command == "delete") {
		// todo:
		// solve edge cases
		int taskNumber = atoi(tokens[1].c_str()) - 1;
		cout << "Deleting task: " +  tasks[taskNumber].title << endl;
		tasks.erase(tasks.begin() + taskNumber);
	} else {
		if (command != "help") {
			cout << "command not recognized: " + command << endl; 
		}
		cout << "available commands: help, add <task>, delete <task number>, display, clear, exit, save, reload" << endl;
	}
	return;
}

// Private methods

void TaskManager::writeToFile() {
    ofstream o;
    o.open(filename);
    
    for (unsigned i = 0; i < tasks.size(); i++) {
        o << tasks[i].title << endl;
    }
    
    o.close();
	cout << "Saved!" << endl;
}

void TaskManager::loadFromFile() {
    ifstream i;
    i.open(filename);
    if (i.is_open() == false) {
        cerr << "File cannot be opened" << endl;
    }
    
    string taskTitle;
    tasks.clear();
    while (getline(i, taskTitle)) {
        add(taskTitle);
    }
    
    i.close();

	cout << "Reloaded!" << endl;
}

void TaskManager::add(string title) {
	if (title == "") {
		cout << "Cannot add an empty task." << endl;
		return;
	}

    Task task;
    task.title = title;
    tasks.push_back(task);
}

void TaskManager::del(int id) {
    cout << "deleted from " + filename + ": \"" + tasks[id - 1].title + "\"" << endl;
    tasks.erase(tasks.begin() + id - 1);
}

// Delete all tasks from memory
void TaskManager::clear() {
    cout << "all content deleted from " + filename << endl;
    tasks.clear();
}

void TaskManager::display() {
    if ( tasks.size() == 0 ) {
        cout << filename + " is empty" << endl;
    } else {
        int idx = 1;
        for ( auto &i : tasks ) {
            cout << to_string(idx) + ": " + i.title << endl;
            idx++;
        }
    }
}

void TaskManager::exit() {
    ::exit(0);
}

// Helper methods

string TaskManager::extractTaskFromTokens(vector<string> tokens) {
	string task;
	for (unsigned i = 1; i < tokens.size(); i++) {
		task = task + tokens[i];
		if (i != tokens.size() - 1) { task = task + " "; }
	}

	return task;
}


// Split a string into individual tokens, separated by whitespace.
vector<string>TaskManager::split(string s) {
    
    vector<string> tokens;
    
    typedef string::size_type string_size;
    string_size i = 0;
    
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i])) {
            ++i;
        }
        
        string_size j = i;
        while (j != s.size() && !isspace(s[j])) {
            j++;
        }
        
        if (i != j) {
            tokens.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    
    return tokens;
}