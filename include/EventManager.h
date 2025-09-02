#pragma once

#include "Event.h"
#include <vector>
#include <string>

class EventManager {
public:
    EventManager(const std::string& filename);

        std::vector<Event> getUpcomingEvents(std::chrono::sys_days date, size_t count = 7);
    
    // МОЙ КОД - поиск событий по ключевому слову
    std::vector<Event> searchEvents(const std::string& keyword);
    
    // МОЙ КОД - подсчет общего количества событий
    size_t getTotalEventsCount() const;


private:
    std::vector<Event> events_;
    void loadFromFile(const std::string& filename);
    std::chrono::sys_days parseDate(const std::string& dateStr);
};
