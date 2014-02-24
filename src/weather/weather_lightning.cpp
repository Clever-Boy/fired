/***********************************************************************
     * File       : weather_lightning.cpp
     * Created    : Feb 24, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Lightning
     * constructor

***********************************************************************/
fired::Lightning::Lightning(sf::Vector2f start, sf::Vector2f end) {
	std::vector<fired::LightningLine> lines;
	std::vector<fired::LightningLine> lines2;

	fired::LightningLine tmpLine, seg1, seg2;
	float offset = LIGHTNING_OFFSET;

	sf::Vector2f mid;
	sf::Vector2f dir, newEnd;
	sf::Vector2f n = end - start;

	n = vNorm(sf::Vector2f(n.y, -n.x));
	lines.push_back(LightningLine(start, end));

	for (unsigned int i = 0; i < LIGHTNING_ITERATIONS; i++) {
		while (!lines.empty()) {
			tmpLine = lines.back();
			lines.pop_back();
			mid = (tmpLine.A + tmpLine.B) / 2.0f;
			mid += n * getRandomOffset(offset);
			lines2.push_back(LightningLine(tmpLine.A, mid));
			lines2.push_back(LightningLine(mid, tmpLine.B));

			if (i < 3) {
				dir = mid - tmpLine.A;
				newEnd = mid + dir * 0.9f;
				lines2.push_back(LightningLine(mid, newEnd));
			}
		}

		while (!lines2.empty()) {
			lines.push_back(lines2.back());
			lines2.pop_back();
		}

		offset /= 2.0f;
	}


	while (!lines.empty()) {
		tmpLine = lines.back();
		line.push_back(sf::Vertex(tmpLine.A, sf::Color::White));
		line.push_back(sf::Vertex(tmpLine.B, sf::Color::White));

		lines.pop_back();
	}
}



/***********************************************************************
     * Lightning
     * destructor

***********************************************************************/
fired::Lightning::~Lightning() {
	line.clear();
}



/***********************************************************************
     * Lightning
     * draw

***********************************************************************/
void fired::Lightning::draw() {
	app->draw(&line[0], line.size(), sf::Lines);
}
