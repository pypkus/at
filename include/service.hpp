#pragma once

#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace at
{
	// Note: Design of this implementation allows it to be expandable in case
	// other features, such as non-blocking trace output to Serial, over
	// network TCP or other protocols are required.

	// This class should be a base for other implementations, such as Serial, 
	// Network over TCP or UDP or other protocols.
	// 
	// Some services may work entirely asynchronously depending on user needs,
	// but will yield unordered data. For system logs it probably wise to have
	// logs in order. Most services are required to maintain output order as 
	// they are called in user code.
	// 
	// For example if we call send_message function with data "A", "B", "C", "D",
	// then the output to a destination must be "ABCD", that would be ordered.
	// Unordered would look like "CABD".
	// 
	// Note: Consider making worker wrapper for ordered and unordered data (trait?).
	// In some cases unordered data may execute faster.
	// Note: Consider a possibility to send not only std::string data, but
	// different data as well. Perhaps use wrapper with std::any for that like in
	// my other project https://github.com/pypkus/aset.
	class service
	{
	public:
		service();

		virtual void add(const std::string& message) = 0;
		virtual void send(const std::string& message) = 0;

	protected:
		virtual bool job_available() = 0;
		virtual std::string get_job() = 0;

		void shutdown();
		void notify();
	private:

		void work();
		void give_task(std::function<void()>& wrap);

		std::condition_variable m_cv;
		std::thread m_thread;
		std::mutex m_mutex;
		bool m_shutdown = false;
	};
}