#include "UnixWindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <iostream>

UnixWindow::UnixWindow()
{
    setObjectName("unixWindow");

    mainPanel = new UnixPanel(this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);
    layout->addWidget(mainPanel);

    this->setWindowFlags(Qt::FramelessWindowHint);
    mainPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->adjustSize();
    this->show();
}

void UnixWindow::minimize()
{
    showMinimized();
}

void UnixWindow::maximize()
{
    if (isMaximized())
    {
        showNormal();
    }
    else
    {
        showMaximized();
    }
}

void UnixWindow::closeWindow()
{
    this->close();
}

void UnixWindow::mousePressEvent(QMouseEvent* evt)
{
    oldWindowPos = evt->globalPos();
}

void UnixWindow::mouseReleaseEvent(QMouseEvent* evt)
{
    dragging = false;
}

void UnixWindow::mouseMoveEvent(QMouseEvent* evt)
{
    const QPoint c_delta = evt->globalPos() - oldWindowPos;
    if (evt->pos().y() < 70 || dragging)
    {
        dragging = true;
        move(x() + c_delta.x(), y() + c_delta.y());
        oldWindowPos = evt->globalPos();
    }
}
