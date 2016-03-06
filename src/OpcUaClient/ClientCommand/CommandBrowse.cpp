
/*
   Copyright 2016 Kai Huebl (kai@huebl-sgh.de)

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

#include <boost/lexical_cast.hpp>
#include <sstream>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaClient/ClientCommand/CommandBrowse.h"

using namespace OpcUaStackCore;

namespace OpcUaClient
{

	CommandBrowse::CommandBrowse(void)
	: CommandBase(CommandBase::Cmd_Browse)
	, nodeIdVec_()
	{
	}

	CommandBrowse::~CommandBrowse(void)
	{
	}

	CommandBase::SPtr
	CommandBrowse::createCommand(void)
	{
		CommandBase::SPtr commandBase = constructSPtr<CommandBrowse>();
		return commandBase;
	}

	bool
	CommandBrowse::validateCommand(void)
	{
		if (nodeIdVec_.size() == 0) {
			OpcUaNodeId::SPtr nodeId = constructSPtr<OpcUaNodeId>();
			nodeId->set((OpcUaUInt32)84, (OpcUaUInt16)0);
			nodeIdVec_.push_back(nodeId);
		}
		return true;
	}

	bool
	CommandBrowse::addParameter(const std::string& parameterName, const std::string& parameterValue)
	{
		if (parameterName == "-NODEID") {
			OpcUaNodeId::SPtr nodeId = constructSPtr<OpcUaNodeId>();
			if (!nodeId->fromString(parameterValue)) {
				std::stringstream ss;
				ss << "node id parameter invalid (" << parameterValue << ")";
				errorMessage(ss.str());
				return false;
			}
			nodeIdVec_.push_back(nodeId);
		}
		else {
			std::stringstream ss;
			ss << "invalid parameter " << parameterName;
			errorMessage(ss.str());
			return false;
		}
		return true;
	}

	std::string
	CommandBrowse::help(void)
	{
		std::stringstream ss;
		ss << "  -Browse: Browse nodes from a opc ua server\n"
		   << "    -Session (0..1): Name of the session.\n"
		   << "    -NodeId (0..N): Start node id\n";
		return ss.str();
	}

	OpcUaNodeId::Vec&
	CommandBrowse::nodeIdVec(void)
	{
		return nodeIdVec_;
	}

}