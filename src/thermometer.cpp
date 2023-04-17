/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
// opendir
#include <dirent.h>
#include <sys/types.h>
// regex
#include <regex>
// read file
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "config.h"
#include "thermometer.h"
#include "heater.h"

Thermometer::Thermometer() : running_(true) {
	FindTempDevices();
}

Thermometer::~Thermometer() {
	if (running_) {
		this->stop(); 
	}
}

void Thermometer::registerHeater(std::shared_ptr<Heater> &heater_ptr) {
	heater_ptr_ = heater_ptr;
}

void Thermometer::stop() {
	device_files_.clear();
	running_ = false;
}

void Thermometer::AutoControlHeater() {
	if (device_files_.empty()) {
		throw std::runtime_error("fail to find any DS18B20 device directory!");
	}
	
	while (running_) {
		int index = 0;
		for (auto fileName : device_files_) {
			std::ifstream finput(fileName, std::ifstream::in);
			// fail to open
			if (!finput.is_open()) {
				throw std::runtime_error("fail to open temperatur files!");
			}
			// read temperature file and record data
			std::string tmp_temp;
			if (getline(finput, tmp_temp)) {
				// cast type from string to double
				double t = std::stod(tmp_temp) * 1.0 / 1000;
				// if read t = 0, means thermometer not finish initialise
				if (!t) { break; }
				#ifdef DEBUG_THERMOMETER
				std::cout << "temps current size : " << tempers_.size() << std::endl;
				std::cout << "temperatur files size : " << device_files_.size() << std::endl;
				#endif
				if (tempers_.size() == device_files_.size()) {
					tempers_[index] = t;
					// callback function from `Class Heater`
					// conditiaonally turnOn&Off
					heater_ptr_->ConditionalOnOff(tempers_);
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
void Thermometer::FindTempDevices() {
	// open devices directory
	/*
	 * it's convenient to use raw point when using function `opendir` and `readdir`
	*/
	DIR* dir = nullptr;
	if(!(dir = opendir(app_config::THERMOMETER_DEV_PATH.c_str()))) {
		throw std::runtime_error("failed to opendir!");
	}
	// search valid files in dev directory
	// for using function `readdir`, need a raw ptr
	dirent* subpath = nullptr;
	//tmp variable to save device file name
  std::string filename;
	while ((subpath = readdir(dir))) {
		// std::cout << subpath->d_name << std::endl;
		// find directory beginning with "28-"
		std::string pattern("^28-.*$");
		std::regex reg(pattern);
		// match
		if (std::regex_match(subpath->d_name, reg)) {
			filename = app_config::THERMOMETER_DEV_PATH
								+ '/' + static_cast<const std::string>(subpath->d_name)
								+ "/temperature";
			device_files_.push_back(filename);
			// break;  // more than one thermometer
		}
	}
	closedir(dir);
}


// Test only
#ifdef DEBUG_THERMOMETER
// const std::vector<double> &Thermometer::get_temps() const{
//   return tempers_;
// }

// const std::vector<std::string> &Thermometer::get_dev() const{
// 	return device_files_;
// } 
#endif