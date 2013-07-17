#ifndef WEIGHTING_H_
#define WEIGHTING_H_ 1

#include <string>
#include "D3PDReader/Event.h"

class Weighting
{
protected:
	Weighting(const std::string& name, const std::string& title)
	 : m_name(name), 
	   m_title(title)
	{

	}

protected:
	virtual ~Weighting() { m_name = ""; m_name = ""; }

public:
	virtual double GetWeight(const D3PDReader::Event* event) = 0;

public:
	inline std::string GetName(void) { return m_name; }

public:
	inline std::string GetTitle(void) { return m_title; }

protected:
	// Name and title
	std::string m_name;
	std::string m_title;

	ClassDef(Weighting, 1);
};

#endif