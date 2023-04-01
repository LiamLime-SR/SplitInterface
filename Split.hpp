#pragma once
#include "SplitSet.hpp"
#include "SplitMap.hpp"

class SpeedCategory;

class SplitTemplate;

class SplitInstance;

class SplitComparison;

class SplitPerformance;

class SplitPractice;

// speedrunning category
class SpeedCategory : public HasName {

private:

    // all split instances performed in category
    NamedMap<SplitTemplate> splitTemplateSet;
    NamedMap<SplitComparison> splitComparisonSet;
    MomentMap<SplitPerformance> splitPerformanceSet;
    MomentMap<SplitPractice> splitPracticeSet;

    // pointer to active speed category when importing from file io
    static const SpeedCategory *activeImport;

public:

    // constructor

    explicit SpeedCategory() : HasName("") {}

    explicit SpeedCategory(const std::string &name) : HasName(name) {}

    // getter

    static const SpeedCategory *getActiveImport() { return activeImport; }

    NamedMap<SplitTemplate> &getSplitTemplateSet() { return splitTemplateSet; }

    NamedMap<SplitComparison> &getSplitComparisonSet() { return splitComparisonSet; }

    MomentMap<SplitPerformance> &getSplitPerformanceSet() { return splitPerformanceSet; }

    MomentMap<SplitPractice> &getSplitPracticeSet() { return splitPracticeSet; }

    const NamedMap<SplitTemplate> &getSplitTemplateSet() const { return splitTemplateSet; }

    const NamedMap<SplitComparison> &getSplitComparisonSet() const { return splitComparisonSet; }

    const MomentMap<SplitPerformance> &getSplitPerformanceSet() const { return splitPerformanceSet; }

    const MomentMap<SplitPractice> &getSplitPracticeSet() const { return splitPracticeSet; }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        HasName::exportFull(stream, newObject);
        splitTemplateSet.exportFull(stream, true);
        splitComparisonSet.exportFull(stream, true);
        splitPerformanceSet.exportFull(stream, true);
        splitPracticeSet.exportFull(stream, true);
        return stream;
    }

    static SpeedCategory *importFull(std::istream &stream, SpeedCategory *result, bool newObject) {

        activeImport = result;
        HasName::importFull(stream, result, newObject);

        NamedMap<SplitTemplate>::importFull(stream, &result->splitTemplateSet, true);
        NamedMap<SplitComparison>::importFull(stream, &result->splitComparisonSet, true);
        MomentMap<SplitPerformance>::importFull(stream, &result->splitPerformanceSet, true);
        MomentMap<SplitPractice>::importFull(stream, &result->splitPracticeSet, true);

        activeImport = nullptr;
        return result;
    }
};

// split template containing split names for route
class SplitTemplate : public HasName, public NameSet {

private:

    // pointer to relevant category
    const SpeedCategory *speedCategory;

public:

    // constructor

    explicit SplitTemplate() : HasName(""), NameSet(0), speedCategory(nullptr) {}

    explicit SplitTemplate(const std::string &name, int size, const SpeedCategory *speedCategory) :
            HasName(name), NameSet(size), speedCategory(speedCategory) {}

    // getter

    const SpeedCategory *getSpeedCategory() const { return speedCategory; }

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const SplitTemplate &a) {

        return stream << static_cast<HasName>(a) << " " << static_cast<NameSet>(a);
    }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        HasName::exportFull(stream, newObject);
        NameSet::exportFull(stream, newObject);
        return stream;
    }

    static SplitTemplate *importFull(std::istream &stream, SplitTemplate *result, bool newObject) {

        if (newObject) {
            Name name;
            Name::importFull(stream, &name, true);
            int size;
            stream >> size;
            *result = SplitTemplate(name, size, SpeedCategory::getActiveImport());
        }

        HasName::importFull(stream, result, false);
        NameSet::importFull(stream, result, false);

        return result;
    }
};

// instance of timed split for route
class SplitInstance : public StreamIO<SplitInstance> {

private:

    // pointer to relevant template
    const SplitTemplate *splitTemplate;

public:

    // constructor

    explicit SplitInstance() : splitTemplate(nullptr) {}

    explicit SplitInstance(const SplitTemplate *splitTemplate) : splitTemplate(splitTemplate) {}

    // getter

    const SplitTemplate *getSplitTemplate() const { return splitTemplate; }

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const SplitInstance &a) {

        return stream << a.splitTemplate->getKey();
    }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        splitTemplate->HasName::exportFull(stream, newObject);
        return stream;
    }

    static SplitInstance *importFull(std::istream &stream, SplitInstance *result, bool newObject) {

        if (newObject) {
            Name templateName;
            Name::importFull(stream, &templateName, true);
            *result = SplitInstance(
                    &SpeedCategory::getActiveImport()->getSplitTemplateSet().getValue(Name(templateName)));
        }

        return result;
    }
};

