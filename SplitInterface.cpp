#include "SplitInterface.hpp"

SplitInterface::SplitInterface(std::istream *inputStream, std::ostream *outputStream) :
        Interface(inputStream, outputStream), speedCategory("EMPTY") {

    addCommand("NewCategory", newCategory);
    addCommand("OutputCategory", outputCategory);
    addCommand("ExportCategory", exportCategory);
    addCommand("ImportCategory", importCategory);

    addCommand("NewTemplate", newTemplate);
    addCommand("NewTemplateWithSplits", newTemplateWithSplits);
    addCommand("RenameTemplateAllSplits", renameTemplateAllSplits);
    addCommand("RenameTemplateAtSplit", renameTemplateAtSplit);
    addCommand("CopyTemplateSplits", copyTemplateSplits);
    addCommand("OutputAllTemplates", outputAllTemplates);
    addCommand("OutputAtTemplate", outputAtTemplate);
    addCommand("DeleteTemplate", deleteTemplate);

    addCommand("NewComparison", newComparison);
    addCommand("NewComparisonWithSplits", newComparisonWithSplits);
    addCommand("RetimeComparisonAllSplits", retimeComparisonAllSplits);
    addCommand("RetimeComparisonAtSplit", retimeComparisonAtSplit);
    addCommand("CopyComparisonSplits", copyComparisonSplits);
    addCommand("OutputAllComparisons", outputAllComparisons);
    addCommand("OutputAtComparison", outputAtComparison);
    addCommand("DeleteComparison", deleteComparison);

    addCommand("NewPerformance", newPerformance);
    addCommand("NewPerformanceWithSplits", newPerformanceWithSplits);
    addCommand("RetimePerformanceAllSplits", retimePerformanceAllSplits);
    addCommand("RetimePerformanceAtSplit", retimePerformanceAtSplit);
    addCommand("CopyPerformanceSplits", copyPerformanceSplits);
    addCommand("OutputAllPerformances", outputAllPerformances);
    addCommand("OutputAtPerformance", outputAtPerformance);
    addCommand("DeletePerformance", deletePerformance);

    addCommand("NewPractice", newPractice);
    addCommand("NewPracticeWithTime", newPracticeWithTime);
    addCommand("RetimePractice", retimePractice);
    addCommand("CopyPracticeTime", copyPracticeTime);
    addCommand("OutputAllPractices", outputAllPractices);
    addCommand("OutputAtPractice", outputAtPractice);
    addCommand("DeletePractice", deletePractice);
}

SpeedCategory *SplitInterface::getSpeedCategory() {

    return &speedCategory;
}

SpeedCategory *SplitInterface::extractSpeedCategory(Interface *interface) {

    return dynamic_cast<SplitInterface *>(interface)->getSpeedCategory();
}

// creates new category [CATEGORY_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newCategory =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "category");
            category = SpeedCategory(name);
            out << "NEW CATEGORY:" << std::endl << category << std::endl;
        };

// outputs working category []
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputCategory =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            out << "CURRENT CATEGORY:" << std::endl << category << std::endl;
        };

// exports category to file [FILE_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::exportCategory =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string fileName = SafeSplit::nextName(arg, "file");
            std::ofstream file(fileName);
            Assert::assertIsOpen(file.is_open(), "category");
            category.exportFull(file, true);
            file.close();
            out << "NEW FILE:" << std::endl << fileName << std::endl;
        };

// imports category from file [FILE_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::importCategory =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string fileName = SafeSplit::nextName(arg, "file");
            std::ifstream file(fileName);
            Assert::assertIsOpen(file.is_open(), "category");
            SpeedCategory::importFull(file, &category, true);
            file.close();
            out << "NEW FILE:" << std::endl << fileName << std::endl;
        };

// creates new split template [TEMPLATE_NAME SPLIT_COUNT]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newTemplate =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "template");
            int size = SafeSplit::nextSize(arg, "template");
            SplitTemplate splitTemplate = SafeSplit::newSplitTemplate(name, size, &category);
            category.getSplitTemplateSet().addValue(splitTemplate);
            out << "NEW TEMPLATE:" << std::endl << splitTemplate << std::endl;
        };

