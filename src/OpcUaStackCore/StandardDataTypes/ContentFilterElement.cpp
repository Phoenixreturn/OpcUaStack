/*
    DataTypeClass: ContentFilterElement

    Generated Source Code - please do not change this source code

    DataTypeCodeGenerator Version:
        OpcUaStackCore - 4.1.0

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardDataTypes/ContentFilterElement.h"

namespace OpcUaStackCore
{
    
    ContentFilterElement::ContentFilterElement(void)
    : Object()
    , ExtensionObjectBase()
    , filterOperator_()
    , filterOperands_()
    {
    }
    
    ContentFilterElement::~ContentFilterElement(void)
    {
    }
    
    FilterOperator&
    ContentFilterElement::filterOperator(void)
    {
        return filterOperator_;
    }
    
    OpcUaExtensibleParameterArray&
    ContentFilterElement::filterOperands(void)
    {
        return filterOperands_;
    }
    
    bool
    ContentFilterElement::operator==(const ContentFilterElement& value)
    {
        ContentFilterElement* dst = const_cast<ContentFilterElement*>(&value);
        if (filterOperator_ != dst->filterOperator()) return false;
        if (filterOperands_ != dst->filterOperands()) return false;
        return true;
    }
    
    bool
    ContentFilterElement::operator!=(const ContentFilterElement& value)
    {
        return !this->operator==(value);
    }
    
    void
    ContentFilterElement::copyTo(ContentFilterElement& value)
    {
        filterOperator_.copyTo(value.filterOperator());
        filterOperands_.copyTo(value.filterOperands());
    }
    
    ContentFilterElement&
    ContentFilterElement::operator=(const ContentFilterElement& value)
    {
        const_cast<ContentFilterElement*>(&value)->copyTo(*this);
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
    ContentFilterElement::factory(void)
    {
    	return constructSPtr<ContentFilterElement>();
    }
    
    std::string
    ContentFilterElement::namespaceName(void)
    {
    	return "http://opcfoundation.org/UA/";
    }
    
    std::string
    ContentFilterElement::typeName(void)
    {
    	return "ContentFilterElement";
    }
    
    OpcUaNodeId
    ContentFilterElement::typeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)583,0);
    }
    
    OpcUaNodeId
    ContentFilterElement::binaryTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)585, 0);
    }
    
    OpcUaNodeId
    ContentFilterElement::xmlTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)584, 0);
    }
    
    OpcUaNodeId
    ContentFilterElement::jsonTypeId(void)
    {
    	return OpcUaNodeId((OpcUaUInt32)15204, 0);
    }
    
    void
    ContentFilterElement::opcUaBinaryEncode(std::ostream& os) const
    {
        filterOperator_.opcUaBinaryEncode(os);
        filterOperands_.opcUaBinaryEncode(os);
    }
    
    void
    ContentFilterElement::opcUaBinaryDecode(std::istream& is)
    {
        filterOperator_.opcUaBinaryDecode(is);
        filterOperands_.opcUaBinaryDecode(is);
    }
    
    bool
    ContentFilterElement::encode(boost::property_tree::ptree& pt, Xmlns& xmlns) const
    {
    }
    
    bool
    ContentFilterElement::decode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
    }
    
    bool
    ContentFilterElement::xmlEncode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
        if (!xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair(element, elementTree));
        return true;
    }
    
    bool
    ContentFilterElement::xmlEncode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::property_tree::ptree elementTree;
    
        elementTree.clear();
        if (!filterOperator_.xmlEncode(elementTree, xmlns)) return false;
        pt.push_back(std::make_pair("FilterOperator", elementTree));
    
        elementTree.clear();
        if (!filterOperands_.xmlEncode(elementTree, "ExtensibleParameter", xmlns)) return false;
        pt.push_back(std::make_pair("FilterOperands", elementTree));
    
        return true;
    }
    
    bool
    ContentFilterElement::xmlDecode(boost::property_tree::ptree& pt, const std::string& element, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree = pt.get_child_optional(element);
        if (!tree) return false;
        return xmlDecode(*tree, xmlns);
    }
    
    bool
    ContentFilterElement::xmlDecode(boost::property_tree::ptree& pt, Xmlns& xmlns)
    {
        boost::optional<boost::property_tree::ptree&> tree;
    
        tree = pt.get_child_optional("FilterOperator");
        if (!tree) return false;
        if (!filterOperator_.xmlDecode(*tree, xmlns)) return false;
    
        tree = pt.get_child_optional("FilterOperands");
        if (!tree) return false;
        if (!filterOperands_.xmlDecode(*tree, "ExtensibleParameter", xmlns)) return false;
    
        return true;
    }
    
    bool
    ContentFilterElement::jsonEncode(boost::property_tree::ptree& pt, const std::string& element)
    {
        return true;
    }
    
    bool
    ContentFilterElement::jsonEncode(boost::property_tree::ptree& pt)
    {
        return true;
    }
    
    bool
    ContentFilterElement::jsonDecode(boost::property_tree::ptree& pt, const std::string& element)
    {
    }
    
    bool
    ContentFilterElement::jsonDecode(boost::property_tree::ptree& pt)
    {
    }
    
    void
    ContentFilterElement::copyTo(ExtensionObjectBase& extensionObjectBase)
    {
    	ContentFilterElement* dst = dynamic_cast<ContentFilterElement*>(&extensionObjectBase);
    	copyTo(*dst);
    }
    
    bool
    ContentFilterElement::equal(ExtensionObjectBase& extensionObjectBase) const
    {
    	ContentFilterElement* dst = dynamic_cast<ContentFilterElement*>(&extensionObjectBase);
    	return *const_cast<ContentFilterElement*>(this) == *dst;
    }
    
    void
    ContentFilterElement::out(std::ostream& os)
    {
        os << "FilterOperator="; filterOperator_.out(os);
        os << ", FilterOperands="; filterOperands_.out(os);
    }

}