// timed comparison for route
class SplitComparison : public HasName, public SplitInstance, public IntervalSet {

public:

    // constructor

    explicit SplitComparison() : HasName(""), SplitInstance(nullptr), IntervalSet(0) {}

    explicit SplitComparison(const std::string &name, const SplitTemplate *splitTemplate) :
            HasName(name), SplitInstance(splitTemplate), IntervalSet(splitTemplate->getSize()) {}

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const SplitComparison &a) {

        return stream << static_cast<HasName>(a) << " " << static_cast<IntervalSet>(a);
    }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        HasName::exportFull(stream, newObject);
        SplitInstance::exportFull(stream, newObject);
        IntervalSet::exportFull(stream, false);
        return stream;
    }

    static SplitComparison *importFull(std::istream &stream, SplitComparison *result, bool newObject) {

        if (newObject) {
            Name name;
            Name::importFull(stream, &name, true);
            Name templateName;
            Name::importFull(stream, &templateName, true);
            *result = SplitComparison(
                    name, &SpeedCategory::getActiveImport()->getSplitTemplateSet().getValue(Name(templateName)));
        }

        HasName::importFull(stream, result, false);
        SplitInstance::importFull(stream, result, false);
        IntervalSet::importFull(stream, result, false);

        return result;
    }
};


// timed full performance of route
class SplitPerformance : public HasMoment, public SplitInstance, public IntervalSet {

public:

    // constructor

    explicit SplitPerformance() : HasMoment(Moment()), SplitInstance(nullptr), IntervalSet(0) {}

    explicit SplitPerformance(const Moment &moment, const SplitTemplate *splitTemplate) :
            HasMoment(moment), SplitInstance(splitTemplate), IntervalSet(splitTemplate->getSize()) {}

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const SplitPerformance &a) {

        return stream << static_cast<HasMoment>(a) << " " << static_cast<IntervalSet>(a);
    }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        HasMoment::exportFull(stream, newObject);
        SplitInstance::exportFull(stream, newObject);
        IntervalSet::exportFull(stream, false);
        return stream;
    }

    static SplitPerformance *importFull(std::istream &stream, SplitPerformance *result, bool newObject) {

        if (newObject) {
            Moment moment;
            Moment::importFull(stream, &moment, true);
            Name templateName;
            Name::importFull(stream, &templateName, true);
            *result = SplitPerformance(
                    moment, &SpeedCategory::getActiveImport()->getSplitTemplateSet().getValue(Name(templateName)));
        }

        HasMoment::importFull(stream, result, false);
        SplitInstance::importFull(stream, result, false);
        IntervalSet::importFull(stream, result, false);

        return result;
    }
};

// time practice of split in route
class SplitPractice : public HasMoment, public SplitInstance {

private:

    // index of relevant split
    int splitIndex;

    // split time
    mutable Period time;

public:

    // constructor

    explicit SplitPractice() : HasMoment(Moment()), SplitInstance(nullptr), time(Period(0)), splitIndex(-1) {}

    explicit SplitPractice(int splitIndex, const Moment &moment, const SplitTemplate *splitTemplate) :
            HasMoment(moment), SplitInstance(splitTemplate), time(Period(0)), splitIndex(splitIndex) {}

    // getter

    Period &getTime() const { return time; }

    // stream operator

    friend std::ostream &operator<<(std::ostream &stream, const SplitPractice &a) {

        return stream << static_cast<HasMoment>(a) << " " << a.splitIndex << " " << a.time;
    }

    // file io

    const std::ostream &exportFull(std::ostream &stream, bool newObject) const override {

        HasMoment::exportFull(stream, newObject);
        SplitInstance::exportFull(stream, newObject);
        stream << splitIndex << " ";
        time.exportFull(stream, false);
        return stream;
    }

    static SplitPractice *importFull(std::istream &stream, SplitPractice *result, bool newObject) {

        if (newObject) {
            Moment moment;
            Moment::importFull(stream, &moment, true);
            Name templateName;
            Name::importFull(stream, &templateName, true);
            int splitIndex;
            stream >> splitIndex;
            *result = SplitPractice(
                    splitIndex, moment,
                    &SpeedCategory::getActiveImport()->getSplitTemplateSet().getValue(Name(templateName)));
        }

        HasMoment::importFull(stream, result, false);
        SplitInstance::importFull(stream, result, false);
        Period::importFull(stream, &result->time, false);

        return result;
    }
};
