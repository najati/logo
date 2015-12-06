#include <string>
#include <thread>

#include <QPushButton>
#include <QTextEdit>
#include <QTimer>

#include <ruby.h>

#include "drawing.h"

class Runner : public QObject {
Q_OBJECT

public:
	Runner();
	void LoadScript(std::string code);
	void Start();

public slots:
	void Tick();
	void Stop();

private:
  QTimer timer;
  VALUE obj;

 	std::string code;

 	std::thread scriptThread;
};

class MyPushButton : public QPushButton
{
Q_OBJECT

public:
	MyPushButton(Runner& runner, const QString &text, QTextEdit& editor);

public slots:
	void handleClicked();

private:
	Runner& runner;
	QTextEdit& editor;
};
