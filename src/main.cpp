#include "EventManager.h"
#include <iostream>
#include <chrono>
#include <format>

int main() {
    try {
        EventManager manager("../data/events.txt");

        auto today = std::chrono::floor<std::chrono::days>(
            std::chrono::system_clock::now()
        );

        auto upcoming = manager.getUpcomingEvents(today);

        if (upcoming.empty()) {
            std::cout << "No upcoming events." << std::endl;
        } else {
            for (const auto& e : upcoming) {
                auto ymd = std::chrono::year_month_day(e.getDate());
                std::cout 
                    << std::format("{:02}.{:02}.{:04} ", 
                                   unsigned(ymd.day()), 
                                   unsigned(ymd.month()), 
                                   int(ymd.year()))
                    << e.getDescription() << "\n";
            }
        }

        // МОЙ КОД - демонстрация подсчета общего количества событий
        std::cout << "\nОбщее количество событий: " << manager.getTotalEventsCount() << std::endl;

        // МОЙ КОД - демонстрация поиска событий
        std::cout << "\nПоиск событий с 'meeting':" << std::endl;
        auto searchResults = manager.searchEvents("meeting");
        if (searchResults.empty()) {
            std::cout << "События с 'meeting' не найдены." << std::endl;
        } else {
            for (const auto& e : searchResults) {
                auto ymd = std::chrono::year_month_day(e.getDate());
                std::cout 
                    << std::format("{:02}.{:02}.{:04} ", 
                                   unsigned(ymd.day()), 
                                   unsigned(ymd.month()), 
                                   int(ymd.year()))
                    << e.getDescription() << "\n";
            }
        }

        // МОЙ КОД - демонстрация поиска событий с 'party'
        std::cout << "\nПоиск событий с 'party':" << std::endl;
        auto partyResults = manager.searchEvents("party");
        if (partyResults.empty()) {
            std::cout << "События с 'party' не найдены." << std::endl;
        } else {
            for (const auto& e : partyResults) {
                auto ymd = std::chrono::year_month_day(e.getDate());
                std::cout 
                    << std::format("{:02}.{:02}.{:04} ", 
                                   unsigned(ymd.day()), 
                                   unsigned(ymd.month()), 
                                   int(ymd.year()))
                    << e.getDescription() << "\n";
            }
        }

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}
