#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include<QImage>
#include<QRect>
#include<QDir>
#include<QFontDatabase>
#include<QTextDocument>
#include<QtConcurrent/QtConcurrent>
#include<QFileDialog>
#include<QPrinter>
#include<QSettings>
#include<QJsonObject>
#include<QDebug>
#include<QButtonGroup>
#include<QFontDialog>
#include<QRandomGenerator>
#include "view.h"
#include "textitem.h"
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void addPage(const QJsonObject & object=QJsonObject());
    ~Widget();

private slots:
    void on_setPage_clicked();
    void on_clearButton_clicked();
    void addIntoLayout(int fromIndex);
    void generatePdf(QString path);
    void generateImage(QString path);
    void disablebuttons();
    void enableButtons();
    void on_generateButton_clicked();
    void unWatch();
    void displayMessage(QString message,int time=4000);

    void on_fileSelectorButton_clicked();
    void on_openProjectButton_clicked();
    void on_saveProjectButton_clicked();
    void on_penWidthSpinBox_valueChanged(int arg1);

    void on_textEditingRadio_toggled(bool checked);
    void on_autoPageNumberCheckBox_toggled(bool checked);
    void on_windowOnTopCheckBox_toggled(bool checked);
    void on_pen_radio_toggled(bool checked);
    void on_radio_high_toggled(bool checked);

    void on_mirrorEffectCheckBox_toggled(bool checked);
    void on_randomSpacingChekcBox_toggled(bool checked);

    void on_randomPerspectiveCheckBox_toggled(bool checked);
    void on_perspectiveBackgroundButton_clicked();
    void on_randomFgcCheckBox_toggled(bool checked);


private:
    Ui::Widget *ui;
    QList<View *> viewList;
    QFont myfont;
    QPixmap backgroundPage;
    QPixmap background;
    int pageCount=0;
    QLayout * layout=nullptr;
    QColor handwritingColor = QColor(22,38,76,230);
    QString rootPath = "C:/AssignmentGenerator";
    QFutureWatcher<void> watcher;
    QList<QFutureWatcher<void> *> watcherlist;
    int watcherIndexCount = 0;
    int outputQuality=0; //( 0->low ,1->high)
    QSettings setting;
    QJsonObject CurrentProjectJObject;
    QButtonGroup generateGroup,editingButtonGroup,penEraserGroup,OutputQuaButtonGroup;

    int headerMaxHeight=300;
    int pageNumberMaxheight=140;
    int DateMaxheight=110;
    int leftSidePageMaxHeight=3162;
    int rightSidePageMaxHeight=3162;

    //control
    bool isPenEditingEnabled=false; //disable pen,enable pen,disable text, enable text
    int penWidth=4; //set pen width
    bool isPen=true;
    bool setAutoPageNumber=true;
    bool mirrorPage=true;
    bool randomWordSpacing=true;
    bool allowRandomPerspective=true;
    bool allowRandomForegroundColor=true;
    QRectF maxSceneRect;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // WIDGET_H
