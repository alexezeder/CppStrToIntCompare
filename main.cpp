#include <iostream>
#include <chrono>
#include <strstream>
#include <sstream>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <boost/version.hpp>
#include <unicode/uversion.h>
#include <unicode/locid.h>
#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/coll.h>

#define PROBES 1000000
#define MAX 10000000

inline void F1(const int i, char *buf, const std::size_t buflen) {
    snprintf(buf, buflen, "%d", i);
}

inline void F2(const int i, std::string &s) {
    std::ostringstream temp;
    temp << i;
    s = temp.str();
}

inline void F3(const int i, char *buf, const int buflen) {
    std::ostrstream temp(buf, buflen);
    temp << i << std::ends;
}

inline void F4(const int i, std::string &s) {
    s = boost::lexical_cast<std::string>(i);
}

int main() {

    std::cout << "Using Boost "
    << BOOST_VERSION / 100000     << "."  // major version
    << BOOST_VERSION / 100 % 1000 << "."  // minor version
    << BOOST_VERSION % 100                // patch level
    << std::endl;

    using namespace std::chrono;

    double times[5];

    for (int i = 0; i < PROBES; ++i) {
        int number = rand() % MAX;
        std::ostringstream temp;
        temp << i;
        size_t length = temp.str().size();

        char *buffer1 = new char[length + 1];
        char *buffer2 = new char[length + 1];
        std::string str1;
        std::string str2;
        std::string str3;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        F1(number, buffer1, length + 1);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        F2(number, str1);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        F3(number, buffer2, length + 1);
        high_resolution_clock::time_point t4 = high_resolution_clock::now();
        F4(number, str2);
        high_resolution_clock::time_point t5 = high_resolution_clock::now();
        str3 = std::to_string(number);
        high_resolution_clock::time_point t6 = high_resolution_clock::now();

        duration<double> time0 = duration_cast<duration<double>>(t2 - t1);
        duration<double> time1 = duration_cast<duration<double>>(t3 - t2);
        duration<double> time2 = duration_cast<duration<double>>(t4 - t3);
        duration<double> time3 = duration_cast<duration<double>>(t5 - t4);
        duration<double> time4 = duration_cast<duration<double>>(t6 - t5);

        times[0] += time0.count();
        times[1] += time1.count();
        times[2] += time2.count();
        times[3] += time3.count();
        times[4] += time4.count();
    }

    std::cout << "TIMES" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << times[i] << std::endl;
    }

    return 0;


}