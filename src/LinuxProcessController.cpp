#include "LinuxProcessController.h"

LinuxProcessController::LinuxProcessController (std::vector<std::string> command)
{
	mCommandToRun = command;
}

LinuxProcessController::~LinuxProcessController ()
{

}

void LinuxProcessController::StartProcessAndWait ()
{
	// If the command executes successfully then do nothing
	// Otherwise throw an exception to signify something went wrong.
}