#include <iostream>
#include <unistd.h> // sleep
#include <ctime>
#include "ads.h"

int main() {
    srand(time(NULL));

    int lastCustomer = -1;
    int elapsedSeconds = 0;

    while (true) {

        int minutesSinceStart = elapsedSeconds / 60;

        int customer = pickNextCustomer(lastCustomer);

        AdMessage ad = getMessageForCustomer(customer, minutesSinceStart);

        std::cout << "------------------------" << std::endl;
        std::cout << "Visar reklam: " << std::endl;
        std::cout << ad.text << std::endl;
        std::cout << "Mode: " << ad.mode << std::endl;

        lastCustomer = customer;

        sleep(20); // 20 sekunder
        elapsedSeconds += 20;
    }

    return 0;
}
