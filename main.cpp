#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ads.h"
#include "display.h"

int main() {
    // Initiera slump
    srand(time(NULL));

    int lastCustomer = -1;
    int elapsedSeconds = 0;

    while (true) {
        // Räkna minuter sedan start
        int minutesSinceStart = elapsedSeconds / 60;

        // Välj nästa kund (inte samma som förra)
        int customer = pickNextCustomer(lastCustomer);

        // Hämta rätt reklam
        AdMessage ad = getMessageForCustomer(customer, minutesSinceStart);

        // Hämta kundnamn
        std::string customerName = getCustomerName(customer);

        // Visa reklamen (20 sekunder)
        showAd(ad, customerName, 20);

        // Uppdatera senaste kund
        lastCustomer = customer;

        // Uppdatera tid
        elapsedSeconds += 20;
    }

    return 0;
}
