#include "ovtkCAlgorithmScenarioImporter.h"

#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include <string>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/validators/common/Grammar.hpp>

XERCES_CPP_NAMESPACE_USE

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBE::Plugins;

using namespace OpenViBEToolkit;

namespace OpenViBEToolkit
{
	namespace
	{
		#define _default_and_copy_constructor_1_(c,m1)                      c(void) { } c(const c& r) : m1(r.m1) { }
		#define _default_and_copy_constructor_2_(c,m1,m2)                   c(void) { } c(const c& r) : m1(r.m1), m2(r.m2) { }
		#define _default_and_copy_constructor_3_(c,m1,m2,m3)                c(void) { } c(const c& r) : m1(r.m1), m2(r.m2), m3(r.m3) { }
		#define _default_and_copy_constructor_4_(c,m1,m2,m3,m4)             c(void) { } c(const c& r) : m1(r.m1), m2(r.m2), m3(r.m3), m4(r.m4) { }
		#define _default_and_copy_constructor_5_(c,m1,m2,m3,m4,m5)          c(void) { } c(const c& r) : m1(r.m1), m2(r.m2), m3(r.m3), m4(r.m4), m5(r.m5) { }
		#define _default_and_copy_constructor_6_(c,m1,m2,m3,m4,m5,m6)       c(void) { } c(const c& r) : m1(r.m1), m2(r.m2), m3(r.m3), m4(r.m4), m5(r.m5), m6(r.m6) { }
		#define _default_and_copy_constructor_7_(c,m1,m2,m3,m4,m5,m6,m7)    c(void) { } c(const c& r) : m1(r.m1), m2(r.m2), m3(r.m3), m4(r.m4), m5(r.m5), m6(r.m6), m7(r.m7) { }
		#define _default_and_copy_constructor_8_(c,m1,m2,m3,m4,m5,m6,m7,m8) c(void) { } c(const c& r) : m1(r.m1), m2(r.m2), m3(r.m3), m4(r.m4), m5(r.m5), m6(r.m6), m7(r.m7), m8(r.m8) { }
		#define _default_and_copy_constructor_9_(c,m1,m2,m3,m4,m5,m6,m7,m8, m9) c(void) { } c(const c& r) : m1(r.m1), m2(r.m2), m3(r.m3), m4(r.m4), m5(r.m5), m6(r.m6), m7(r.m7), m8(r.m8), m9(r.m9) { }


		typedef struct _SScenarioInput
		{
			_default_and_copy_constructor_4_(_SScenarioInput, m_oTypeIdentifier, m_sName, m_oLinkedBoxIdentifier, m_ui32LinkedBoxInputIndex)
			CIdentifier m_oTypeIdentifier;
			CString m_sName;
			CIdentifier m_oLinkedBoxIdentifier;
			uint32 m_ui32LinkedBoxInputIndex;
		} SScenarioInput;

		typedef struct _SScenarioOutput
		{
			_default_and_copy_constructor_4_(_SScenarioOutput, m_oTypeIdentifier, m_sName, m_oLinkedBoxIdentifier, m_ui32LinkedBoxOutputIndex)
			CIdentifier m_oTypeIdentifier;
			CString m_sName;
			CIdentifier m_oLinkedBoxIdentifier;
			uint32 m_ui32LinkedBoxOutputIndex;
		} SScenarioOutput;

		typedef struct _SInput
		{
			_default_and_copy_constructor_2_(_SInput, m_oTypeIdentifier, m_sName);
			CIdentifier m_oTypeIdentifier;
			CString m_sName;
		} SInput;

		typedef struct _SOutput
		{
			_default_and_copy_constructor_2_(_SOutput, m_oTypeIdentifier, m_sName);
			CIdentifier m_oTypeIdentifier;
			CString m_sName;
		} SOutput;

