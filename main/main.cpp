#include <cstdlib>
#include <ctime>
#include <string>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ads.h"
#include "lcd.h"

extern "C" void app_main() {
    srand(time(nullptr));

    lcdInit();

    int lastCustomer = -1;
    int elapsedSeconds = 0;

    while (true) {
        int minutesSinceStart = elapsedSeconds / 60;

        int customer = pickNextCustomer(lastCustomer);
        AdMessage ad = getMessageForCustomer(customer, minutesSinceStart);
        std::string customerName = getCustomerName(customer);

        showAdOnLcd(ad, customerName, 20);

        lastCustomer = customer;
        elapsedSeconds += 20;
    }
}
