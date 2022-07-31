#ifndef PROGRESSNUMBER_H
#define PROGRESSNUMBER_H
#include<QMetaType>

class ProgressNumber
{
public:
    ProgressNumber(int progressValue);
    ProgressNumber();
    int getProgressValue() const;

private:
    int progressValue;
};
Q_DECLARE_METATYPE(ProgressNumber)
#endif // PROGRESSNUMBER_H
