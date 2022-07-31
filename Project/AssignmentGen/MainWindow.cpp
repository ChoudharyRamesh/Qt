#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QStandardPaths>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,setting("QByteCore","AssignmentGenerator")
{

    ui->setupUi(this);

    generateGroup.addButton(ui->radio_pdf);
    generateGroup.addButton(ui->radio_image);
    editingButtonGroup.addButton(ui->drawingRadio);
    editingButtonGroup.addButton(ui->textEditingRadio);
    penEraserGroup.addButton(ui->pen_radio);
    penEraserGroup.addButton(ui->eraser_radio);
    OutputQuaButtonGroup.addButton(ui->radio_low);
    OutputQuaButtonGroup.addButton(ui->radio_high);

    ui->clearButton->setFocus();
    ui->radio_pdf->setChecked(true);
    ui->pageSpinBox->setRange(1,1000);
    ui->pageSpinBox->setValue(1);
    ui->radio_pdf->setChecked(true);
    ui->filePathLine->setReadOnly(true);
    ui->textEditingRadio->setChecked(true);
    ui->penWidthSpinBox->setRange(1,100);
    ui->penWidthSpinBox->setValue(4);
    ui->autoPageNumberCheckBox->setChecked(true);
    ui->pen_radio->setChecked(true);
    ui->radio_low->setChecked(true);
    ui->mirrorEffectCheckBox->setChecked(true);
    ui->randomSpacingChekcBox->setChecked(true);
    ui->randomPerspectiveCheckBox->setChecked(true);
    ui->randomFgcCheckBox->setChecked(true);


    layout = ui->scrollAreaWidget->layout();
    setWindowTitle("Assignment Generator");
    setMaximumWidth(810);
    setGeometry(730,30,810,800);


    //setFont
    int id = QFontDatabase::addApplicationFont(":/Fonts/MyFont.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    myfont.setFamily(family);
    myfont.setPixelSize(82); //customFont.setPointSize(50);

    //set background page
    backgroundPage.load(":/Template/MyFontGrey.png");//height = 3512
    maxSceneRect.setRect(0,0,backgroundPage.width(),backgroundPage.height());

    //load path from setting
    QString savePath = setting.value("rooPath").toString();
    if(savePath.isEmpty())
        setting.setValue("rooPath",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/AssignmentGen");
    else rootPath = savePath;
    // check path existance
    if(!QDir(rootPath).exists())
        QDir().mkpath(rootPath);
    ui->filePathLine->setText(rootPath);

    //set background
    background = QPixmap(backgroundPage.width(),backgroundPage.height());
    background.fill(Qt::black);

    on_setPage_clicked(); // addPage();
}

void Widget::addPage(const QJsonObject & jobject)
{
    //increase page count
    pageCount++;

    View * view  = new View();
    Scene * scene = new Scene(&isPenEditingEnabled,&penWidth,&isPen,&maxSceneRect,view);

    TextItem * textItem = new TextItem(rightSidePageMaxHeight,&randomWordSpacing);
    TextItem * sideTextItem = new TextItem(leftSidePageMaxHeight);
    TextItem * pageNumber = new TextItem(pageNumberMaxheight);
    TextItem * Date = new TextItem(DateMaxheight);
    TextItem * header = new TextItem(headerMaxHeight);

    scene->textItem=textItem;
    scene->sideTextItem = sideTextItem;
    scene->pageNumber = pageNumber;
    scene->Date = Date;
    scene->header = header;


    //add background
    scene->addPixmap(backgroundPage);

    //set page ,it's offset and styles
    textItem->setPos(252,350);
    textItem->setTextWidth(backgroundPage.width()-250);
    textItem->setFont(myfont);
    if(isPenEditingEnabled==false)
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    textItem->setDefaultTextColor(handwritingColor);
    textItem->document()->setMaximumBlockCount(28);
    scene->addItem(textItem);


    //set sider page
    sideTextItem->setPos(20,350);
    sideTextItem->setTextWidth(210);
    sideTextItem->setFont(myfont);
    if(isPenEditingEnabled==false)
        sideTextItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    sideTextItem->setDefaultTextColor(handwritingColor);
    sideTextItem->document()->setMaximumBlockCount(28);
    scene->addItem(sideTextItem);


    //add page number
    pageNumber->setFont(myfont);
    pageNumber->setPos(2280,60);
    pageNumber->setTextWidth(200);
    pageNumber->document()->setMaximumBlockCount(1);
    pageNumber->setDefaultTextColor(handwritingColor);
    if(isPenEditingEnabled==false)
        pageNumber->setTextInteractionFlags(Qt::TextEditorInteraction);
    scene->addItem(pageNumber);


    // add date
    QFont datefont = myfont;
    datefont.setPixelSize(60);
    Date->setFont(datefont);
    Date->setPos(2180,160);
    Date->setTextWidth(300);
    Date->document()->setMaximumBlockCount(1);
    if(isPenEditingEnabled==false)
        Date->setTextInteractionFlags(Qt::TextEditorInteraction);
    Date->setDefaultTextColor(handwritingColor);
    scene->addItem(Date);

    //add header
    QFont headerfont = myfont;
    headerfont.setPixelSize(70);
    header->setFont(headerfont);
    header->setPos(0,2);
    header->setTextWidth(2480);
    header->document()->setMaximumBlockCount(3);
    if(isPenEditingEnabled==false)
        header->setTextInteractionFlags(Qt::TextEditorInteraction);
    header->setDefaultTextColor(handwritingColor);
    scene->addItem(header);

    view->scale(0.25,0.26);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setMinimumHeight(scene->height()*0.26);


    if(!jobject.isEmpty())
    {
        textItem->setPlainText(jobject["rc"].toString());
        sideTextItem->setPlainText(jobject["lc"].toString());
        pageNumber->setPlainText(jobject["pnc"].toString());
        Date->setPlainText(jobject["dc"].toString());
        header->setPlainText(jobject["hc"].toString());

        QJsonArray lineArray = jobject["lineArray"].toArray();
        QJsonObject object;
        QPen pen;
        pen.setColor(handwritingColor);
        Line * line;
        QPointF p1,p2;
        for(int i=0;i<lineArray.size();i++)
        {
            object = lineArray.at(i).toObject();
            pen.setWidth(object["penwidth"].toInt());

            p1.setX(qreal(object["x1"].toDouble()));
            p1.setY(qreal(object["y1"].toDouble()));
            p2.setX(qreal(object["x2"].toDouble()));
            p2.setY(qreal(object["y2"].toDouble()));

            line = new Line(p1,p2,pen);
            scene->addItem(line);
        }
    }
    else  if(setAutoPageNumber)
        pageNumber->setPlainText(QString::number(pageCount));

    view->setScene(scene);
    viewList.append(view);

}

Widget::~Widget()
{
    qDeleteAll(viewList);
    delete ui;
}

void Widget::on_setPage_clicked()
{
    int currentPageCount = ui->pageSpinBox->value();
    if(currentPageCount==this->pageCount)return;
    int addCount = currentPageCount-pageCount;
    int fromCount = pageCount;
    if(currentPageCount>pageCount)
    {
        for(int i=0;i<addCount;i++)
            addPage();
        addIntoLayout(fromCount);
    }
    else
    {
        int delpage = pageCount-currentPageCount;
        for(int i=0;i<delpage;i++)
        {
            auto gview = viewList.last();
            layout->removeWidget(gview);
            delete gview;
            viewList.removeLast();
            pageCount--;
        }
    }

}

void Widget::on_clearButton_clicked()
{
    int size = viewList.size();
    for(int i=0;i<size;i++)
    {
        auto gview = viewList.last();
        layout->removeWidget(gview);
        delete gview;
        viewList.removeLast();
        pageCount--;
    }
    ui->pageSpinBox->setValue(0);
}

void Widget::addIntoLayout(int fromIndex)
{
    int size = viewList.size();
    for(int i=fromIndex;i<size;i++)
        layout->addWidget(viewList.at(i));
}


void Widget::unWatch()
{
    watcherIndexCount--;
    if(watcherIndexCount==0)
    {
        qDeleteAll(watcherlist);
        watcherlist.clear();
        enableButtons();
    }
}


void Widget::disablebuttons()
{
    ui->messageLabel->setText("Saving...");
    ui->clearButton->setEnabled(false);
    ui->generateButton->setEnabled(false);
    ui->radio_pdf->setEnabled(false);
    ui->radio_image->setEnabled(false);
    ui->pageSpinBox->setEnabled(false);
    ui->scrollAreaWidget->setEnabled(false);
    ui->setPage->setEnabled(false);
    ui->fileSelectorButton->setEnabled(false);
    ui->openProjectButton->setEnabled(false);
    ui->saveProjectButton->setEnabled(false);
    ui->drawingRadio->setEnabled(false);
    ui->filePathLine->setEnabled(false);
    ui->textEditingRadio->setEnabled(false);
    ui->penWidthSpinBox->setEnabled(false);
    ui->autoPageNumberCheckBox->setEnabled(false);
    ui->pen_radio->setEnabled(false);
    ui->radio_low->setEnabled(false);
    ui->radio_high->setEnabled(false);
    ui->mirrorEffectCheckBox->setEnabled(false);
    ui->randomSpacingChekcBox->setEnabled(false);
    ui->randomPerspectiveCheckBox->setEnabled(false);
    ui->perspectiveBackgroundButton->setEnabled(false);
    ui->randomFgcCheckBox->setEnabled(false);

}

void Widget::enableButtons()
{
    ui->clearButton->setEnabled(true);
    ui->generateButton->setEnabled(true);
    ui->radio_pdf->setEnabled(true);
    ui->radio_image->setEnabled(true);
    ui->pageSpinBox->setEnabled(true);
    ui->setPage->setEnabled(true);
    ui->scrollAreaWidget->setEnabled(true);
    ui->messageLabel->clear();
    ui->fileSelectorButton->setEnabled(true);
    ui->openProjectButton->setEnabled(true);
    ui->saveProjectButton->setEnabled(true);
    ui->drawingRadio->setEnabled(true);
    ui->filePathLine->setEnabled(true);
    ui->textEditingRadio->setEnabled(true);
    ui->penWidthSpinBox->setEnabled(true);
    ui->autoPageNumberCheckBox->setEnabled(true);
    ui->pen_radio->setEnabled(true);
    ui->radio_low->setEnabled(true);
    ui->radio_high->setEnabled(true);
    ui->mirrorEffectCheckBox->setEnabled(true);
    ui->randomSpacingChekcBox->setEnabled(true);
    ui->randomPerspectiveCheckBox->setEnabled(true);
    ui->perspectiveBackgroundButton->setEnabled(true);
    ui->randomFgcCheckBox->setEnabled(true);

}


void Widget::on_generateButton_clicked()
{
    if(viewList.size()<=0)
    {
        displayMessage("Nothing to generate",2000);
        return;
    }
    QString path;
    if(ui->radio_image->isChecked())
    {
        path = QFileDialog::getSaveFileName(this, tr("Save File"),rootPath+"/untitled.png", "*.png");
        if(path.isEmpty())return;
        path = path.remove(".png");
    }
    else
    {
        path = QFileDialog::getSaveFileName(this, tr("Save File"),rootPath+"/untitled.pdf", "*.pdf");
        if(path.isEmpty())return;
    }

    disablebuttons();
    if(ui->radio_image->isChecked())generateImage(path);
    else generatePdf(path);

}

void Widget::generatePdf(QString path)
{
    auto function = [this,path](){
        QPrinter printer;
        printer.setFullPage(true);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(path);
        QPainter pdfPainter(&printer);
        QGraphicsScene * scene=nullptr;
        QPixmap tempPixmap;
        QTransform rotateTransfrom;
        rotateTransfrom.rotate(180);
        int size = viewList.size();


        for(int i=0;i<size;i++)
        {
            scene = viewList.at(i)->scene();
            QPixmap pixmap(scene->width(),scene->height());
            QPainter painter(&pixmap);
            scene->render(&painter,pixmap.rect(),QRectF(10,10,pixmap.width()-20,pixmap.height()-20));
            if(mirrorPage)
            {
                bool ok = false;
                if(i%2==0)
                {
                    if(i+1<size)
                    {
                        scene = viewList.at(i+1)->scene();
                        ok=true;
                    }
                }
                else
                {
                    if(i-1>=0)
                    {
                        scene = viewList.at(i-1)->scene();
                        ok=true;
                    }
                }
                if(ok)
                {
                    QImage image(scene->width(),scene->height(),QImage::Format_ARGB32);
                    QPainter imagePainter(&image);
                    scene->render(&imagePainter,image.rect(),QRectF(10,10,pixmap.width()-20,pixmap.height()-20));
                    imagePainter.end();
                    image  = image.mirrored();
                    image  = image.transformed(rotateTransfrom);
                    tempPixmap = QPixmap::fromImage(image);
                    painter.setOpacity(0.13);
                    painter.drawPixmap(pixmap.rect(),tempPixmap,tempPixmap.rect());
                }
            }
            painter.end();

            if(!outputQuality)//low Q
                pixmap = pixmap.scaled(pixmap.width()*0.3,pixmap.height()*0.3,Qt::KeepAspectRatio);

            if(allowRandomPerspective)//perspective
            {
                QPolygonF targetArea,selectedArea;
                targetArea<<QPoint(0,0)<<QPoint(scene->width(),0)<<
                            QPoint(scene->width(),scene->height())<<QPoint(0,scene->height());

                int max = 50;
                int a =  QRandomGenerator::global()->bounded(-max,max);
                int b =  QRandomGenerator::global()->bounded(-max/2,max+a);
                int c =  QRandomGenerator::global()->bounded(-max/2,max+b);
                int d =  QRandomGenerator::global()->bounded(-max/2,max+c);
                int e =  QRandomGenerator::global()->bounded(-max/2,max+d);
                int f =   QRandomGenerator::global()->bounded(-max/2,max+e);
                int g =  QRandomGenerator::global()->bounded(-max/2,max+f);
                int h =  QRandomGenerator::global()->bounded(-max/2,max+g);

                selectedArea<<QPoint(a,b)<<QPoint(scene->width()+c,d)<<
                              QPoint(scene->width()+e,scene->height()+f)<<QPoint(g,scene->height()+h);

                QTransform transform;
                if(QTransform::quadToQuad(selectedArea, targetArea, transform))
                    pixmap = pixmap.transformed(transform,Qt::SmoothTransformation);

                QPixmap tempMap(background);
                QPainter(&tempMap).drawPixmap(tempMap.rect(),pixmap,pixmap.rect());
                pixmap = tempMap;
            }


            if(allowRandomForegroundColor)//random foreground
            {
                int red =  QRandomGenerator::global()->bounded(80,110);
                int green =  QRandomGenerator::global()->bounded(120,170);
                int blue =  QRandomGenerator::global()->bounded(230,255);
                int opac = QRandomGenerator::global()->bounded(20,50);
                QPainter(&pixmap).fillRect(pixmap.rect(),QBrush(QColor::fromRgb(red,green,blue,opac)));
            }

            pdfPainter.drawPixmap(QRectF(0,0,printer.width(),printer.height()),pixmap,pixmap.rect());
            if(i+1<size) printer.newPage();
        }
    };
    watcher.setFuture(QtConcurrent::run(function));
    connect(&watcher,&QFutureWatcher<void>::finished,[this](){enableButtons();});
}


void Widget::generateImage(QString path)
{
    int size = viewList.size();
    auto function = [this,path](int start,int end){

        QGraphicsScene * scene=nullptr;
        QPixmap tempPixmap;
        QTransform rotateTransfrom;
        rotateTransfrom.rotate(180);

        for(int i=start;i<end;i++)
        {
            scene = viewList.at(i)->scene();
            QPixmap pixmap(scene->width(),scene->height());
            QPainter painter(&pixmap);
            scene->render(&painter,pixmap.rect(),QRectF(10,10,pixmap.width()-20,pixmap.height()-20));
            if(mirrorPage)
            {
                bool ok = false;
                if(i%2==0)
                {
                    if(i+1<end)
                    {
                        scene = viewList.at(i+1)->scene();
                        ok=true;
                    }
                }
                else
                {
                    if(i-1>=start)
                    {
                        scene = viewList.at(i-1)->scene();
                        ok=true;
                    }
                }
                if(ok)
                {
                    QImage image(scene->width(),scene->height(),QImage::Format_ARGB32);
                    QPainter imagePainter(&image);
                    scene->render(&imagePainter,image.rect(),QRectF(10,10,pixmap.width()-20,pixmap.height()-20));
                    imagePainter.end();
                    image  = image.mirrored();
                    image  = image.transformed(rotateTransfrom);
                    tempPixmap = QPixmap::fromImage(image);
                    painter.setOpacity(0.15);
                    painter.drawPixmap(pixmap.rect(),tempPixmap,tempPixmap.rect());
                }
            }
            painter.end();


            if(allowRandomPerspective)
            {
                QPolygonF targetArea,selectedArea;
                targetArea<<QPoint(0,0)<<QPoint(scene->width(),0)<<
                            QPoint(scene->width(),scene->height())<<QPoint(0,scene->height());

                int max = 50;
                int a =  QRandomGenerator::global()->bounded(-max,max);
                int b =  QRandomGenerator::global()->bounded(-max/2,max+a);
                int c =  QRandomGenerator::global()->bounded(-max/2,max+b);
                int d =  QRandomGenerator::global()->bounded(-max/2,max+c);
                int e =  QRandomGenerator::global()->bounded(-max/2,max+d);
                int f =   QRandomGenerator::global()->bounded(-max/2,max+e);
                int g =  QRandomGenerator::global()->bounded(-max/2,max+f);
                int h =  QRandomGenerator::global()->bounded(-max/2,max+g);

                selectedArea<<QPoint(a,b)<<QPoint(scene->width()+c,d)<<
                              QPoint(scene->width()+e,scene->height()+f)<<QPoint(g,scene->height()+h);

                QTransform transform;
                if(QTransform::quadToQuad(selectedArea, targetArea, transform))
                    pixmap = pixmap.transformed(transform,Qt::SmoothTransformation);

                QPixmap tempMap(background);
                QPainter(&tempMap).drawPixmap(tempMap.rect(),pixmap,pixmap.rect());
                pixmap = tempMap;
            }

            if(allowRandomForegroundColor)//random foreground
            {
                int red =  QRandomGenerator::global()->bounded(80,110);
                int green =  QRandomGenerator::global()->bounded(120,170);
                int blue =  QRandomGenerator::global()->bounded(230,255);
                int opac = QRandomGenerator::global()->bounded(20,50);
                QPainter(&pixmap).fillRect(pixmap.rect(),QBrush(QColor::fromRgb(red,green,blue,opac)));
            }

            if(!outputQuality)
                pixmap = pixmap.scaled(pixmap.width()*0.3,pixmap.height()*0.3,Qt::KeepAspectRatio);
            pixmap.save(path+QString::number(i+1)+".png");
        }
    };

    int threadSize = 2;
    if(size>=20) threadSize = 4;
    if(size>=100)threadSize= 8;
    if(size>=300)threadSize=16;
    if(size>=700)threadSize=32;

    int onethread = size/threadSize;
    QFuture<void> future;
    for(int i=0;i<threadSize;i++)
    {
        QFutureWatcher<void> * watcher  = new QFutureWatcher<void>();
        watcherlist.append(watcher);
        if(i==threadSize-1)future =   QtConcurrent::run(function,i*onethread,size);
        else  future = QtConcurrent::run(function,i*onethread,(i+1)*onethread);
        watcher->setFuture(future);
        connect(watcher,&QFutureWatcher<void>::finished,[this](){unWatch();});
        watcherIndexCount++;
    }

}


void Widget::on_fileSelectorButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,"Select Dir",rootPath);
    if(path.isEmpty())return;
    rootPath = path;
    setting.setValue("rooPath",rootPath);
    ui->filePathLine->setText(rootPath);
}

