#ifndef PROGRESSEVENT_H
#define PROGRESSEVENT_H

#include<QEvent>

class ProgressEvent : public QEvent
{
public:
  explicit ProgressEvent( int progressValue=0);
  enum{EventId = QEvent::User+1};
  int getProgressValue() const;

private:
  int progressValue;
};

#endif // PROGRESSEVENT_H
