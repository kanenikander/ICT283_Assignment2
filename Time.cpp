#include "Time.h"

Time::Time()
{
    SetHours(24);
    SetMinutes(60);
}

Time::Time(const Time &other) {
    hours = other.GetHours();
    minutes = other.GetMinutes();
}

Time::Time(unsigned h,unsigned m) {
    SetTime(h,m);
}

void Time::SetTime(unsigned h,unsigned m) {
    if(Validate(h,m)) {
        SetHours(h);
        SetMinutes(m);
    } else {
        SetHours(24);
        SetMinutes(60);
    }
}

void Time::SetHours(unsigned h) {
    hours = h;
}

void Time::SetMinutes(unsigned m) {
    minutes = m;
}

unsigned Time::GetHours() const {
    return hours;
}

unsigned Time::GetMinutes() const {
    return minutes;
}

bool Time::Validate(unsigned h,unsigned m) {
    return (h < 24 && m < 60);
}

bool Time::operator ==( const Time & other ) {

    if(this->GetHours() == other.GetHours()) {
        if(this->GetMinutes() == other.GetMinutes()) {
            return true;
        }
    }
    return false;

}

bool Time::operator <( const Time & other ) {

    if(this->GetHours() < other.GetHours()) {
        if(this->GetMinutes() < other.GetMinutes()) {
            return true;
        }
    }
    return false;

}

bool Time::operator >( const Time & other ) {

    if(this->GetHours() > other.GetHours()) {
        if(this->GetMinutes() > other.GetMinutes()) {
            return true;
        }
    }
    return false;

}
