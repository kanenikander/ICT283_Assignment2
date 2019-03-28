#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include <vector>

    /**
    * @author Kane Nikander
    * @version 1.5
    * @date 24/05/2018
    * @section description
    * @brief The Extractor class is used to collect data when passed as a function parameter.
    */
template<class T>
class Extractor
{

    private:

            /** Holds extracted data */
        static vector<T> dataVector;

    public:

            /**
            * @brief Adds data to vector.
            *
            * @param T &data
            * @return static void
            */
        static void GetData(T &data) {
            dataVector.push_back(data);
        }

            /**
            * @brief returns size of vector.
            *
            * @return int
            */
        int size();

            /**
            * @brief Clears the vector.
            *
            * @return void
            */
        void clear();

            /**
            * @brief Overloads subscript operator.
            * Overloads operator to allow access to vector elements directly.
            * Returns blank instance of T if out of bounds.
            * @param int index
            * @return T&
            */
        T& operator[](int index);

};

template<class T>
int Extractor<T>::size() {
    return dataVector.size();
}

template<class T>
void Extractor<T>::clear() {
    dataVector.clear();
}

template<class T>
T& Extractor<T>::operator[](int index) {
    if(index < dataVector.size()) {
        return dataVector.at(index);
    } else {
        return *(new T); //memory leak!
    }
}

template<class T>
vector<T> Extractor<T>::dataVector;

#endif // EXTRACTOR_H
