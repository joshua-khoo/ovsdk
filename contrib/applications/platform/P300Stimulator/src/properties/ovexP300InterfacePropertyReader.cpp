#include "ovexP300InterfacePropertyReader.h"

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBEApplications;

using namespace std;

P300InterfacePropertyReader::P300InterfacePropertyReader(OpenViBE::Kernel::IKernelContext* kernelContext) : ExternalP300PropertyReader(kernelContext) 
{
	GColor l_cDefaultColor;
	l_cDefaultColor.red = 0; l_cDefaultColor.green = 0; l_cDefaultColor.blue = 0;
	
	m_eSpellingMode = COPY_MODE;
	m_sStimulatorConfigFile = CString("");
	m_sSymbolDefinitionFile = CString("");
	m_AdditionalConfigurationFile = CString("");
	m_sFlashGroupDefinitionFile = CString("");
	m_sStimulatorMode = CString("");
	m_bFullScreen = false;
	m_bCentralFeedbackFreeMode = true;
	m_bCentralFeedbackCopyMode = true;
	m_ui32ParallelPortNumber = 0;
	m_ui32SampleFrequency = 0;
	m_f32WindowWidth = 0;
	m_f32WindowHeight = 0;
	m_sFlashMode =  CString("copy");
	m_sNGramDatabaseName = CString("");
	
	m_bHardwareTagging = false;
	m_sFeedbackPresentationMode = CString("central");
	m_bEnablePhotoDiode = false;
	
	m_ui32MaxFeedbackSymbols = 0;
	m_oFeedbackStartColor = l_cDefaultColor;
	m_oFeedbackEndColor = l_cDefaultColor;
	m_ui32ColorFeedbackSteps = 0;
	m_f32FeedbackStartValue = 0;
	m_bContinuousFeedback = false;			
}

void P300InterfacePropertyReader::openChild(const char* sName, const char** sAttributeName, const char** sAttributeValue, XML::uint64 ui64AttributeCount)
{
	writeAttribute(sName, sAttributeName, sAttributeValue, ui64AttributeCount);
	
	m_vNode.push(sName);
	if (CString(sName)==CString("Tagging"))
      {
		if (CString(*sAttributeValue)==CString("hardware"))
			m_bHardwareTagging = true;
		else if (CString(*sAttributeValue)==CString("software"))
			m_bHardwareTagging = false;
	}
	if (CString(sName)==CString("Screen"))
	{
		for (uint32 it=0; it<ui64AttributeCount; it++)
		{
			if (CString(*(sAttributeName+it))==CString("width"))
				//m_ui32WindowWidth = strtoul(*(sAttributeValue+it),NULL,0);
				m_f32WindowWidth = static_cast<float32>(m_pKernelContext->getConfigurationManager().expandAsUInteger(CString(*(sAttributeValue+it))));
			else if(CString(*(sAttributeName+it))==CString("height"))
				//m_ui32WindowHeight = strtoul(*(sAttributeValue+it),NULL,0);
				m_f32WindowHeight = static_cast<float32>(m_pKernelContext->getConfigurationManager().expandAsUInteger(CString(*(sAttributeValue+it))));
		}
	}
	if (CString(sName)==CString("FeedbackPresentation"))
		m_sFeedbackPresentationMode = CString(*sAttributeValue);	
	if (CString(sName)==CString("ContinuousFeedback"))
	{
		if (CString(*(sAttributeValue))==CString("enabled"))
			m_bContinuousFeedback = true;
		else
			m_bContinuousFeedback = false;
	}
}

