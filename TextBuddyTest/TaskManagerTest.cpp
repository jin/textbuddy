#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\TextBuddy\TaskManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTest
{		
	TEST_CLASS(TextBuddyTest)
	{
	public:
		
		TEST_METHOD(Add)
		{
			TaskManager taskManager = TaskManager("tasks.txt");
			int current_size = taskManager.numberOfTasks();
			taskManager.executeCommand("add buy milk");
			Assert::AreEqual(current_size + 1, taskManager.numberOfTasks());
		}

	};
}