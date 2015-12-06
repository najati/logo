
#include <QApplication>
#include <QFile>

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QTextEdit>
#include "hello.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include <ruby.h>

// save on run
// errors/output to console
// syntax highlighting ?

VALUE line(VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2) {
	Q_UNUSED(self);
	Drawing::Line(NUM2DBL(x1), NUM2DBL(y1), NUM2DBL(x2), NUM2DBL(y2));
	return Qnil;
}

VALUE clear(VALUE self) {
	Q_UNUSED(self);
	Drawing::Clear();
	return Qnil;
}


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

	QHBoxLayout mainLayout;

	QVBoxLayout editorLayout;
	editorLayout.addWidget(&editor);
	editorLayout.addWidget(&helloButton);

	QGraphicsScene scene(0, 0, 600, 600);

	Drawing::Init(&scene);

	QGraphicsView sceneView(&scene);
	sceneView.setMinimumSize(610, 610);

	mainLayout.addLayout(&editorLayout);
	mainLayout.addWidget(&sceneView);

	window.setLayout(&mainLayout);
	window.show();

	ruby_init();
	ruby_script("Logo embed");
  // ruby_init_loadpath();

	rb_define_global_function("line", reinterpret_cast<VALUE(*)(...)>(line), 4);
	rb_define_global_function("clear", reinterpret_cast<VALUE(*)(...)>(clear), 0);

	return app.exec();
}
