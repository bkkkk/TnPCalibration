#include "MuonEfficiency/EventWeighting.h"
#include "MuonEfficiency/Weighting.h"
#include "JacobUtils/LoggingUtility.h"
#include "D3PDReader/Event.h"

EventWeighting::EventWeighting(const std::string& name)
{

};

EventWeighting::~EventWeighting()
{

};

int EventWeighting::AddWeighting(Weighting* weighting)
{
	m_weightings[weighting->GetName()] = weighting;
	return (1);
};

double EventWeighting::GetTotalWeighting(const D3PDReader::Event* event)
{
	double totalWgt = 1;

	// Grab iterator of first 
	std::map<std::string, Weighting*>::iterator iter = m_weightings.begin();

	for(; iter != m_weightings.end(); iter++)
	{
		totalWgt *= (*iter).second->GetWeight(event);
	};

	return (totalWgt);
};

Weighting* EventWeighting::GetWeighting(const std::string& name)
{
	if(m_weightings.find(name) != m_weightings.end())
	{
		return (m_weightings[name]);
	} else
	{
		LOG_WARNING() << "Could not find weighting in map";
		return (NULL);
	};
};

// Needed for streaming
ClassImp(EventWeighting)