		typedef struct _SSetting
		{
			//_default_and_copy_constructor_4_(_SSetting, m_oTypeIdentifier, m_sName, m_sDefaultValue, m_sValue);
			_SSetting(void) :m_bModifiability(false) { }
			_SSetting(const _SSetting& r) : m_oTypeIdentifier(r.m_oTypeIdentifier),
				m_sName(r.m_sName),
				m_sDefaultValue(r.m_sDefaultValue),
				m_sValue(r.m_sValue),
				m_bModifiability(r.m_bModifiability) { }
			CIdentifier m_oTypeIdentifier;
			CString m_sName;
			CString m_sDefaultValue;
			CString m_sValue;
			boolean m_bModifiability;
		} SSetting;
		typedef struct _SAttribute
		{
			_default_and_copy_constructor_2_(_SAttribute, m_oIdentifier, m_sValue);
			CIdentifier m_oIdentifier;
			CString m_sValue;
		} SAttribute;
		typedef struct _SBox
		{
			_default_and_copy_constructor_7_(_SBox, m_oIdentifier, m_oAlgorithmClassIdentifier, m_sName, m_vInput, m_vOutput, m_vSetting, m_vAttribute);
			CIdentifier m_oIdentifier;
			CIdentifier m_oAlgorithmClassIdentifier;
			CString m_sName;
			std::vector<SInput> m_vInput;
			std::vector<SOutput> m_vOutput;
			std::vector<SSetting> m_vSetting;
			std::vector<SAttribute> m_vAttribute;
		} SBox;
		typedef struct _SComment
		{
			_default_and_copy_constructor_3_(_SComment, m_oIdentifier, m_sText, m_vAttribute);
			CIdentifier m_oIdentifier;
			CString m_sText;
			std::vector<SAttribute> m_vAttribute;
		} SComment;
		typedef struct _SLinkSource
		{
			_default_and_copy_constructor_2_(_SLinkSource, m_oBoxIdentifier, m_ui32BoxOutputIndex);
			CIdentifier m_oBoxIdentifier;
			uint32 m_ui32BoxOutputIndex;
		} SLinkSource;
		typedef struct _SLinkTarget
		{
			_default_and_copy_constructor_2_(_SLinkTarget, m_oBoxIdentifier, m_ui32BoxInputIndex);
			CIdentifier m_oBoxIdentifier;
			uint32 m_ui32BoxInputIndex;
		} SLinkTarget;
		typedef struct _SLink
		{
			_default_and_copy_constructor_4_(_SLink, m_oIdentifier, m_oLinkSource, m_oLinkTarget, m_vAttribute);
			CIdentifier m_oIdentifier;
			SLinkSource m_oLinkSource;
			SLinkTarget m_oLinkTarget;
			std::vector<SAttribute> m_vAttribute;
		} SLink;
		typedef struct _SScenario
		{
			_default_and_copy_constructor_4_(_SScenario, m_vBox, m_vComment, m_vLink, m_vAttribute);
			std::vector<SSetting> m_vSetting;
			std::vector<SScenarioInput> m_vScenarioInput;
			std::vector<SScenarioOutput> m_vScenarioOutput;
			std::vector<SBox> m_vBox;
			std::vector<SComment> m_vComment;
			std::vector<SLink> m_vLink;
			std::vector<SAttribute> m_vAttribute;
		} SScenario;

		#undef _default_and_copy_constructor_1_
		#undef _default_and_copy_constructor_2_
		#undef _default_and_copy_constructor_3_
		#undef _default_and_copy_constructor_4_
		#undef _default_and_copy_constructor_5_
		#undef _default_and_copy_constructor_6_
		#undef _default_and_copy_constructor_7_
		#undef _default_and_copy_constructor_8_
		#undef _default_and_copy_constructor_9_
	};

	class CAlgorithmScenarioImporterContext : public IAlgorithmScenarioImporterContext
	{
	public:

