
/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "arrow.h"
#include "diagramitem.h"
#include "diagramscene.h"
#include "diagramtextitem.h"
#include "mainwindow.h"

#include <QtWidgets>
#include <QList>
#include <QGraphicsItemGroup>

const int InsertTextButton = 10;

//! [0]
MainWindow::MainWindow()
{
    createActions();
    createToolBox();
    createMenus();

    scene = new DiagramScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(itemInserted(DiagramItem*)),
            this, SLOT(itemInserted(DiagramItem*)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
            this, SLOT(textInserted(QGraphicsTextItem*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);
}
//! [0]
//!
QList <QGraphicsItem *> list;
int i;
bool cutflag = false, groupflag = false;
void MainWindow::copyFunction() {
    list.clear();
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        list.append(item);
    }
}

QList <QGraphicsItem *> pasteList;
int dx = 50, dy = 50;
void MainWindow::pasteFunction() {
    foreach (QGraphicsItem *item, list) {
        if (item->type() == DiagramItem::Type) {
            DiagramItem *tmp = qgraphicsitem_cast<DiagramItem*>(item);
            DiagramItem *diagramitem = new DiagramItem(tmp->diagramType(), itemMenu);
            diagramitem->setX(item->x() + dx);
            diagramitem->setY(item->y() + dy);
            scene->addItem(diagramitem);
        }
        else if (item->type() == Arrow::Type) {
            Arrow *tmp = qgraphicsitem_cast<Arrow*>(item);
            Arrow *arrow = new Arrow(tmp->startItem(),tmp->endItem());
            arrow->setX(item->x());
            arrow->setY(item->y());
            scene->addItem(arrow);
            break;
        }
        else if (item->type() == DiagramTextItem::Type) {
            DiagramTextItem *tmp = qgraphicsitem_cast<DiagramTextItem*>(item);
            DiagramTextItem *text = new DiagramTextItem();
            text->setX(item->x() + dx);
            text->setY(item->y() + dy);
            text->setFont(tmp->font());
            text->setPlainText(tmp->toPlainText());
            scene->addItem(text);
        }
        dx += 50, dy += 50;
    }
}

void MainWindow::cutFunction() {
    list.clear();
    cutflag = true;
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        list.append(item);
        i = list.length();
        scene->removeItem(item);
    }
}

QGraphicsItemGroup *group;
QList <QGraphicsItemGroup *> grouplist;
QList <QGraphicsItem *> tmplist;
void MainWindow::groupFunction() {
    groupflag = true;
    group = scene->createItemGroup(scene->selectedItems());
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        tmplist.append(item);
    }
    grouplist.append(group);
    group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}
bool ungroupflag = false;
void MainWindow::ungroupFunction() {
    ungroupflag = true;
    scene->destroyItemGroup(group);
}
bool undoflag = false;
bool undogroup = false;
bool redoflag = false;
void MainWindow::undoFunction() {
    undoflag = true;
    if (cutflag == true) {
        cutflag = false;
        i--;
        scene->addItem(list.at(i));
        return;
    }
    if (redoflag) {
        redoflag = false;
        i--;
        scene->addItem(list.at(i));
        return;
    }
    if (groupflag == true) {
        groupflag = false;
        scene->destroyItemGroup(group);
        return;
    }
    if (ungroupflag == true) {
        ungroupflag = false;
        group = scene->createItemGroup(scene->selectedItems());
        group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        return;
    }
    list.append(scene->items().front());
    i = list.length();
    scene->removeItem(scene->items().front());

}

