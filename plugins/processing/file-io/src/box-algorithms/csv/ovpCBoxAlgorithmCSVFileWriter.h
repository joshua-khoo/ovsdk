#ifndef __OpenViBEPlugins_BoxAlgorithm_CSVFileWriter_H__
#define __OpenViBEPlugins_BoxAlgorithm_CSVFileWriter_H__

#include "../../ovp_defines.h"
#include <openvibe/ov_all.h>
#include <toolkit/ovtk_all.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

// TODO:
// - please move the identifier definitions in ovp_defines.h
// - please include your desciptor in ovp_main.cpp

//#define OVP_ClassId_BoxAlgorithm_CSVFileWriter     OpenViBE::CIdentifier(0x2C9312F1, 0x2D6613E5)
//#define OVP_ClassId_BoxAlgorithm_CSVFileWriterDesc OpenViBE::CIdentifier(0x65075FF7, 0x2B555E97)


namespace OpenViBEPlugins
{
	namespace FileIO
	{
		class CBoxAlgorithmCSVFileWriter : public OpenViBEToolkit::TBoxAlgorithm < OpenViBE::Plugins::IBoxAlgorithm >
		{
		public:

			CBoxAlgorithmCSVFileWriter(void);
			virtual void release(void) { delete this; }

			virtual OpenViBE::boolean initialize(void);
			virtual OpenViBE::boolean uninitialize(void);
			virtual OpenViBE::boolean processInput(OpenViBE::uint32 ui32InputIndex);
			virtual OpenViBE::boolean process(void);

			OpenViBE::boolean process_streamedMatrix(void);
			OpenViBE::boolean process_stimulation(void);

			_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxAlgorithm < OpenViBE::Plugins::IBoxAlgorithm >, OVP_ClassId_BoxAlgorithm_CSVFileWriter);

		protected:

			std::ofstream m_oFileStream;

			OpenViBE::CString m_sSeparator;
			OpenViBE::CIdentifier m_oTypeIdentifier;
			OpenViBE::boolean m_bFirstBuffer;
			OpenViBE::boolean (OpenViBEPlugins::FileIO::CBoxAlgorithmCSVFileWriter::*m_fpRealProcess)(void);

			OpenViBEToolkit::TDecoder < CBoxAlgorithmCSVFileWriter >* m_pStreamDecoder;
			OpenViBE::IMatrix* m_pMatrix;
			OpenViBE::boolean m_bDeleteMatrix;

			OpenViBE::uint64 m_ui64SampleCount;

			// OpenViBE::Kernel::TParameterHandler < const OpenViBE::IMemoryBuffer* > ip_pMemoryBuffer;
			// OpenViBE::Kernel::TParameterHandler < OpenViBE::IMatrix* > op_pMatrix;
			// OpenViBE::Kernel::TParameterHandler < OpenViBE::IMatrix* > op_pMinMaxFrequencyBand;
			// OpenViBE::Kernel::TParameterHandler < OpenViBE::uint64 > op_ui64SamplingFrequency;
			// OpenViBE::Kernel::TParameterHandler < OpenViBE::IStimulationSet* > op_pStimulationSet;

		};

		class CBoxAlgorithmCSVFileWriterListener : public OpenViBEToolkit::TBoxListener < OpenViBE::Plugins::IBoxListener >
		{
		public:

			virtual OpenViBE::boolean onInputTypeChanged(OpenViBE::Kernel::IBox& rBox, const OpenViBE::uint32 ui32Index)
			{
				// @note this doesn't currently work as ConnectionEditor replaces the value set here by the gtk widget text field contents				
				OpenViBE::CIdentifier l_oTypeIdentifier;
				rBox.getInputType(ui32Index, l_oTypeIdentifier);
				rBox.setInputName(ui32Index, this->getTypeManager().getTypeName(l_oTypeIdentifier));

				return true;
			}

			_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxListener < OpenViBE::Plugins::IBoxListener >, OV_UndefinedIdentifier);
		};

		class CBoxAlgorithmCSVFileWriterDesc : public OpenViBE::Plugins::IBoxAlgorithmDesc
		{
		public:

			virtual void release(void) { }

			virtual OpenViBE::CString getName(void) const                { return OpenViBE::CString("CSV File Writer"); }
			virtual OpenViBE::CString getAuthorName(void) const          { return OpenViBE::CString("Yann Renard"); }
			virtual OpenViBE::CString getAuthorCompanyName(void) const   { return OpenViBE::CString("INRIA"); }
			virtual OpenViBE::CString getShortDescription(void) const    { return OpenViBE::CString("Writes signal in a CSV (text based) file"); }
			virtual OpenViBE::CString getDetailedDescription(void) const { return OpenViBE::CString(""); }
			virtual OpenViBE::CString getCategory(void) const            { return OpenViBE::CString("File reading and writing/CSV"); }
			virtual OpenViBE::CString getVersion(void) const             { return OpenViBE::CString("1.0"); }
			virtual OpenViBE::CString getStockItemName(void) const       { return OpenViBE::CString("gtk-open"); }

			virtual OpenViBE::CIdentifier getCreatedClass(void) const    { return OVP_ClassId_BoxAlgorithm_CSVFileWriter; }
			virtual OpenViBE::Plugins::IPluginObject* create(void)       { return new OpenViBEPlugins::FileIO::CBoxAlgorithmCSVFileWriter; }
			virtual OpenViBE::Plugins::IBoxListener* createBoxListener(void) const               { return new CBoxAlgorithmCSVFileWriterListener; }
			virtual void releaseBoxListener(OpenViBE::Plugins::IBoxListener* pBoxListener) const { delete pBoxListener; }

			virtual OpenViBE::boolean getBoxPrototype(
				OpenViBE::Kernel::IBoxProto& rBoxAlgorithmPrototype) const
			{
				rBoxAlgorithmPrototype.addInput  ("Input signal",  OV_TypeId_Signal);
				rBoxAlgorithmPrototype.addSetting("Filename",         OV_TypeId_Filename, "record-[$core{date}-$core{time}].csv");
				rBoxAlgorithmPrototype.addSetting("Column separator", OV_TypeId_String, ";");
				rBoxAlgorithmPrototype.addSetting("Precision",        OV_TypeId_Integer, "10");
				rBoxAlgorithmPrototype.addFlag(OpenViBE::Kernel::BoxFlag_CanModifyInput);

				rBoxAlgorithmPrototype.addInputSupport(OV_TypeId_Signal);
				rBoxAlgorithmPrototype.addInputSupport(OV_TypeId_StreamedMatrix);
				rBoxAlgorithmPrototype.addInputSupport(OV_TypeId_Spectrum);
				rBoxAlgorithmPrototype.addInputSupport(OV_TypeId_Stimulations);
				rBoxAlgorithmPrototype.addInputSupport(OV_TypeId_FeatureVector);

				return true;
			}

			_IsDerivedFromClass_Final_(OpenViBE::Plugins::IBoxAlgorithmDesc, OVP_ClassId_BoxAlgorithm_CSVFileWriterDesc);
		};
	};
};

#endif // __OpenViBEPlugins_BoxAlgorithm_CSVFileWriter_H__
