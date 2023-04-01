#pragma once
#include <ctime>
#include <numeric>
#include <sstream>
#include "StreamIO.hpp"

// period of time
class Period : public StreamIO<Period> {

private:

    // elapsed seconds
    double secondCount;

public:

    // conversion factor
    static const int secondPerMinute;
    static const int minutePerHour;
    static const int secondPerHour;

    // formatting
    static const int secondDecimalDigitCount;
    static const int secondWholeDigitCount;
    static const int minuteDigitCount;
    static const int hourDigitCount;
    static const int extraCharCount;
    static const int totalCharCount;
    static const char componentDelimiter;

    // constructor

    explicit Period();

    explicit Period(double secondCount);

    explicit Period(double secondCount, int minuteCount, int hourCount);

    explicit Period(const std::string &asString);

    // setter

    Period &set(double newSecondCount);

    Period &set(double newSecondCount, int minuteCount, int hourCount);

    Period &set(const std::string &asString);

    // unit conversion

    double secondInAllCount() const;

    double secondInHourCount() const;

    double secondInMinuteCount() const;

    int minuteInAllCount() const;

    int minuteInHourCount() const;

    int hourInAllCount() const;

    static double composeSecondCount(double secondCount, int minuteCount, int hourCount);

    // parsing

    static double parseSecondCount(const std::string &asString);

    static int parseMinuteCount(const std::string &asString);

    static int parseHourCount(const std::string &asString);

    // to string operator

    explicit operator std::string() const;

    // arithmetic operator

    Period operator+(const Period &a) const;

    Period operator-(const Period &a) const;

    Period operator*(double a) const;

    Period operator/(double a) const;

    double operator/(const Period &a) const;

    Period &operator=(const Period &a);

    Period &operator+=(const Period &a);

    Period &operator-=(const Period &a);

    Period &operator*=(double a);

    Period &operator/=(double a);

    // comparison operator

    bool operator==(const Period &a) const;

    bool operator!=(const Period &a) const;

    bool operator<(const Period &a) const;

    bool operator>(const Period &a) const;

    bool operator<=(const Period &a) const;

    bool operator>=(const Period &a) const;

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const Period &period);

    friend std::istream &operator>>(std::istream &stream, Period &period);

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override;

    static Period *importFull(std::istream &stream, Period *result, bool newObject);
};

// standard calendar day
class Date : public StreamIO<Date> {

private:

    // elapsed days
    int dayCount;

public:

    // conversion factor
    static const int leapYearDifferenceByYear;
    static const int dayPerYear;
    static const int monthPerYear;
    static const int yearPerLeapCycle;
    static const int monthPerLeapCycle;
    static const int dayPerLeapCycle;
    static const int dayPerMonthByMonth[];
    static const int leapYearDifferenceByMonth[];

    // formatting
    static const int dayDigitCount;
    static const int monthDigitCount;
    static const int yearDigitCount;
    static const int extraCharCount;
    static const int totalCharCount;
    static const char componentDelimiter;

    // constructor

    explicit Date();

    explicit Date(int dayCount);

    explicit Date(int dayCount, int monthCount, int yearCount);

    explicit Date(const std::string &asString);

    // setter

    Date &set(int newDayCount);

    Date &set(int newDayCount, int monthCount, int yearCount);

    Date &set(const std::string &asString);

    // unit conversion

    int dayInAllCount() const;

    int dayInLeapCycleCount() const;

    int dayInYearCount() const;

    int dayInMonthCount() const;

    int monthInAllCount() const;

    int monthInLeapCycleCount() const;

    int monthInYearCount() const;

    int yearInAllCount() const;

    int yearInLeapCycleCount() const;

    int leapCycleInAllCount() const;

    bool isLeapYear() const;

    static int composeDayCount(int dayCount, int monthCount, int yearCount);

    static int composeDayCount(int dayCount, int monthCount, int yearCount, int leapCycleCount);

    // parsing

    static int parseDayCount(const std::string &asString);

    static int parseMonthCount(const std::string &asString);

    static int parseYearCount(const std::string &asString);

    // to string operator

    explicit operator std::string() const;

    // comparison operator

    Date &operator=(const Date &a);

    bool operator==(const Date &a) const;

    bool operator!=(const Date &a) const;

    bool operator<(const Date &a) const;

    bool operator>(const Date &a) const;

    bool operator<=(const Date &a) const;

    bool operator>=(const Date &a) const;

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const Date &period);

    friend std::istream &operator>>(std::istream &stream, Date &period);

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override;

    static Date *importFull(std::istream &stream, Date *result, bool newObject);
};


// moment in calendar year
class Moment : public StreamIO<Moment> {

private:

    // elapsed seconds
    long long secondCount;

public:

    // conversion factor
    static const int hourPerDay;

    // formatting
    static const int extraCharCount;
    static const int totalCharCount;
    static const char componentDelimiter;

    // standard epoch - 1 Jan 1970
    static const Moment epoch;

    // parsing token to retrieve current moment
    static const std::string nowToken;

    // constructor

    explicit Moment();

    explicit Moment(long long secondCount);

    explicit Moment(const Date &day, const Period &time);

    explicit Moment(const std::string &asString);

    // setter

    Moment &set(long long newSecondCount);

    Moment &set(const Date &day, const Period &time);

    Moment &set(const std::string &asString);

    // unit conversion

    long long getSecondCount() const;

    Date getDay() const;

    Period getTime() const;

    static long long composeSecondCount(const Date &day, const Period &time);

    // parsing

    static Date parseDay(const std::string &asString);

    static Period parseTime(const std::string &asString);

    static Moment parseWithNow(const std::string &asString);

    // get current moment

    static Moment now();

    // to string operator

    explicit operator std::string() const;

    // comparison operator

    Moment &operator=(const Moment &a);

    bool operator==(const Moment &a) const;

    bool operator!=(const Moment &a) const;

    bool operator<(const Moment &a) const;

    bool operator>(const Moment &a) const;

    bool operator<=(const Moment &a) const;

    bool operator>=(const Moment &a) const;

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const Moment &moment);

    friend std::istream &operator>>(std::istream &stream, Moment &moment);

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override;

    static Moment *importFull(std::istream &stream, Moment *result, bool newObject);
};
