#include "Order.h"

std::ostream& operator<<(std::ostream& str, Order& o) {
	std::string result = "";
	int i = 1;
	if (o.devices.size() > 0) {
		for (auto iter = o.devices.begin(); iter != o.devices.end(); iter++) {
			result += std::to_string(i++) + ") Device type: " + iter->first->get_device_type() + ", name: " + iter->first->get_name();
			result += ", amount: " + std::to_string(iter->second) + '\n';
		}
		result += "Total price: " + std::to_string(o.total_price) + " rubles\n";
	}
	else result = "<empty>";
	str << result;
	return str;
}