// creates new split template with split names [TEMPLATE_NAME SPLIT_COUNT SPLIT_NAMES...]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newTemplateWithSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "template");
            int size = SafeSplit::nextSize(arg, "template");
            SplitTemplate splitTemplate = SafeSplit::newSplitTemplate(name, size, &category);
            SafeSplit::fillSplitTemplate(arg, &splitTemplate);
            category.getSplitTemplateSet().addValue(splitTemplate);
            out << "NEW TEMPLATE:" << std::endl << splitTemplate << std::endl;
        };

// rename all splits in split template [TEMPLATE_NAME SPLIT_NAMES...]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::renameTemplateAllSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(name, &category);
            SafeSplit::fillSplitTemplate(arg, &splitTemplate);
            out << "RENAME TEMPLATE:" << std::endl << splitTemplate << std::endl;
        };

// rename single split in template [TEMPLATE_NAME SPLIT_INDEX SPLIT_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::renameTemplateAtSplit =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string refName = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(refName, &category);
            int index = SafeSplit::nextIndex(splitTemplate.getSize(), arg, "template split");
            std::string newName = SafeSplit::nextName(arg, "template split");
            splitTemplate.getSet()[index] = Name(newName);
            out << "RENAME TEMPLATE:" << std::endl << splitTemplate << std::endl;
        };

// copy split names between split templates [SOURCE_TEMPLATE_NAME DESTINATION_TEMPLATE_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::copyTemplateSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string nameSource = SafeSplit::nextName(arg, "source template");
            std::string nameDestination = SafeSplit::nextName(arg, "destination template");
            const SplitTemplate &splitTemplateSource = *SafeSplit::getSplitTemplate(nameSource, &category);
            const SplitTemplate &splitTemplateDestination = *SafeSplit::getSplitTemplate(nameDestination, &category);
            SafeSplit::copySplitTemplate(&splitTemplateSource, &splitTemplateDestination);
            out << "SOURCE TEMPLATE:" << std::endl << splitTemplateSource << std::endl;
            out << "DESTINATION TEMPLATE:" << std::endl << splitTemplateDestination << std::endl;
        };

// output all templates in category []
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputAllTemplates =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            out << "CURRENT TEMPLATE:" << std::endl << category.getSplitTemplateSet();
        };

// output single template in category [TEMPLATE_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputAtTemplate =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(name, &category);
            out << "CURRENT TEMPLATE:" << std::endl << splitTemplate << std::endl;
        };

// delete template from category [TEMPLATE_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::deleteTemplate =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "template");
            SplitTemplate splitTemplate = SafeSplit::removeSplitTemplate(name, &category);
            out << "DELETE TEMPLATE:" << std::endl << splitTemplate << std::endl;
        };

// create new split comparison [COMPARISON_NAME TEMPLATE_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newComparison =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string comparisonName = SafeSplit::nextName(arg, "comparison");
            std::string templateName = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(templateName, &category);
            SplitComparison splitComparison = SafeSplit::newSplitComparison(comparisonName, &splitTemplate);
            category.getSplitComparisonSet().addValue(splitComparison);
            out << "NEW COMPARISON:" << std::endl << splitTemplate << std::endl << splitComparison << std::endl;
        };

// create new split comparison with split times [COMPARISON_NAME TEMPLATE_NAME SPLIT_TIMES...]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newComparisonWithSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string comparisonName = SafeSplit::nextName(arg, "comparison");
            std::string templateName = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(templateName, &category);
            SplitComparison splitComparison = SafeSplit::newSplitComparison(comparisonName, &splitTemplate);
            SafeSplit::fillSplitComparison(arg, &splitComparison);
            category.getSplitComparisonSet().addValue(splitComparison);
            out << "NEW COMPARISON:" << std::endl << splitTemplate << std::endl << splitComparison << std::endl;
        };

// retime all splits in split comparison [COMPARISON_NAME SPLIT_TIMES...]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::retimeComparisonAllSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "comparison");
            const SplitComparison &splitComparison = *SafeSplit::getSplitComparison(name, &category);
            const SplitTemplate &splitTemplate = *splitComparison.getSplitTemplate();
            SafeSplit::fillSplitComparison(arg, &splitComparison);
            out << "RETIME COMPARISON:" << std::endl << splitTemplate << std::endl << splitComparison << std::endl;
        };

