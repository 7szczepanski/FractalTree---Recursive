#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;

int width = 1200;
int height = 800;
class Line {
public:
	Line(Vector2f a_, Vector2f b_) {
		a = a_;
		b = b_;
	}

	void show(RenderWindow &target_) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(a.x, a.y)),
			sf::Vertex(sf::Vector2f(b.x, b.y))
		};

		target_.draw(line, 2, sf::Lines);
	}

protected:
	Vector2f a;
	Vector2f b;
};


void branch(vector<Line> &lines, Vector2f start_, int len_, float aL_, float aR_) {
	float angleL = aL_;
	float angleR = aR_;
	float len = len_;
	if (len == 3) return;
	Vector2f endL;
	Vector2f endR;
	Vector2f start = start_;
	endL = Vector2f(start.x, start.y - len);
	Transform rotL;
	rotL.rotate(angleL, start.x, start.y);
	Vector2f positionARL = rotL.transformPoint(endL);
	endL = positionARL;

	endR = Vector2f(start.x, start.y - len);
	Transform rotR;
	rotR.rotate(angleR, start.x, start.y);
	Vector2f positionARR = rotR.transformPoint(endR);
	endR = positionARR;

	Line left(start, endL);
	Line right(start, endR);

	lines.push_back(right);
	lines.push_back(left);
	if (len > 3) {
		branch(lines, endL, len * 0.67, angleL + 20, -20 - angleR);
		branch(lines, endR, len*0.67, angleL - 20, -20 + angleR);
	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Fractal Tree - Recursive");
	sf::RectangleShape background(Vector2f(width, height));
	background.setFillColor(Color(51, 51, 51));

	vector<Line> lines;
	Vector2f st(Vector2f(width / 2-220, height));
	branch(lines, st, 300, 45, 45);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(background);
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			for (int i = 0; i < lines.size(); i++) {
				lines[i].show(window); 
			}

			
			window.display();
		}

		return 0;
	}

}