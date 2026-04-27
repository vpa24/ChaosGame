// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf; 
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	Font font;
	if (!font.loadFromFile("SuperMario256.ttf")) {
		cerr << "Error: Could not load font file" << endl;
		return -1;
	}

	Text text;
	text.setFont(font);
	text.setString("Welcome to Chaos Game!");
	text.setCharacterSize(20);
	text.setFillColor(Color::Magenta);
	text.setPosition(10.f, 20.f);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y)); //fourth click - push back to points vector
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
			for (int i = 0; i < 1000; i++)
			{
				int randdomVertextIndex = rand() % 3;
				Vector2f targetVertex = vertices[randdomVertextIndex];
				Vector2f lastPoint = points.back();

				Vector2f newPoint;
				newPoint.x = (lastPoint.x + targetVertex.x) / 2.0;
				newPoint.y = (lastPoint.y + targetVertex.y) / 2.0;
				points.push_back(newPoint);
 			}
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(text);
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		///TODO:  Draw points
		for (int i = 0; i < points.size(); i++) {
			RectangleShape dot(Vector2f(2, 2)); // Small 2x2 pixel dot
			dot.setPosition(points[i]);
			dot.setFillColor(Color::Green);
			window.draw(dot);
		}
		window.display();
	}
}