void MainWindow::redoFunction() {
    redoflag = true;
    if (undoflag && !groupflag) {
        undoflag = false;
        group = scene->createItemGroup(scene->selectedItems());
        group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        return;
    }
    if (undoflag && !cutflag) {
        undoflag = false;
        i = list.length();
        scene->removeItem(scene->items().front());
        return;
    }
    if (undoflag) {
        undoflag = false;
        list.append(scene->items().front());
        i = list.length();
        scene->removeItem(scene->items().front());
        return;
    }
    if (list.isEmpty() || i < 0) {return;}
    i--;
    scene->addItem(list.at(i));

}
bool saveflag = false;
QString filename;
void MainWindow::saveFunction() {

    if (!saveflag) {
        filename = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath());
        //QFile file(fileName);
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Could not save"), tr("Error"), QMessageBox::Retry);
        return;
    }
    saveflag = true;
    QTextStream out(&file);
    int idcount = 0;
    foreach(QGraphicsItem *item, scene->items()) {
        if (item->type() == DiagramItem::Type) {
            DiagramItem *diagramitem = qgraphicsitem_cast<DiagramItem*>(item);
            int mytag = diagramitem->diagramitemtag + idcount;
            int type = diagramitem->diagramType();
            int xpos = diagramitem->x();
            int ypos = diagramitem->y();
            QString fillcolor = diagramitem->brush().color().name();
            QString lineColor = diagramitem->pen().color().name();
            out << mytag <<","<< type << ","<< xpos << ","
                << ypos << ","<< fillcolor << ","<< lineColor << endl;
        }
        else if (item->type() == Arrow::Type) {
            Arrow *arrow = qgraphicsitem_cast<Arrow*>(item);
            int mytag = arrow->arrowtag + idcount;
            int startItem = arrow->startItem()->diagramitemtag;
            int endItem = arrow->endItem()->diagramitemtag;
            QString lineColor = arrow->getColor().name();
            int lineWidth = arrow->pen().width();
            out << mytag <<","<< "LINE" << ","<< startItem << ","
                << endItem << ","<< lineColor << ","<< lineWidth << endl;
        }
        else if (item->type() == DiagramTextItem::Type) {
            DiagramTextItem *text = qgraphicsitem_cast<DiagramTextItem*>(item);
            int mytag = text->texttag + idcount;
            int textx = text->x();
            int texty = text->y();
            QString font = text->font().family();
            int size = text->font().pointSize();
            QString message = text->toPlainText();
            out << mytag <<","<< "TEXT" << ","<< textx << ","
                << texty << ","<< font << ","<< size << "," << message << endl;
        }
        idcount++;
    }
    file.close();
}
void MainWindow::saveAsFunction() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath());
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Could not save"), tr("Error"), QMessageBox::Retry);
        return;
    }
    QTextStream out(&file);
    int idcount = 0;
    foreach(QGraphicsItem *item, scene->items()) {
        if (item->type() == DiagramItem::Type) {
            DiagramItem *diagramitem = qgraphicsitem_cast<DiagramItem*>(item);
            int mytag = diagramitem->diagramitemtag + idcount;
            int type = diagramitem->diagramType();
            int xpos = diagramitem->x();
            int ypos = diagramitem->y();
            QString fillcolor = diagramitem->brush().color().name();
            QString lineColor = diagramitem->pen().color().name();
            out << mytag <<","<< type << ","<< xpos << ","
                << ypos << ","<< fillcolor << ","<< lineColor << endl;
        }
        else if (item->type() == Arrow::Type) {
            Arrow *arrow = qgraphicsitem_cast<Arrow*>(item);
            int mytag = arrow->arrowtag + idcount;
            int startItem = arrow->startItem()->diagramitemtag;
            int endItem = arrow->endItem()->diagramitemtag;
            QString lineColor = arrow->getColor().name();
            int lineWidth = arrow->pen().width();
            out << mytag <<","<< "LINE" << ","<< startItem << ","
                << endItem << ","<< lineColor << ","<< lineWidth << endl;
        }
        else if (item->type() == DiagramTextItem::Type) {
            DiagramTextItem *text = qgraphicsitem_cast<DiagramTextItem*>(item);
            int mytag = text->texttag + idcount;
            int textx = text->x();
            int texty = text->y();
            QString font = text->font().family();
            int size = text->font().pointSize();
            QString message = text->toPlainText();
            out << mytag <<","<< "TEXT" << ","<< textx << ","
                << texty << ","<< font << ","<< size << "," << message << endl;
        }
        idcount++;
    }
    file.close();
}
void MainWindow::openFunction() {

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Could not save file"), tr("Error"), QMessageBox::Retry);
        return;
    }
    //clear everything from scene
    foreach (QGraphicsItem *item, scene->items()) {
        scene->removeItem(item);
    }
    QTextStream in(&file);
    QList <DiagramItem *> templist;

    while (!in.atEnd()) {
        QString input = in.readLine();
        QStringList line = input.split(",");
        while (input == NULL || input == "") {
            input = in.readLine();
            line = input.split(",");
        }
        /*if (input == NULL || input == "") {
            input = in.readLine();
            line = input.split(",");
        }*/
        if (line[1] == "TEXT") {
            DiagramTextItem *text = new DiagramTextItem();
            text->texttag = line[0].toInt();
            text->setX(line[2].toDouble());
            text->setY(line[3].toDouble());
            text->font().setFamily(line[4]);
            text->font().setPointSize(line[5].toInt());
            text->setPlainText(line[6]);
            scene->addItem(text);
        }
        else if (line[1].toInt() == 0 || line[1].toInt() == 1 || line[1].toInt() == 2
              || line[1].toInt() == 3 || line[1].toInt() == 4 || line[1].toInt() == 5
              || line[1].toInt() == 6) {
            DiagramItem *diagramitem = new DiagramItem(DiagramItem::DiagramType(line[1].toInt()), itemMenu);
            diagramitem->setX(line[2].toDouble());
            diagramitem->setY(line[3].toDouble());
            templist.append(diagramitem);
            scene->addItem(diagramitem);
        }
        else if (line[1] == "LINE") {
            Arrow *arrow = new Arrow(templist.at(line[1].toInt()), templist.at(line[2].toInt()));
            scene->addItem(arrow);
        }
    }
    file.close();
}

