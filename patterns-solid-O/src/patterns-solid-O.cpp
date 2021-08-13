//============================================================================
// Name        : patterns-solid-O.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : www.udemy.com/course/patterns-cplusplus/learn/lecture/7736678#overview
//============================================================================

// open closed principle
// open for extension, closed for modification
// Featuring the Specification Pattern

#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum class Color { yellow, red, green, blue, orange, purple };
enum class Size { small, medium, large };

struct ProduceItem
{
	string name;
	Color color;
	Size size;
};

class ProductFilter
{
public:
	typedef vector<ProduceItem*> Items;

	Items by_color(Items items, const Color color)
	{
		Items result;
		for (auto& i : items)
			if (i->color == color)
				result.push_back(i);
		return result;
	}

	Items by_size(Items items, const Size size)
	{
		Items result;
		for (auto& i : items)
			if (i->size == size)
				result.push_back(i);
		return result;
	}

	Items by_name(Items items, const string name)
	{
		Items result;
		for (auto& i : items)
			if (i->name == name)
				result.push_back(i);
		return result;
	}

	Items by_size_and_color(Items items, const Size size, const Color color)
	{
		Items result;
		for (auto& i : items)
			if (i->size == size && i->color == color)
				result.push_back(i);
		return result;
	}
};

#ifdef NOT_NEEDED
template <typename T> struct AndSpecification;
#endif

template <typename T> struct Specification
{
	virtual ~Specification() = default;
	virtual bool is_satisfied(T* item) const = 0;

	// new: breaks OCP if you add it post-hoc
	/*AndSpecification<T> operator&&(Specification<T>&& other)
  {
    return AndSpecification<T>(*this, other);
  }*/
};

#ifdef NOT_NEEDED
// new:
template <typename T> AndSpecification<T> operator&&
(const Specification<T>& first, const Specification<T>& second)
{
	return { first, second };
}
#endif

template <class T> class ItemFilter
{
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
	virtual ~ItemFilter() {}
};

template <typename T> struct Filter
{
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
	virtual ~Filter() {}
};

class BetterFilter : Filter<ProduceItem>
{
public:
	vector<ProduceItem*> filter(vector<ProduceItem*> items, Specification<ProduceItem> &spec) override
	{
		vector<ProduceItem*> result;
		for (auto& p : items)
			if (spec.is_satisfied(p))
				result.push_back(p);
		return result;
	}
};

struct ColorSpecification : Specification<ProduceItem>
{
	Color color;

	ColorSpecification(Color color) : color(color) {}

	bool is_satisfied(ProduceItem *item) const override {
		return item->color == color;
	}
};

struct SizeSpecification : Specification<ProduceItem>
{
	Size size;

	// The explicit keyword in C++ is used to mark constructors to not implicitly convert types.
	// It can only be used in declarations of constructors within a class declaration.
	// This is useful if an object has overloaded constructors.
	// In the course lecture the instructor used a code generation feature of the IDE.
	// A student later inquired about the usage and instructor Dmitri said:
	// "...it's an artifact of code generation"
	// So...we can remove the item.
	//
	SizeSpecification(const Size size): size{ size }
	{
	}

	bool is_satisfied(ProduceItem* item) const override {
		return item->size == size;
	}
};

template <typename T> struct AndSpecification : Specification<T>
{
	const Specification<T>& first;
	const Specification<T>& second;

	AndSpecification(const Specification<T>& first, const Specification<T>& second) : first(first), second(second) {}

	bool is_satisfied(T *item) const override {
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

// new:

int main()
{
	ProduceItem apple{"Granny Smith Apple", Color::green, Size::small};
	ProduceItem bg_apple{"McIntosh Apple", Color::green, Size::large};
	ProduceItem br_apple{"Honey Crisp Apple", Color::red, Size::large};
	ProduceItem tree{"Spruce Tree", Color::green, Size::large};
	ProduceItem house{"Big Blue-House", Color::blue, Size::large};
	ProduceItem sg_house{"Small Green House", Color::green, Size::small};
	ProduceItem bo_house{"Big Orange House", Color::orange, Size::large};

	const vector<ProduceItem*> all { &apple, &bg_apple, &br_apple, &tree, &house, &sg_house, &bo_house };

	BetterFilter bf;
	ColorSpecification green(Color::green);
	auto green_things = bf.filter(all, green);
	for (auto& x : green_things)
		cout << "Green produce Items " << x->name << " is green\n";

	// CN: Here I take a different tack and instead of using the 'AndSpecification' design, a simpler solution
	//     is to take the result vector from the first Color filter and perform a second Size filter.
	SizeSpecification grande(Size::large);
	auto large_and_green = bf.filter(green_things, grande);
	for(auto& x : large_and_green)
		cout << "Green & large produce item " << x->name << " is green AND large\n";
	cout << endl;

#ifdef NOT_NEEDED
	SizeSpecification large(Size::large);
	AndSpecification<ProduceItem> green_and_large(green, large);

	//auto big_green_things = bf.filter(all, green_and_large);

	// use the operator instead (same for || etc.)
	auto spec = green && large;
	for (auto& x : bf.filter(all, spec))
		cout << "Green '&&' large produce item " << x->name << " is green and large\n";

	// warning: the following will compile but will NOT work
	// auto spec2 = SizeSpecification{Size::large} &&
	//              ColorSpecification{Color::blue};
#endif

	getchar();
	return 0;
}
