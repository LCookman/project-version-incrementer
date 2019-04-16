#pragma once

#include <vector>

#include "IProcessController.h"

class LinuxProcessController : public IProcessController
{
private:
	std::vector<std::string> mCommandToRun;

public:
	LinuxProcessController (std::vector<std::string> command);
	~LinuxProcessController ();

	void StartProcessAndWait ();
};