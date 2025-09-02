#include "EventManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

EventManager::EventManager(const std::string& filename) {
    loadFromFile(filename);
}

void EventManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    size_t lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;

        if (line.size() < 11) {
            throw std::runtime_error(
                "Invalid line (too short) at line " + std::to_string(lineNumber) +
                ": " + line
            );
        }

        std::string dateStr = line.substr(0, 10); // "DD.MM.YYYY"
        std::string description = line.substr(11); // текст после даты и пробела

        std::chrono::sys_days date = parseDate(dateStr);
        events_.push_back(Event(date, description));
    }
}


std::chrono::sys_days EventManager::parseDate(const std::string& dateStr) {
    int d, m, y;
    char dot1, dot2;
    std::istringstream ss(dateStr);
    ss >> d >> dot1 >> m >> dot2 >> y;
    if (!ss || dot1 != '.' || dot2 != '.') {
        throw std::runtime_error("Invalid date format: " + dateStr);
    }

    std::chrono::year_month_day ymd{std::chrono::year(y)/std::chrono::month(m)/std::chrono::day(d)};
    if (!ymd.ok()) {
        throw std::runtime_error("Invalid date: " + dateStr);
    }
    return std::chrono::sys_days{ymd};
}

std::vector<Event> EventManager::getUpcomingEvents(std::chrono::sys_days date, size_t count) {
    std::vector<Event> upcomingEvents;
    for (const Event& e : events_) {
        if (e.getDate() >= date) {
            upcomingEvents.push_back(e);
        }
    }
    std::sort(upcomingEvents.begin(), upcomingEvents.end());
    if (upcomingEvents.size() > count) {
        upcomingEvents.erase(upcomingEvents.begin() + count, upcomingEvents.end());
    }

    return upcomingEvents;
}

// МОЙ КОД - поиск событий по ключевому слову
std::vector<Event> EventManager::searchEvents(const std::string& keyword) {
    std::vector<Event> results;
    
    // Проходим по всем событиям в списке
    for (const Event& e : events_) {
        // Проверяем, содержит ли описание события искомое слово
        if (e.getDescription().find(keyword) != std::string::npos) {
            // Если содержит - добавляем в результаты
            results.push_back(e);
        }
    }
    
    return results;
}

// МОЙ КОД - подсчет общего количества событий
size_t EventManager::getTotalEventsCount() const {
    // Просто возвращаем размер вектора events_
    return events_.size();
}
