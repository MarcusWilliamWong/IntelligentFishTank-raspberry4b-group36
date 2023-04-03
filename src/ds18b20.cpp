#include "ds18b20_.h"

// opendir
#include <dirent.h>
#include <sys/types.h>

// regex
#include <regex>

// read file
#include <string>
#include <iostream>
#include <fstream>

Thermometer::Thermometer() {
  this->ReadTemp();
}

double Thermometer::get_temp() const {
  return this->temp_;
} 

bool Thermometer::ReadTemp() {
  std::string devdir;
  if ((devdir = FindTempDevices()).empty()) {
    std::cerr << "Can't find temperature devices\n";
  }
  // GPIO 23 24 25 12
  // open temperature file
  std::string device_file(devdir + "/temperature");
  std::ifstream finput(device_file, std::ifstream::in);
  if (!finput.is_open()) {
    std::cerr << "Can't open temperatur file\n";
    return false;
  }

  // read temperature file and record
  std::string tmp_temp;
  if (getline(finput, tmp_temp)) {
    // cast type from string to double
    this->temp_ = std::stod(tmp_temp) * 1.0 / 1000;
    return true;
  } else {
    std::cerr << "Temperature file is empty!\n";
    return false;
  }
}

std::string Thermometer::FindTempDevices() {
	// open devices directory
	const char* dirname = "/sys/bus/w1/devices";
	// const char* dirname = "D:/Desktop/2_PGT/2 term/Big Data/lecture";
	// const char* dirname = "D:/Desktop/2_PGT";
	
	DIR* dir = nullptr;
	if(!(dir = opendir(dirname))) {
		std::cerr << "Opendir error!\n";
	}
	dirent* subpath = nullptr;
  std::string devdir;
	while ((subpath = readdir(dir))) {
		std::cout << subpath->d_name << std::endl;
		// find DS18B20 directory
		std::string pattern("^28-.*$");
		std::regex reg(pattern);
		// match
		if (std::regex_match(subpath->d_name, reg)) {
			devdir = static_cast<const std::string>(dirname) 
														+ '/' + static_cast<const std::string>(subpath->d_name);
			// std::cout << devdir << std::endl;
      return devdir;
		} else {
			std::cerr << "Can't find DS18B20 device directory!\n";
		}
	}

  return devdir;
	// const std::string fp{dirname};
	// std::ifstream finput(fp);
}

