#include "Time.hpp"

static std::string parse(const std::string &asString, char delimiter, int index) {

    std::string result;
    std::stringstream asStream(asString);

    for (int i = 0; i < index; i++) std::getline(asStream, result, delimiter);
    std::getline(asStream, result, delimiter);

    return result;
}

const int Period::secondPerMinute = 60;
const int Period::minutePerHour = 60;
const int Period::secondPerHour = secondPerMinute * minutePerHour;

const int Period::secondDecimalDigitCount = 1;
const int Period::secondWholeDigitCount = 2;
const int Period::minuteDigitCount = 2;
const int Period::hourDigitCount = 2;
const int Period::extraCharCount = 3;

const int Period::totalCharCount =
        secondDecimalDigitCount + secondWholeDigitCount +
        minuteDigitCount + hourDigitCount + extraCharCount;

const char Period::componentDelimiter = ':';

Period::Period() : secondCount(set(0).secondCount) {}

Period::Period(double secondCount) : secondCount(set(secondCount).secondCount) {}

Period::Period(double secondCount, int minuteCount, int hourCount) :
        secondCount(set(secondCount, minuteCount, hourCount).secondCount) {}

Period::Period(const std::string &asString) : secondCount(set(asString).secondCount) {}

Period &Period::set(double newSecondCount) {

    secondCount = newSecondCount;
    return *this;
}

Period &Period::set(double newSecondCount, int minuteCount, int hourCount) {

    return set(composeSecondCount(newSecondCount, minuteCount, hourCount));
}

Period &Period::set(const std::string &asString) {

    return set(parseSecondCount(asString), parseMinuteCount(asString), parseHourCount(asString));
}

double Period::secondInAllCount() const { return secondCount; }

double Period::secondInHourCount() const { return secondInAllCount() - secondPerHour * hourInAllCount(); }

double Period::secondInMinuteCount() const { return secondInAllCount() - secondPerMinute * minuteInAllCount(); }

int Period::minuteInAllCount() const { return (int) secondInAllCount() / secondPerMinute; }

int Period::minuteInHourCount() const { return minuteInAllCount() - minutePerHour * hourInAllCount(); }

int Period::hourInAllCount() const { return minuteInAllCount() / minutePerHour; }

double Period::composeSecondCount(double secondCount, int minuteCount, int hourCount) {

    return secondCount + secondPerMinute * minuteCount + secondPerHour * hourCount;
}

double Period::parseSecondCount(const std::string &asString) {

    return std::stod(parse(asString, componentDelimiter, 2));
}

int Period::parseMinuteCount(const std::string &asString) {

    return std::stoi(parse(asString, componentDelimiter, 1));
}

int Period::parseHourCount(const std::string &asString) {

    return std::stoi(parse(asString, componentDelimiter, 0));
}

Period::operator std::string() const {

    std::stringstream format;
    format <<
           "%0" << hourDigitCount << "d" << componentDelimiter <<
           "%0" << minuteDigitCount << "d" << componentDelimiter <<
           "%0" << secondWholeDigitCount + secondDecimalDigitCount + 1 << "." << secondDecimalDigitCount << "f";

    char result[totalCharCount + 1];
    sprintf(result, format.str().c_str(), hourInAllCount(), minuteInHourCount(), secondInMinuteCount());
    return result;
}

Period Period::operator+(const Period &a) const { return Period(secondCount + a.secondCount); }

Period Period::operator-(const Period &a) const { return Period(secondCount - a.secondCount); }

Period Period::operator*(double a) const { return Period(secondCount * a); }

Period Period::operator/(double a) const { return Period(secondCount / a); }

double Period::operator/(const Period &a) const { return secondCount / a.secondCount; }

Period &Period::operator=(const Period &a) {

    set(a.secondCount);
    return *this;
}

Period &Period::operator+=(const Period &a) {

    set(secondCount + a.secondCount);
    return *this;
}

