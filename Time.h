#ifndef TIME_H
#define TIME_H

    /**
    * @author Kane Nikander
    * @version 8.1
    * @date 21/05/2018
    * @section description
    * @brief The Time class represtents a time, containing hours, minutes and meridiem
    */
class Time
{

    public:

            /**
            * @brief A constructor.
            * Construct a blank date with no parameters
            */
        Time();

            /**
            * @brief A copy constructor.
            * Construct a time from another time (a deep copy).
            * @param const Time &other
            */
        Time(const Time &other);

            /**
            * @brief A constructor.
            * Construct a 24-hour format time from hours and minutes.
            * @param unsigned h, unsigned m
            */
        Time(unsigned h,unsigned m);

            /**
            * @brief Set time.
            * Validates hours and minutes to a valid 24-hour time. If invalid sets to default (0:0N).
            * @param unsigned h, unsigned m, string mer
            * @return void
            */
        void SetTime(unsigned h,unsigned m);

            /**
            * @brief Get hours.
            *
            * @return const unsigned
            */
        unsigned GetHours() const;

            /**
            * @brief Get minutes.
            *
            * @return const unsigned
            */
        unsigned GetMinutes() const;

            /**
            * @brief Determine if two times are equal.
            *
            * @return bool
            */
        bool operator ==( const Time & other );

            /**
            * @brief Determine if a time is before another time.
            *
            * @return bool
            */
        bool operator <( const Time & other );

            /**
            * @brief Determine if a time is after another time.
            *
            * @return bool
            */
        bool operator >( const Time & other );


    private:

            /** hours of time */
        unsigned hours;

            /** minutes of time */
        unsigned minutes;

            /**
            * @brief Set hours.
            *
            * @param unsigned h
            * @return void
            */
        void SetHours(unsigned h);

            /**
            * @brief Set minutes.
            *
            * @param unsigned m
            * @return void
            */
        void SetMinutes(unsigned m);

            /**
            * @brief Determine if time is a valid 24-hour time. If invalid sets to default (0:0N).
            *
            * @param unsigned h, unsigned m
            * @return bool
            */
        bool Validate(unsigned h,unsigned m);

};

#endif // TIME_H
