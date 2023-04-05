#include "myds18b20.h"
// opendir
#include <dirent.h>
#include <sys/types.h>
// regex
#include <regex>
// read file
#include <iostream>
#include <fstream>
#include <thread>

Thermometer::Thermometer() {
	this->tc = nullptr;
	this->FindTempDevices();
}

void Thermometer::registerCallback(ThermoCallback *tc) {
	this->tc = tc;
}

// const std::vector<double> &Thermometer::get_temp() const{
//   return this->tempers_;
// }

// const std::vector<std::string> &Thermometer::get_dev() const{
	// return this->device_files;
// } 

void Thermometer::ReadAllTemp() {
	if (this->device_files.empty()) {
		std::cerr << "Can't find any DS18B20 device directory!\n";
	}
	
	this->running_ = true;
	while (this->running_) {
		int index = 0;
		for (const auto &fileName : this->device_files) {
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
				if (this->tempers_.size() == this->device_files.size()) {
					(this->tempers_)[index] = t;
				} else {
					this->tempers_.push_back(t);
				}
				++index;
			}
			// close temperature file
			finput.close();
		}
		// get temperatures
		tc->hasTemperature(this->tempers_);
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
			this->device_files.push_back(filename);
		}
	}
	closedir(dir);

	// Return the whole device directories
  return this->device_files;
}

void Thermometer::start() {
	// std::cout << "start\n";
	// std::cout << std::thread::hardware_concurrency() << std::endl;
	t_ = std::thread(&Thermometer::ReadAllTemp, this);
	// this->ReadTemp();
}

void Thermometer::stop() {
	this->running_ = false;
	if (t_.joinable()) {
		t_.join();
	} else {
		std::cerr << "Can't joint thread!\n";
	}
}