void Widget::displayMessage(QString message, int time)
{
    ui->messageLabel->setText(message);
    QTimer::singleShot(time,this,[this](){ ui->messageLabel->clear();});
    return;
}

void Widget::on_openProjectButton_clicked()
{
    if(!viewList.isEmpty())
    {
        displayMessage("Firsrt clear current project");
        return;
    }

    QString fileUrl = QFileDialog::getOpenFileName(this, tr("Open File"),rootPath,"*.as");
    if(fileUrl.isEmpty())return;

    QFile file(fileUrl);
    if(!file.open(QFile::ReadOnly))
    {
        displayMessage("File is not opening");
        return;
    }

    QString data = file.readAll();
    file.close();
    QJsonArray pageArray  = QJsonDocument::fromJson(data.toUtf8()).array();

    int fromCount = pageCount;
    for(int i=0;i<pageArray.size();i++){
        addPage(pageArray.at(i).toObject());
    }
    addIntoLayout(fromCount);
    ui->pageSpinBox->setValue(pageCount);
}


void Widget::on_saveProjectButton_clicked()
{
    if(viewList.isEmpty())
    {
        displayMessage("Nothing to save");
        return;
    }

    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),rootPath+"/untitled.as", "*.as");
    if(path.isEmpty())return;

    QFile file(path);
    if(!file.open(QFile::WriteOnly))return;

    ui->messageLabel->setText("Saving...");
    disablebuttons();
    QJsonArray jarray;
    QString hc,pnc,dc,lc,rc;
    for(int i=0;i<viewList.size();i++)
    {
        QJsonObject jobject;
        Scene * scene = (Scene *) viewList.at(i)->scene();
        hc = scene->header->toPlainText();
        dc  = scene->Date->toPlainText();
        pnc  = scene->pageNumber->toPlainText();
        lc  =scene->sideTextItem->toPlainText();
        rc  = scene->textItem->toPlainText();

        jobject.insert("hc",hc);
        jobject.insert("dc",dc);
        jobject.insert("pnc",pnc);
        jobject.insert("lc",lc);
        jobject.insert("rc",rc);

        QJsonArray GraphicsLineArray;
        auto items  = scene->items();
        QJsonObject graphicsObject;
        Line * graphicsLine=nullptr;
        QLineF  line;
        for(int i=0;i<items.size();i++){
            graphicsLine =   dynamic_cast<Line *>(items.at(i));
            if(graphicsLine==nullptr)continue;
            line = graphicsLine->line();

            graphicsObject.insert("x1",line.x1());
            graphicsObject.insert("y1",line.y1());
            graphicsObject.insert("x2",line.x2());
            graphicsObject.insert("y2",line.y2());
            graphicsObject.insert("penwidth",graphicsLine->pen().width());
            GraphicsLineArray.append(graphicsObject);
        }
        jobject.insert("lineArray",GraphicsLineArray);

        jarray.append(jobject);
    }

    QString finalData = QJsonDocument(jarray).toJson();
    file.write(finalData.toUtf8());
    file.close();
    enableButtons();
}

