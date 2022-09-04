#pragma once

#include "file_service.hpp"
#include <memory>
#include <utility>
#include <vector>

namespace at
{
	// TODO: Implement callback routine where if error occurs, user is warned.

	// Intended to be static singleton
	template <typename TService>
	class trace_manager
	{
	public:
		using const_message = const std::string;
		using const_destination = const std::string;

		trace_manager() = default;
		trace_manager(const trace_manager&) = delete;
    	trace_manager & operator=(const trace_manager&) = delete;

		static trace_manager& get_instance();

		void forward_message(const_message& message);

		bool select_stream(const_destination& destination_name);
		void create_stream(const_destination& destination_name);
		void void_stream(const_destination& destination_name);

	private:
		std::shared_ptr<TService> m_selected_service;
		std::vector<std::shared_ptr<TService>> m_stream_services;
	};

	template <typename TService>
	trace_manager<TService>& trace_manager<TService>::get_instance()
	{
		static trace_manager tm;
		return tm;
	}

	template <typename TService>
	void trace_manager<TService>::forward_message(const_message& message)
	{
		if(m_selected_service)
		{
			m_selected_service->add(message);
		}

		// TODO: No service is selected, should warn user by callback.
	}

	template <typename TService>
	bool trace_manager<TService>::select_stream(const std::string& destination_name)
	{
		for(auto& i : m_stream_services)
		{
			if(i->get_name() == destination_name)
			{
				m_selected_service = i;
				return true;
			}
		}

		return false;
	}

	template <typename TService>
	void trace_manager<TService>::create_stream(const std::string& destination_name)
	{
		std::shared_ptr<TService> service = std::make_shared<TService>(destination_name);
		m_stream_services.emplace_back(std::move(service));
	}

	template <typename TService>
	void trace_manager<TService>::void_stream(const std::string& destination_name)
	{
		for(auto& i : m_stream_services)
		{
			if(i->get_name() == destination_name)
			{
				i.reset();

				if(m_selected_service->get_name() == destination_name)
				{
					m_selected_service.reset();
				}

				return;
			}
		}

		// No stream was found, continue...
	}

	// TODO: Find a way to make all this thread-safe. Logging should be available everywhere.

	// If tracer did not complete it's task, it will be a blocking function.
	template <typename TService>
	static void void_tracer(const std::string& destination)
	{
		trace_manager<TService>& tm = trace_manager<TService>::get_instance();
		tm.void_stream(destination);
	}

	template <typename TService>
	static void select_tracer(const std::string& destination)
	{
		trace_manager<TService>& tm = trace_manager<TService>::get_instance();
		if(!tm.select_stream(destination))
		{
			tm.create_stream(destination);
			if(!tm.select_stream(destination))
			{
				// TODO: If code approaches here, then stream failed to create.
				// must be reported by a callback function.
			}
		}

		// TODO: If code approaches here, no stream was found. Must report to user
		// by a callback function.
	}

	template <typename TService = file_service>
	static void trace(const std::string& message)
	{
		trace_manager<TService>& tm = trace_manager<TService>::get_instance();
		tm.forward_message(message);
		// In case no service is selected, ideally should report. Not implemented yet. 
	}
}