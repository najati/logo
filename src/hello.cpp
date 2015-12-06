#include <QFile>
#include <QDebug>
#include "hello.h"

#include "drawing.h"

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

Runner::Runner() : timer(this) {
	ruby_init();
	ruby_script("Logo embed");
  // ruby_init_loadpath();

	rb_define_global_function("line", reinterpret_cast<VALUE(*)(...)>(line), 4);
	rb_define_global_function("clear", reinterpret_cast<VALUE(*)(...)>(clear), 0);

  connect(&timer, SIGNAL(timeout()), this, SLOT(Tick()));
}

void Runner::LoadScript(std::string code) {
	this->code = code;

	QFile mainFile("./main.rb");
	mainFile.open(QIODevice::WriteOnly | QIODevice::Text);
	mainFile.write(code.c_str());
	mainFile.close();

	// scriptThread = std::thread(std::bind(&Runner::ThreadRunner, this));
	// scriptThread.join();
}

void Runner::Start() {
	int status;
	rb_eval_string_protect(code.c_str(), &status);

	if (status) {
		VALUE rbError = rb_funcall(rb_gv_get("$!"), rb_intern("message"), 0);
		qDebug() << StringValuePtr(rbError);
	};

	obj = rb_eval_string("Object.new");

	rb_funcall(obj, rb_intern("start"), 0);

	timer.start(16);
}

void Runner::Tick() {
	rb_funcall(obj, rb_intern("update"), 0);
	rb_funcall(obj, rb_intern("draw"), 0);
	Drawing::Clear();
}

void Runner::Stop() {
	timer.stop();
}

MyPushButton::MyPushButton(Runner& runner, const QString &text, QTextEdit& editor) :
QPushButton(text),
runner(runner),
editor(editor)
{
	setObjectName("mypushbutton");
}

void MyPushButton::handleClicked() {
	runner.LoadScript(editor.toPlainText().toUtf8().constData());
	runner.Start();
}

