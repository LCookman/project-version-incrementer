#pragma once

#include <vector>

#include "IProcessController.h"

class WindowsProcessController : public IProcessController
{
private:
	std::vector<std::string> mCommandToRun;

public:
	WindowsProcessController (std::vector<std::string> command);
	~WindowsProcessController ();

	void StartProcessAndWait ();
};