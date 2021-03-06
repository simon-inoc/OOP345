// Workshop 9 - Smart Pointers
// w9.cpp

#include <iostream>
#include <iomanip>
#include <memory>
#include "Element.h"
#include "List.h"

const int FWC = 5;
const int FWD = 12;
const int FWP = 8;

w9::List<w9::Product> merge(const w9::List<w9::Description>& desc,
	const w9::List<w9::Price>& price) {
	w9::List<w9::Product> priceList;

	//Outer loop: Go through each product description
	for (size_t d = 0; d < desc.size(); d++) {
		//Inner loop: for each description, loop through the list of product prices by product code.
		for (size_t p = 0; p < price.size(); p++) {
			if (desc[d].code == price[p].code) {
				
				//w9::Product* product = new w9::Product(desc[d].desc, price[p].price);
				std::unique_ptr<w9::Product> product(new w9::Product(desc[d].desc, price[p].price));
				if (!product->validate()) {
					throw std::string("***Negative prices are invalid***");
				}
				priceList += std::move(product);
			}
		}
	}
	return priceList;
}

int main(int argc, char** argv) {
	std::cout << "\nCommand Line : ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << ' ';
	}
	std::cout << std::endl;
	if (argc != 3) {
		std::cerr << "\n***Incorrect number of arguments***\n";
		return 1;
	}

	try {
		w9::List<w9::Description> desc(argv[1]);
		std::cout << std::endl;
		std::cout << std::setw(FWC) << "Code" <<
			std::setw(FWD) << "Description" << std::endl;
		std::cout << desc << std::endl;
		w9::List<w9::Price> price(argv[2]);
		std::cout << std::endl;
		std::cout << std::setw(FWC) << "Code" <<
			std::setw(FWP) << "Price" << std::endl;
		std::cout << price << std::endl;
		w9::List<w9::Product> priceList = merge(desc, price);
		std::cout << std::endl;
		std::cout << std::setw(FWD) << "Description" <<
			std::setw(FWP) << "Price" << std::endl;
		std::cout << priceList << std::endl;
	}
	catch (const std::string& msg) {
		std::cerr << msg << std::endl;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

	std::cout << "\nPress any key to continue ... ";
	std::cin.get();
}