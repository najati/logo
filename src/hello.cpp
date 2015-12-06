#include <QFile>
#include <QDebug>
#include "hello.h"

#include "drawing.h"

#include <ruby.h>

void Runner::LoadScript(QString _code) {
	code = std::move(_code);
	bytes = code.toLatin1().data();

	QFile mainFile("./main.rb");
	mainFile.open(QIODevice::WriteOnly | QIODevice::Text);
	mainFile.write(bytes);
	mainFile.close();
	// scriptThread = std::thread(std::bind(&Runner::ThreadRunner, this));
	// scriptThread.join();
}

void Runner::Start() {
	int status;
	rb_eval_string_protect(bytes, &status);
	if (status) {
		VALUE rbError = rb_funcall(rb_gv_get("$!"), rb_intern("message"), 0);
		qDebug() << StringValuePtr(rbError);
	};
}

void Runner::Stop() {
}

MyPushButton::MyPushButton(Runner& runner, const QString &text, QTextEdit& editor) :
QPushButton(text),
runner(runner),
editor(editor)
{
	setObjectName("mypushbutton");
}

void MyPushButton::handleClicked() {
	runner.LoadScript(editor.toPlainText());
	runner.Start();
}