//! [1]
void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    QString text = button->text();
    if (text == tr("Blue Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
    else if (text == tr("White Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
    else if (text == tr("Gray Grid"))
        scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
    else
        scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

    scene->update();
    view->update();
}
//! [1]

//! [2]
void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }
    if (id == InsertTextButton) {
        scene->setMode(DiagramScene::InsertText);
    } else {
        scene->setItemType(DiagramItem::DiagramType(id));
        scene->setMode(DiagramScene::InsertItem);
    }
}
//! [2]

//! [3]
void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        if (item->type() == Arrow::Type) {
            scene->removeItem(item);
            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
        }
    }

    foreach (QGraphicsItem *item, scene->selectedItems()) {
         if (item->type() == DiagramItem::Type)
             qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
         scene->removeItem(item);
         delete item;
     }
}
//! [3]

//! [4]
void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [4]

//! [5]
void MainWindow::bringToFront()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue && item->type() == DiagramItem::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [5]

//! [6]
void MainWindow::sendToBack()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue && item->type() == DiagramItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}
//! [6]

//! [7]
void MainWindow::itemInserted(DiagramItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);
}
//! [7]

//! [8]
void MainWindow::textInserted(QGraphicsTextItem *)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}
//! [8]

//! [9]
void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}
//! [9]

//! [10]
void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}
//! [10]

//! [11]
void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}
//! [11]

//! [12]
void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/textpointer.png",
                                     qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}
//! [12]

//! [13]
void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png",
                                     qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}
//! [13]

//! [14]
void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png",
                                     qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}
//! [14]

//! [15]
void MainWindow::textButtonTriggered()
{
    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}
//! [15]

//! [16]
void MainWindow::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}
//! [16]

//! [17]
void MainWindow::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}
//! [17]

//! [18]
void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}
//! [18]

//! [19]
void MainWindow::itemSelected(QGraphicsItem *item)
{
    DiagramTextItem *textItem =
    qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());
}
//! [19]

//! [20]
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));
}
//! [20]