		explicit CAlgorithmScenarioImporterContext(IAlgorithmContext& rAlgorithmContext)
			:m_rAlgorithmContext(rAlgorithmContext)
		{
		}

		virtual boolean processStart(const CIdentifier& rIdentifier);
		virtual boolean processIdentifier(const CIdentifier& rIdentifier, const CIdentifier& rValue);
		virtual boolean processString(const CIdentifier& rIdentifier, const CString& rValue);
		virtual boolean processUInteger(const CIdentifier& rIdentifier, const uint64 ui64Value);
		virtual boolean processStop(void);

		_IsDerivedFromClass_Final_(IAlgorithmScenarioImporterContext, OV_UndefinedIdentifier);

	public:

		IAlgorithmContext& m_rAlgorithmContext;
		SScenario m_oSymbolicScenario;
	};

	std::string xercesToString(const XMLCh* xercesString)
	{
		std::unique_ptr<char[]> charArray(XMLString::transcode(xercesString));
		return std::string(charArray.get());
	}

	const char* xercesToCString(const XMLCh* xercesString)
	{
		return xercesToString(xercesString).c_str();
	}

	class CErrorHandler final : public xercesc::HandlerBase
	{
		public:

		explicit CErrorHandler(IAlgorithmContext& rAlgorithmContext)
			:m_rAlgorithmContext(rAlgorithmContext)
		{
		}

		void fatalError(const xercesc::SAXParseException& exception) override
		{
			this->error(exception);
		}

		void error(const xercesc::SAXParseException& exception) override
		{
			// we just issue a warning here because the calling method
			// implements a fallback mechanism and we don't want to populate
			// the error manager if the importer returns gracefully.
			OV_WARNING(
				"Failed to validate xml: error [" << xercesToCString(exception.getMessage()) << "], line number [" << static_cast<uint64>(exception.getLineNumber()) << "]",
				m_rAlgorithmContext.getLogManager()
			);
		}

		void warning(const xercesc::SAXParseException& exception) override
		{
			OV_WARNING(
				"Warning while validating xml: warning [" << xercesToCString(exception.getMessage()) << "], line number [" << static_cast<uint64>(exception.getLineNumber()) << "]",
				m_rAlgorithmContext.getLogManager()
			);
		}

		private:
			IAlgorithmContext& m_rAlgorithmContext;
	};
}

bool CAlgorithmScenarioImporter::validateXML(const unsigned char* xmlBuffer, unsigned long xmlBufferSize)
{
	// implementation of the fallback mechanism

	// error manager is used to differentiate errors from invalid xml
	this->getErrorManager().releaseErrors();

	if(this->validateXMLAgainstSchema((OpenViBE::Directories::getDataDir() + "/kernel/openvibe-scenario-v1.xsd"), xmlBuffer, xmlBufferSize)) {
		return true;
	}
	else if(this->getErrorManager().hasError())
	{
		// this is not a validation error thus we return directly
		return false;
	}

	if(this->validateXMLAgainstSchema((OpenViBE::Directories::getDataDir() + "/kernel/openvibe-scenario-legacy.xsd"), xmlBuffer, xmlBufferSize)) {
		OV_WARNING_K("Importing scenario with legacy format: legacy scenarii might be deprecated in the future so upgrade to v1 format when possible");
		return true;
	}
	else if(this->getErrorManager().hasError())
	{
		// this is not a validation error thus we return directly
		return false;
	}

	OV_ERROR_KRF(
		"Failed to validate scenario against XSD schemas",
		OpenViBE::Kernel::ErrorType::BadXMLSchemaValidation
	);
}

