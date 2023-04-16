//
// Created by AlmightyLin on 2023/4/15.
//

#include "VEML7700.h"
#include <iostream>

using namespace std;

int main()
{
    VEML7700 veml;
    veml.begin();

    veml.setIntegrationTime(VEML7700::als_itime_t::ALS_INTEGRATION_100ms);
    veml.setGain(VEML7700::als_gain_t::ALS_GAIN_x2);

    float lux;
    for (int i = 0; i < 10; ++i) {
      veml.getALSLux(lux);
    VEML7700::als_gain_t gain;
    VEML7700::als_itime_t itime;
    uint16_t raw_counts;
    veml.getAutoALSLux(lux, gain, itime, raw_counts);
    cout << "Current Lux: " << lux << endl;
    cout << "Gain: " << gain << endl;
    cout << "Integration Time: " << itime << endl;
    cout << "Raw Counts: " << raw_counts << endl;
    getchar();
    }
    

    return 0;
}