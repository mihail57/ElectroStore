
#ifndef DEVICE_H
#define DEVICE_H

#pragma once

#include <iostream>
#include "Containers.h"
#include "Component.h"

class Device abstract
{
protected:
	std::string name;
	std::string producer;
	std::string desc;
	int ram_size;
	int drive_size;
	uint32_t price;
	
	CPU* cp;

	Device(std::string n, std::string prod, std::string dsc, int ram, int drive, uint32_t prc, CPU* c) :
		name(n), producer(prod), desc(dsc), ram_size(ram), drive_size(drive), price(prc), cp(c) {};
	~Device() { delete cp; }
public:

	std::string get_cpu() { return cp->get_description(); }
	uint32_t get_price() { return price; }

	inline std::string get_name() { return name; }

	virtual std::string get_full_description() = 0;
	virtual std::string get_device_type() = 0;
};

class Notebook : public Device {
private:
	Videocard* vd;
public:
	Notebook(std::string n, std::string prod, std::string dsc, int ram, int drive, uint32_t prc, CPU* c, Videocard* v) :
		Device(n, prod, dsc, ram, drive, prc, c), vd(v) {};
	~Notebook() { delete vd; }

	std::string get_videocard() { return vd->get_description(); }

	virtual std::string get_device_type() { return "Notebook"; }
	virtual std::string get_full_description();
};



class MobileDevice abstract : public Device {
protected:
	std::string android_version;

	MobileDevice(std::string n, std::string prod, std::string dsc, int ram, int drive, uint32_t prc, CPU* c, std::string andr) :
		Device(n, prod, dsc, ram, drive, prc, c), android_version(andr) {};
public:

	std::string get_android_version() { return android_version; }
};

class Phone : public MobileDevice {
public:
	Phone(std::string n, std::string prod, std::string dsc, int ram, int drive, uint32_t prc, CPU* c, std::string andr) :
		MobileDevice(n, prod, dsc, ram, drive, prc, c, andr) {};

	virtual std::string get_device_type() { return "Phone"; }
	virtual std::string get_full_description();
};

class Tablet : public MobileDevice {
public:
	Tablet(std::string n, std::string prod, std::string dsc, int ram, int drive, uint32_t prc, CPU* c, std::string andr) :
		MobileDevice(n, prod, dsc, ram, drive, prc, c, andr) {};

	virtual std::string get_device_type() { return "Tablet"; }
	virtual std::string get_full_description();
};

#endif // !DEVICE_H
