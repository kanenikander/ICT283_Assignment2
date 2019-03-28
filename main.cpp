#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "WeatherSensorType.h"
#include "WeatherData.h"
#include "Time.h"
#include "Date.h"

istream & operator >>(istream &input, WeatherData &WD);
ostream & operator <<(ostream &os, const Date &D);
ostream & operator <<(ostream &os, const Time &T);

void Method1(WeatherData &WD);
void Method2(WeatherData &WD);
void Method3(WeatherData &WD);
void Method4(WeatherData &WD, ofstream &ofile);
void Method5(WeatherData &WD);

string ConvertMonthToString(unsigned m);
float RoundToDecimal(float num, int decimalPlace);
int CheckOccurrenceOfChar(string text, char character);
string GetStringFromDelimiter(unsigned pos, char delimiter, string text);
float CovertFromWm2ToKWhm2(float wm2);

int main()
{
    WeatherData WD;

    ifstream infilelist("data/met_index.txt");
    string fileName = "";
    while(getline(infilelist,fileName)) {
        fileName = "data/" + fileName;
        ifstream infile(fileName.c_str());
        infile >> WD;
        infile.close();
    }
    infilelist.close();

    string input;
    do {

        cout << '\n' << "WEATHER LOG PROGRAM" << endl;
        cout << " 1. Average wind speed and average temperature for a specified month and year." << endl;
        cout << " 2. Average wind speed and average ambient air temperature for each month of a specified year." << endl;
        cout << " 3. Total solar radiation in kWh/m2 for each month of a specified year." << endl;
        cout << " 4. Average wind speed (km/h), average ambient air temperature and total solar radiation in" << '\n' << "    kWh/m2 for each month of a specified year." << endl;
        cout << " 5. Times for the highest solar radiation in kWh/m2 of a specified date." << endl;
        cout << " 6. Exit the program." << endl;

        cout << '\n' << "Enter one of the above numbers to perform its operation: ";
        cin >> input;

        if(input == "1") {
            Method1(WD);
        } else if(input == "2") {
            Method2(WD);
        } else if(input == "3") {
            Method3(WD);
        } else if(input == "4") {
            ofstream ofile("WindTempSolar.csv");
            Method4(WD,ofile);
            ofile.close();
        } else if(input == "5") {
            Method5(WD);
        } else if(input != "6") {
            cout << '\n' << "You have not made a valid selection." << endl;
        }

    } while(input != "6");

    return 0;
}

ostream &operator <<(ostream &os, const Date &D) {

    if(D.GetDay() == 0 && D.GetMonth() == 0 && D.GetYear() == 0) {
        os << "-/-/-";
    } else {
        os << D.GetDay() << "/" << D.GetMonth() << "/" << D.GetYear();
    }

    return os;
}

ostream &operator <<(ostream &os, const Time &T) {

    if(T.GetHours() == 24 && T.GetMinutes() == 60) { //fix with invalid time later

        os << "--:--";

    } else {

        //output hours
        if(T.GetHours() < 10) {
            os << "0" << T.GetHours();
        } else {
            os << T.GetHours();
        }

        os << ":";

        //output minutes
        if(T.GetMinutes() < 10) {
            os << "0" << T.GetMinutes();
        } else {
            os << T.GetMinutes();
        }

    }

    return os;
}

