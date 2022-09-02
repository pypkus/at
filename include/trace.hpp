#pragma once

#include "file_service.hpp"

namespace at
{
	template <typename TService = file_service>
	static void trace(const std::string& destination, const std::string& message)
	{
		static TService service(destination);
		service.add(message);
	}
}