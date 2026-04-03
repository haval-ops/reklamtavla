#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ads.h"
#include "display.h"

int main() {
    srand(time(NULL));

    int lastCustomer = -1;
    int elapsedSeconds = 0;

    while (true) {
        int minutesSinceStart = elapsedSeconds / 60;

        int customer = pickNextCustomer(lastCustomer);
        AdMessage ad = getMessageForCustomer(customer, minutesSinceStart);

        std::cout << "------------------------" << std::endl;
        std::cout << "Ny reklam vald:" << std::endl;
        std::cout << ad.text << std::endl;
        std::cout << "Visningstid: 20 sekunder" << std::endl;

        showAd(ad, 20);

        lastCustomer = customer;
        elapsedSeconds += 20;
    }

    return 0;
}