//! [21]
void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Conditional"), DiagramItem::Conditional), 0, 0);
    layout->addWidget(createCellWidget(tr("Process"), DiagramItem::Step),0, 1);
    layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::Io), 1, 0);
    layout->addWidget(createCellWidget(tr("Terminal"), DiagramItem::Terminal), 2, 0);
    layout->addWidget(createCellWidget(tr("Preparation"), DiagramItem::Preparation), 2, 1);
    layout->addWidget(createCellWidget(tr("Off-Page Connector"), DiagramItem::Connector), 3, 0);
//! [21]

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    QGridLayout *backgroundLayout = new QGridLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"),
                                                           ":/images/background1.png"), 0, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("White Grid"),
                                                           ":/images/background2.png"), 0, 1);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Gray Grid"),
                                                           ":/images/background3.png"), 1, 0);
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("No Grid"),
                                                           ":/images/background4.png"), 1, 1);

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);


//! [22]
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}
//! [22]

//! [23]
void MainWindow::createActions()
{
    //Added
    saveAction = new QAction(QIcon(":/images/bringtofront.png"),
                                 tr("Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save this, don't worry"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFunction()));

    saveAsAction = new QAction(QIcon(":/images/bringtofront.png"),
                                 tr("Save As"), this);
    saveAsAction->setShortcut(tr("Ctrl+D"));
    saveAsAction->setStatusTip(tr("SaveAs this, don't worry"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsFunction()));

    openAction = new QAction(QIcon(":/images/bringtofront.png"),
                                 tr("Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open this, don't worry"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFunction()));

    copyAction = new QAction(QIcon(":/images/bringtofront.png"),
            tr("Copy"), this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("Copy this, don't worry"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copyFunction()));

    pasteAction = new QAction(QIcon(":/images/bringtofront.png"),
            tr("Paste"), this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("Paste this, don't worry"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(pasteFunction()));

    cutAction = new QAction(QIcon(":/images/bringtofront.png"),
            tr("Cut"), this);
    cutAction->setShortcut(tr("Ctrl+Q"));
    cutAction->setStatusTip(tr("Cut this, don't worry"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cutFunction()));

    undoAction = new QAction(QIcon(":/images/bringtofront.png"),
            tr("Undo"), this);
    undoAction->setShortcut(tr("Ctrl+3"));
    undoAction->setStatusTip(tr("Undo this, don't worry"));
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undoFunction()));

    redoAction = new QAction(QIcon(":/images/bringtofront.png"),
            tr("Redo"), this);
    redoAction->setShortcut(tr("Ctrl+4"));
    redoAction->setStatusTip(tr("Redo this, don't worry"));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redoFunction()));

    groupAction = new QAction(QIcon(":/images/bringtofront.png"),
            tr("Group"), this);
    groupAction->setShortcut(tr("Ctrl+1"));
    groupAction->setStatusTip(tr("Group this, don't worry"));
    connect(groupAction, SIGNAL(triggered()), this, SLOT(groupFunction()));

    ungroupAction = new QAction(QIcon(":/images/bringtofront.png"),
            tr("UnGroup"), this);
    ungroupAction->setShortcut(tr("Ctrl+2"));
    ungroupAction->setStatusTip(tr("UnGroup this, don't worry"));
    connect(ungroupAction, SIGNAL(triggered()), this, SLOT(ungroupFunction()));
    //Added end

    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()), this, SLOT(bringToFront()));
//! [23]

    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+B"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()), this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    QPixmap pixmap(":/images/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/images/italic.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/images/underline.png"), tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

//! [24]
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(cutAction);
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(groupAction);
    toolsMenu->addAction(ungroupAction);
}
//! [24]

//! [25]
void MainWindow::createToolbars()
{
//! [25]
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

//! [26]
    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));
//! [26]

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);
//! [27]
}
//! [27]

//! [28]
QWidget *MainWindow::createBackgroundCellWidget(const QString &text, const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
//! [28]

//! [29]
QWidget *MainWindow::createCellWidget(const QString &text, DiagramItem::DiagramType type)
{

    DiagramItem item(type, itemMenu);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}
//! [29]

//! [30]
QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}
//! [30]

//! [31]
QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}
//! [31]

//! [32]
QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
//! [32]
