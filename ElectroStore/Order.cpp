#include "Order.h"

std::string Order::print() {
	std::string result = "";
	int i = 1;
	if (devices.size() > 0) {
		for (auto iter = devices.begin(); iter != devices.end(); iter++) {
			result += std::to_string(i++) + ") Device type: " + iter->first->get_device_type() + ", name: " + iter->first->get_name();
			result += ", amount: " + std::to_string(iter->second) + '\n';
		}
		result += "Total price: " + std::to_string(total_price) + " rubles\n";
	}
	else result = "<empty>";
	return result;
}