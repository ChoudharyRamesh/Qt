#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include<QTreeView>
#include<QLineEdit>
#include<QEvent>
#include "lineedit.h"

class CustomTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CustomTreeView(QWidget *parent = nullptr);
signals:
private:
   LineEdit * lineedit;

};

#endif // CUSTOMTREEVIEW_H
