#include "progressevent.h"

ProgressEvent::ProgressEvent(int  progressValue ):QEvent(static_cast<QEvent::Type>(EventId))
{
  this->progressValue=progressValue;
}

int ProgressEvent::getProgressValue() const
{
    return progressValue;
}

