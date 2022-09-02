#include <trace.hpp>
#include <iostream>

int main()
{
	at::trace("output.txt", "A log of text A");
	at::trace("output.txt", "A log of text B");
	at::trace("output.txt", "A log of text C");
	at::trace("output.txt", "A log of text D");

	std::cout << "Main thread finalized!" << std::endl;
}