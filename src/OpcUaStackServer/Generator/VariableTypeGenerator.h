/*
   Copyright 2017 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackCore_VariableTypeGenerator_h__
#define __OpcUaStackCore_VariableTypeGenerator_h__

#include <boost/shared_ptr.hpp>
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackServer/InformationModel/InformationModel.h"

using namespace OpcUaStackCore;

namespace OpcUaStackServer
{

	class DLLEXPORT VariableTypeGenerator
	{
	  public:
		typedef boost::shared_ptr<VariableTypeGenerator> SPtr;

		VariableTypeGenerator(void);
		~VariableTypeGenerator(void);

		void informationModel(InformationModel::SPtr& informationModel);
		void variableType(OpcUaNodeId& variableTypeNodeId);
		void projectNamespace(const std::string& projectNamespace);
		void parentProjectNamespace(const std::string& parentProjectNamespace);
		std::string& sourceContent(void);
		std::string& headerContent(void);

		bool generate(void);

	  private:
		bool createVariableElementVec(const std::string& prefix, OpcUaNodeId& nodeId);

		//
		// header functions
		//
		bool generateHeader(void);

		//
		// source functions
		//
		bool generateSource(void);

		InformationModel::SPtr informationModel_;
		BaseNodeClass::SPtr variableTypeNode_;
		BaseNodeClass::SPtr parentVariableTypeNode_;
		OpcUaNodeId variableTypeNodeId_;
		OpcUaNodeId parentVariableTypeNodeId_;
		uint32_t variableTypeNumber_;
		std::string variableTypeName_;
		std::string parentVariableTypeName_;
		std::string sourceContent_;
		std::string headerContent_;

		std::string namespaceUri_;
		std::string projectNamespace_;
		std::string parentProjectNamespace_;
		std::string projectDirectory_;
		std::string parentProjectDirectory_;

	};


}

#endif
