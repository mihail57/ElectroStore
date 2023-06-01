
#ifndef ORDER_H
#define ORDER_H

#pragma once

#include <iostream>
#include "Device.h"

struct Order
{
private:
	List<Pair<Device*, int>> devices;

	uint32_t total_price;
public:
	Order() { total_price = 0; };
	Order(const Order& o) : devices(o.devices) { total_price = o.total_price; };

	inline void add_to_order(Device* d, int count) {
		Pair<Device*, int> p(d, count);
		devices.push_back(p);
		total_price += d->get_price() * count;
	}
	inline uint32_t get_total_price() { return total_price; }
	inline int32_t count() { return devices.size(); }

	inline Pair<Device*, int>& get(int32_t index) { return devices.get(index); }
	inline void remove(int32_t index) { 
		auto t = devices.remove(index); 
		total_price -= t.first->get_price() * t.second;
	}

	friend std::ostream& operator<<(std::ostream& str, Order& o);
};

#endif // !ORDER_H