Period &Period::operator-=(const Period &a) {

    set(secondCount - a.secondCount);
    return *this;
}

Period &Period::operator*=(double a) {

    set(secondCount * a);
    return *this;
}

Period &Period::operator/=(double a) {

    set(secondCount / a);
    return *this;
}

bool Period::operator==(const Period &a) const { return secondCount == a.secondCount; }

bool Period::operator!=(const Period &a) const { return secondCount != a.secondCount; }

bool Period::operator<(const Period &a) const { return secondCount < a.secondCount; }

bool Period::operator>(const Period &a) const { return secondCount > a.secondCount; }

bool Period::operator<=(const Period &a) const { return secondCount <= a.secondCount; }

bool Period::operator>=(const Period &a) const { return secondCount >= a.secondCount; }

std::ostream &operator<<(std::ostream &stream, const Period &period) {

    return stream << period.operator std::string();
}

std::istream &operator>>(std::istream &stream, Period &period) {

    std::string asString;
    stream >> asString;
    period.set(asString);
    return stream;
}

const std::ostream &Period::exportFull(std::ostream &stream, bool newObject) const {

    return stream << secondCount << " ";
}

Period *Period::importFull(std::istream &stream, Period *result, bool newObject) {

    double secondCount;
    stream >> secondCount;
    if (newObject) *result = Period(secondCount);
    else result->set(secondCount);
    return result;
}

const int Date::dayPerYear = 365;
const int Date::leapYearDifferenceByYear = 1;
const int Date::monthPerYear = 12;
const int Date::yearPerLeapCycle = 4;
const int Date::monthPerLeapCycle = monthPerYear * yearPerLeapCycle;
const int Date::dayPerLeapCycle = dayPerYear * yearPerLeapCycle + leapYearDifferenceByYear;
const int Date::dayPerMonthByMonth[monthPerYear] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int Date::leapYearDifferenceByMonth[monthPerYear] = {00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00};

const int Date::dayDigitCount = 2;
const int Date::monthDigitCount = 2;
const int Date::yearDigitCount = 4;
const int Date::extraCharCount = 2;

const int Date::totalCharCount =
        dayDigitCount + monthDigitCount +
        yearDigitCount + extraCharCount;

const char Date::componentDelimiter = '/';

Date::Date() : dayCount(set(0).dayCount) {}

Date::Date(int dayCount) : dayCount(set(dayCount).dayCount) {}

Date::Date(int dayCount, int monthCount, int yearCount) :
        dayCount(set(dayCount, monthCount, yearCount).dayCount) {}

Date::Date(const std::string &asString) : dayCount(set(asString).dayCount) {}

Date &Date::set(int newDayCount) {

    dayCount = newDayCount;
    return *this;
}

Date &Date::set(int newDayCount, int monthCount, int yearCount) {

    return set(composeDayCount(newDayCount, monthCount, yearCount));
}

Date &Date::set(const std::string &asString) {

    return set(parseDayCount(asString), parseMonthCount(asString), parseYearCount(asString));
}

int Date::dayInAllCount() const { return dayCount; }

int Date::dayInLeapCycleCount() const { return dayInAllCount() - dayPerLeapCycle * leapCycleInAllCount(); }

int Date::monthInAllCount() const { return monthInLeapCycleCount() + monthPerLeapCycle * leapCycleInAllCount(); }

int Date::monthInLeapCycleCount() const { return monthInYearCount() + monthPerYear * yearInLeapCycleCount(); }

int Date::yearInAllCount() const { return yearInLeapCycleCount() + yearPerLeapCycle * leapCycleInAllCount(); }

int Date::leapCycleInAllCount() const { return dayInAllCount() / dayPerLeapCycle; }

bool Date::isLeapYear() const { return yearInLeapCycleCount() == 0; }

int Date::dayInYearCount() const {

    return dayInLeapCycleCount() - dayPerYear * yearInLeapCycleCount() - !isLeapYear() * leapYearDifferenceByYear;
}

