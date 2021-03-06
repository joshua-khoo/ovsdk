#ifndef __OpenViBEPlugins_BoxAlgorithm_EpochAverage_H__
#define __OpenViBEPlugins_BoxAlgorithm_EpochAverage_H__

#include "../../ovp_defines.h"
#include <toolkit/ovtk_all.h>

#define OVP_ClassId_BoxAlgorithm_EpochAverage                                          OpenViBE::CIdentifier(0x21283D9F, 0xE76FF640)
#define OVP_ClassId_BoxAlgorithm_EpochAverageDesc                                      OpenViBE::CIdentifier(0x95F5F43E, 0xBE629D82)

namespace OpenViBEPlugins
{
	namespace SignalProcessing
	{
		class CBoxAlgorithmEpochAverage : public OpenViBEToolkit::TBoxAlgorithm<OpenViBE::Plugins::IBoxAlgorithm>
		{
		public:

			virtual void release(void) { delete this; }

			virtual OpenViBE::boolean initialize(void);
			virtual OpenViBE::boolean uninitialize(void);

			virtual OpenViBE::boolean processInput(OpenViBE::uint32 ui32InputIndex);
			virtual OpenViBE::boolean process(void);

			_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxAlgorithm<OpenViBE::Plugins::IBoxAlgorithm>, OVP_ClassId_BoxAlgorithm_EpochAverage)

		protected:

			OpenViBE::Kernel::IAlgorithmProxy* m_pStreamDecoder;
			OpenViBE::Kernel::IAlgorithmProxy* m_pStreamEncoder;
			OpenViBE::Kernel::IAlgorithmProxy* m_pMatrixAverage;

			OpenViBE::Kernel::TParameterHandler < OpenViBE::uint64 > ip_ui64MatrixCount;
			OpenViBE::Kernel::TParameterHandler < OpenViBE::uint64 > ip_ui64AveragingMethod;
		};

		class CBoxAlgorithmEpochAverageListener : public OpenViBEToolkit::TBoxListener < OpenViBE::Plugins::IBoxListener >
		{
		public:

			virtual OpenViBE::boolean onInputTypeChanged(OpenViBE::Kernel::IBox& rBox, const OpenViBE::uint32 ui32Index)
			{
				OpenViBE::CIdentifier l_oTypeIdentifier;
				rBox.getInputType(ui32Index, l_oTypeIdentifier);
				rBox.setOutputType(ui32Index, l_oTypeIdentifier);
				return true;
			}

			virtual OpenViBE::boolean onOutputTypeChanged(OpenViBE::Kernel::IBox& rBox, const OpenViBE::uint32 ui32Index)
			{
				OpenViBE::CIdentifier l_oTypeIdentifier;
				rBox.getOutputType(ui32Index, l_oTypeIdentifier);
				rBox.setInputType(ui32Index, l_oTypeIdentifier);
				return true;
			};

			_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxListener < OpenViBE::Plugins::IBoxListener >, OV_UndefinedIdentifier);
		};

		class CBoxAlgorithmEpochAverageDesc : public OpenViBE::Plugins::IBoxAlgorithmDesc
		{
		public:

			virtual void release(void) { }
			virtual OpenViBE::CString getName(void) const                { return OpenViBE::CString("Epoch average"); }
			virtual OpenViBE::CString getAuthorName(void) const          { return OpenViBE::CString("Yann Renard"); }
			virtual OpenViBE::CString getAuthorCompanyName(void) const   { return OpenViBE::CString("INRIA/IRISA"); }
			virtual OpenViBE::CString getShortDescription(void) const    { return OpenViBE::CString("Averages matrices among time, this can be used to enhance ERPs"); }
			virtual OpenViBE::CString getDetailedDescription(void) const { return OpenViBE::CString("This box can average matrices of different types including signal, spectrum or feature vectors"); }
			virtual OpenViBE::CString getCategory(void) const            { return OpenViBE::CString("Signal processing/Averaging"); }
			virtual OpenViBE::CString getVersion(void) const             { return OpenViBE::CString("1.0"); }
			virtual OpenViBE::CString getSoftwareComponent(void) const   { return OpenViBE::CString("openvibe-sdk"); }
			virtual OpenViBE::CString getAddedSoftwareVersion(void) const   { return OpenViBE::CString("0.0.0"); }
			virtual OpenViBE::CString getUpdatedSoftwareVersion(void) const { return OpenViBE::CString("0.0.0"); }
			
			virtual OpenViBE::CIdentifier getCreatedClass(void) const    { return OVP_ClassId_BoxAlgorithm_EpochAverage; }
			virtual OpenViBE::Plugins::IPluginObject* create(void)       { return new OpenViBEPlugins::SignalProcessing::CBoxAlgorithmEpochAverage(); }
			virtual OpenViBE::Plugins::IBoxListener* createBoxListener(void) const               { return new CBoxAlgorithmEpochAverageListener; }
			virtual void releaseBoxListener(OpenViBE::Plugins::IBoxListener* pBoxListener) const { delete pBoxListener; }

			virtual OpenViBE::boolean getBoxPrototype(
				OpenViBE::Kernel::IBoxProto& rPrototype) const
			{
				rPrototype.addInput  ("Input epochs",    OV_TypeId_StreamedMatrix);
				rPrototype.addOutput ("Averaged epochs", OV_TypeId_StreamedMatrix);
				rPrototype.addSetting("Averaging type",  OVP_TypeId_EpochAverageMethod, OVP_TypeId_EpochAverageMethod_MovingAverage.toString());
				rPrototype.addSetting("Epoch count",     OV_TypeId_Integer, "4");
				rPrototype.addFlag   (OpenViBE::Kernel::BoxFlag_CanModifyOutput);
				rPrototype.addFlag   (OpenViBE::Kernel::BoxFlag_CanModifyInput);

				rPrototype.addInputSupport(OV_TypeId_Signal);
				rPrototype.addInputSupport(OV_TypeId_Spectrum);
				rPrototype.addInputSupport(OV_TypeId_StreamedMatrix);
				rPrototype.addInputSupport(OV_TypeId_FeatureVector);
				rPrototype.addInputSupport(OV_TypeId_TimeFrequency);

				rPrototype.addOutputSupport(OV_TypeId_Signal);
				rPrototype.addOutputSupport(OV_TypeId_Spectrum);
				rPrototype.addOutputSupport(OV_TypeId_StreamedMatrix);
				rPrototype.addOutputSupport(OV_TypeId_FeatureVector);
				rPrototype.addOutputSupport(OV_TypeId_TimeFrequency);
				return true;
			}

			_IsDerivedFromClass_Final_(OpenViBE::Plugins::IBoxAlgorithmDesc, OVP_ClassId_BoxAlgorithm_EpochAverageDesc)
		};
	};
};

#endif // __OpenViBEPlugins_BoxAlgorithm_EpochAverage_H__