bool CAlgorithmScenarioImporter::validateXMLAgainstSchema(const char *validationSchema, const unsigned char* xmlBuffer, unsigned long xmlBufferSize)
{

	this->getLogManager() << LogLevel_Info << "Validating XML against schema [" << validationSchema << "]\n";

	XMLPlatformUtils::Initialize();
	MemBufInputSource* xercesBuffer = new MemBufInputSource(xmlBuffer, xmlBufferSize, "xml memory buffer");

	XercesDOMParser* parser = new XercesDOMParser();
	parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);
    parser->setDoSchema(true);
    parser->setValidationConstraintFatal(true);
    parser->setValidationSchemaFullChecking(true);
    parser->setExternalNoNamespaceSchemaLocation(validationSchema);

	ErrorHandler* errorHandler = (ErrorHandler*) new CErrorHandler(this->getAlgorithmContext());
    parser->setErrorHandler(errorHandler);

    parser->parse(*xercesBuffer);
    unsigned int errorCount = parser->getErrorCount();

    delete parser;
	delete errorHandler;
	delete xercesBuffer;

	XMLPlatformUtils::Terminate();

	return (errorCount == 0);
}

boolean CAlgorithmScenarioImporter::process(void)
{
	TParameterHandler < IScenario* > op_pScenario(this->getOutputParameter(OV_Algorithm_ScenarioImporter_OutputParameterId_Scenario));
	IScenario* l_pScenario=op_pScenario;

	OV_ERROR_UNLESS_KRF(
		l_pScenario,
		"Output scenario is NULL",
		OpenViBE::Kernel::ErrorType::BadOutput
	);

	TParameterHandler < IMemoryBuffer* > ip_pMemoryBuffer(this->getInputParameter(OV_Algorithm_ScenarioImporter_InputParameterId_MemoryBuffer));
	IMemoryBuffer* l_pMemoryBuffer=ip_pMemoryBuffer;

	OV_ERROR_UNLESS_KRF(
		l_pMemoryBuffer,
		"Input memory buffer is NULL",
		OpenViBE::Kernel::ErrorType::BadInput
	);

	if(!this->validateXML(l_pMemoryBuffer->getDirectPointer(), l_pMemoryBuffer->getSize()))
	{
		return false; // error handling is handled in validateXML
	}

	std::map<CIdentifier, CIdentifier> l_vBoxIdMapping;

	CAlgorithmScenarioImporterContext l_oContext(this->getAlgorithmContext());

	OV_ERROR_UNLESS_KRF(
		this->import(l_oContext, *l_pMemoryBuffer),
		"Import failed",
		OpenViBE::Kernel::ErrorType::Internal
	);

	SScenario& l_rSymbolicScenario=l_oContext.m_oSymbolicScenario;

	// Now build the scenario according to what has been loaded
	std::vector<SBox>::const_iterator b;
	std::vector<SComment>::const_iterator c;
	std::vector<SInput>::const_iterator i;
	std::vector<SOutput>::const_iterator o;
	std::vector<SSetting>::const_iterator s;
	std::vector<SLink>::const_iterator l;
	std::vector<SAttribute>::const_iterator a;

	for(s=l_rSymbolicScenario.m_vSetting.begin(); s!=l_rSymbolicScenario.m_vSetting.end(); ++s)
	{
		l_pScenario->addSetting(
			s->m_sName,
			s->m_oTypeIdentifier,
			s->m_sDefaultValue);
		l_pScenario->setSettingValue(
			l_pScenario->getSettingCount()-1,
			s->m_sValue);
	}


	for(b=l_rSymbolicScenario.m_vBox.begin(); b!=l_rSymbolicScenario.m_vBox.end(); ++b)
	{
		IBox* l_pBox=NULL;
		CIdentifier l_oNewBoxIdentifier;

		l_pScenario->addBox(l_oNewBoxIdentifier, b->m_oIdentifier);
		l_pBox=l_pScenario->getBoxDetails(l_oNewBoxIdentifier);
		if(l_pBox)
		{
			l_pBox->setName(b->m_sName);

			for(i=b->m_vInput.begin(); i!=b->m_vInput.end(); ++i)
			{
				l_pBox->addInput(
					i->m_sName,
					i->m_oTypeIdentifier);
			}

			for(o=b->m_vOutput.begin(); o!=b->m_vOutput.end(); ++o)
			{
				l_pBox->addOutput(
					o->m_sName,
					o->m_oTypeIdentifier);
			}
			for(s=b->m_vSetting.begin(); s!=b->m_vSetting.end(); ++s)
			{
				const CIdentifier& l_oType = s->m_oTypeIdentifier;
				if(l_oType!=OV_TypeId_Boolean && l_oType!=OV_TypeId_Integer && l_oType!=OV_TypeId_Float && l_oType!=OV_TypeId_String
						&& l_oType!=OV_TypeId_Filename && l_oType!=OV_TypeId_Script && l_oType!=OV_TypeId_Color && l_oType!=OV_TypeId_ColorGradient
						&& !(this->getTypeManager().isEnumeration(l_oType)) && (!this->getTypeManager().isBitMask(l_oType)))
				{
					if(this->getConfigurationManager().expandAsBoolean("${Kernel_AbortScenarioImportOnUnknownSetting}", true))
					{
						OV_ERROR_KRF(
							"The type of the setting " << s->m_sName <<" (" << l_oType.toString() << ") from box " << b->m_sName << " cannot be recognized.",
							OpenViBE::Kernel::ErrorType::BadSetting
						);
					}
					else
					{
						OV_WARNING_K("The type of the setting " << s->m_sName <<" (" << l_oType.toString() << ") from box " << b->m_sName << " cannot be recognized.");
					}
				}

				l_pBox->addSetting(
					s->m_sName,
					s->m_oTypeIdentifier,
					s->m_sDefaultValue,
					-1,
					s->m_bModifiability);
				l_pBox->setSettingValue(
					l_pBox->getSettingCount()-1,
					s->m_sValue);

			}
			for(a=b->m_vAttribute.begin(); a!=b->m_vAttribute.end(); ++a)
			{
				l_pBox->addAttribute(
					a->m_oIdentifier,
					a->m_sValue);
			}

			// it is important to set box algorithm at
			// last so the box listener is never called
			l_pBox->setAlgorithmClassIdentifier(b->m_oAlgorithmClassIdentifier);
		}
		l_vBoxIdMapping[b->m_oIdentifier]=l_oNewBoxIdentifier;
	}

	for(c=l_rSymbolicScenario.m_vComment.begin(); c!=l_rSymbolicScenario.m_vComment.end(); ++c)
	{
		IComment* l_pComment=NULL;
		CIdentifier l_oNewCommentIdentifier;

		l_pScenario->addComment(l_oNewCommentIdentifier, c->m_oIdentifier);
		l_pComment=l_pScenario->getCommentDetails(l_oNewCommentIdentifier);
		if(l_pComment)
		{
			l_pComment->setText(c->m_sText);

			for(a=c->m_vAttribute.begin(); a!=c->m_vAttribute.end(); ++a)
			{
				l_pComment->addAttribute(
					a->m_oIdentifier,
					a->m_sValue);
			}
		}
	}
	for(l=l_rSymbolicScenario.m_vLink.begin(); l!=l_rSymbolicScenario.m_vLink.end(); ++l)
	{
		ILink* l_pLink=NULL;
		CIdentifier l_oNewLinkIdentifier;

		l_pScenario->connect(
			l_oNewLinkIdentifier,
			l_vBoxIdMapping[l->m_oLinkSource.m_oBoxIdentifier],
			l->m_oLinkSource.m_ui32BoxOutputIndex,
			l_vBoxIdMapping[l->m_oLinkTarget.m_oBoxIdentifier],
			l->m_oLinkTarget.m_ui32BoxInputIndex,
			l->m_oIdentifier);
		l_pLink=l_pScenario->getLinkDetails(l_oNewLinkIdentifier);
		if(l_pLink)
		{
			for(a=l->m_vAttribute.begin(); a!=l->m_vAttribute.end(); ++a)
			{
				l_pLink->addAttribute(
					a->m_oIdentifier,
					a->m_sValue);
			}
		}
	}

	uint32 l_ui32ScenarioInputIndex = 0;
	for(auto symbolicScenarioInput : l_rSymbolicScenario.m_vScenarioInput)
	{
		l_pScenario->addInput(symbolicScenarioInput.m_sName, symbolicScenarioInput.m_oTypeIdentifier);
		if (symbolicScenarioInput.m_oLinkedBoxIdentifier != OV_UndefinedIdentifier)
		{
			l_pScenario->setScenarioInputLink(l_ui32ScenarioInputIndex, symbolicScenarioInput.m_oLinkedBoxIdentifier, symbolicScenarioInput.m_ui32LinkedBoxInputIndex);
		}
		l_ui32ScenarioInputIndex++;
	}

	uint32 l_ui32ScenarioOutputIndex = 0;
	for(auto symbolicScenarioOutput : l_rSymbolicScenario.m_vScenarioOutput)
	{
		l_pScenario->addOutput(symbolicScenarioOutput.m_sName, symbolicScenarioOutput.m_oTypeIdentifier);
		if (symbolicScenarioOutput.m_oLinkedBoxIdentifier != OV_UndefinedIdentifier)
		{
			l_pScenario->setScenarioOutputLink(l_ui32ScenarioOutputIndex, symbolicScenarioOutput.m_oLinkedBoxIdentifier, symbolicScenarioOutput.m_ui32LinkedBoxOutputIndex);
		}
		l_ui32ScenarioOutputIndex++;
	}

	for(a=l_rSymbolicScenario.m_vAttribute.begin(); a!=l_rSymbolicScenario.m_vAttribute.end(); ++a)
	{
		l_pScenario->addAttribute(
			a->m_oIdentifier,
			a->m_sValue);
	}

	if(l_pScenario->checkNeedsUpdateBox())
	{
		CIdentifier l_oBoxIdentifier;
		while((l_oBoxIdentifier = l_pScenario->getNextNeedsUpdateBoxIdentifier(l_oBoxIdentifier)) != OV_UndefinedIdentifier)
		{
			const IBox* l_pBox = l_pScenario->getBoxDetails(l_oBoxIdentifier);

			if(this->getConfigurationManager().expandAsBoolean("${Kernel_AbortScenarioImportWhenBoxNeedsUpdate}", true))
			{
				OV_ERROR_KRF(
					"Box " << l_pBox->getName() << " [" << l_pBox->getAlgorithmClassIdentifier().toString() << "] must be updated",
					OpenViBE::Kernel::ErrorType::BadConfig
				);
			}
			else
			{
				OV_WARNING_K("Box " << l_pBox->getName() << " [" << l_pBox->getAlgorithmClassIdentifier().toString() << "] should be updated");
			}
		}
	}

	return true;
}