int Date::dayInMonthCount() const {

    int dayInYear = dayInYearCount();
    dayInYear -= std::accumulate(dayPerMonthByMonth, dayPerMonthByMonth + monthInYearCount(), 0);
    if (isLeapYear())
        dayInYear -= std::accumulate(leapYearDifferenceByMonth, leapYearDifferenceByMonth + monthInYearCount(), 0);
    return dayInYear;
}

int Date::monthInYearCount() const {

    int dayInYear = dayInYearCount();
    for (int i = 0; i < monthPerYear; i++) {
        if (dayInYear < dayPerMonthByMonth[i] + isLeapYear() * leapYearDifferenceByMonth[i]) return i;
        dayInYear -= dayPerMonthByMonth[i] + isLeapYear() * leapYearDifferenceByMonth[i];
    }
    return monthPerYear;
}

int Date::yearInLeapCycleCount() const {

    int dayInLeapCycle = dayInLeapCycleCount();
    if (dayInLeapCycle < dayPerYear + leapYearDifferenceByYear) return 0;
    dayInLeapCycle -= dayPerYear + leapYearDifferenceByYear;
    return dayInLeapCycle / dayPerYear + 1;
}

int Date::composeDayCount(int dayCount, int monthCount, int yearCount) {

    int leapCycleCount = yearCount / yearPerLeapCycle;
    int yearInLeapCycle = yearCount - yearPerLeapCycle * leapCycleCount;
    return composeDayCount(dayCount, monthCount, yearInLeapCycle, leapCycleCount);
}

int Date::composeDayCount(int dayCount, int monthCount, int yearCount, int leapCycleCount) {

    int sum = 0;
    bool isLeapYear = yearCount == 0;
    bool pastLeapYear = yearCount > 0;

    sum += dayCount;
    sum += dayPerYear * yearCount;
    sum += dayPerLeapCycle * leapCycleCount;
    sum += pastLeapYear * leapYearDifferenceByYear;

    sum += std::accumulate(dayPerMonthByMonth, dayPerMonthByMonth + monthCount, 0);
    sum += isLeapYear * std::accumulate(leapYearDifferenceByMonth, leapYearDifferenceByMonth + monthCount, 0);

    return sum;
}

int Date::parseDayCount(const std::string &asString) {

    return std::stoi(parse(asString, componentDelimiter, 1)) - 1;
}

int Date::parseMonthCount(const std::string &asString) {

    return std::stoi(parse(asString, componentDelimiter, 0)) - 1;
}

int Date::parseYearCount(const std::string &asString) {

    return std::stoi(parse(asString, componentDelimiter, 2));
}

Date::operator std::string() const {

    std::stringstream format;
    format <<
           "%0" << monthDigitCount << "d" << componentDelimiter <<
           "%0" << dayDigitCount << "d" << componentDelimiter <<
           "%0" << yearDigitCount << "d";

    char result[totalCharCount + 1];
    sprintf(result, format.str().c_str(), monthInYearCount() + 1, dayInMonthCount() + 1, yearInAllCount());
    return result;
}

Date &Date::operator=(const Date &a) {

    set(a.dayCount);
    return *this;
}

bool Date::operator==(const Date &a) const { return dayCount == a.dayCount; }

bool Date::operator!=(const Date &a) const { return dayCount != a.dayCount; }

bool Date::operator<(const Date &a) const { return dayCount < a.dayCount; }

bool Date::operator>(const Date &a) const { return dayCount > a.dayCount; }

bool Date::operator<=(const Date &a) const { return dayCount <= a.dayCount; }

bool Date::operator>=(const Date &a) const { return dayCount >= a.dayCount; }

std::ostream &operator<<(std::ostream &stream, const Date &date) {

    return stream << date.operator std::string();
}

