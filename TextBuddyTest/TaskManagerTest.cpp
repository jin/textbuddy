#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>

#include "..\TextBuddy\TaskManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTest
{		
	TEST_CLASS(TextBuddyTest)
	{
	public:

		TEST_METHOD(LoadEmptyTasksFile)
		{
			TaskManager taskManager = TaskManager("tasks.txt");
			Assert::AreEqual(0, taskManager.numberOfTasks());
		}

		TEST_METHOD(AddTask)
		{
			TaskManager taskManager = TaskManager("tasks.txt");
			taskManager.executeCommand("add buy milk");
			Assert::AreEqual(1, taskManager.numberOfTasks());
		}

		TEST_METHOD(DeleteTask)
		{
			TaskManager taskManager = TaskManager("tasks.txt");
			taskManager.executeCommand("add buy milk");
			taskManager.executeCommand("add walk the dog");
			taskManager.executeCommand("delete 2");
			Assert::AreEqual(1, taskManager.numberOfTasks());
		}

		TEST_METHOD(DeleteNonExistentTask)
		{
			TaskManager taskManager = TaskManager("tasks.txt");
			taskManager.executeCommand("add buy milk");
			taskManager.executeCommand("delete 2");
			Assert::AreEqual(1, taskManager.numberOfTasks());
		}


		TEST_METHOD(LoadNonEmptyTasksFile)
		{
			// Adding a task manually to the file
			std::ofstream out("tasks.txt");
			out << "add buy milk\n";
			out.close();

			TaskManager taskManager = TaskManager("tasks.txt");
			Assert::AreEqual(1, taskManager.numberOfTasks());
		}


		TEST_METHOD(ClearTasks)
		{
			TaskManager taskManager = TaskManager("tasks.txt");
			taskManager.executeCommand("add buy milk");
			taskManager.executeCommand("add walk the dog");
			taskManager.executeCommand("clear");
			Assert::AreEqual(0, taskManager.numberOfTasks());
		}

		TEST_METHOD(SortTasks)
		{
			TaskManager taskManager = TaskManager("tasks.txt");
			taskManager.executeCommand("add buy milk");
			taskManager.executeCommand("add buy zebras");
			taskManager.executeCommand("add solve rubik's cube");
			taskManager.executeCommand("add yell at animals");
			taskManager.executeCommand("add yell at people");
			std::vector<Task> expected = taskManager.tasks;

			taskManager.executeCommand("clear");
			taskManager.executeCommand("add yell at people");
			taskManager.executeCommand("add buy zebras");
			taskManager.executeCommand("add buy milk");
			taskManager.executeCommand("add solve rubik's cube");
			taskManager.executeCommand("add yell at animals");
			taskManager.executeCommand("sort");

			for (unsigned i = 0; i < 4; i++)
			{
				Assert::AreEqual(taskManager.tasks[i].title, expected[i].title);
			}
		}

		TEST_METHOD_CLEANUP(RemoveTasksFile)
		{
			std::remove("tasks.txt");
		}
	};
}