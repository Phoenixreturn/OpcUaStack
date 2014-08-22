#include "OpcUaStackCore/ServiceSet/EventNotificationList.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUa EventNotificationList
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	EventNotificationList::EventNotificationList(void)
	: ObjectPool<EventNotificationList>()
	, eventFieldListArraySPtr_(EventFieldListArray::construct())
	{
	}

	EventNotificationList::~EventNotificationList(void)
	{
	}

	void 
	EventNotificationList::events(const EventFieldListArray::SPtr events)
	{
		eventFieldListArraySPtr_ = events;
	}

	
	EventFieldListArray::SPtr 
	EventNotificationList::events(void) const
	{
		return eventFieldListArraySPtr_;
	}

	ExtensibleParameterBase::BSPtr 
	EventNotificationList::factory(void)
	{
		return EventNotificationList::construct();
	}

	void 
	EventNotificationList::opcUaBinaryEncode(std::ostream& os) const
	{
		OpcUaInt32 magic;
		magic = 1490;
		OpcUaNumber::opcUaBinaryEncode(os, magic);
		eventFieldListArraySPtr_->opcUaBinaryEncode(os);
	}
	
	void 
	EventNotificationList::opcUaBinaryDecode(std::istream& is)
	{
		OpcUaInt32 magic;
		OpcUaNumber::opcUaBinaryDecode(is, magic);
		eventFieldListArraySPtr_->opcUaBinaryDecode(is);
	}
}