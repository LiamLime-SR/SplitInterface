#pragma once
#include <fstream>
#include "Interface.hpp"
#include "SafeSplit.hpp"

// interface for split operations
class SplitInterface : public Interface {

private:

    // current working category
    SpeedCategory speedCategory;

public:

    // constructor

    explicit SplitInterface(std::istream *inputStream, std::ostream *outputStream);

    // getter

    SpeedCategory *getSpeedCategory();

    static SpeedCategory *extractSpeedCategory(Interface *interface);

    // operator

    static const std::function<void(std::istream &, std::ostream &, Interface *)> newCategory;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputCategory;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> exportCategory;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> importCategory;

    static const std::function<void(std::istream &, std::ostream &, Interface *)> newTemplate;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> newTemplateWithSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> renameTemplateAllSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> renameTemplateAtSplit;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> copyTemplateSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputAllTemplates;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputAtTemplate;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> deleteTemplate;

    static const std::function<void(std::istream &, std::ostream &, Interface *)> newComparison;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> newComparisonWithSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> retimeComparisonAllSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> retimeComparisonAtSplit;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> copyComparisonSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputAllComparisons;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputAtComparison;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> deleteComparison;

    static const std::function<void(std::istream &, std::ostream &, Interface *)> newPerformance;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> newPerformanceWithSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> retimePerformanceAllSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> retimePerformanceAtSplit;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> copyPerformanceSplits;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputAllPerformances;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputAtPerformance;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> deletePerformance;

    static const std::function<void(std::istream &, std::ostream &, Interface *)> newPractice;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> newPracticeWithTime;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> retimePractice;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> copyPracticeTime;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputAllPractices;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> outputAtPractice;
    static const std::function<void(std::istream &, std::ostream &, Interface *)> deletePractice;
};
