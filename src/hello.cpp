#include <QDebug>
#include "hello.h"

MyPushButton::MyPushButton(const QString &text) : QPushButton(text)
{
	setObjectName("mypushbutton");
}

void MyPushButton::handleClicked() {
	qDebug() << "Hello, world!";
}
