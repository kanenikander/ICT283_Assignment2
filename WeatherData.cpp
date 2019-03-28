#include "WeatherData.h"

WeatherData::WeatherData() {

}

void WeatherData::Insert(WeatherSensorType dataRow) {

    Date newDate = dataRow.d;
    Time newTime = dataRow.t;

    if(weatherMap.find(newDate.GetYear()) != weatherMap.end()) { //if year is not in map

        if(weatherMap.at(newDate.GetYear()).find(newDate.GetMonth()) != weatherMap.at(newDate.GetYear()).end()) { //if month is not in map

            if(weatherMap.at(newDate.GetYear()).at(newDate.GetMonth()).find(newDate.GetDay()) != weatherMap.at(newDate.GetYear()).at(newDate.GetMonth()).end()) { //if day is not in map

                weatherMap.at(newDate.GetYear()).at(newDate.GetMonth()).at(newDate.GetDay()).Insert(dataRow);

            } else {

                WeatherBST tempBST;
                tempBST.Insert(dataRow);
                weatherMap.at(newDate.GetYear()).at(newDate.GetMonth()).insert(make_pair(newDate.GetDay(),tempBST));

            }

        } else {

            WeatherBST tempBST;
            tempBST.Insert(dataRow);
            DayMap dm;
            dm.insert(make_pair(newDate.GetDay(),tempBST));
            weatherMap.at(newDate.GetYear()).insert(make_pair(newDate.GetMonth(),dm));

        }

    } else {

        WeatherBST tempBST;
        tempBST.Insert(dataRow);
        DayMap dm;
        dm.insert(make_pair(newDate.GetDay(),tempBST));
        MonthMap mm;
        mm.insert(make_pair(newDate.GetMonth(),dm));
        weatherMap.insert(make_pair(newDate.GetYear(),mm));

    }

}

vector<WeatherSensorType>& WeatherData::GetByYear(int year) {
    weatherVector.clear();

    if(weatherMap.find(year) != weatherMap.end()) { //if selected year exists
        YearMapItr i = weatherMap.find(year); //for that year
        for(MonthMapItr j = i->second.begin(); j != i->second.end(); j++) { //for each month
            for(DayMapItr k = j->second.begin(); k != j->second.end(); k++) { //for each day
                Extractor<WeatherSensorType> tempExt;
                k->second.PreOrder(tempExt.GetData);
                for(int l=0; l<tempExt.size(); l++) {
                    weatherVector.push_back(tempExt[l]); //collect data
                }
                tempExt.clear();
            }
        }
    }

    return weatherVector;
}

vector<WeatherSensorType>& WeatherData::GetByMonth(int month,int year) {
    weatherVector.clear();

    if(weatherMap.find(year) != weatherMap.end()) { //if selected year exists
        if(weatherMap.at(year).find(month) != weatherMap.at(year).end()) { //if selected month exists
            MonthMapItr i = weatherMap.at(year).find(month); //for that month
            for(DayMapItr j = i->second.begin(); j != i->second.end(); j++) { //for each day
                Extractor<WeatherSensorType> tempExt;
                j->second.InOrder(tempExt.GetData);
                for(int k=0; k<tempExt.size(); k++) {
                    weatherVector.push_back(tempExt[k]); //collect data
                }
                tempExt.clear();
            }

        }
    }

    return weatherVector;
}

vector<WeatherSensorType>& WeatherData::GetByDay(int day,int month,int year) {
    weatherVector.clear();

    if(weatherMap.find(year) != weatherMap.end()) { //if selected year exists
        if(weatherMap.at(year).find(month) != weatherMap.at(year).end()) {//if selected month exists
            if(weatherMap.at(year).at(month).find(day) != weatherMap.at(year).at(month).end()) { //if selected day exists
                DayMapItr i = weatherMap.at(year).at(month).find(day); //for that day
                Extractor<WeatherSensorType> tempExt;
                i->second.InOrder(tempExt.GetData);
                for(int j=0; j<tempExt.size(); j++) {
                    weatherVector.push_back(tempExt[j]); //collect data
                }
                tempExt.clear();
            }
        }
    }

    return weatherVector;
}


