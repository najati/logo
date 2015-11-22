#include <QPushButton>

class MyPushButton : public QPushButton
{
Q_OBJECT

public:
	MyPushButton(const QString &text);

public slots:
	void handleClicked();
};
