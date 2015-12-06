#include <QPushButton>
#include <QTextEdit>

#include <thread>

#include "drawing.h"

class Runner {
public:
	void LoadScript(QString code);
	void Start();
	void Stop();

private:
 	QString code;
 	const char *bytes;

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
