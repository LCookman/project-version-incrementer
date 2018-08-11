#pragma once

#include <string>

class IProcessController
{
public:
	virtual ~IProcessController () {};
	virtual void StartProcessAndWait () = 0;
};