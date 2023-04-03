#include "myds18b20.h"

// opendir
#include <dirent.h>
#include <sys/types.h>

// regex
#include <regex>

// read file
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

Thermometer::Thermometer() {
	this->FindTempDevices();
	this->running_ = true;
	this->start();
}

void Thermometer::start() {
	t_ = std::thread(&Thermometer::ReadTemp, this);
}

void Thermometer::stop() {
	if (t_.joinable()) {
		t_.join();
	} else {
		std::cerr << "Can't joint thread!\n";
	}
}

const std::vector<double> &Thermometer::get_temp() const {
  return this->temp_;
} 

void Thermometer::ReadTemp() {
	if (this->device_files.empty()) {
		std::cerr << "Can't find any DS18B20 device directory!\n";
	}
	while (this->running_) {
		// we connect thermometers with GPIO 23 24 25 12
		for (int i = 0; i < this->device_files.size(); ++i) {
			// open temperature file
			std::ifstream finput(this->device_files[i], std::ifstream::in);
			if (!finput.is_open()) {
				std::cerr << "Can't open temperatur file!\n";
				return;
			}
			// read temperature file and record
			std::string tmp_temp;
			if (getline(finput, tmp_temp)) {
				if (this->temp_.size() == this->device_files.size()) {
					// cast type from string to double
					this->temp_[i] = std::stod(tmp_temp) * 1.0 / 1000;
				} else {
					this->temp_.push_back(std::stod(tmp_temp));
				}
			}
			// close temperature file
			finput.close();
		}
	}
}

// find and record thermometer files
const std::vector<std::string> Thermometer::FindTempDevices() {
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
		std::cout << subpath->d_name << std::endl;
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

	if (this->device_files.empty()) {
		std::cerr << "Can't find any DS18B20 device directory!\n";
	}
	// Return the whole device directories
  return this->device_files;
}

Thermometer::~Thermometer() {
	this->running_ = false;
	this->stop();
}