// retime single split in split comparison [COMPARISON_NAME SPLIT_INDEX SPLIT_TIME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::retimeComparisonAtSplit =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string refName = SafeSplit::nextName(arg, "comparison");
            const SplitComparison &splitComparison = *SafeSplit::getSplitComparison(refName, &category);
            const SplitTemplate &splitTemplate = *splitComparison.getSplitTemplate();
            int index = SafeSplit::nextIndex(splitTemplate.getSize(), arg, "comparison split");
            Period newTime = SafeSplit::nextTime(arg, "comparison split");
            splitComparison.getSet()[index] = newTime;
            out << "RETIME COMPARISON:" << std::endl << splitTemplate << std::endl << splitComparison << std::endl;
        };

// copy split times between split comparisons [SOURCE_COMPARISON_NAME DESTINATION_COMPARISON_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::copyComparisonSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string nameSource = SafeSplit::nextName(arg, "source comparison");
            std::string nameDestination = SafeSplit::nextName(arg, "destination comparison");
            const SplitComparison &splitComparisonSource =
                    *SafeSplit::getSplitComparison(nameSource, &category);
            const SplitComparison &splitComparisonDestination =
                    *SafeSplit::getSplitComparison(nameDestination, &category);
            const SplitTemplate &splitTemplateSource = *splitComparisonSource.getSplitTemplate();
            const SplitTemplate &splitTemplateDestination = *splitComparisonDestination.getSplitTemplate();
            SafeSplit::copySplitComparison(&splitComparisonSource, &splitComparisonDestination);
            out <<
                    "SOURCE COMPARISON:" << std::endl <<
                    splitTemplateSource << std::endl <<
                    splitComparisonSource << std::endl;
            out <<
                    "DESTINATION COMPARISON:" << std::endl <<
                    splitTemplateDestination << std::endl <<
                    splitComparisonDestination << std::endl;
        };

// output all split comparisons in category []
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputAllComparisons =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            out << "CURRENT COMPARISON:" << std::endl << category.getSplitComparisonSet();
        };

// output single split comparison in category [COMPARISON_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputAtComparison =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "comparison");
            const SplitComparison &splitComparison = *SafeSplit::getSplitComparison(name, &category);
            const SplitTemplate &splitTemplate = *splitComparison.getSplitTemplate();
            out << "CURRENT COMPARISON:" << std::endl << splitTemplate << std::endl << splitComparison << std::endl;
        };

// delete split comparison from category [COMPARISON_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::deleteComparison =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            std::string name = SafeSplit::nextName(arg, "comparison");
            SplitComparison splitComparison = SafeSplit::removeSplitComparison(name, &category);
            const SplitTemplate &splitTemplate = *splitComparison.getSplitTemplate();
            out << "DELETE COMPARISON:" << std::endl << splitTemplate << std::endl << splitComparison << std::endl;
        };

// create new split performance [PERFORMANCE_MOMENT TEMPLATE_NAME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newPerformance =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment performanceMoment = SafeSplit::nextMoment(arg, "performance");
            std::string templateName = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(templateName, &category);
            SplitPerformance splitPerformance = SafeSplit::newSplitPerformance(performanceMoment, &splitTemplate);
            category.getSplitPerformanceSet().addValue(splitPerformance);
            out << "NEW PERFORMANCE:" << std::endl << splitTemplate << std::endl << splitPerformance << std::endl;
        };

// create new split performance with split times [PERFORMANCE_MOMENT TEMPLATE_NAME SPLIT_TIMES...]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newPerformanceWithSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment performanceMoment = SafeSplit::nextMoment(arg, "performance");
            std::string templateName = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(templateName, &category);
            SplitPerformance splitPerformance = SafeSplit::newSplitPerformance(performanceMoment, &splitTemplate);
            SafeSplit::fillSplitPerformance(arg, &splitPerformance);
            category.getSplitPerformanceSet().addValue(splitPerformance);
            out << "NEW PERFORMANCE:" << std::endl << splitTemplate << std::endl << splitPerformance << std::endl;
        };

