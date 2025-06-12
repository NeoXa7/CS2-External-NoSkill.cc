#pragma once

// class to get refrence object of an another class
template <typename T>
class Instance
{
public:
	static T& Get() {
		static T instance;
		return instance;
	}
};