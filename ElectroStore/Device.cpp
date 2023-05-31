#include "Device.h"

std::string Notebook::get_full_description() {
	std::string result = "Notebook name: " + this->name + "\nProducer: " + this->producer;
	result += "\nRAM size: " + std::to_string(this->ram_size) + "GB\nDrive size: " + std::to_string(this->drive_size) + "GB";
	result += "\nPrice: " + std::to_string(price) + " rubles\n";
	result += this->get_cpu() + '\n' + this->get_videocard() + '\n';
	if(!this->desc.empty()) result += this->desc + '\n';
	return result;
}

std::string Phone::get_full_description() {
	std::string result = "Phone name: " + this->name + "\nProducer: " + this->producer;
	result += "\nRAM size: " + std::to_string(this->ram_size) + "GB\nDrive size: " + std::to_string(this->drive_size) + "GB";
	result += "\nPrice: " + std::to_string(price) + " rubles\n" + this->get_cpu() + '\n';
	result += "Android version: " + this->android_version + '\n';
	if (!this->desc.empty()) result += this->desc + '\n';
	return result;
}

std::string Tablet::get_full_description() {
	std::string result = "Tablet name: " + this->name + "\nProducer: " + this->producer;
	result += "\nRAM size: " + std::to_string(this->ram_size) + "GB\nDrive size: " + std::to_string(this->drive_size) + "GB";
	result += "\nPrice: " + std::to_string(price) + " rubles\n" + this->get_cpu() + '\n';
	result += "Android version: " + this->android_version + '\n';
	if (!this->desc.empty()) result += this->desc + '\n';
	return result;
}