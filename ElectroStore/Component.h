
#ifndef COMPONENT_H
#define COMPONENT_H

#pragma once

#include <iostream>
#include <string>

class Component
{
protected:
	std::string name;
	Component(std::string n) { name = n; }
public:
	virtual std::string get_description() = 0;
};

class Videocard : public Component {
private:
	uint32_t video_mem;
public:
	Videocard(std::string n, uint32_t v) : Component(n), video_mem(v) {};
	virtual std::string get_description();
};

class CPU : public Component {
	uint32_t clock_rate;
public:
	CPU(std::string n, uint32_t c) : Component(n), clock_rate(c) {};
	virtual std::string get_description();
};


#endif // !COMPONENT_H

