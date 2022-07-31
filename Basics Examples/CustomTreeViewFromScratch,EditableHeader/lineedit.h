#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    int currentLogicalIndex;
    explicit LineEdit(QWidget *parent = nullptr);

signals:

};

#endif // LINEEDIT_H
