#include "Date.h"

Date::Date()
{
    SetDay(0);
    SetMonth(0);
    SetYear(0);
}

Date::Date(const Date &other) {
    day = other.GetDay();
    month = other.GetMonth();
    year = other.GetYear();
}

Date::Date(unsigned d, unsigned m, unsigned y)
{
    SetDate(d,m,y);
}

void Date::SetDate(unsigned d, unsigned m, unsigned y) {
    if(ValidateDate(d,m,y)) {
        SetDay(d);
        SetMonth(m);
        SetYear(y);
    } else {
        SetDay(0);
        SetMonth(0);
        SetYear(0);
    }
}

void Date::SetDay(unsigned d) {
    day = d;
}

void Date::SetMonth(unsigned m) {
    month = m;
}

void Date::SetYear(unsigned y) {
    year = y;
}

unsigned Date::GetDay() const {
    return day;
}


unsigned Date::GetMonth() const {
    return month;
}

unsigned Date::GetYear() const {
    return year;
}

bool Date::ValidateDate(unsigned d,unsigned m,unsigned y) {
    if(y > 0 && y < 9999) {
        if(m == 2) {
            if((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) { //if leap year
                if (d > 0 && d <= 29) {
                    return true;
                }
            } else {
                if (d > 0 && d <= 28) {
                    return true;
                }
            }
        } else if(m == 4 || m == 6 || m == 9 || m == 11) {
            if (d > 0 && d <= 30) {
                return true;
            }
        } else if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
            if (d > 0 && d <= 31) {
                return true;
            }
        }
    }
    return false;
}

bool Date::operator ==( const Date & other ) {
    if(this->GetYear() == other.GetYear()) {
        if(this->GetMonth() == other.GetMonth()) {
            if(this->GetDay() == other.GetDay()) {
                return true;
            }
        }
    }
    return false;
}

bool Date::operator >( const Date & other ) {
    if(this->GetYear() > other.GetYear()) {
        return true;
    } else if(this->GetYear() == other.GetYear()) {
        if(this->GetMonth() > other.GetMonth()) {
            return true;
        } else if(this->GetMonth() == other.GetMonth()) {
            if(this->GetDay() > other.GetDay()) {
                return true;
            }
        }
    }
    return false;
}

bool Date::operator <( const Date & other ) {
    if(this->GetYear() < other.GetYear()) {
        return true;
    } else if(this->GetYear() == other.GetYear()) {
        if(this->GetMonth() < other.GetMonth()) {
            return true;
        } else if(this->GetMonth() == other.GetMonth()) {
            if(this->GetDay() < other.GetDay()) {
                return true;
            }
        }
    }
    return false;
}
