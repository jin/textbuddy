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

class TaskManager {
private:
    std::vector<Task> tasks; // Main vector to store tasks during runtime
    std::string filename;
    bool saved;

    void clearInput();
    void writeToFile();
    void loadFromFile();
    void respondWithMessage(std::string message);
    void display();
    void clear();
    void add(std::string title);
    void del(int id);
    void exit();
    void loop();

    int promptToSave();

    std::string extractTaskTitleFromTokens(std::vector<std::string> tokens);
    int extractTaskNumberFromTokens(std::vector<std::string> tokens);
    std::vector<std::string> tokenize(std::string s);
    
public:
    TaskManager(std::string filename);

    void init();
    void executeCommand(std::string commandLine);
};