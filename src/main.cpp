#include <QApplication>

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QTextEdit>
#include "hello.h"

#include <QGraphicsScene>
#include <QGraphicsView>


int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QWidget window;

	MyPushButton helloButton("Hello world!");
	helloButton.resize(100, 30);
	MyPushButton::connect(&helloButton, SIGNAL (clicked()), &helloButton, SLOT (handleClicked()));

	QTextEdit editor;
	editor.setPlainText("Hello, world!");

	QHBoxLayout mainLayout;

	QVBoxLayout editorLayout;
	editorLayout.addWidget(&editor);
	editorLayout.addWidget(&helloButton);

	QGraphicsScene scene(0, 0, 600, 600);

	QGraphicsView sceneView(&scene);

	mainLayout.addLayout(&editorLayout);
	mainLayout.addWidget(&sceneView);

	window.setLayout(&mainLayout);
	window.show();

	return app.exec();
}
