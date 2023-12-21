#include "Dog.h"
#include "Cat.h"
#include "Fance.h"
#include "Tree.h"
#include <iostream>
#include <ctime>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Physical.h"

static const int HEIGHT = 800;
static const int WIDTH = 800;

using namespace sf;



bool checkCollissions(Physical* obj1, Physical* obj2);

int main()
{

	

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Dog&Cat");

	std::list<Tree*> trees;
	std::list<Fance*> fances;
	std::list<MovingObject*> pets;
	srand(time(0));
	int x = 70;
	int y = 70;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Tree* tree = new Tree(x, y);
			x += 200;
			trees.push_back(tree);
		}
		y += 200;
		x -= 550;
	}

	fances.push_back(new Fance(145, 120));
	fances.push_back(new Fance(440, 520));
	fances.push_back(new Fance(405, 320));

	Dog* dog = new Dog(MovingObject::Left,750, 750);
	Cat* cat = new Cat(MovingObject::Right, 50, 50, dog);

	pets.push_back(dog);
	pets.push_back(cat);
	bool blick = true;
	int actionInterval = 0;
	std::string dogImage;


	sf::Music music;
	if (!music.openFromFile("music.ogg"))
		return -1;
	music.play();
	music.setLoop(true);
	bool gameTime = false;

	Texture catT;
	catT.loadFromFile("cat_left.png");
	Sprite catSprite(catT);
	int movingCatPreload = 0;
	int movingDogPreload = 0;

	Texture dogT;
	dogT.loadFromFile("dog_left.png");
	Sprite dogSprite(dogT);

	while (window.isOpen() && cat->getCatched() == false && dog->getLifes() > 0)
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && dog->getCanMove() == true && gameTime) {
				if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W) {
					dog->Move(MovingObject::Up);
				}
				if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S) {
					dog->Move(MovingObject::Down);
				}
				if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A) {
					dog->Move(MovingObject::Left);
				}
				if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D) {
					dog->Move(MovingObject::Right);
				}
			}
		}

		if (gameTime) {
			if (dog->getCanMove() == false) {
				if (actionInterval % 50 == 0) {
					dog->reduceCooldown();
				}
				if (dog->getCooldown() <= 0) {
					dog->unshocked();
					dog->setImage();

				}
			}

			if (dog->getCanMove() == false) {
				if (dogImage == "dog_left.png") {

					if (actionInterval % 20 == 0) {
						if (blick) {
							dog->setImageToDog("red_dog_left.png");
							blick = false;
						}
						else {
							dog->setImageToDog("none_dog.png");
							blick = true;
						}
					}
				}
				else {
					if (actionInterval % 20 == 0) {
						if (blick) {
							dog->setImageToDog("red_dog_right.png");
							blick = false;
						}
						else {
							dog->setImageToDog("none_dog.png");
							blick = true;
						}
					}
				}
			}

			for (auto tree : trees) {
				if (checkCollissions(tree, dog)) {
					dog->collisionReact();
					dog->shocked();
					dog->decreaseLifes();
					dogImage = dog->getImage();
					//todo make stun
				}
			}

			for (auto fance : fances) {
				if (checkCollissions(fance, dog)) {
					dog->collisionReact();
					dog->shocked();
					dog->decreaseLifes();
					dogImage = dog->getImage();
					//todo make stun
				}
			}

			if (dog->objectOutOfFrame()) {
				dog->collisionReact();
			}
			if (cat->getCatchable()) {
				cat->Move(cat->getDirection());
			}

			for (auto tree : trees) {
				if (checkCollissions(cat, tree) && cat->getCatchable() == true) {
					cat->collisionReact();
				}
			}

			for (auto fance : fances) {
				if (checkCollissions(cat, fance) && cat->getCatchable() == true) {
					cat->collisionReact();
				}
			}

			if (checkCollissions(cat, dog) && cat->getCatchable() == true) {
				if (cat->getCooldown() <= 0) {
					double minToTree = 1000;
					double minToFance = 1000;
					std::list <std::pair<Tree*, double>> lenghtToTrees;
					std::list <std::pair<Fance*, double>> lenghtToFances;
					for (auto tree : trees) {
						double lenght = sqrt(pow(tree->getX() - cat->getX(), 2) + pow(tree->getY() - cat->getY(), 2));
						if (lenght < minToTree) {
							minToTree = lenght;
							std::pair<Tree*, double> p;
							p.first = tree;
							p.second = minToTree;
							lenghtToTrees.push_front(p);
						}
					}
					for (auto fance : fances) {
						double lenght = sqrt(pow(fance->getX() - cat->getX(), 2) + pow(fance->getY() - cat->getY(), 2));
						if (lenght < minToFance) {
							minToFance = lenght;
							std::pair<Fance*, double> p;
							p.first = fance;
							p.second = minToFance;
							lenghtToFances.push_front(p);
						}
					}
					if (minToFance < minToTree) {
						cat->getOnFance(lenghtToFances.front().first);
					}
					else {
						cat->getOnTree(lenghtToTrees.front().first);
					}
					lenghtToFances.clear();
					lenghtToTrees.clear();
				}
				else {
					cat->setCatched();
				}
			}

			if (cat->getCatchable() == false) {
				if (actionInterval % 50 == 0) {
					cat->reduceTimeToHide();
				}
				if (cat->getTimeLeftToHide() < 0) {
					if (cat->getTree()) {
						cat->getOffTree();
					}
					else {
						cat->getOffFance();
					}
				}
			}
			if (cat->getCatchable() == true && cat->getCooldown() > 0) {
				if (actionInterval % 50 == 0) {
					cat->reduceCooldown();
					std::cout << cat->getCooldown();
				}
			}
		}
		

		
		// Redraw window
		

		if (!gameTime) {
			if (actionInterval % 20 == 0) {
				catSprite.setPosition(600 - movingCatPreload, 750);
				dogSprite.setPosition(750 - movingDogPreload, 750);
				movingCatPreload += 3;
				movingDogPreload += 2;
				if (movingDogPreload > 780) {
					gameTime = true;
				}
			}
			window.clear(Color(255, 255, 255, 0));
			window.draw(catSprite);
			window.draw(dogSprite);
		}

		if (gameTime) {
			window.clear(Color(255, 255, 255, 0));
			for (auto tree : trees) {
				Texture texture;
				texture.loadFromFile(tree->getImage());
				Sprite sprite(texture);
				sprite.move(float(tree->getX()), float(tree->getY()));
				window.draw(sprite);
			}
			for (auto fance : fances) {
				Texture texture;
				texture.loadFromFile(fance->getImage());
				Sprite sprite(texture);
				sprite.move(float(fance->getX()), float(fance->getY()));
				window.draw(sprite);
			}
			for (auto pet : pets) {
				Texture texture;
				texture.loadFromFile(pet->getImage());
				Sprite sprite(texture);
				sprite.move(float(pet->getX()), float(pet->getY()));
				window.draw(sprite);
			}
		}

		window.display();
		actionInterval++;
	}
	

	
	for (auto tree : trees) {
		delete tree;
	}
	for (auto fance : fances) {
		delete fance;
	}
	for (auto pet : pets) {
		delete pet;
	}
	
	return 0;
}

bool checkCollissions(Physical* obj1, Physical* obj2) {
	int x1, x2, y1, y2;
	x1 = obj1->getX(); int x11 = x1 + obj1->getW();
	y1 = obj1->getY(); int y11 = y1 + obj1->getH();
	//left up corner (x1, y1)
	//right up corner (x11, y1)
	//left d corner (x1, y11)
	//right d corner (x11, y11)
	x2 = obj2->getX(); int x21 = x2 + obj2->getW();
	y2 = obj2->getY(); int y21 = y2 + obj2->getH();

	bool s1 = (x1 >= x2 && x1 <= x21) || (x11 >= x2 && x11 <= x21);
	bool s2 = (y1 >= y2 && y1 < y21) || (y11 >= y2 && y11 <= y21);
	bool s3 = (x2 >= x1 && x2 <= x11) || (x21 >= x1 && x21 <= x11);
	bool s4 = (y2 >= y1 && y2 <= y11) || (y21 >= y1 && y21 <= y11);

	if ((s1 && s2) || (s3 && s4) || (s1 && s4) || (s3 && s2)) {
		return true;
	}
	else return false;
}