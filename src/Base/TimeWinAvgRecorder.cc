/**
 * Recorder that outputs the average of a value over a second
 */

#include "omnetpp/csimulation.h"
#include "omnetpp/cresultrecorder.h"
#include <cmath>

using namespace omnetpp;

class TimeWinAvgRecorder : public cNumericResultRecorder
{
protected:
    int resultCount;
    simtime_t endSecond;
    double sum;
    void *handle;        // identifies output vector for the output vector manager
    simtime_t lastTime;  // to ensure increasing timestamp order
    double lastValue;    // for getCurrentValue()
    virtual void subscribedTo(cResultFilter *prev) override;
    virtual void collect(simtime_t_cref t, double value, cObject *details);
    virtual void finish(cResultFilter *prev) override;
public:
    TimeWinAvgRecorder() {sum = 0; endSecond = endSecond +1; resultCount = 1;}
    virtual ~TimeWinAvgRecorder();
    virtual simtime_t getLastWriteTime() const {return lastTime;}
    virtual double getLastValue() const {return lastValue;}
    virtual std::string str() const override;
};

Register_ResultRecorder("timeWinAvg", TimeWinAvgRecorder);

TimeWinAvgRecorder::~TimeWinAvgRecorder()
{
    if (handle != nullptr)
        getEnvir()->deregisterOutputVector(handle);
}

void TimeWinAvgRecorder::finish(cResultFilter *prev)
{
    double average = sum/resultCount;
    getEnvir()->recordInOutputVector(handle, endSecond, average);
}

void TimeWinAvgRecorder::subscribedTo(cResultFilter *prev)
{
    cNumericResultRecorder::subscribedTo(prev);

    // we can register the vector here, because base class ensures we are subscribed only at once place
    opp_string_map attributes = getStatisticAttributes();

    handle = getEnvir()->registerOutputVector(getComponent()->getFullPath().c_str(), getResultName().c_str());
    ASSERT(handle != nullptr);
    for (opp_string_map::iterator it = attributes.begin(); it != attributes.end(); ++it)
        getEnvir()->setVectorAttribute(handle, it->first.c_str(), it->second.c_str());
}

void TimeWinAvgRecorder::collect(simtime_t_cref t, double value, cObject *details)
{
    if (t < lastTime) {
        throw cRuntimeError("%s: Cannot record data with an earlier timestamp (t=%s) "
                "than the previously recorded value (t=%s)",
                getClassName(), SIMTIME_STR(t), SIMTIME_STR(lastTime));
    }

    lastTime = t;
    lastValue = value;

    if(t < endSecond)
    {
        sum = sum + value;
        resultCount++;
    }else{
        double average = sum/resultCount;
        getEnvir()->recordInOutputVector(handle, endSecond, average);

        resultCount = 1;
        sum = value;

        endSecond = floor(t.dbl()) +1;
    }
}

std::string TimeWinAvgRecorder::str() const
{
    std::stringstream os;
    os << getResultName() << ": ";
    if (std::isnan(lastValue))
        os << "(empty)";
    else
        os << "last write: t=" << getLastWriteTime() << " value=" << getLastValue();
    return os.str();
}