void Widget::on_penWidthSpinBox_valueChanged(int arg1){
    penWidth=arg1;
}

void Widget::on_textEditingRadio_toggled(bool checked){
    if(checked)
    {
        isPenEditingEnabled=false;
        int page = viewList.size();
        ui->pen_radio->setEnabled(false);
        ui->eraser_radio->setEnabled(false);
        ui->penWidthSpinBox->setEnabled(false);
        for(int i=0;i<page;i++)
        {
            Scene * scene = (Scene *)viewList.at(i)->scene();
            scene->textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            scene->sideTextItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            scene->pageNumber->setTextInteractionFlags(Qt::TextEditorInteraction);
            scene->Date->setTextInteractionFlags(Qt::TextEditorInteraction);
            scene->header->setTextInteractionFlags(Qt::TextEditorInteraction);
        }
    }
    else
    {
        isPenEditingEnabled=true;
        int page = viewList.size();
        ui->pen_radio->setEnabled(true);
        ui->eraser_radio->setEnabled(true);
        ui->penWidthSpinBox->setEnabled(true);
        for(int i=0;i<page;i++)
        {
            Scene * scene = (Scene *)viewList.at(i)->scene();
            scene->textItem->setTextInteractionFlags(Qt::NoTextInteraction);
            scene->sideTextItem->setTextInteractionFlags(Qt::NoTextInteraction);
            scene->pageNumber->setTextInteractionFlags(Qt::NoTextInteraction);
            scene->Date->setTextInteractionFlags(Qt::NoTextInteraction);
            scene->header->setTextInteractionFlags(Qt::NoTextInteraction);
        }
    }
}

