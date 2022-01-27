#include "progressnumber.h"

ProgressNumber::ProgressNumber(int progressValue)
{
    this->progressValue=progressValue;
}

ProgressNumber::ProgressNumber()
{

}

int ProgressNumber::getProgressValue() const
{
    return progressValue;
}
