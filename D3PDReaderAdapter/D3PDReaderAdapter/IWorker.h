#ifndef TNPCALIBRATION_IWORKER_H
#define TNPCALIBRATION_IWORKER_H

class TH1;

class IWorker {
public:
    IWorker() = default;
    ~IWorker() = default;

public:
    virtual void addOutput(TH1* histogram) = 0;
};

#endif
