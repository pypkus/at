#include "service.hpp"
#include <iostream>

namespace at 
{
	service::service()
	{
		m_thread = std::thread(&service::work, this);
	}

	void service::notify()
	{
		m_cv.notify_one();
	}

	void service::shutdown()
	{
		m_shutdown = true;
		notify();
		m_thread.join();
	}

	void service::work()
	{
		while (true)
		{
			std::unique_lock<std::mutex> ul(m_mutex);
			while (!m_shutdown && !job_available()) 
			{
				m_cv.wait(ul);
			}

			if (!job_available())
			{
				// Note: this code will execute when service object
				// destructor is called
				std::cout << "Worker thread finalized" << std::endl;
				return;
			}

			send(get_job());
		}
	}

	void service::give_task(std::function<void()>& wrap)
	{
		std::unique_lock<std::mutex> ul(m_mutex);
		wrap();
		m_cv.notify_one();
	}
}