void P300InterfacePropertyReader::processChildData(const char* sData)
{
	ExternalP300PropertyReader::writeElement(m_vNode.top().toASCIIString(), sData);
	CString l_sExpandedString = m_pKernelContext->getConfigurationManager().expand(CString(sData));

	if(m_vNode.top()==CString("Mode"))
	{
		if(l_sExpandedString==CString("Cal"))
			m_eSpellingMode = CALIBRATION_MODE;
		else if(l_sExpandedString==CString("Cop"))
			m_eSpellingMode = COPY_MODE;
		else if(l_sExpandedString==CString("Fr"))
			m_eSpellingMode = FREE_MODE;
		else if(l_sExpandedString==CString("Oddball"))
			m_eSpellingMode = ODDBALL;	
	}
	if(m_vNode.top()==CString("StimulatorMode"))
	{
		if(l_sExpandedString==CString("Online"))
			m_sStimulatorMode = CString("Online");
		else if(l_sExpandedString==CString("Replay"))
			m_sStimulatorMode = CString("Replay");
	}
	if(m_vNode.top()==CString("StimulatorConfigFile"))
	{
		m_sStimulatorConfigFile = OpenViBE::Directories::getDistRootDir() + "/share/" + l_sExpandedString;
	}
	if(m_vNode.top()==CString("AdditionalConfigurationFile"))
	{
		m_AdditionalConfigurationFile = OpenViBE::Directories::getDistRootDir() + "/share/" + l_sExpandedString;
	}	
	if(m_vNode.top()==CString("SymbolDefinitionFile"))
	{
		m_sSymbolDefinitionFile = OpenViBE::Directories::getDistRootDir() + "/share/" + l_sExpandedString;
	}
	if(m_vNode.top()==CString("FlashGroupDefinitionFile"))
	{
		m_sFlashGroupDefinitionFile = l_sExpandedString;
	}
	if(m_vNode.top()==CString("Screen"))
	{
		if (l_sExpandedString==CString("full"))
			m_bFullScreen =  true;
		else
			m_bFullScreen =  false;
	}
	if(m_vNode.top()==CString("FlashMode"))
	{
		m_sFlashMode =  l_sExpandedString;
	}	
	if (m_vNode.top()==CString("FeedbackPresentation"))
	{
		if (m_sFeedbackPresentationMode==CString("free"))
		{
			if (l_sExpandedString==CString("central"))
				m_bCentralFeedbackFreeMode = true;
			else
				m_bCentralFeedbackFreeMode = false;
		}
		else if (m_sFeedbackPresentationMode==CString("copy"))
		{
			if (l_sExpandedString==CString("central"))
				m_bCentralFeedbackCopyMode = true;
			else
				m_bCentralFeedbackCopyMode = false;	
		}
	}
	if(m_vNode.top()==CString("ParallelPortNumber"))
	{
		m_ui32ParallelPortNumber = strtoul(sData,NULL,0);
	}
	if(m_vNode.top()==CString("PhotoDiode"))
	{
		if(CString("yes")==l_sExpandedString)
			m_bEnablePhotoDiode = true;
		else
			m_bEnablePhotoDiode = false;
	}
	if(m_vNode.top()==CString("SampleFrequency"))
	{
		m_ui32SampleFrequency = strtoul(sData,NULL,0);
	}
	if(m_vNode.top()==CString("NGramDatabase"))
	{
		m_sNGramDatabaseName = OpenViBE::Directories::getDistRootDir() + "/share/" + l_sExpandedString;
	}
	if(m_bContinuousFeedback)
	{
		if(m_vNode.top()==CString("MaxFeedbackSymbols"))
			m_ui32MaxFeedbackSymbols = static_cast<uint32>(m_pKernelContext->getConfigurationManager().expandAsUInteger(l_sExpandedString));
		if(m_vNode.top()==CString("FeedbackStartColor"))
			m_oFeedbackStartColor = _AutoCast_(sData);
		if(m_vNode.top()==CString("FeedbackEndColor"))
			m_oFeedbackEndColor = _AutoCast_(sData);
		if(m_vNode.top()==CString("ColorFeedbackSteps"))
			m_ui32ColorFeedbackSteps = static_cast<uint32>(m_pKernelContext->getConfigurationManager().expandAsUInteger(l_sExpandedString));
		if(m_vNode.top()==CString("FeedbackStartValue"))
			m_f32FeedbackStartValue = static_cast<float32>(m_pKernelContext->getConfigurationManager().expandAsFloat(l_sExpandedString));
	}
}

void P300InterfacePropertyReader::closeChild(void)
{
	m_vNode.pop();
}
