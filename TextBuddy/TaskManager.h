//
//  TaskManager.h
//  TextBuddy
//
//  Created by jin on 13/8/14.
//  Copyright (c) 2014 CryptApps. All rights reserved.
//
//  This is the main TaskManager class that defines the methods 
//  and variables used for task management. 
//  
//  CRUD, save and loading are supported.

#include <iostream>
#include <vector>

typedef struct Task {
    std::string title;
} Task;

struct less_than_key {
	inline bool operator() (const Task& lhs, const Task& rhs) {
		int result = lhs.title.compare(rhs.title);
		if (result < 0) {
			return true;
		} else {
			return false;
		}
	}
};

class TaskManager {
private:
    std::string filename;

    void loop();

    void writeToFile();
    void loadFromFile();
    void add(std::string title);
    void del(int id);
    void display();
    void clear();
    void exit();
	void sort();
    void respondWithMessage(std::string message);
    void clearInput();

    std::string extractTaskTitleFromTokens(std::vector<std::string> tokens);
    int extractTaskNumberFromTokens(std::vector<std::string> tokens);
    std::vector<std::string> tokenize(std::string s);
    
public:
    TaskManager(std::string filename);
    std::vector<Task> tasks; // Main vector to store tasks during runtime
    void executeCommand(std::string commandLine);
    void init();

	int numberOfTasks();
};