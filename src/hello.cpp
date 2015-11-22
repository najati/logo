#include <QFile>
#include <QDebug>
#include "hello.h"

#include "drawing.h"

#include <ruby.h>


MyPushButton::MyPushButton(const QString &text, QTextEdit& editor) : QPushButton(text), editor(editor)
{
	setObjectName("mypushbutton");
}

void MyPushButton::handleClicked() {
	auto text = editor.toPlainText();
	QByteArray ba = text.toLatin1();
	const char *script = ba.data();

	QFile mainFile("./main.rb");
	mainFile.open(QIODevice::WriteOnly | QIODevice::Text);
	mainFile.write(script);
	mainFile.close();

	int status;
	rb_eval_string_protect(script, &status);
	if (status) {
		VALUE rbError = rb_funcall(rb_gv_get("$!"), rb_intern("message"), 0);
		qDebug() << StringValuePtr(rbError);
	};
}
