//============================================================================
// Name        : factoryMethod-PizzaFactory.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

/*
 * Factory
 * Definition: A utility class that creates an instance of a class from a family of derived classes
 *
 * Abstract Factory
 * Definition: A utility class that creates an instance of several families of classes. It can also
 * return a factory for a certain group.
 *
 * The Factory Design Pattern is useful in a situation that requires the creation of many different
 * types of objects, all derived from a common base type. The Factory Method defines a method for
 * creating the objects, which subclasses can then override to specify the derived type that will
 * be created. Thus, at run time, the Factory Method can be passed a description of a desired object
 * (e.g., a string read from user input) and return a base class pointer to a new instance of that
 * object. The pattern works best when a well-designed interface is used for the base class, so
 * there is no need to cast the returned object.
 *
 * Problem
 * We want to decide at run time what object is to be created based on some configuration or
 * application parameter. When we write the code, we do not know what class should be instantiated.
 *
 * Solution
 * Define an interface for creating an object, but let subclasses decide which class to instantiate.
 * Factory Method lets a class defer instantiation to subclasses.
 */
enum PizzaSize {
	Small,
	Medium,
	Large,
	ExtraLarge,
	NumberSizes
};

class Empty {};

class Pizza {
public:
	Pizza(PizzaSize pizzaSize) {sizeOfPizza = pizzaSize; }
	string getPizzaSizeOrdered() {
		string sizeName[] = {"small", "medium", "large", "extra-large"};
		return sizeName[sizeOfPizza];
	}
	float sizeMultiplier() {
		float sizeCostMultiplier[] = {1.0, 1.3, 1.5, 1,75};
		return sizeCostMultiplier[sizeOfPizza];
	}
	virtual float getPrice() = 0;
	virtual string getPizzaName() = 0;
	virtual ~Pizza() {};  /* without this, no destructor for derived Pizza's will be called. */
protected:

	PizzaSize sizeOfPizza;
	static const int Small_Pizza = 0;
	static const int Medium_Pizza = 1;
	static const int Large_Pizza = 2;
	static const int Extra_Large_Pizza = 3;
};

class HamAndMushroomPizza : public Pizza {

public:
	HamAndMushroomPizza(PizzaSize pizzaSize) : Pizza(pizzaSize) {};
	virtual float getPrice() { return 8.50 * sizeMultiplier(); };
	virtual string getPizzaName() { return "Sausage & Mushroom"; }
	virtual ~HamAndMushroomPizza() {};
};

class DeluxePizza : public Pizza {
public:
	DeluxePizza(PizzaSize pizzaSize) : Pizza(pizzaSize) {};
	virtual float getPrice() { return 10.50 * sizeMultiplier(); };
	virtual string getPizzaName() { string name("Deluxe"); return name; }
	virtual ~DeluxePizza() {};
};

class HawaiianPizza : public Pizza {
public:
	HawaiianPizza(PizzaSize pizzaSize) : Pizza(pizzaSize) {};
	virtual float getPrice() { return 11.50 * sizeMultiplier(); };
	virtual string getPizzaName() { string name("Hawaiian"); return name; }
	virtual ~HawaiianPizza() {};
};

class PizzaFactory {
public:
	enum PizzaType {
		HamMushroom,
		Deluxe,
		Hawaiian
	};

	static unique_ptr<Pizza> createPizza(PizzaType pizzaType, PizzaSize pizzaSize) {
		switch (pizzaType) {
		case HamMushroom: return make_unique<HamAndMushroomPizza>(pizzaSize);
		case Deluxe:      return make_unique<DeluxePizza>(pizzaSize);
		case Hawaiian:    return make_unique<HawaiianPizza>(pizzaSize);
		}
		throw "invalid pizza type.";
	}
};

/*
* Create all available pizzas and print their prices
*/
void pizza_information(PizzaFactory::PizzaType pizzatype, PizzaSize pizzaSize)
{
	unique_ptr<Pizza> pizza = PizzaFactory::createPizza(pizzatype, pizzaSize);
	cout << "Price of a " << pizza->getPizzaSizeOrdered() << " " << pizza->getPizzaName() << " pizza is $" << pizza->getPrice() << std::endl;
}

int main()
{
	cout << "https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Factory" << endl; // prints https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Factory

	pizza_information(PizzaFactory::HamMushroom, Medium);
	pizza_information(PizzaFactory::Deluxe, Small);
	pizza_information(PizzaFactory::Hawaiian, ExtraLarge);

	cout << "Class Empty size = " << sizeof(Empty) << endl;
	return 0;
}
