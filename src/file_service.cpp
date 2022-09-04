#include "file_service.hpp"

#include <iostream>
#include <string>

namespace at
{
	bool file_service::job_available()
	{
		return !m_messages.empty();
	}

	std::string file_service::get_job()
	{
		if (job_available())
		{
			std::string result = m_messages.front();
			m_messages.pop();

			return result;
		}

		return "";
	}

	file_service::file_service(const std::string& destination) : m_dest_name(destination)
	{
		m_destination.open(destination, std::fstream::out);
	}

	file_service::~file_service()
	{
		shutdown();
		m_destination.close();
	}

	void file_service::add(const std::string& message)
	{
		m_messages.push(message);
		// Must notify worker about new job.
		notify();
	}

	void file_service::send(const std::string& message)
	{
		// Note: It probably would be better to use faster file IO methods
		// but is kept like this for simplicity.
		if (m_destination.is_open())
		{
			std::cout << message << std::endl;
			m_destination << message << std::endl;
		}
	}

	std::string file_service::get_name()
	{
		return m_dest_name;
	}
}