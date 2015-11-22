#pragma once

#include <QGraphicsScene>

class Drawing {
public:
	static void Line(float x1, float y1, float x2, float y2) {
		Drawing::scene->addLine(x1, y1, x2, y2);
	}

	static void Clear() {
		Drawing::scene->clear();
	}

	static void Init(QGraphicsScene* scene) {
		Drawing::scene = scene;
	}

private:
	Drawing() {};

	static QGraphicsScene* scene;
};
