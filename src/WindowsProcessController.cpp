#include "WindowsProcessController.h"

WindowsProcessController::WindowsProcessController (std::vector<std::string> command)
{
	mCommandToRun = command;
}

WindowsProcessController::~WindowsProcessController ()
{

}

void WindowsProcessController::StartProcessAndWait ()
{
	// If the process has started successfully then return nothing
	// Otherwise throw an exception signifying something went wrong.
}