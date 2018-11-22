/*
    DataTypeClass: EnumDescription

    Generated Source Code - please do not change this source code

    DataTypeCodeGenerator Version:
        OpcUaStackCore - 4.1.0

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardDataTypes/EnumDescription.h"

namespace OpcUaStackCore
{
    
    EnumDescription::EnumDescription(void)
    : DataTypeDescription()
    , enumDefinition_()
    , builtInType_()
    {
    }
    
    EnumDescription::~EnumDescription(void)
    {
    }
    
    EnumDefinition&
    EnumDescription::enumDefinition(void)
    {
        return enumDefinition_;
    }
    
    OpcUaByte&
    EnumDescription::builtInType(void)
    {
        return builtInType_;
    }
    
    bool
    EnumDescription::operator==(const EnumDescription& value)
    {
        EnumDescription* dst = const_cast<EnumDescription*>(&value);
        if (enumDefinition_ != dst->enumDefinition()) return false;
        if (builtInType_ != dst->builtInType()) return false;
        return true;
    }
    
    bool
    EnumDescription::operator!=(const EnumDescription& value)
    {
        return !this->operator==(value);
    }
    
    void
    EnumDescription::copyTo(EnumDescription& value)
    {
        enumDefinition_.copyTo(value.enumDefinition());
        value.builtInType_ = builtInType_;
    }
    
    EnumDescription&
    EnumDescription::operator=(const EnumDescription& value)
    {
        const_cast<EnumDescription*>(&value)->copyTo(*this);
        return *this;
    }
    
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    //
    // ExtensionObjectBase
    //
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    
    ExtensionObjectBase::SPtr
    EnumDescription::factory(void)
    {
    	return constructSPtr<EnumDescription>();
    }
    
    std::string
    EnumDescription::namespaceName(void)
    {
    	return "http://opcfoundation.org/UA/";
    }
    
    std::string
    EnumDescription::typeName(void)
    {
    	return "EnumDescription";
    }
    
    OpcUaNodeId
    EnumDescription::typeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15488,0);
    }
    
    OpcUaNodeId
    EnumDescription::binaryTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)127, 0);
    }
    
    OpcUaNodeId
    EnumDescription::xmlTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15590, 0);
    }
    
    OpcUaNodeId
    EnumDescription::jsonTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15059, 0);
    }
    
    void
    EnumDescription::opcUaBinaryEncode(std::ostream& os) const
    {
        enumDefinition_.opcUaBinaryEncode(os);
        OpcUaNumber::opcUaBinaryEncode(os,builtInType_);
    }
    
    void
    EnumDescription::opcUaBinaryDecode(std::istream& is)
    {
        enumDefinition_.opcUaBinaryDecode(is);
        OpcUaNumber::opcUaBinaryDecode(is,builtInType_);
    }
    
    bool
    EnumDescription::encode(boost::property_tree::ptree& pt, Xmlns& xmlns) const
    {
    }
    
    bool
    EnumDescription::decode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
    }
    
    bool
    EnumDescription::xmlEncode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
        if (!xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair(element, elementTree));
        return true;
    }
    
    bool
    EnumDescription::xmlEncode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
    
        elementTree.clear();
        if (!enumDefinition_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("EnumDefinition", elementTree));
    
        elementTree.clear();
        if(!XmlNumber::xmlEncode(elementTree, builtInType_)) return false;
        pt.push_back(std::make_pair("BuiltInType", elementTree));
    
        return true;
    }
    
    bool
    EnumDescription::xmlDecode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree = pt.get_child_optional(element);
        if (!tree) return false;
        return xmlDecode(*tree, xmlns);
    }
    
    bool
    EnumDescription::xmlDecode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree;
    
        tree = pt.get_child_optional("EnumDefinition");
        if (!tree) return false;
        if (!enumDefinition_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("BuiltInType");
        if (!tree) return false;
        if(!XmlNumber::xmlDecode(*tree, builtInType_)) return false;
    
        return true;
    }
    
    bool
    EnumDescription::jsonEncode(boost::property_tree::ptree& pt, const std::string& element)
    {
        return true;
    }
    
    bool
    EnumDescription::jsonEncode(boost::property_tree::ptree& pt)
    {
        return true;
    }
    
    bool
    EnumDescription::jsonDecode(boost::property_tree::ptree& pt, const std::string& element)
    {
    }
    
    bool
    EnumDescription::jsonDecode(boost::property_tree::ptree& pt)
    {
    }
    
    void
    EnumDescription::copyTo(ExtensionObjectBase& extensionObjectBase)
    {
    	EnumDescription* dst = dynamic_cast<EnumDescription*>(&extensionObjectBase);
    	copyTo(*dst);
    }
    
    bool
    EnumDescription::equal(ExtensionObjectBase& extensionObjectBase) const
    {
    	EnumDescription* dst = dynamic_cast<EnumDescription*>(&extensionObjectBase);
    	return *const_cast<EnumDescription*>(this) == *dst;
    }
    
    void
    EnumDescription::out(std::ostream& os)
    {
        os << "EnumDefinition="; enumDefinition_.out(os);
        os << ", BuiltInType=" << builtInType_;
    }

}