// retime all splits in split performance [PERFORMANCE_MOMENT SPLIT_TIMES...]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::retimePerformanceAllSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment moment = SafeSplit::nextMoment(arg, "performance");
            const SplitPerformance &splitPerformance = *SafeSplit::getSplitPerformance(moment, &category);
            const SplitTemplate &splitTemplate = *splitPerformance.getSplitTemplate();
            SafeSplit::fillSplitPerformance(arg, &splitPerformance);
            out << "RETIME PERFORMANCE:" << std::endl << splitTemplate << std::endl << splitPerformance << std::endl;
        };

// retime single split in split performance [PERFORMANCE_MOMENT SPLIT_INDEX SPLIT_TIME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::retimePerformanceAtSplit =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment refMoment = SafeSplit::nextMoment(arg, "performance");
            const SplitPerformance &splitPerformance = *SafeSplit::getSplitPerformance(refMoment, &category);
            const SplitTemplate &splitTemplate = *splitPerformance.getSplitTemplate();
            int index = SafeSplit::nextIndex(splitTemplate.getSize(), arg, "performance split");
            Period newTime = SafeSplit::nextTime(arg, "performance split");
            splitPerformance.getSet()[index] = newTime;
            out << "RETIME PERFORMANCE:" << std::endl << splitTemplate << std::endl << splitPerformance << std::endl;
        };

// copy split times between split performances [SOURCE_PERFORMANCE_MOMENT DESTINATION_PERFORMANCE_MOMENT]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::copyPerformanceSplits =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment momentSource = SafeSplit::nextMoment(arg, "source performance");
            Moment momentDestination = SafeSplit::nextMoment(arg, "destination performance");
            const SplitPerformance &splitPerformanceSource =
                    *SafeSplit::getSplitPerformance(momentSource, &category);
            const SplitPerformance &splitPerformanceDestination =
                    *SafeSplit::getSplitPerformance(momentDestination, &category);
            const SplitTemplate &splitTemplateSource = *splitPerformanceSource.getSplitTemplate();
            const SplitTemplate &splitTemplateDestination = *splitPerformanceDestination.getSplitTemplate();
            SafeSplit::copySplitPerformance(&splitPerformanceSource, &splitPerformanceDestination);
            out <<
                    "SOURCE PERFORMANCE:" << std::endl <<
                    splitTemplateSource << std::endl <<
                    splitPerformanceSource << std::endl;
            out <<
                    "DESTINATION PERFORMANCE:" << std::endl <<
                    splitTemplateDestination << std::endl <<
                    splitPerformanceDestination << std::endl;
        };

// output all split performances in category []
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputAllPerformances =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            out << "CURRENT PERFORMANCE:" << std::endl << category.getSplitPerformanceSet();
        };

// output single split performance in category [PERFORMANCE_MOMENT]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputAtPerformance =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment moment = SafeSplit::nextMoment(arg, "performance");
            const SplitPerformance &splitPerformance = *SafeSplit::getSplitPerformance(moment, &category);
            const SplitTemplate &splitTemplate = *splitPerformance.getSplitTemplate();
            out << "CURRENT PERFORMANCE:" << std::endl << splitTemplate << std::endl << splitPerformance << std::endl;
        };

// delete split performance in category [PERFORMANCE_MOMENT]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::deletePerformance =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment moment = SafeSplit::nextMoment(arg, "performance");
            SplitPerformance splitPerformance = SafeSplit::removeSplitPerformance(moment, &category);
            const SplitTemplate &splitTemplate = *splitPerformance.getSplitTemplate();
            out << "DELETE PERFORMANCE:" << std::endl << splitTemplate << std::endl << splitPerformance << std::endl;
        };

// create new split practice [PRACTICE_MOMENT TEMPLATE_NAME SPLIT_INDEX]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newPractice =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment practiceMoment = SafeSplit::nextMoment(arg, "practice");
            std::string templateName = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(templateName, &category);
            int splitIndex = SafeSplit::nextIndex(splitTemplate.getSize(), arg, "practice split");
            SplitPractice splitPractice = SafeSplit::newSplitPractice(splitIndex, practiceMoment, &splitTemplate);
            category.getSplitPracticeSet().addValue(splitPractice);
            out << "NEW PRACTICE:" << std::endl << splitTemplate << std::endl << splitPractice << std::endl;
        };

