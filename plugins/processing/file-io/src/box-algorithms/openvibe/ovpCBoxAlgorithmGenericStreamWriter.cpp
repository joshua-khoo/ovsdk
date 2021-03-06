#include "ovpCBoxAlgorithmGenericStreamWriter.h"

#include <fs/Files.h>

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBE::Plugins;

using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::FileIO;

CBoxAlgorithmGenericStreamWriter::CBoxAlgorithmGenericStreamWriter(void)
	:m_bIsHeaderGenerate(false)
	,m_oWriter(*this)
{
}

boolean CBoxAlgorithmGenericStreamWriter::initialize(void)
{
	m_sFilename = FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 0);
	bool l_bUseCompression = FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 1);

	if(l_bUseCompression)
	{
		OV_WARNING_K("Impossible to use compression as it is not yet implemented");
	}

	return true;
}

boolean CBoxAlgorithmGenericStreamWriter::uninitialize(void)
{
	if(m_oFile.is_open())
	{
		m_oFile.close();
	}
	return true;
}

boolean CBoxAlgorithmGenericStreamWriter::generateFileHeader()
{
	const IBox& l_rStaticBoxContext=this->getStaticBoxContext();

	m_oSwap.setSize(0, true);

	m_oWriterHelper.connect(&m_oWriter);

	m_oWriterHelper.openChild(EBML_Identifier_Header);
	 m_oWriterHelper.openChild(EBML_Identifier_DocType);
	  m_oWriterHelper.setASCIIStringAsChildData("OpenViBE_Stream_File");
	 m_oWriterHelper.closeChild();

	 m_oWriterHelper.openChild(EBML_Identifier_EBMLVersion);
	  m_oWriterHelper.setUIntegerAsChildData(1);
	 m_oWriterHelper.closeChild();

	 m_oWriterHelper.openChild(EBML_Identifier_EBMLIdLength);
	  m_oWriterHelper.setUIntegerAsChildData(10);
	 m_oWriterHelper.closeChild();
	m_oWriterHelper.closeChild();

	m_oWriterHelper.openChild(OVP_NodeId_OpenViBEStream_Header);
	 m_oWriterHelper.openChild(OVP_NodeId_OpenViBEStream_Header_Compression);
	  m_oWriterHelper.setUIntegerAsChildData(0 /* compression flag */);
	 m_oWriterHelper.closeChild();
	for(uint32 i=0; i<l_rStaticBoxContext.getInputCount(); i++)
	{
		CIdentifier l_oIdentifier;
		l_rStaticBoxContext.getInputType(i, l_oIdentifier);

		m_oWriterHelper.openChild(OVP_NodeId_OpenViBEStream_Header_StreamType);
		 m_oWriterHelper.setUIntegerAsChildData(l_oIdentifier.toUInteger());
		m_oWriterHelper.closeChild();
	}
	m_oWriterHelper.closeChild();
	m_oWriterHelper.disconnect();

	FS::Files::openOFStream(m_oFile, m_sFilename.toASCIIString(), std::ios::binary | std::ios::trunc);

	OV_ERROR_UNLESS_KRF(
		m_oFile.good(),
		"Error opening file [" << m_sFilename << "] for writing",
		OpenViBE::Kernel::ErrorType::BadFileWrite
	);

	m_oFile.write(reinterpret_cast<const char*>(m_oSwap.getDirectPointer()), (std::streamsize)m_oSwap.getSize());

	m_bIsHeaderGenerate = true;
	return true;
}

boolean CBoxAlgorithmGenericStreamWriter::processInput(uint32 ui32InputIndex)
{
	getBoxAlgorithmContext()->markAlgorithmAsReadyToProcess();
	return true;
}

boolean CBoxAlgorithmGenericStreamWriter::process(void)
{
	const IBox& l_rStaticBoxContext=this->getStaticBoxContext();
	IBoxIO& l_rDynamicBoxContext=this->getDynamicBoxContext();

	if(!m_bIsHeaderGenerate)
	{
		if(!generateFileHeader())
		{
			return false;
		}
	}

	m_oSwap.setSize(0, true);

	for(uint32 i=0; i<l_rStaticBoxContext.getInputCount(); i++)
	{
		for(uint32 j=0; j<l_rDynamicBoxContext.getInputChunkCount(i); j++)
		{
			m_oWriterHelper.connect(&m_oWriter);
			m_oWriterHelper.openChild(OVP_NodeId_OpenViBEStream_Buffer);
			 m_oWriterHelper.openChild(OVP_NodeId_OpenViBEStream_Buffer_StreamIndex);
			  m_oWriterHelper.setUIntegerAsChildData(i);
			 m_oWriterHelper.closeChild();
			 m_oWriterHelper.openChild(OVP_NodeId_OpenViBEStream_Buffer_StartTime);
			  m_oWriterHelper.setUIntegerAsChildData(l_rDynamicBoxContext.getInputChunkStartTime(i, j));
			 m_oWriterHelper.closeChild();
			 m_oWriterHelper.openChild(OVP_NodeId_OpenViBEStream_Buffer_EndTime);
			  m_oWriterHelper.setUIntegerAsChildData(l_rDynamicBoxContext.getInputChunkEndTime(i, j));
			 m_oWriterHelper.closeChild();
			 m_oWriterHelper.openChild(OVP_NodeId_OpenViBEStream_Buffer_Content);
			  m_oWriterHelper.setBinaryAsChildData(l_rDynamicBoxContext.getInputChunk(i, j)->getDirectPointer(), l_rDynamicBoxContext.getInputChunk(i, j)->getSize());
			 m_oWriterHelper.closeChild();
			m_oWriterHelper.closeChild();
			m_oWriterHelper.disconnect();
			l_rDynamicBoxContext.markInputAsDeprecated(i, j);
		}
	}

	if(m_oSwap.getSize() != 0)
	{
		m_oFile.write(reinterpret_cast<const char*>(m_oSwap.getDirectPointer()), (std::streamsize)m_oSwap.getSize());

		OV_ERROR_UNLESS_KRF(
			m_oFile.good(),
			"Error opening file [" << m_sFilename << "] for writing",
			OpenViBE::Kernel::ErrorType::BadFileWrite
		);
	}

	return true;
}

void CBoxAlgorithmGenericStreamWriter::write(const void* pBuffer, const EBML::uint64 ui64BufferSize)
{
	m_oSwap.append(reinterpret_cast<const uint8*>(pBuffer), ui64BufferSize);
}
