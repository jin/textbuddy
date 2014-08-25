//
//  TaskManager.h
//  TextBuddy
//
//  Created by jin on 13/8/14.
//  Copyright (c) 2014 CryptApps. All rights reserved.

#include <iostream>
#include <vector>

typedef struct Task {
    std::string title;
} Task;

class TaskManager {
	// Main vector to store tasks during runtime
    std::vector<Task> tasks;
    std::string filename;
    
private:
    std::vector<std::string> split(std::string s);

    void clearInput();
    void writeToFile();
    void loadFromFile();
    
    void display();
    void clear();
    void add(std::string title);
    void del(int id);
    void exit();

	std::string extractTaskFromTokens(std::vector<std::string> tokens);
    
public:
    TaskManager(std::string filename);
    
    void loop();
	void executeCommand(std::vector<std::string> tokens);
};