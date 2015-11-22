#include <QPushButton>
#include <QTextEdit>

#include "drawing.h"

class MyPushButton : public QPushButton
{
Q_OBJECT

public:
	MyPushButton(const QString &text, QTextEdit& editor);

public slots:
	void handleClicked();

private:
	QTextEdit& editor;
 	static Drawing *globalDrawing;
};