istream &operator >>(istream &input, WeatherData &WD) {

    string line;
    while(getline(input,line)) {

        if(line != "" && CheckOccurrenceOfChar(line,',') == 17) {

            bool valid = true;

            //Date and Time
            string tempData = GetStringFromDelimiter(1,',',line);

            //Date
            string tempDate = GetStringFromDelimiter(1,' ',tempData);
            string tempDay = GetStringFromDelimiter(1,'/',tempDate);
            string tempMonth = GetStringFromDelimiter(2,'/',tempDate);
            string tempYear = GetStringFromDelimiter(3,'/',tempDate);
            Date d(atoi(tempDay.c_str()),atoi(tempMonth.c_str()),atoi(tempYear.c_str()));
            if(d.GetDay() == 0 && d.GetMonth() == 0 && d.GetYear() == 0) {
                valid = false;
            }

            //Time
            string tempTime = GetStringFromDelimiter(2,' ',tempData);
            string tempHours = GetStringFromDelimiter(1,':',tempTime);
            string tempMinutes = GetStringFromDelimiter(2,':',tempTime);
            int hours = atoi(tempHours.c_str());
            int minutes = atoi(tempMinutes.c_str());
            if(hours == 0) {
                if(tempHours != "0" && tempHours != "00") {
                    valid = false;
                }
            }
            if(minutes == 0) {
                if(tempMinutes != "0" && tempMinutes != "00") {
                    valid = false;
                }
            }
            Time t(hours,minutes);
            if(t.GetHours() == 24 && t.GetMinutes() == 60) {
                valid = false;
            }

            //DP
            string tempLine = line.substr(line.find(",")+1,line.length());
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float DP = atof(tempData.c_str());
            if(DP == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //DTa
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float Dta = atof(tempData.c_str());
            if(Dta == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //Dts
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float Dts = atof(tempData.c_str());
            if(Dts == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //EV
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float EV = atof(tempData.c_str());
            if(EV == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //QFE
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float QFE = atof(tempData.c_str());
            if(QFE == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //QFF
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float QFF = atof(tempData.c_str());
            if(QFF == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //QNH
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float QNH = atof(tempData.c_str());
            if(QNH == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //RF
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float RF = atof(tempData.c_str());
            if(RF == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //RH
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float RH = atof(tempData.c_str());
            if(RH == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //S
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float S = atof(tempData.c_str());
            if(S == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //SR
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float SR = atof(tempData.c_str());
            if(SR == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //ST1
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float ST1 = atof(tempData.c_str());
            if(ST1 == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //ST2
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float ST2 = atof(tempData.c_str());
            if(ST2 == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //ST3
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float ST3 = atof(tempData.c_str());
            if(ST3 == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //ST4
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float ST4 = atof(tempData.c_str());
            if(ST4 == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //Sx
            tempData = tempLine.substr(0,tempLine.find(","));
            tempLine = tempLine.substr(tempLine.find(",")+1,tempLine.length());
            float Sx = atof(tempData.c_str());
            if(Sx == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            //T
            tempData = tempLine.substr(0,tempLine.length());
            float T = atof(tempData.c_str());
            if(T == 0) {
                if(tempData != "0") {
                    valid = false;
                }
            }

            if(valid) {
                WeatherSensorType tempWST;

                tempWST.d = d;
                tempWST.t = t;
                tempWST.DP = DP;
                tempWST.Dta = Dta;
                tempWST.Dts = Dts;
                tempWST.EV = EV;
                tempWST.QFE = QFE;
                tempWST.QFF = QFF;
                tempWST.QNH = QNH;
                tempWST.RF = RF;
                tempWST.RH = RH;
                tempWST.S = S;
                tempWST.SR = SR;
                tempWST.ST1 = ST1;
                tempWST.ST2 = ST2;
                tempWST.ST3 = ST3;
                tempWST.ST4 = ST4;
                tempWST.Sx = Sx;
                tempWST.T = T;

                WD.Insert(tempWST);
            }
        }
    }
    return input;
}

//The average wind speed and average temperature
//for a specified month and year. (print on screen only)
//EXAMPLE:
//January 1905: 5.5 km/h, 25.5 degrees C
void Method1(WeatherData &WL) {

    Date tempDate;
    string input;

    cout << '\n' << "Enter month and year (MM/YYYY): ";
    cin >> input;

    int month = atoi(GetStringFromDelimiter(1,'/',input).c_str());
    int year = atoi(GetStringFromDelimiter(2,'/',input).c_str());

    if(month != 0 && year != 0) {

        vector<WeatherSensorType> tempVector = WL.GetByMonth(month,year);

        float SSum = 0; //wind speed
        float TSum = 0; //temperature
        int count = 0;

        for(int i=0; i<tempVector.size(); i++) {
            SSum += tempVector.at(i).S;
            TSum += tempVector.at(i).T;
            count++;
        }

        if(count != 0) {
            cout << '\n' << ConvertMonthToString(month) << " "
            << year << ": "
            << RoundToDecimal((SSum/count)*3.6,1) << " km/h, "
            << RoundToDecimal(TSum/count,1) << " degrees C"
            << endl;
        } else {
            cout << '\n' << ConvertMonthToString(month) << " "
            << year << ": " << "No Data" << endl;
        }
    } else {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }

}

//Average wind speed and average ambient air temperature
//for each month of a specified year. (print on screen only)
//EXAMPLE:
//1905
//January: 5.5 km/h, 25.5 degrees C
//February: 4.5 km/h, 27.5 degrees C
//...
void Method2(WeatherData &WL) {

    Date tempDate;
    string input;

    cout << '\n' << "Enter year (YYYY): ";
    cin >> input;

    int year = atoi(input.c_str());

    if(year != 0) {

        cout << '\n' << year << endl;

        for(int i=1; i<13; i++) { //for each month

            vector<WeatherSensorType> tempVector = WL.GetByMonth(i,year);

            float SSum = 0; //wind speed
            float TSum = 0; //temperature
            int count = 0;

            for(int j=0; j<tempVector.size(); j++) {
                SSum += tempVector.at(j).S;
                TSum += tempVector.at(j).T;
                count++;
            }

            if(count != 0) {
                cout << ConvertMonthToString(i) << ": "
                << RoundToDecimal((SSum/count)*3.6,1) << " km/h, "
                << RoundToDecimal(TSum/count,1) << " degrees C"
                << endl;
            } else {
                cout << ConvertMonthToString(i) << ": No Data" << endl;
            }
        }

    } else {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }
}

//Total solar radiation in kWh/m^2 for each month of a
//specified year. (print on screen only)
//EXAMPLE:
//1905
//January: 196.4 kWh/m^2
//February: 200.3 kWh/m^2
void Method3(WeatherData &WL) {

    Date tempDate;
    string input;

    cout << '\n' << "Enter year (YYYY): ";
    cin >> input;

    int year = atoi(input.c_str());

    if(year != 0) {

        cout << '\n' << year << endl;

        for(int i=1; i<13; i++) {

            vector<WeatherSensorType> tempVector = WL.GetByMonth(i,year);

            float sum = 0; //of solar radiation
            int count = 0;

            for(int j=0; j<tempVector.size(); j++) {
                if(tempVector.at(j).SR >= 100) { //only values over 100
                    sum += tempVector.at(j).SR;
                    count++;
                }
            }

            if(count != 0) {
                cout << ConvertMonthToString(i) << ": "
                << RoundToDecimal(CovertFromWm2ToKWhm2(sum),1) << " kWh/m2"
                << endl;
            } else {
                cout << ConvertMonthToString(i) << ": No Data" << endl;
            }
        }

    } else {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }

}

//Average wind speed (km/h), average ambient air temperature
//and total solar radiation in kWh/m^2 for each month of a
//specified year. (print to a file called "WindTempSollar.csv")
//OUTPUT FORMAT
//Year
//Month,Average Wind Speed,Average Temperature, Solar Radiation
//EXAMPLE:
//1905
//January,5.5,25.5,196.4
//Febuary,4.5,27.5,200.3
//...
void Method4(WeatherData &WL, ofstream &ofile) {

    Date tempDate;
    string input;

    cout << '\n' << "Enter year (YYYY): ";
    cin >> input;

    int year = atoi(input.c_str());

    if(year != 0) {

        ofile << '\n' << year << endl;
        bool found = false;

        for(int i=1; i<13; i++) {

            vector<WeatherSensorType> tempVector = WL.GetByMonth(i,year);

            float SSum = 0; //wind speed
            float TSum = 0; //temperature
            float SRSum = 0; //solar radiation
            int count = 0;

            for(int j=0; j<tempVector.size(); j++) {

                SSum += tempVector.at(j).S;
                TSum += tempVector.at(j).T;
                if(tempVector.at(j).SR >= 100) { //only values over 100
                    SRSum += tempVector.at(j).SR;
                }
                count++;

            }

            if(count != 0) {
                ofile << ConvertMonthToString(i) << ","
                << RoundToDecimal((SSum/count)*3.6,1) << ","
                << RoundToDecimal(TSum/count,1) << ","
                << RoundToDecimal(CovertFromWm2ToKWhm2(SRSum),1)<< endl;
                found = true;
            }
        }

        if(!found) {
            ofile << "No Data" << endl;
        }

    } else {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }
}

//Given a Date in the form d/m/yyyy, show the times for the highest solar radiation
//for that Date. Output to screen using this sample format: (There will be one or more
//time values that are output.)
//OUTPUT FORMAT
//Date: 11/29/2019
//High solar radiation for the day: 1046 W/m2
//Time:
//10:40
//11:30
void Method5(WeatherData &WD) {

    Date tempDate;
    string input;

    cout << '\n' << "Enter date (D/M/YYYY): ";
    cin >> input;

    int day = atoi(GetStringFromDelimiter(1,'/',input).c_str());
    int month = atoi(GetStringFromDelimiter(2,'/',input).c_str());
    int year = atoi(GetStringFromDelimiter(3,'/',input).c_str());

    if(day != 0 && month != 0 && year != 0) {

        vector<WeatherSensorType> tempVector = WD.GetByDay(day,month,year);

        if(tempVector.size() != 0) {

            vector<Time> timeVector;
            float highest = 0;

            for(int i=0; i<tempVector.size(); i++) {

                if(tempVector.at(i).SR > highest) {
                    timeVector.clear();
                    timeVector.push_back(tempVector.at(i).t);
                    highest = tempVector.at(i).SR;
                } else if(tempVector.at(i).SR == highest) {
                    timeVector.push_back(tempVector.at(i).t);
                }

            }

            cout << '\n' << "High solar radiation for the day: " << RoundToDecimal(highest,1) << " W/m2" << endl;
            cout << "Time:" << endl;
            for(int i=0; i<timeVector.size(); i++) {
                cout << timeVector.at(i) << endl;
            }

        } else {
            cout << '\n' << "No data." << endl;
        }

    } else {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }

}

//converts month to its text equivalent
string ConvertMonthToString(unsigned m) {

    string output = "";
    switch(m) {
        case 1:
            output = "January";
            break;
        case 2:
            output = "February";
            break;
        case 3:
            output = "March";
            break;
        case 4:
            output = "April";
            break;
        case 5:
            output = "May";
            break;
        case 6:
            output = "June";
            break;
        case 7:
            output = "July";
            break;
        case 8:
            output = "August";
            break;
        case 9:
            output = "September";
            break;
        case 10:
            output = "October";
            break;
        case 11:
            output = "November";
            break;
        case 12:
            output = "December";
            break;
    }

    return output;
}

//rounds a float to specified decimal place
float RoundToDecimal(float num, int decimalPlace) {
    return roundf(num * pow(10,decimalPlace)) / pow(10,decimalPlace);
}

//returns occurence of a character in string
int CheckOccurrenceOfChar(string text, char character) {
    int count = 0;
    for(int i=0; i<text.length(); i++) {
        if(text.at(i) == character) {
            count++;
        }
    }
    return count;
}

//returns substring of string within position in delimiter
string GetStringFromDelimiter(unsigned pos, char delimiter, string text) {
    int occurrence = CheckOccurrenceOfChar(text,delimiter);
    if(pos-1 <= occurrence) {

        for(int i=0; i<pos-1; i++) {
            text = text.substr(text.find(delimiter)+1,text.length());
        }

        if(pos-1 == occurrence) {
            return text;
        } else {
            return text.substr(0,text.find(delimiter));
        }

    } else {
        return "";
    }
}

//Convert a float from W/m2 to kWh/m2
float CovertFromWm2ToKWhm2(float wm2) {
    return((wm2*((float)1/6))/1000);
}