std::istream &operator>>(std::istream &stream, Date &date) {

    std::string asString;
    stream >> asString;
    date.set(asString);
    return stream;
}

const std::ostream &Date::exportFull(std::ostream &stream, bool newObject) const {

    return stream << dayCount << " ";
}

Date *Date::importFull(std::istream &stream, Date *result, bool newObject) {

    int dayCount;
    stream >> dayCount;
    if (newObject) *result = Date(dayCount);
    else result->set(dayCount);
    return result;
}

const int Moment::hourPerDay = 24;

const int Moment::extraCharCount = 1;
const int Moment::totalCharCount = Date::totalCharCount + Period::totalCharCount + extraCharCount;
const char Moment::componentDelimiter = '@';

const Moment Moment::epoch = Moment(Date(0, 0, 1970), Period(0, 0, 0));
const std::string Moment::nowToken = "NOW";

Moment::Moment() : secondCount(set(0).secondCount) {}

Moment::Moment(long long secondCount) : secondCount(set(secondCount).secondCount) {}

Moment::Moment(const Date &day, const Period &time) :
        secondCount(set(day, time).secondCount) {}

Moment::Moment(const std::string &asString) : secondCount(set(asString).secondCount) {}

Moment &Moment::set(long long newSecondCount) {

    secondCount = newSecondCount;
    return *this;
}

Moment &Moment::set(const Date &day, const Period &time) {

    return set(composeSecondCount(day, time));
}

Moment &Moment::set(const std::string &asString) {

    return set(parseDay(asString), parseTime(asString));
}

long long Moment::getSecondCount() const { return secondCount; }

Date Moment::getDay() const {

    return Date((int) (secondCount / Period::secondPerHour / hourPerDay));
}

Period Moment::getTime() const {

    return Period((double) (secondCount - (long long) getDay().dayInAllCount() * hourPerDay * Period::secondPerHour));
}

long long Moment::composeSecondCount(const Date &day, const Period &time) {

    return (long long) time.secondInAllCount() + (long long) day.dayInAllCount() * hourPerDay * Period::secondPerHour;
}

Date Moment::parseDay(const std::string &asString) {

    return Date(parse(asString, componentDelimiter, 0));
}

Period Moment::parseTime(const std::string &asString) {

    return Period(parse(asString, componentDelimiter, 1));
}

Moment Moment::parseWithNow(const std::string &asString) {

    if (asString == nowToken) return now();
    return Moment(asString);
}

Moment Moment::now() { return Moment(std::time(nullptr) + Moment::epoch.getSecondCount()); }

Moment::operator std::string() const {

    std::stringstream result;
    result << getDay() << Moment::componentDelimiter << getTime();
    return result.str();
}

Moment &Moment::operator=(const Moment &a) {

    set(a.secondCount);
    return *this;
}

bool Moment::operator==(const Moment &a) const { return secondCount == a.secondCount; }

bool Moment::operator!=(const Moment &a) const { return secondCount != a.secondCount; }

bool Moment::operator<(const Moment &a) const { return secondCount < a.secondCount; }

bool Moment::operator>(const Moment &a) const { return secondCount > a.secondCount; }

bool Moment::operator<=(const Moment &a) const { return secondCount <= a.secondCount; }

bool Moment::operator>=(const Moment &a) const { return secondCount >= a.secondCount; }

std::ostream &operator<<(std::ostream &stream, const Moment &moment) {

    return stream << moment.operator std::string();
}

std::istream &operator>>(std::istream &stream, Moment &moment) {

    std::string asString;
    stream >> asString;
    moment.set(asString);
    return stream;
}

const std::ostream &Moment::exportFull(std::ostream &stream, bool newObject) const {

    return stream << secondCount << " ";
}

Moment *Moment::importFull(std::istream &stream, Moment *result, bool newObject) {

    long long secondCount;
    stream >> secondCount;
    if (newObject) *result = Moment(secondCount);
    else result->set(secondCount);
    return result;
}
