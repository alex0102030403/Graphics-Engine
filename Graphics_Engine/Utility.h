#pragma once

#include <deque>
#include <string>
#include <vector>

class Utility
{

public:

	static void ParseString(std::string& string,
		std::vector<std::string>& subStrings, char token);

	static void AddMessage(const std::string& message);
	static std::string ReadMessage();

private:

	static std::deque<std::string> s_messages;

};