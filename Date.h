#ifndef DATE_H
#define DATE_H

    /**
    * @author Kane Nikander
    * @version 8.1
    * @date 21/05/2018
    * @section description
    * @brief The Date class represtents a date, containing a day, month and year
    */
class Date
{

    public:

            /**
            * @brief A constructor.
            * Construct a blank date with no parameters
            */
        Date();

            /**
            * @brief A copy constructor.
            * Construct a date from another date (a deep copy).
            * @param const Date &other
            */
        Date(const Date &other);

            /**
            * @brief A constructor.
            * Construct a date from a day, month, and year.
            * @param unsigned d, unsigned m, unsigned y
            */
        Date(unsigned d,unsigned m,unsigned y);

            /**
            * @brief Set date.
            * Validates day, month and year to a valid date. If invalid sets to default (0/0/0).
            * @param unsigned d, unsigned m, unsigned y
            * @return void
            */
        void SetDate(unsigned d,unsigned m,unsigned y);

            /**
            * @brief Get day.
            *
            * @return const unsigned
            */
        unsigned GetDay() const;

            /**
            * @brief Get month.
            *
            * @return const unsigned
            */
        unsigned GetMonth() const;

            /**
            * @brief Get year.
            *
            * @return const unsigned
            */
        unsigned GetYear() const;

        /**
            * @brief Determine if two dates are equal.
            *
            * @return bool
            */
        bool operator ==( const Date & other );

            /**
            * @brief Determine if a date is before another date.
            *
            * @return bool
            */
        bool operator <( const Date & other );

            /**
            * @brief Determine if a date is after another date.
            *
            * @return bool
            */
        bool operator >( const Date & other );

    private:

            /** day of date */
        unsigned day;

            /** month of date */
        unsigned month;

            /** year of date */
        unsigned year;

            /**
            * @brief Determine if date is a valid date. If not set day,month and year to 0.
            *
            * @param unsigned d, unsigned m, unsigned y
            * @return bool
            */
        bool ValidateDate(unsigned d,unsigned m,unsigned y);

             /**
            * @brief Set day.
            *
            * @param unsigned d
            * @return void
            */
        void SetDay(unsigned d);

            /**
            * @brief Set month.
            *
            * @param unsigned m
            * @return void
            */
        void SetMonth(unsigned m);

            /**
            * @brief Set year.
            *
            * @param unsigned y
            * @return void
            */
        void SetYear(unsigned y);

};

#endif // DATE_H
