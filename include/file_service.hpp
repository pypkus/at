#pragma once

#include <queue>
#include <fstream>

#include "service.hpp"

namespace at
{
	class file_service : public service
	{
	public:
		file_service(const std::string& destination);
		~file_service();
		void add(const std::string& message);
		void send(const std::string& message);

	private:
		bool job_available();
		std::string get_job();

		std::queue<std::string> m_messages;
		std::fstream m_destination;
	};
}