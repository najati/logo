#pragma once

#include <vector>

#include <QDebug>

#include <QGraphicsScene>
#include <QLine>


class Drawing {
public:
	static void Line(float x1, float y1, float x2, float y2) {
		drawing->_Line(x1, y1, x2, y2);
	}

	static void Clear() {
		auto swap = drawing;
		drawing = painting;
		painting = swap;

		drawing->_Clear();
		scene->clear();
		for (auto line : painting->lines) {
			scene->addLine(line);
		}
	}

	static void Init(QGraphicsScene* scene) {
		drawing = new Drawing();
		painting = new Drawing();
		Drawing::scene = scene;
	}

private:
	Drawing() {};

	void _Line(float x1, float y1, float x2, float y2) {
		lines.push_back(QLine(x1, y1, x2, y2));
	}

	void _Clear() {
		lines.clear();
	}

	std::vector<QLine> lines;

	static Drawing* drawing;
	static Drawing* painting;
	static QGraphicsScene* scene;
};
