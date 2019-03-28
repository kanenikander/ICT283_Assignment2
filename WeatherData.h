#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <map>
#include "BST.h"
#include "Extractor.h"
#include "Date.h"
#include "Time.h"
#include "WeatherSensorType.h"

typedef BST<WeatherSensorType> WeatherBST;

typedef map<int,WeatherBST> DayMap;
typedef map<int,DayMap> MonthMap;
typedef map<int,MonthMap> YearMap;

typedef DayMap::iterator DayMapItr;
typedef MonthMap::iterator MonthMapItr;
typedef YearMap::iterator YearMapItr;

    /**
    * @author Kane Nikander
    * @version 2.6
    * @date 21/05/2018
    * @section description
    * @brief The WeatherData class represents an accumulation of WeatherSensorType data organised by date.
    */
class WeatherData
{

    private:
            /** All weather data */
        YearMap weatherMap;

            /** Currently extracted weather data */
        vector<WeatherSensorType> weatherVector;

    public:

            /**
            * @brief A constructor.
            * Construct a blank weather data object with no parameters.
            */
        WeatherData();

            /**
            * @brief Add a row of weather data.
            * Inserts an instance of WeatherSensorType sorted by date.
            * @param WeatherSensorType dataRow
            * @return void
            */
        void Insert(WeatherSensorType dataRow);

            /**
            * @brief Returns vector of weather data of a year.
            * Returns vector of WeatherSensorType objects of a specified year.
            * @param int year
            * @return vector<WeatherSensorType>&
            */
        vector<WeatherSensorType>& GetByYear(int year);

            /**
            * @brief Returns vector of weather data of a month and year.
            * Returns vector of WeatherSensorType objects of a specified month and year.
            * @param int month, int year
            * @return vector<WeatherSensorType>&
            */
        vector<WeatherSensorType>& GetByMonth(int month,int year);

            /**
            * @brief Returns vector of weather data of a day, month and year.
            * Returns vector of WeatherSensorType objects of a specified day, month and year.
            * @param int day, int month, int year
            * @return vector<WeatherSensorType>&
            */
        vector<WeatherSensorType>& GetByDay(int day,int month,int year);

};

#endif // WEATHERDATA_H
