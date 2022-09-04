#include "file_service.hpp"
#include <trace.hpp>
#include <iostream>

int main()
{
	at::select_tracer<at::file_service>("output.txt");

	at::trace("a block of text A");
	at::trace("a block of text B");
	at::trace("a block of text C");
	at::trace("a block of text D");

	// Unnecerasy, but needs to be tested. The later function should print out last.
	//at::void_tracer<at::file_service>("output.txt");

	std::cout << "Main thread finalized!" << std::endl;
}