#ifndef WEATHERSENSORTYPE_H
#define WEATHERSENSORTYPE_H

#include "Time.h"
#include "Date.h"

    /**
    * @author Kane Nikander
    * @version 7.5
    * @date 18/04/2017
    * @section description
    * @brief The WeatherSensorType struct represtents a variety of weather related data.
    */
struct WeatherSensorType{

        /** date */
    Date d;

        /** time */
    Time t;

        /** Dew Point Temperature */
    float DP;

        /** Wind Direction (10min Mean) 10m */
    float Dta;

        /** Wind Direction (10min SD) 10m */
    float Dts;

        /** Evaporation (Accumulated) */
    float EV;

        /** Barometric Pressure (QFE Station Elevation) */
    float QFE;

        /** Barometric Pressure (QFF Mean Sea Level) */
    float QFF;

        /** Barometric Pressure (QNH Aviation Standard) */
    float QNH;

        /** Rainfall (Accumulated) */
    float RF;

        /** Relative Humidity */
    float RH;

        /** Wind Speed (10min Mean) 10m */
    float S;

        /** Solar Radiation (10min Avg) */
    float SR;

        /** Soil Temperature (125mm depth) */
    float ST1;

        /** Soil Temperature (250mm depth) */
    float ST2;

        /** Soil Temperature (500mm depth) */
    float ST3;

        /** Soil Temperature (1000mm depth) */
    float ST4;

        /** Wind Gust Speed 10m */
    float Sx;

        /** Ambient Air Temperature 1m */
    float T;

    bool operator <( const WeatherSensorType & other ) {
        return(t < other.t);
    }

    bool operator >( const WeatherSensorType & other ) {
        return(t > other.t);
    }

    bool operator ==( const WeatherSensorType & other ) {
        return(t == other.t);
    }

};


#endif // WEATHERSENSORTYPE_H
