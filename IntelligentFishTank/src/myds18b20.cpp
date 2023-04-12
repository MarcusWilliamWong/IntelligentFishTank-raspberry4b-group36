#include "myds18b20.h"
#include "heater.h"
// opendir
#include <dirent.h>
#include <sys/types.h>
// regex
#include <regex>
// read file
#include <iostream>
#include <fstream>
#include <thread>

Thermometer::Thermometer() : running_(true), heater_ptr_(nullptr) {
	FindTempDevices();
}

void Thermometer::registerHeater(Heater *heater_ptr) {
	heater_ptr_ = heater_ptr;
}

void Thermometer::ReadAllTemp() {
	if (device_files_.empty()) {
		std::cerr << "Can't find any DS18B20 device directory!\n";
	}
	
	while (running_) {
		int index = 0;
		for (const auto &fileName : device_files_) {
			std::ifstream finput(fileName, std::ifstream::in);
			// open fail
			if (!finput.is_open()) {
				std::cerr << "Can't open temperatur file!\n";
				return;
			}
			// read temperature file and record
			std::string tmp_temp;
			if (getline(finput, tmp_temp)) {
				// cast type from string to double
				double t = std::stod(tmp_temp) * 1.0 / 1000;
				if (tempers_.size() == device_files_.size()) {
					tempers_[index] = t;
					// return 4 temperatures
					heater_ptr_->ProcessTempers(tempers_);
				} else {
					tempers_.push_back(t);
				}
				++index;
			}
			// close temperature file
			finput.close();
		}
	}
}

// find and record thermometer files
const std::vector<std::string> &Thermometer::FindTempDevices() {
	// open devices directory
	const char* dirname = "/sys/bus/w1/devices";
	DIR* dir = nullptr;
	if(!(dir = opendir(dirname))) {
		std::cerr << "Opendir error!\n";
	}
	dirent* subpath = nullptr;
	//tmp variable to save device file name
  std::string filename;
	while ((subpath = readdir(dir))) {
		// std::cout << subpath->d_name << std::endl;
		// // find directory beginning with "28-"
		std::string pattern("^28-.*$");
		std::regex reg(pattern);
		// match
		if (std::regex_match(subpath->d_name, reg)) {
			filename = static_cast<const std::string>(dirname) 
							+ '/' + static_cast<const std::string>(subpath->d_name)
							+ "/temperature";
			// std::cout << filename << std::endl;
			device_files_.push_back(filename);
		}
	}
	closedir(dir);

	// Return the whole device directories
  return device_files_;
}

void Thermometer::turnOn() {
	running_ = true;
	ReadAllTemp();
}

void Thermometer::turnOff() {
	running_ = false;
}

// const std::vector<double> &Thermometer::get_temp() const{
//   return tempers_;
// }

// const std::vector<std::string> &Thermometer::get_dev() const{
	// return device_files;
// } 
