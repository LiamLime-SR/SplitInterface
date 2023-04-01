#include "SafeSplit.hpp"

std::string SafeSplit::nextName(std::istream &stream, const std::string &message) {

    std::string name;
    stream >> name;
    return Assert::assertHas(name, message + " name");
}

int SafeSplit::nextSize(std::istream &stream, const std::string &message) {

    Assert::assertHas(stream, message + " size");
    int size;
    stream >> size;
    return Assert::assertPositive(size, message + " size");
}

int SafeSplit::nextIndex(int max, std::istream &stream, const std::string &message) {

    Assert::assertHas(stream, message + " index");
    int index;
    stream >> index;
    return Assert::assertRange(index, max, message + " index");
}

Period SafeSplit::nextTime(std::istream &stream, const std::string &message) {

    Assert::assertHas(stream, message + " time");
    Period time;
    stream >> time;
    return time;
}

Moment SafeSplit::nextMoment(std::istream &stream, const std::string &message) {

    std::string asString = nextName(stream, message + " moment");
    return Moment::parseWithNow(asString);
}

SplitTemplate SafeSplit::newSplitTemplate(const std::string &name, int size, const SpeedCategory *speedCategory) {

    Assert::assertNonexist(
            Name(name), speedCategory->getSplitTemplateSet().getMap(), "template name");
    SplitTemplate splitTemplate = SplitTemplate(name, size, speedCategory);
    return splitTemplate;
}

const SplitTemplate *SafeSplit::getSplitTemplate(const std::string &name, const SpeedCategory *speedCategory) {

    Assert::assertExist(Name(name), speedCategory->getSplitTemplateSet().getMap(), "template name");
    const SplitTemplate *splitTemplate = &speedCategory->getSplitTemplateSet().getValue(Name(name));
    return splitTemplate;
}

SplitTemplate SafeSplit::removeSplitTemplate(const std::string &name, SpeedCategory *speedCategory) {

    Assert::assertExist(Name(name), speedCategory->getSplitTemplateSet().getMap(), "template name");
    SplitTemplate splitTemplate = speedCategory->getSplitTemplateSet().delValue(Name(name));
    return splitTemplate;
}

const SplitTemplate *SafeSplit::fillSplitTemplate(
        std::istream &stream, const SplitTemplate *splitTemplate) {

    Assert::assertHas(stream, splitTemplate->getSize(), "template split name");
    stream >> *splitTemplate;
    return splitTemplate;
}

const SplitTemplate *SafeSplit::copySplitTemplate(
        const SplitTemplate *splitTemplateSource, const SplitTemplate *splitTemplateDestination) {

    Assert::assertEqual(
            splitTemplateSource->getSize(),
            splitTemplateDestination->getSize(),
            "template size");
    splitTemplateDestination->copy(*splitTemplateSource);
    return splitTemplateDestination;
}

SplitComparison SafeSplit::newSplitComparison(const std::string &name, const SplitTemplate *splitTemplate) {

    Assert::assertNonexist(
            Name(name), splitTemplate->getSpeedCategory()->getSplitComparisonSet().getMap(), "comparison name");
    SplitComparison splitComparison = SplitComparison(name, splitTemplate);
    return splitComparison;
}

const SplitComparison *SafeSplit::getSplitComparison(const std::string &name, const SpeedCategory *speedCategory) {

    Assert::assertExist(Name(name), speedCategory->getSplitComparisonSet().getMap(), "comparison name");
    const SplitComparison *splitComparison = &speedCategory->getSplitComparisonSet().getValue(Name(name));
    return splitComparison;
}

SplitComparison SafeSplit::removeSplitComparison(const std::string &name, SpeedCategory *speedCategory) {

    Assert::assertExist(Name(name), speedCategory->getSplitComparisonSet().getMap(), "comparison name");
    SplitComparison splitComparison = speedCategory->getSplitComparisonSet().delValue(Name(name));
    return splitComparison;
}

const SplitComparison *SafeSplit::fillSplitComparison(
        std::istream &stream, const SplitComparison *splitComparison) {

    Assert::assertHas(stream, splitComparison->getSplitTemplate()->getSize(), "comparison split time");
    stream >> *splitComparison;
    return splitComparison;
}

const SplitComparison *SafeSplit::copySplitComparison(
        const SplitComparison *splitComparisonSource, const SplitComparison *splitComparisonDestination) {

    Assert::assertEqual(
            splitComparisonSource->getSize(),
            splitComparisonDestination->getSize(),
            "comparison size");
    splitComparisonDestination->copy(*splitComparisonSource);
    return splitComparisonDestination;
}

SplitPerformance SafeSplit::newSplitPerformance(const Moment &moment, const SplitTemplate *splitTemplate) {

    Assert::assertNonexist(
            moment, splitTemplate->getSpeedCategory()->getSplitPerformanceSet().getMap(), "performance moment");
    SplitPerformance splitPerformance = SplitPerformance(moment, splitTemplate);
    return splitPerformance;
}

const SplitPerformance *SafeSplit::getSplitPerformance(const Moment &moment, const SpeedCategory *speedCategory) {

    Assert::assertExist(moment, speedCategory->getSplitPerformanceSet().getMap(), "performance moment");
    const SplitPerformance *splitPerformance = &speedCategory->getSplitPerformanceSet().getValue(moment);
    return splitPerformance;
}

SplitPerformance SafeSplit::removeSplitPerformance(const Moment &moment, SpeedCategory *speedCategory) {

    Assert::assertExist(moment, speedCategory->getSplitPerformanceSet().getMap(), "performance moment");
    SplitPerformance splitPerformance = speedCategory->getSplitPerformanceSet().delValue(moment);
    return splitPerformance;
}

const SplitPerformance *SafeSplit::fillSplitPerformance(
        std::istream &stream, const SplitPerformance *splitPerformance) {

    Assert::assertHas(stream, splitPerformance->getSplitTemplate()->getSize(), "performance split time");
    stream >> *splitPerformance;
    return splitPerformance;
}

const SplitPerformance *SafeSplit::copySplitPerformance(
        const SplitPerformance *splitPerformanceSource, const SplitPerformance *splitPerformanceDestination) {

    Assert::assertEqual(
            splitPerformanceSource->getSize(),
            splitPerformanceDestination->getSize(),
            "performance size");
    splitPerformanceDestination->copy(*splitPerformanceSource);
    return splitPerformanceDestination;
}

SplitPractice SafeSplit::newSplitPractice(int splitIndex, const Moment &moment, const SplitTemplate *splitTemplate) {

    Assert::assertNonexist(
            moment, splitTemplate->getSpeedCategory()->getSplitPracticeSet().getMap(), "practice moment");
    SplitPractice splitPractice = SplitPractice(splitIndex, moment, splitTemplate);
    return splitPractice;
}

const SplitPractice *SafeSplit::getSplitPractice(const Moment &moment, const SpeedCategory *speedCategory) {

    Assert::assertExist(moment, speedCategory->getSplitPracticeSet().getMap(), "practice moment");
    const SplitPractice *splitPractice = &speedCategory->getSplitPracticeSet().getValue(moment);
    return splitPractice;
}

SplitPractice SafeSplit::removeSplitPractice(const Moment &moment, SpeedCategory *speedCategory) {

    Assert::assertExist(moment, speedCategory->getSplitPracticeSet().getMap(), "practice moment");
    SplitPractice splitPractice = speedCategory->getSplitPracticeSet().delValue(moment);
    return splitPractice;
}
