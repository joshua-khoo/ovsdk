#include "ovexP300SharedMemoryReader.h"

#include <utility>



#include <iostream>//to rm

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBEApplications;

using namespace std;

void ExternalP300SharedMemoryReader::openSharedMemory(OpenViBE::CString sharedMemoryName)
{
	m_pSharedVariableHandler = new ISharedMemoryReader::SharedVariableHandler(sharedMemoryName);
}

uint64 ExternalP300SharedMemoryReader::readNextPrediction()
{
	uint64 l_ui64Result;
	l_ui64Result = 0;
	
	IStimulationSet* l_pStimulationSet = dynamic_cast<IStimulationSet*>(m_pSharedVariableHandler->front(0));
	
	if (l_pStimulationSet!=NULL && l_pStimulationSet->getStimulationCount()>0)
	{
		//std::cout << "ExternalP300SharedMemoryReader::readNextPrediction\n";
		l_ui64Result = l_pStimulationSet->getStimulationIdentifier(0);
		for(int i=0; i<l_pStimulationSet->getStimulationCount(); i++)
		{
			std::cout << "ExternalP300SharedMemoryReader::readNextPrediction " << i <<  " " <<  l_pStimulationSet->getStimulationIdentifier(i) << "\n";
		}
		m_pSharedVariableHandler->clear(0); //tricky: if outside if-clause this could delete all elements before it has been read (between reading and clearing processes can be put on hold by OS scheduler)
		delete l_pStimulationSet;
	}

	return l_ui64Result;
}

//caller should clean up the returned pointer
IMatrix* ExternalP300SharedMemoryReader::readNextSymbolProbabilities()
{
	IMatrix* l_pMatrix = dynamic_cast<IMatrix*>(m_pSharedVariableHandler->front(1));
	IMatrix* l_pReturnMatrix = NULL;
	if (l_pMatrix!=NULL)
	{
		l_pReturnMatrix = new CMatrix();
		OpenViBEToolkit::Tools::Matrix::copy(*l_pReturnMatrix, *l_pMatrix);
		delete l_pMatrix;
	}
	
	return l_pReturnMatrix;
}

void ExternalP300SharedMemoryReader::clearSymbolProbabilities()
{
	m_pSharedVariableHandler->clear(1);
}

//it should be the creating application that handles the removal of the shared memory variables
void ExternalP300SharedMemoryReader::closeSharedMemory()
{
	delete m_pSharedVariableHandler;
}

IStimulationSet * ExternalP300SharedMemoryReader::readStimulation()
{
	CStimulationSet* l_pStimulusSet=NULL;

	IStimulationSet* l_pStimulationSet = dynamic_cast<IStimulationSet*>(m_pSharedVariableHandler->front(0));
	while(l_pStimulationSet!=NULL)
	{
		if(l_pStimulusSet==NULL)
		{
			std::cout << " >:Ffront: ";
			l_pStimulusSet = new CStimulationSet();
		}
		OpenViBEToolkit::Tools::StimulationSet::append(*l_pStimulusSet, *l_pStimulationSet);
		std::cout << " pop: ";
		m_pSharedVariableHandler->pop_front(0);
		std::cout << " front: ";
		l_pStimulationSet = dynamic_cast<IStimulationSet*>(m_pSharedVariableHandler->front(0));
	}
	m_pSharedVariableHandler->clear(0);
	return l_pStimulusSet;
}
