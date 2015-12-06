
#include <QApplication>
#include <QFile>

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QTextEdit>
#include "hello.h"

#include <QGraphicsScene>
#include <QGraphicsView>

// save on run
// errors/output to console
// syntax highlighting ?

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QWidget window;

	QTextEdit editor;
	QFile mainFile("./main.rb");
	mainFile.open(QIODevice::ReadOnly | QIODevice::Text);
	editor.setPlainText(mainFile.readAll());

	Runner runner;

	MyPushButton helloButton(runner, "Run", editor);
	helloButton.resize(100, 30);
	MyPushButton::connect(&helloButton, SIGNAL (clicked()), &helloButton, SLOT (handleClicked()));

	QPushButton stopButton("Stop");
	stopButton.resize(100, 30);
	QPushButton::connect(&stopButton, SIGNAL (clicked()), &runner, SLOT (Stop()));

	QHBoxLayout mainLayout;

	QVBoxLayout editorLayout;
	editorLayout.addWidget(&editor);
	editorLayout.addWidget(&helloButton);
	editorLayout.addWidget(&stopButton);

	QGraphicsScene scene(0, 0, 600, 600);

	Drawing::Init(&scene);

	QGraphicsView sceneView(&scene);
	sceneView.setMinimumSize(610, 610);

	mainLayout.addLayout(&editorLayout);
	mainLayout.addWidget(&sceneView);

	window.setLayout(&mainLayout);
	window.show();

	return app.exec();
}
