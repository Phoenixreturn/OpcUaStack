#include <boost/lexical_cast.hpp>
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeIdBase.h"
#include <sstream>

namespace OpcUaStackCore
{

	class OpcUaTypeVisitor : public boost::static_visitor<>
	{
	  public:
		void operator()(OpcUaNodeIdNullType) { opcUaBuildInType_ = OpcUaBuildInType_Unknown; }
		void operator()(OpcUaUInt32) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaUInt32; }
		void operator()(OpcUaString::SPtr) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaString; }
		void operator()(OpcUaGuid::SPtr) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaGuid; }
		void operator()(OpcUaByteString::SPtr) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaByteString; }

		OpcUaBuildInType opcUaBuildInType_;
	};


	OpcUaNodeIdBase::OpcUaNodeIdBase(void)
	: namespaceIndex_(0)
	, nodeIdValue_()
	{
	}

	OpcUaNodeIdBase::~OpcUaNodeIdBase(void)
	{
	}

	OpcUaNodeIdValue 
	OpcUaNodeIdBase::nodeIdValue(void)
	{
		return nodeIdValue_;
	}
	
	void 
	OpcUaNodeIdBase::nodeIdValue(OpcUaNodeIdValue& nodeIdValue)
	{
		nodeIdValue_ = nodeIdValue;
	}

	void 
	OpcUaNodeIdBase::namespaceIndex(OpcUaUInt16 namespaceIndex)
	{
		namespaceIndex_ = namespaceIndex;
	}

	OpcUaInt16 
	OpcUaNodeIdBase::namespaceIndex(void) const
	{
		return namespaceIndex_;
	}

	OpcUaBuildInType 
	OpcUaNodeIdBase::nodeIdType(void) const
	{
		OpcUaTypeVisitor opcUaTypeVisitor;
		boost::apply_visitor(opcUaTypeVisitor, nodeIdValue_);
		return opcUaTypeVisitor.opcUaBuildInType_;
	}

	void 
	OpcUaNodeIdBase::set(OpcUaUInt32 nodeId, OpcUaUInt16 namespaceIndex)
	{
		namespaceIndex_ = namespaceIndex;
		nodeIdValue_ = nodeId;
	}

	void 
	OpcUaNodeIdBase::set(const std::string& nodeId, OpcUaUInt16 namespaceIndex)
	{
		if (nodeId.length() == 36 && nodeId.substr(8,1) == "-" && nodeId.substr(13,1) == "-" && nodeId.substr(18,1) == "-" && nodeId.substr(23,1) == "-") {
			OpcUaGuid::SPtr opcUaGuidSPtr = OpcUaGuid::construct();
			*opcUaGuidSPtr = nodeId;
			nodeIdValue_ = opcUaGuidSPtr;
		}
		else {
			OpcUaString::SPtr opcUaStringSPtr = OpcUaString::construct();
			*opcUaStringSPtr = nodeId;
			nodeIdValue_ = opcUaStringSPtr;
		}
		namespaceIndex_ = namespaceIndex;
	}

	void 
	OpcUaNodeIdBase::set(OpcUaByte* buf, OpcUaInt32 bufLen, OpcUaUInt16 namespaceIndex)
	{
		OpcUaByteString::SPtr opcUaByteStringSPtr = OpcUaByteString::construct();
		opcUaByteStringSPtr->value(buf, bufLen);
		namespaceIndex_ = namespaceIndex;
		nodeIdValue_ = opcUaByteStringSPtr;
	}

	bool 
	OpcUaNodeIdBase::get(OpcUaUInt32& nodeId, OpcUaUInt16& namespaceIndex)
	{
		if (nodeIdType() != OpcUaBuildInType_OpcUaUInt32) {
			return false;
		}

		namespaceIndex = namespaceIndex_;
		nodeId = boost::get<OpcUaUInt32>(nodeIdValue_);
		return true;
	}

	bool 
	OpcUaNodeIdBase::get(std::string& nodeId, OpcUaUInt16& namespaceIndex)
	{
		namespaceIndex = namespaceIndex_;
		if (nodeIdType() == OpcUaBuildInType_OpcUaString) {
			OpcUaString::SPtr opcUaStringSPtr;
			opcUaStringSPtr = boost::get<OpcUaString::SPtr>(nodeIdValue_);
			nodeId = opcUaStringSPtr->value();
		}
		else if (nodeIdType() == OpcUaBuildInType_OpcUaGuid) {
			OpcUaGuid::SPtr opcUaGuidSPtr;
			opcUaGuidSPtr = boost::get<OpcUaGuid::SPtr>(nodeIdValue_); 
			nodeId = *opcUaGuidSPtr;
		}
		else {
			return false;
		}
		return true;
	}

	bool 
	OpcUaNodeIdBase::get(OpcUaByte** buf, OpcUaInt32* bufLen, OpcUaUInt16& namespaceIndex)
	{
		if (nodeIdType() != OpcUaBuildInType_OpcUaByteString) {
			return false;
		}

		namespaceIndex = namespaceIndex_;
		OpcUaByteString::SPtr opcUaByteStringSPtr;
		opcUaByteStringSPtr = boost::get<OpcUaByteString::SPtr>(nodeIdValue_);
		opcUaByteStringSPtr->value(buf, bufLen);
		return true;
	}

	void 
	OpcUaNodeIdBase::copyTo(OpcUaNodeIdBase& opcUaNodeIdBase)
	{
		opcUaNodeIdBase.namespaceIndex(namespaceIndex_);

		OpcUaBuildInType type =  nodeIdType();
		switch(type)
		{
			case OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt32 value = boost::get<OpcUaUInt32>(nodeIdValue_);
				opcUaNodeIdBase.nodeId(value);
				break;
			}
			case OpcUaBuildInType_OpcUaString:
			{
				OpcUaString::SPtr value = boost::get<OpcUaString::SPtr>(nodeIdValue_);
				OpcUaString::SPtr newValue = OpcUaString::construct();
				value->copyTo(*newValue);
				opcUaNodeIdBase.nodeId(newValue);
				break;
			}
			case OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaGuid::SPtr value = boost::get<OpcUaGuid::SPtr>(nodeIdValue_);
				OpcUaGuid::SPtr newValue = OpcUaGuid::construct();
				value->copyTo(*newValue);
				opcUaNodeIdBase.nodeId(newValue);
				break;
			}
			case OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaByteString::SPtr value = boost::get<OpcUaByteString::SPtr>(nodeIdValue_);
				OpcUaByteString::SPtr newValue = OpcUaByteString::construct();
				value->copyTo(*newValue);
				opcUaNodeIdBase.nodeId(newValue);
				break;
			}
		}
	}

	bool 
	OpcUaNodeIdBase::operator!=(const OpcUaNodeIdBase& opcUaNodeId) const
	{
		return !operator==(opcUaNodeId);
	}

	bool 
	OpcUaNodeIdBase::operator==(const OpcUaNodeIdBase& opcUaNodeIdBase) const
	{
		return ((opcUaNodeIdBase < *this) == false) &&  ((*this < opcUaNodeIdBase) == false);
	}

	bool 
	OpcUaNodeIdBase::operator<(const OpcUaNodeIdBase& opcUaNodeIdBase) const
	{
		if (namespaceIndex() < opcUaNodeIdBase.namespaceIndex()) {
			return true;
		}

		if (opcUaNodeIdBase.namespaceIndex() < namespaceIndex()) {
			return false;
		}

		if (nodeIdType() < opcUaNodeIdBase.nodeIdType()) {
			return true;
		}

		if (opcUaNodeIdBase.nodeIdType() < nodeIdType()) {
			return false;
		}

		switch(nodeIdType())
		{
			case OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt32 value1 = boost::get<OpcUaUInt32>(nodeIdValue_);
				OpcUaUInt32 value2 = opcUaNodeIdBase.nodeId<OpcUaUInt32>();
				return value1 < value2;
				break;
			}
			case OpcUaBuildInType_OpcUaString:
			{
				OpcUaString::SPtr value1 = boost::get<OpcUaString::SPtr>(nodeIdValue_);
				OpcUaString::SPtr value2 = opcUaNodeIdBase.nodeId<OpcUaString::SPtr>();

				if (value1.get() == NULL && value2.get() == NULL) return false;
				if (value1.get() != NULL && value2.get() == NULL) return false;
				if (value1.get() == NULL && value2.get() != NULL) return true;
				return *value1 < *value2;
				break;
			}
			case OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaGuid::SPtr value1 = boost::get<OpcUaGuid::SPtr>(nodeIdValue_);
				OpcUaGuid::SPtr value2 = opcUaNodeIdBase.nodeId<OpcUaGuid::SPtr>();

				if (value1.get() == NULL && value2.get() == NULL) return false;
				if (value1.get() != NULL && value2.get() == NULL) return false;
				if (value1.get() == NULL && value2.get() != NULL) return true;
				return *value1 < *value2;
				break;
			}
			case OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaByteString::SPtr value1 = boost::get<OpcUaByteString::SPtr>(nodeIdValue_);
				OpcUaByteString::SPtr value2 = opcUaNodeIdBase.nodeId<OpcUaByteString::SPtr>();

				if (value1.get() == NULL && value2.get() == NULL) return false;
				if (value1.get() != NULL && value2.get() == NULL) return false;
				if (value1.get() == NULL && value2.get() != NULL) return true;
				return *value1 < *value2;
				break;
			}
		}

		return false;
	}

	OpcUaByte 
	OpcUaNodeIdBase::encodingFlag(void) const
	{
		return 0x00;
	}
		
	void 
	OpcUaNodeIdBase::encodingFlag(OpcUaByte expandedEncodingFlag)
	{
	}

	void 
	OpcUaNodeIdBase::opcUaBinaryEncode(std::ostream& os) const
	{
		OpcUaBuildInType type =  nodeIdType();
		OpcUaByte ef = encodingFlag();

		if (type == OpcUaBuildInType_Unknown) {
			OpcUaUInt32 nodeId = 0;
			OpcUaUInt16 namespaceIndex = 0;
			const_cast<OpcUaNodeIdBase*>(this)->set(nodeId, namespaceIndex);
			type =  nodeIdType();
		}

		if (namespaceIndex_ == 0 && type == OpcUaBuildInType_OpcUaUInt32) {
			OpcUaUInt32 identifier = boost::get<OpcUaUInt32>(nodeIdValue_);
			if (identifier <= 0xFF) {
				OpcUaByte encodingMask = 0x00+ef;
				OpcUaNumber::opcUaBinaryEncode(os, encodingMask);
				OpcUaNumber::opcUaBinaryEncode(os, (OpcUaStackCore::OpcUaByte)identifier);
				return;
			}
		}

		if (namespaceIndex_ <= 0xFF && type == OpcUaBuildInType_OpcUaUInt32) {
			OpcUaUInt32 identifier = boost::get<OpcUaUInt32>(nodeIdValue_);
			if (identifier <= 0xFFFF) {
				OpcUaByte encodingMask = 0x01+ef;
				OpcUaNumber::opcUaBinaryEncode(os, encodingMask);
				OpcUaNumber::opcUaBinaryEncode(os, (OpcUaStackCore::OpcUaByte)namespaceIndex_);
				OpcUaNumber::opcUaBinaryEncode(os, (OpcUaStackCore::OpcUaUInt16)identifier);
				return;
			}
		}

		switch(type)
		{
			case OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaByte encodingMask = 0x02+ef;
				OpcUaNumber::opcUaBinaryEncode(os, encodingMask);
				OpcUaNumber::opcUaBinaryEncode(os, namespaceIndex_);
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaUInt32>(nodeIdValue_));
				break;
			}
			case OpcUaBuildInType_OpcUaString:
			{
				OpcUaByte encodingMask = 0x03+ef;
				OpcUaNumber::opcUaBinaryEncode(os, encodingMask);
				OpcUaNumber::opcUaBinaryEncode(os, namespaceIndex_);
				boost::get<OpcUaString::SPtr>(nodeIdValue_)->opcUaBinaryEncode(os);
				break;
			}
			case OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaByte encodingMask = 0x04+ef;
				OpcUaNumber::opcUaBinaryEncode(os, encodingMask);
				OpcUaNumber::opcUaBinaryEncode(os, namespaceIndex_);
				boost::get<OpcUaGuid::SPtr>(nodeIdValue_)->opcUaBinaryEncode(os);
				break;
			}
			case OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaByte encodingMask = 0x05+ef;
				OpcUaNumber::opcUaBinaryEncode(os, encodingMask);
				OpcUaNumber::opcUaBinaryEncode(os, namespaceIndex_);
				boost::get<OpcUaByteString::SPtr>(nodeIdValue_)->opcUaBinaryEncode(os);
				break;
			}
		}
	}

	void 
	OpcUaNodeIdBase::opcUaBinaryDecode(std::istream& is)
	{
		OpcUaByte encodingByte;
		OpcUaNumber::opcUaBinaryDecode(is, encodingByte);

		OpcUaByte ef = encodingByte & 0xF0;
		encodingFlag(ef);
		encodingByte &= 0x0F;

		switch (encodingByte)
		{
			case 0x00:
			{
				OpcUaByte identifier;
				namespaceIndex_ = 0;
				OpcUaNumber::opcUaBinaryDecode(is, identifier);
				nodeIdValue_ = (OpcUaInt32)identifier;
				break;
			}
			case 0x01:
			{
				OpcUaByte namespaceIndex;
				OpcUaUInt16 identifier;
				OpcUaNumber::opcUaBinaryDecode(is, namespaceIndex);
				OpcUaNumber::opcUaBinaryDecode(is, identifier);
				namespaceIndex_ = namespaceIndex;
				nodeIdValue_ = (OpcUaInt32)identifier;
				break;
			}
			case 0x02:
			{
				OpcUaInt32 value;
				OpcUaNumber::opcUaBinaryDecode(is, namespaceIndex_);
				OpcUaNumber::opcUaBinaryDecode(is, value);
				nodeIdValue_ = value;
				break;
			}
			case 0x03:
			{
				OpcUaString::SPtr value = OpcUaString::construct();
				OpcUaNumber::opcUaBinaryDecode(is, namespaceIndex_);
				value->opcUaBinaryDecode(is);
				nodeIdValue_ = value;
				break;
			}
			case 0x04:
			{
				OpcUaGuid::SPtr value = OpcUaGuid::construct();
				OpcUaNumber::opcUaBinaryDecode(is, namespaceIndex_);
				value->opcUaBinaryDecode(is);
				nodeIdValue_ = value;
				break;
			}
			case 0x05:
			{
				OpcUaByteString::SPtr value = OpcUaByteString::construct();
				OpcUaNumber::opcUaBinaryDecode(is, namespaceIndex_);
				value->opcUaBinaryDecode(is);
				nodeIdValue_ = value;
				break;
			}
		}
	}

	bool 
	OpcUaNodeIdBase::fromString(const std::string& nodeIdString)
	{
		size_t pos;
		size_t posBegin;
		size_t posEnd;

		//
		// find token "ns=" (optional)
		//
		namespaceIndex_ = 0;
		pos = nodeIdString.find("ns=");
		if (pos == std::string::npos) {
			posBegin = 0;
			posEnd = 0;
		}
		else {
			posBegin = 3;
			posEnd = nodeIdString.find_first_of(',', posBegin);
			if (posEnd == std::string::npos) return false;

			try {
				namespaceIndex_ = boost::lexical_cast<uint16_t>(nodeIdString.substr(posBegin, posEnd-posBegin));
			} catch (boost::bad_lexical_cast&)
			{
				return false;
			}
			posBegin = posEnd+1;
		}

		//
		// find token "i=" (optional)
		//
		pos = nodeIdString.find("i=", posBegin);
		if (pos != std::string::npos) {
			posBegin = pos+2;
			posEnd = nodeIdString.length();

			try {
				uint32_t value = boost::lexical_cast<uint32_t>(nodeIdString.substr(posBegin, posEnd-posBegin));
				nodeId(value);
			} catch (boost::bad_lexical_cast&)
			{
				return false;
			}

			return true;
		}

		//
		// find token "s=" (optional)
		//
		pos = nodeIdString.find("s=", posBegin);
		if (pos != std::string::npos) {
			posBegin = pos+2;
			posEnd = nodeIdString.length();

			try {
				OpcUaString::SPtr value = OpcUaString::construct();
				*value = nodeIdString.substr(posBegin, posEnd-posBegin); 
				nodeId(value);
			} catch (boost::bad_lexical_cast&)
			{
				return false;
			}

			return true;
		}

		return false;
	}

	std::string 
	OpcUaNodeIdBase::toString(void) const
	{
		std::stringstream nodeIdStream;
		nodeIdStream << "ns=" << namespaceIndex_ << ","; 

		switch(nodeIdType())
		{
			case OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt32 value = boost::get<OpcUaUInt32>(nodeIdValue_);
				nodeIdStream << "i=" << value;
				break;
			}
			case OpcUaBuildInType_OpcUaString:
			{
				OpcUaString::SPtr value = boost::get<OpcUaString::SPtr>(nodeIdValue_);
				if (value.get() != nullptr) {
					std::string str = *value;
					nodeIdStream << "s=" << str;
				}
				break;
			}
			case OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaGuid::SPtr value = boost::get<OpcUaGuid::SPtr>(nodeIdValue_);
				if (value.get() != nullptr) {
					std::string str = *value;
					nodeIdStream << "g=" << str;
				}
				break;
			}
			case OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaByteString::SPtr value = boost::get<OpcUaByteString::SPtr>(nodeIdValue_);
				if (value.get() != nullptr) {
					std::string str = value->toHexString();
					nodeIdStream << "h=" << str;
				}
				break;
			}
		}
		return nodeIdStream.str();
	}

}