boolean CAlgorithmScenarioImporterContext::processStart(const CIdentifier& rIdentifier)
{
	if(false) { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_OpenViBEScenario)                         { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Settings)                        { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Setting)                         { m_oSymbolicScenario.m_vSetting.push_back(SSetting()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Inputs)                          { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Input)                           { m_oSymbolicScenario.m_vScenarioInput.push_back(SScenarioInput()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Outputs)                         { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Output)                          { m_oSymbolicScenario.m_vScenarioOutput.push_back(SScenarioOutput()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Creator)                                  { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_CreatorVersion)                           { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Attributes)                      { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Attribute)                       { m_oSymbolicScenario.m_vAttribute.push_back(SAttribute()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Attributes)                           { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Attribute)                            { m_oSymbolicScenario.m_vBox.back().m_vAttribute.push_back(SAttribute()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Attributes)                          { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Attribute)                           { m_oSymbolicScenario.m_vLink.back().m_vAttribute.push_back(SAttribute()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Boxes)                                    { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box)                                      { m_oSymbolicScenario.m_vBox.push_back(SBox()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Comments)                                 { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Comment)                                  { m_oSymbolicScenario.m_vComment.push_back(SComment()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Comment_Attributes)                       { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Comment_Attribute)                        { m_oSymbolicScenario.m_vComment.back().m_vAttribute.push_back(SAttribute());}
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Links)                                    { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link)                                     { m_oSymbolicScenario.m_vLink.push_back(SLink()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Source)                              { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Target)                              { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Inputs)                               { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Input)                                { m_oSymbolicScenario.m_vBox.back().m_vInput.push_back(SInput()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Outputs)                              { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Output)                               { m_oSymbolicScenario.m_vBox.back().m_vOutput.push_back(SOutput()); }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Settings)                             { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Setting)                              { m_oSymbolicScenario.m_vBox.back().m_vSetting.push_back(SSetting()); }
	//
	else OV_ERROR("(start) Unexpected node identifier " << rIdentifier.toString(), OpenViBE::Kernel::ErrorType::BadArgument, false, m_rAlgorithmContext.getErrorManager(), m_rAlgorithmContext.getLogManager());

	return true;
}

boolean CAlgorithmScenarioImporterContext::processIdentifier(const CIdentifier& rIdentifier, const CIdentifier& rValue)
{
	if(false) { }

	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Setting_TypeIdentifier)          { m_oSymbolicScenario.m_vSetting.back().m_oTypeIdentifier=rValue; }

	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Input_TypeIdentifier)            { m_oSymbolicScenario.m_vScenarioInput.back().m_oTypeIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Input_LinkedBoxIdentifier)       { m_oSymbolicScenario.m_vScenarioInput.back().m_oLinkedBoxIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Output_TypeIdentifier)           { m_oSymbolicScenario.m_vScenarioOutput.back().m_oTypeIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Output_LinkedBoxIdentifier)      { m_oSymbolicScenario.m_vScenarioOutput.back().m_oLinkedBoxIdentifier=rValue; }

	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Attribute_Identifier)                 { m_oSymbolicScenario.m_vBox.back().m_vAttribute.back().m_oIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Identifier)                           { m_oSymbolicScenario.m_vBox.back().m_oIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_AlgorithmClassIdentifier)             { m_oSymbolicScenario.m_vBox.back().m_oAlgorithmClassIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Input_TypeIdentifier)                 { m_oSymbolicScenario.m_vBox.back().m_vInput.back().m_oTypeIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Output_TypeIdentifier)                { m_oSymbolicScenario.m_vBox.back().m_vOutput.back().m_oTypeIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Setting_TypeIdentifier)               { m_oSymbolicScenario.m_vBox.back().m_vSetting.back().m_oTypeIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Comment_Identifier)                       { m_oSymbolicScenario.m_vComment.back().m_oIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Comment_Attribute_Identifier)             { m_oSymbolicScenario.m_vComment.back().m_vAttribute.back().m_oIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Attribute_Identifier)                { m_oSymbolicScenario.m_vLink.back().m_vAttribute.back().m_oIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Identifier)                          { m_oSymbolicScenario.m_vLink.back().m_oIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Source_BoxIdentifier)                { m_oSymbolicScenario.m_vLink.back().m_oLinkSource.m_oBoxIdentifier=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Target_BoxIdentifier)                { m_oSymbolicScenario.m_vLink.back().m_oLinkTarget.m_oBoxIdentifier=rValue; }

	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Attribute_Identifier)            { m_oSymbolicScenario.m_vAttribute.back().m_oIdentifier=rValue; }
	else OV_ERROR("(id) Unexpected node identifier " << rIdentifier.toString(), OpenViBE::Kernel::ErrorType::BadArgument, false, m_rAlgorithmContext.getErrorManager(), m_rAlgorithmContext.getLogManager());

	return true;
}

boolean CAlgorithmScenarioImporterContext::processString(const CIdentifier& rIdentifier, const CString& rValue)
{
	if(false) { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Attribute_Value)                      { m_oSymbolicScenario.m_vBox.back().m_vAttribute.back().m_sValue=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Name)                                 { m_oSymbolicScenario.m_vBox.back().m_sName=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Input_Name)                           { m_oSymbolicScenario.m_vBox.back().m_vInput.back().m_sName=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Output_Name)                          { m_oSymbolicScenario.m_vBox.back().m_vOutput.back().m_sName=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Setting_Name)                         { m_oSymbolicScenario.m_vBox.back().m_vSetting.back().m_sName=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Setting_DefaultValue)                 { m_oSymbolicScenario.m_vBox.back().m_vSetting.back().m_sDefaultValue=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Setting_Value)                        { m_oSymbolicScenario.m_vBox.back().m_vSetting.back().m_sValue=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Box_Setting_Modifiability)				  { m_oSymbolicScenario.m_vBox.back().m_vSetting.back().m_bModifiability=(rValue==CString("true"))?true:false; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Comment_Text)                             { m_oSymbolicScenario.m_vComment.back().m_sText=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Comment_Attribute_Value)                  { m_oSymbolicScenario.m_vComment.back().m_vAttribute.back().m_sValue=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Attribute_Value)                     { m_oSymbolicScenario.m_vLink.back().m_vAttribute.back().m_sValue=rValue; }

	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Attribute_Value)                 { m_oSymbolicScenario.m_vAttribute.back().m_sValue=rValue; }

	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Setting_Name)                         { m_oSymbolicScenario.m_vSetting.back().m_sName=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Setting_DefaultValue)                 { m_oSymbolicScenario.m_vSetting.back().m_sDefaultValue=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Setting_Value)                        { m_oSymbolicScenario.m_vSetting.back().m_sValue=rValue; }

	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Input_Name)                        { m_oSymbolicScenario.m_vScenarioInput.back().m_sName=rValue; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Output_Name)                       { m_oSymbolicScenario.m_vScenarioOutput.back().m_sName=rValue; }

	else OV_ERROR("(string) Unexpected node identifier " << rIdentifier.toString(), OpenViBE::Kernel::ErrorType::BadArgument, false, m_rAlgorithmContext.getErrorManager(), m_rAlgorithmContext.getLogManager());

	return true;
}

boolean CAlgorithmScenarioImporterContext::processUInteger(const CIdentifier& rIdentifier, const uint64 ui64Value)
{
	if(false) { }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Source_BoxOutputIndex)               { m_oSymbolicScenario.m_vLink.back().m_oLinkSource.m_ui32BoxOutputIndex=(uint32)ui64Value; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Link_Target_BoxInputIndex)                { m_oSymbolicScenario.m_vLink.back().m_oLinkTarget.m_ui32BoxInputIndex=(uint32)ui64Value; }

	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Input_LinkedBoxInputIndex)       { m_oSymbolicScenario.m_vScenarioInput.back().m_ui32LinkedBoxInputIndex=(uint32)ui64Value; }
	else if(rIdentifier==OVTK_Algorithm_ScenarioExporter_NodeId_Scenario_Output_LinkedBoxOutputIndex)     { m_oSymbolicScenario.m_vScenarioOutput.back().m_ui32LinkedBoxOutputIndex=(uint32)ui64Value; }

	else OV_ERROR("(uint) Unexpected node identifier " << rIdentifier.toString(), OpenViBE::Kernel::ErrorType::BadArgument, false, m_rAlgorithmContext.getErrorManager(), m_rAlgorithmContext.getLogManager());

	return true;
}

boolean CAlgorithmScenarioImporterContext::processStop(void)
{
	return true;
}
