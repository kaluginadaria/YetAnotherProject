#include "EventCollector.hpp"



void EventCollector::CollectKeyEvent(KeyEvent newEvent)
{
	for (auto& event : events)
	{
		if (event == newEvent)
		{
			return;
		}
	}
	events.emplace_back(newEvent);
}

void EventCollector::CollectMousPosition(float x, float y)
{
	mouse_X = x;
	mouse_Y = y;
}

const std::vector<KeyEvent>& EventCollector::GetEvents() const
{
	return events;
}

float EventCollector::GetMouseX() const
{
	return mouse_X;
}

float EventCollector::GetMouseY() const
{
	return mouse_Y;
}

void EventCollector::Flush()
{
	events.resize(0);
	mouse_X = 0;
	mouse_Y = 0;
}

