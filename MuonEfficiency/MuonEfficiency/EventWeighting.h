#ifndef EVENTWEIGHTING_H_
#define EVENTWEIGHTING_H_ 1

#include <map>
#include <string>
#include "TH1F.h"

namespace D3PDReader {
	class Event;
}

class Weighting;

class EventWeighting
{
public:
	EventWeighting(const std::string& name="");

public:
 	~EventWeighting();

public:
	int AddWeighting(Weighting* weighting);

public:
	double GetTotalWeighting(const D3PDReader::Event* event);

public:
	Weighting* GetWeighting(const std::string& name);

private:
	std::map<std::string, Weighting*> m_weightings;

	ClassDef(EventWeighting, 1)
};

#endif
