#ifndef __OpenViBEPlugins_BoxAlgorithm_SpatialFilter_H__
#define __OpenViBEPlugins_BoxAlgorithm_SpatialFilter_H__

#include <openvibe/ov_all.h>
#include <toolkit/ovtk_all.h>

#include <vector>

#define OVP_ClassId_BoxAlgorithm_SpatialFilter     OpenViBE::CIdentifier(0xDD332C6C, 0x195B4FD4)
#define OVP_ClassId_BoxAlgorithm_SpatialFilterDesc OpenViBE::CIdentifier(0x72A01C92, 0xF8C1FA24)

namespace OpenViBEPlugins
{
	namespace SignalProcessing
	{
		class CBoxAlgorithmSpatialFilter : public OpenViBEToolkit::TBoxAlgorithm < OpenViBE::Plugins::IBoxAlgorithm >
		{
		public:

			virtual void release(void) { delete this; }

			virtual OpenViBE::boolean initialize(void);
			virtual OpenViBE::boolean uninitialize(void);
			virtual OpenViBE::boolean processInput(OpenViBE::uint32 ui32InputIndex);
			virtual OpenViBE::boolean process(void);

			_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxAlgorithm < OpenViBE::Plugins::IBoxAlgorithm >, OVP_ClassId_BoxAlgorithm_SpatialFilter);

		protected:

			OpenViBEToolkit::TDecoder < CBoxAlgorithmSpatialFilter >* m_pStreamDecoder;
			OpenViBEToolkit::TEncoder < CBoxAlgorithmSpatialFilter >* m_pStreamEncoder;

			OpenViBE::CMatrix m_oFilterBank;

		private:
			// Loads the m_vCoefficient vector (representing a matrix) from the given string. c1 and c2 are separator characters between floats.
			OpenViBE::uint32 loadCoefficients(const OpenViBE::CString &rCoefficients, const char c1, const char c2,  OpenViBE::uint32 nRows, OpenViBE::uint32 nCols);

		};

		class CBoxAlgorithmSpatialFilterListener : public OpenViBEToolkit::TBoxListener < OpenViBE::Plugins::IBoxListener >
		{
		public:

			virtual OpenViBE::boolean onInputTypeChanged(OpenViBE::Kernel::IBox& rBox, const OpenViBE::uint32 ui32Index)
			{
				OpenViBE::CIdentifier l_oTypeIdentifier;
				rBox.getInputType(0, l_oTypeIdentifier);
				rBox.setOutputType(0, l_oTypeIdentifier);
				return true;
			}

			virtual OpenViBE::boolean onOutputTypeChanged(OpenViBE::Kernel::IBox& rBox, const OpenViBE::uint32 ui32Index)
			{
				OpenViBE::CIdentifier l_oTypeIdentifier;
				rBox.getOutputType(0, l_oTypeIdentifier);
				rBox.setInputType(0, l_oTypeIdentifier);
				return true;
			}

			_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxListener < OpenViBE::Plugins::IBoxListener >, OV_UndefinedIdentifier);
		};

		class CBoxAlgorithmSpatialFilterDesc : public OpenViBE::Plugins::IBoxAlgorithmDesc
		{
		public:

			virtual void release(void) { }

			virtual OpenViBE::CString getName(void) const                { return OpenViBE::CString("Spatial Filter"); }
			virtual OpenViBE::CString getAuthorName(void) const          { return OpenViBE::CString("Yann Renard, Jussi T. Lindgren"); }
			virtual OpenViBE::CString getAuthorCompanyName(void) const   { return OpenViBE::CString("Inria"); }
			virtual OpenViBE::CString getShortDescription(void) const    { return OpenViBE::CString("Maps M inputs to N outputs by multiplying the each input vector with a matrix"); }
			virtual OpenViBE::CString getDetailedDescription(void) const { return OpenViBE::CString("The applied coefficient matrix must be specified as a box parameter. The filter processes each sample independently of the past samples."); }
			virtual OpenViBE::CString getCategory(void) const            { return OpenViBE::CString("Signal processing/Filtering"); }
			virtual OpenViBE::CString getVersion(void) const             { return OpenViBE::CString("1.1"); }
			virtual OpenViBE::CString getSoftwareComponent(void) const   { return OpenViBE::CString("openvibe-sdk"); }
			virtual OpenViBE::CString getAddedSoftwareVersion(void) const   { return OpenViBE::CString("0.0.0"); }
			virtual OpenViBE::CString getUpdatedSoftwareVersion(void) const { return OpenViBE::CString("0.1.0"); }
			
			virtual OpenViBE::CIdentifier getCreatedClass(void) const    { return OVP_ClassId_BoxAlgorithm_SpatialFilter; }
			virtual OpenViBE::Plugins::IPluginObject* create(void)       { return new OpenViBEPlugins::SignalProcessing::CBoxAlgorithmSpatialFilter; }
			virtual OpenViBE::Plugins::IBoxListener* createBoxListener(void) const               { return new CBoxAlgorithmSpatialFilterListener; }
			virtual void releaseBoxListener(OpenViBE::Plugins::IBoxListener* pBoxListener) const { delete pBoxListener; }

			virtual OpenViBE::boolean getBoxPrototype(
				OpenViBE::Kernel::IBoxProto& rBoxAlgorithmPrototype) const
			{
				rBoxAlgorithmPrototype.addInput  ("Input Signal",                OV_TypeId_Signal);
				rBoxAlgorithmPrototype.addOutput ("Output Signal",               OV_TypeId_Signal);
				rBoxAlgorithmPrototype.addSetting("Spatial Filter Coefficients", OV_TypeId_String,  "1;0;0;0;0;1;0;0;0;0;1;0;0;0;0;1");
				rBoxAlgorithmPrototype.addSetting("Number of Output Channels",   OV_TypeId_Integer, "4");
				rBoxAlgorithmPrototype.addSetting("Number of Input Channels",    OV_TypeId_Integer, "4");
				rBoxAlgorithmPrototype.addSetting("Filter matrix file",          OV_TypeId_Filename,  "");
				rBoxAlgorithmPrototype.addFlag   (OpenViBE::Kernel::BoxFlag_CanModifyInput);
				rBoxAlgorithmPrototype.addFlag   (OpenViBE::Kernel::BoxFlag_CanModifyOutput);

				rBoxAlgorithmPrototype.addInputSupport(OV_TypeId_StreamedMatrix);
				rBoxAlgorithmPrototype.addInputSupport(OV_TypeId_Spectrum);
				rBoxAlgorithmPrototype.addInputSupport(OV_TypeId_Signal);

				rBoxAlgorithmPrototype.addOutputSupport(OV_TypeId_StreamedMatrix);
				rBoxAlgorithmPrototype.addOutputSupport(OV_TypeId_Spectrum);
				rBoxAlgorithmPrototype.addOutputSupport(OV_TypeId_Signal);

				return true;
			}

			_IsDerivedFromClass_Final_(OpenViBE::Plugins::IBoxAlgorithmDesc, OVP_ClassId_BoxAlgorithm_SpatialFilterDesc);
		};
	};
};

#endif // __OpenViBEPlugins_BoxAlgorithm_SpatialFilter_H__
