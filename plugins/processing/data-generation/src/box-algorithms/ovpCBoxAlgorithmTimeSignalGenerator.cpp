#include "ovpCBoxAlgorithmTimeSignalGenerator.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <openvibe/ovITimeArithmetics.h>

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBE::Plugins;
using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::DataGeneration;
using namespace OpenViBEToolkit;
using namespace std;

CBoxAlgorithmTimeSignalGenerator::CBoxAlgorithmTimeSignalGenerator(void)
	: m_bHeaderSent(false)
	,m_ui32SamplingFrequency(0)
	,m_ui32GeneratedEpochSampleCount(0)
	,m_ui32SentSampleCount(0)
{

}

void CBoxAlgorithmTimeSignalGenerator::release(void)
{
	delete this;
}

boolean CBoxAlgorithmTimeSignalGenerator::initialize(void)
{
	m_oSignalEncoder.initialize(*this,0);

	// Parses box settings to try connecting to server
	m_ui32SamplingFrequency = FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 0);
	m_ui32GeneratedEpochSampleCount = FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 1);
	m_bHeaderSent=false;

	m_ui32SentSampleCount=0;

	return true;
}

boolean CBoxAlgorithmTimeSignalGenerator::uninitialize(void)
{
	m_oSignalEncoder.uninitialize();

	return true;
}

boolean CBoxAlgorithmTimeSignalGenerator::processClock(CMessageClock& rMessageClock)
{
	getBoxAlgorithmContext()->markAlgorithmAsReadyToProcess();
	return true;
}

boolean CBoxAlgorithmTimeSignalGenerator::process(void)
{
	IBoxIO* l_pDynamicBoxContext=getBoxAlgorithmContext()->getDynamicBoxContext();

	if(!m_bHeaderSent)
	{
		m_oSignalEncoder.getInputSamplingRate() = m_ui32SamplingFrequency;

		IMatrix* l_pMatrix=m_oSignalEncoder.getInputMatrix();

		l_pMatrix->setDimensionCount(2);
		l_pMatrix->setDimensionSize(0, 1);
		l_pMatrix->setDimensionSize(1, m_ui32GeneratedEpochSampleCount);
		l_pMatrix->setDimensionLabel(0, 0, "Time signal");

		m_oSignalEncoder.encodeHeader();

		m_bHeaderSent=true;

		l_pDynamicBoxContext->markOutputAsReadyToSend(0, 0, 0);
	}
	else
	{
		float64* l_pSampleBuffer = m_oSignalEncoder.getInputMatrix()->getBuffer();

		uint32 l_ui32SentSampleCount=m_ui32SentSampleCount;
		float64 l_f64SamplingFrequency=static_cast<float64>(m_ui32SamplingFrequency);
		for(uint32 i=0; i<m_ui32GeneratedEpochSampleCount; i++)
		{
			l_pSampleBuffer[i]=(i+m_ui32SentSampleCount)/l_f64SamplingFrequency;
		}

		m_oSignalEncoder.encodeBuffer();

		m_ui32SentSampleCount+=m_ui32GeneratedEpochSampleCount;

		uint64 l_ui64StartTime = ITimeArithmetics::sampleCountToTime(m_ui32SamplingFrequency, l_ui32SentSampleCount);
		uint64 l_ui64EndTime = ITimeArithmetics::sampleCountToTime(m_ui32SamplingFrequency, m_ui32SentSampleCount);

		l_pDynamicBoxContext->markOutputAsReadyToSend(0, l_ui64StartTime, l_ui64EndTime);
	}

	return true;
}

OpenViBE::uint64 CBoxAlgorithmTimeSignalGenerator::getClockFrequency(void)
{
	// Intentional parameter swap to get the frequency
	return ITimeArithmetics::sampleCountToTime(m_ui32GeneratedEpochSampleCount, m_ui32SamplingFrequency);
}
