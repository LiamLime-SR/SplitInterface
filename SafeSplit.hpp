#pragma once
#include "Split.hpp"
#include "Assertion.hpp"

// safe operations on splits with assertions on user input
namespace SafeSplit {

    // retrieve valid name string from stream
    std::string nextName(std::istream &stream, const std::string &message);

    // retrieve valid array size from stream
    int nextSize(std::istream &stream, const std::string &message);

    // retrieve valid array index from stream
    int nextIndex(int max, std::istream &stream, const std::string &message);

    // retrieve parsed period from stream
    Period nextTime(std::istream &stream, const std::string &message);

    // retrieve parsed moment from stream
    Moment nextMoment(std::istream &stream, const std::string &message);

    // create new split template and add to category
    SplitTemplate newSplitTemplate(const std::string &name, int size, const SpeedCategory *speedCategory);

    // get split template from category
    const SplitTemplate *getSplitTemplate(const std::string &name, const SpeedCategory *speedCategory);

    // remove split template from category
    SplitTemplate removeSplitTemplate(const std::string &name, SpeedCategory *speedCategory);

    // fill split template data
    const SplitTemplate *fillSplitTemplate(std::istream &stream, const SplitTemplate *splitTemplate);

    // copy data between split templates
    const SplitTemplate *copySplitTemplate(
            const SplitTemplate *splitTemplateSource, const SplitTemplate *splitTemplateDestination);

    // create new split comparison and add to template
    SplitComparison newSplitComparison(const std::string &name, const SplitTemplate *splitTemplate);

    // get split comparison from category
    const SplitComparison *getSplitComparison(const std::string &name, const SpeedCategory *speedCategory);

    // remove split comparison from category
    SplitComparison removeSplitComparison(const std::string &name, SpeedCategory *speedCategory);

    // fill split comparison data
    const SplitComparison *fillSplitComparison(std::istream &stream, const SplitComparison *splitComparison);

    // copy data between split comparisons
    const SplitComparison *copySplitComparison(
            const SplitComparison *splitComparisonSource, const SplitComparison *splitComparisonDestination);

    // create new split performance and add to template
    SplitPerformance newSplitPerformance(const Moment &moment, const SplitTemplate *splitTemplate);

    // get split performance from category
    const SplitPerformance *getSplitPerformance(const Moment &moment, const SpeedCategory *speedCategory);

    // remove split performance from category
    SplitPerformance removeSplitPerformance(const Moment &moment, SpeedCategory *speedCategory);

    // fill split performance data
    const SplitPerformance *fillSplitPerformance(std::istream &stream, const SplitPerformance *splitPerformance);

    // copy data between split performance
    const SplitPerformance *copySplitPerformance(
            const SplitPerformance *splitPerformanceSource, const SplitPerformance *splitPerformanceDestination);

    // create new split practice and add to template
    SplitPractice newSplitPractice(int splitIndex, const Moment &moment, const SplitTemplate *splitTemplate);

    // get split practice from category
    const SplitPractice *getSplitPractice(const Moment &moment, const SpeedCategory *speedCategory);

    // remove split practice from category
    SplitPractice removeSplitPractice(const Moment &moment, SpeedCategory *speedCategory);
}
