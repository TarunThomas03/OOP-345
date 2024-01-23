

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include <string>
#include "Cheese.h"

namespace sdds
{
	class CheeseShop
	{
		std::string m_name{};
		unsigned m_numCheeses{};
		const Cheese** m_cheeses{};	//Dynamically allocated array of dynamically allocated cheeses

	public:
		CheeseShop();
		CheeseShop(const std::string& name);
		CheeseShop& addCheese(const Cheese& addCheese);
		/// <summary>
		/// rats ate all the cheese
		/// </summary>
		void emptyShop();
		/// <summary>
		/// have you got any cheese?
		/// </summary>
		operator bool() const;

		std::ostream& print(std::ostream& out) const;

		//rule of 5
		CheeseShop(const CheeseShop& copy);
		CheeseShop(CheeseShop&& move) noexcept;
		CheeseShop& operator=(const CheeseShop& copy);
		CheeseShop& operator=(CheeseShop&& move) noexcept;
		~CheeseShop();

	};

	std::ostream& operator<<(std::ostream& out, const CheeseShop& cs);

}
#endif // !SDDS_CHEESESHOP_H
