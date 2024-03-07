#include "Utility.h"

std::deque<std::string> Utility::s_messages;

void Utility::ParseString(std::string& string, std::vector<std::string>& subStrings, char token)
{
	size_t start = 0;
	size_t end = 0;

	while (end != std::string::npos)
	{
		end = string.find(token, start);
		if ((end - start) > 0)
		{
			subStrings.push_back(string.substr(start, end - start));
		}
		start = end + 1;
	}
}

void Utility::AddMessage(const std::string& message)
{
	s_messages.push_front(message);
}

std::string Utility::ReadMessage()
{
	if (!s_messages.empty())
	{
		auto message = s_messages.back();
		s_messages.pop_back();
		return message;
	}

	return std::string();
}