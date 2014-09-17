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
#include <algorithm>

typedef struct Task {
    std::string title;
} Task;

struct less_than_key {
    inline bool operator() (const Task& lhs, const Task& rhs) {
        std::string lhs_title = lhs.title;
        std::string rhs_title = rhs.title;
        std::transform(lhs_title.begin(), lhs_title.end(), lhs_title.begin(), ::toupper);
        std::transform(rhs_title.begin(), rhs_title.end(), rhs_title.begin(), ::toupper);
		return (lhs_title.compare(rhs_title) < 0);
    }
};

class TaskManager {
private:
    std::string filename;
    std::vector<Task> tasks;
    std::vector<Task> latestSearchResult;

    void loop();
    void writeToFile();
    void loadFromFile();
    void add(std::string title);
    void del(int id);
    void display();
    void displaySearchResult();
    void clear();
    void exit();
    void sort(); // Sort by ascending alphabetical order.
    void search(std::string searchString);
    void respondWithMessage(std::string message);
    void clearInput();

    bool stringFound(std::string str, std::string term);

    std::string extractSearchStringFromTokens(std::vector<std::string> tokens);
    std::string extractTaskTitleFromTokens(std::vector<std::string> tokens);
    int extractTaskNumberFromTokens(std::vector<std::string> tokens);
    std::vector<std::string> tokenize(std::string s);
    
public:
    TaskManager(std::string filename);

    std::vector<Task> getTasks();
    std::vector<Task> getLatestSearchResult();
    void executeCommand(std::string commandLine);
    void init();

    int numberOfTasks();
};