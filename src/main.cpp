#include <QDebug>

#include <QApplication>

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QTextEdit>
#include "hello.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include <ruby.h>

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
	scene.addLine(10, 10, 110, 110);

	QGraphicsView sceneView(&scene);

	mainLayout.addLayout(&editorLayout);
	mainLayout.addWidget(&sceneView);

	window.setLayout(&mainLayout);
	window.show();

  ruby_init();
  ruby_init_loadpath();

  int status;
  rb_load_protect(rb_str_new2("./test.rb"), 0, &status);
  if (status) {
    VALUE rbError = rb_funcall(rb_gv_get("$!"), rb_intern("message"), 0);
    qDebug() << StringValuePtr(rbError);
  };
  ruby_finalize();

	return app.exec();
}
