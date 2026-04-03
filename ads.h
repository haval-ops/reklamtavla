#ifndef ADS_H
#define ADS_H

#include <string>

enum DisplayMode {
    STATIC_TEXT,
    SCROLL_TEXT,
    BLINK_TEXT
};

struct AdMessage {
    std::string text;
    DisplayMode mode;
};

struct Customer {
    std::string name;
    int weight;
};

// Funktioner
int pickNextCustomer(int lastCustomer);
AdMessage getMessageForCustomer(int customerIndex, int minutesSinceStart);

#endif