void Widget::on_autoPageNumberCheckBox_toggled(bool checked){
    setAutoPageNumber=checked;
}

void Widget::on_windowOnTopCheckBox_toggled(bool checked){
    if(checked)setWindowFlag(Qt::WindowStaysOnTopHint,true);
    else setWindowFlag(Qt::WindowStaysOnTopHint,false);
    show();
}

void Widget::on_pen_radio_toggled(bool checked){
    isPen=checked;
}

void Widget::keyPressEvent(QKeyEvent *event){
    if(event->modifiers()==Qt::ShiftModifier  && event->key()==Qt::Key_E)
    {
        if(ui->pen_radio->isChecked())ui->eraser_radio->setChecked(true);
        else ui->pen_radio->setChecked(true);
    }
    else  return QWidget::keyPressEvent(event);
}

void Widget::on_radio_high_toggled(bool checked)
{
    outputQuality=checked;
}

void Widget::on_mirrorEffectCheckBox_toggled(bool checked)
{
    mirrorPage=checked;
}

void Widget::on_randomSpacingChekcBox_toggled(bool checked)
{
    randomWordSpacing=checked;
}

void Widget::on_randomPerspectiveCheckBox_toggled(bool checked)
{
    allowRandomPerspective= checked;
    if(checked)ui->perspectiveBackgroundButton->setEnabled(true);
    else ui->perspectiveBackgroundButton->setEnabled(false);
}

void Widget::on_perspectiveBackgroundButton_clicked()
{
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("Open File"),rootPath,"*.png *.jpg");
    if(fileUrl.isEmpty()){
        displayMessage("Cancelled",2000);
        return;
    }
    background.load(fileUrl);
    background = background.scaled(backgroundPage.width(),backgroundPage.height());
    displayMessage("background set successfully",2000);
}

void Widget::on_randomFgcCheckBox_toggled(bool checked)
{
    allowRandomForegroundColor=checked;
}
