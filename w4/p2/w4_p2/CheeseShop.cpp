

#include <iostream>
#include <string>
#include "CheeseShop.h"

using namespace std;
using namespace sdds;

sdds::CheeseShop::CheeseShop()
{
	m_name = "No Name";
	m_numCheeses = 0u;
	m_cheeses = nullptr;
}

CheeseShop::CheeseShop(const string& name)
{
	m_name = name;
	m_numCheeses = 0u;
	m_cheeses = nullptr;
}

CheeseShop& sdds::CheeseShop::addCheese(const Cheese& addCheese)
{

	//creating a new array thats 1 bigger
	const Cheese** newArr = new const Cheese * [m_numCheeses + 1];

	//copying from old array to new
	for (size_t i = 0; i < m_numCheeses; i++)
	{
		newArr[i] = m_cheeses[i];
	}

	//adding the new one to new array
	newArr[m_numCheeses] = new Cheese(addCheese);

	//clearing current collection before taking new address
	delete[] m_cheeses;
	//moving the address of the new array to member
	m_cheeses = newArr;
	m_numCheeses++;

	return *this;
}

void sdds::CheeseShop::emptyShop()
{
	if (*this)
	{
		for (size_t i = 0; i < m_numCheeses; i++)
		{
			delete m_cheeses[i];
			m_cheeses[i] = nullptr;
		}
	}
	m_name = "";
	m_numCheeses = 0u;
	delete[] m_cheeses;
	m_cheeses = nullptr;
}

sdds::CheeseShop::operator bool() const
{
	return m_cheeses != nullptr;
}

std::ostream& sdds::CheeseShop::print(std::ostream& out) const
{
	out << "--------------------------" << endl
		<< m_name << endl
		<< "--------------------------" << endl;

	if (*this)
	{
		for (size_t i = 0; i < m_numCheeses; i++)
		{
			out << *(m_cheeses[i]);
		}
		out << "--------------------------" << endl;
	}
	else
	{
		out << "This shop is out of cheese!" << endl
			<< "--------------------------" << endl;
	}
	return out;
}

sdds::CheeseShop::CheeseShop(const CheeseShop& copy)
{
	*this = copy;
}

sdds::CheeseShop::CheeseShop(CheeseShop&& move) noexcept
{
	*this = std::move(move);
}

CheeseShop& sdds::CheeseShop::operator=(const CheeseShop& copy)
{
	if (this != &copy)
	{
		for(size_t i = 0u; i < m_numCheeses ; i++)
		{
			delete m_cheeses[i];
		}
		delete[] m_cheeses;
		
		m_name = copy.m_name;
		m_numCheeses = copy.m_numCheeses;
		m_cheeses = new const Cheese * [m_numCheeses];

		for (size_t i = 0; i < m_numCheeses; i++)
		{
			m_cheeses[i] = new Cheese{ *(copy.m_cheeses[i]) };
			//*(m_cheeses[i]) = *(copy.m_cheeses[i]);
		}
	}

	return *this;
}

CheeseShop& sdds::CheeseShop::operator=(CheeseShop&& move) noexcept
{
	if (this != &move)
	{
		emptyShop();
		//take everything
		m_name = move.m_name;
		m_numCheeses = move.m_numCheeses;
		m_cheeses = move.m_cheeses;
		//leave nothing behind
		move.m_cheeses = nullptr;
		move.m_name = "";
		move.m_numCheeses = 0u;
	}

	return *this;
}

sdds::CheeseShop::~CheeseShop()
{
	emptyShop();
}

std::ostream& sdds::operator<<(std::ostream& out, const CheeseShop& cs)
{
	return cs.print(out);
}