// create new split practice with split time [PRACTICE_MOMENT TEMPLATE_NAME SPLIT_INDEX SPLIT_TIME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::newPracticeWithTime =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment practiceMoment = SafeSplit::nextMoment(arg, "practice");
            std::string templateName = SafeSplit::nextName(arg, "template");
            const SplitTemplate &splitTemplate = *SafeSplit::getSplitTemplate(templateName, &category);
            int splitIndex = SafeSplit::nextIndex(splitTemplate.getSize(), arg, "practice split");
            SplitPractice splitPractice = SafeSplit::newSplitPractice(splitIndex, practiceMoment, &splitTemplate);
            splitPractice.getTime() = SafeSplit::nextTime(arg, "practice");
            category.getSplitPracticeSet().addValue(splitPractice);
            out << "NEW PRACTICE:" << std::endl << splitTemplate << std::endl << splitPractice << std::endl;
        };

// retime split practice [PRACTICE_MOMENT SPLIT_TIME]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::retimePractice =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment moment = SafeSplit::nextMoment(arg, "practice");
            const SplitPractice &splitPractice = *SafeSplit::getSplitPractice(moment, &category);
            const SplitTemplate &splitTemplate = *splitPractice.getSplitTemplate();
            splitPractice.getTime() = SafeSplit::nextTime(arg, "practice");
            out << "RETIME PRACTICE:" << std::endl << splitTemplate << std::endl << splitPractice << std::endl;
        };

// copy split times between split practices [SOURCE_PRACTICE_MOMENT DESTINATION_PRACTICE_MOMENT]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::copyPracticeTime =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment momentSource = SafeSplit::nextMoment(arg, "source practice");
            Moment momentDestination = SafeSplit::nextMoment(arg, "destination practice");
            const SplitPractice &splitPracticeSource =
                    *SafeSplit::getSplitPractice(momentSource, &category);
            const SplitPractice &splitPracticeDestination =
                    *SafeSplit::getSplitPractice(momentDestination, &category);
            const SplitTemplate &splitTemplateSource = *splitPracticeSource.getSplitTemplate();
            const SplitTemplate &splitTemplateDestination = *splitPracticeDestination.getSplitTemplate();
            splitPracticeDestination.getTime() = splitPracticeSource.getTime();
            out <<
                "SOURCE PRACTICE:" << std::endl <<
                splitTemplateSource << std::endl <<
                splitPracticeSource << std::endl;
            out <<
                "DESTINATION PRACTICE:" << std::endl <<
                splitTemplateDestination << std::endl <<
                splitPracticeDestination << std::endl;
        };

// output all split practices in category []
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputAllPractices =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            out << "CURRENT PRACTICE:" << std::endl << category.getSplitPracticeSet();
        };

// output single split practice in category [PRACTICE_MOMENT]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::outputAtPractice =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment moment = SafeSplit::nextMoment(arg, "practice");
            const SplitPractice &splitPractice = *SafeSplit::getSplitPractice(moment, &category);
            const SplitTemplate &splitTemplate = *splitPractice.getSplitTemplate();
            out << "CURRENT PRACTICE:" << std::endl << splitTemplate << std::endl << splitPractice << std::endl;
        };

// delete split practice from category [PRACTICE_MOMENT]
const std::function<void(std::istream &, std::ostream &, Interface *)> SplitInterface::deletePractice =
        [](std::istream &arg, std::ostream &out, Interface *interface) {

            SpeedCategory &category = *extractSpeedCategory(interface);
            Moment moment = SafeSplit::nextMoment(arg, "practice");
            SplitPractice splitPractice = SafeSplit::removeSplitPractice(moment, &category);
            const SplitTemplate &splitTemplate = *splitPractice.getSplitTemplate();
            out << "DELETE PRACTICE:" << std::endl << splitTemplate << std::endl << splitPractice << std::endl;
        };
