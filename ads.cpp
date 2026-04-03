#include "ads.h"
#include <vector>
#include <cstdlib>

std::vector<Customer> customers = {
    {"Harry", 5000},
    {"Farmor Anka", 3000},
    {"Svarte Petter", 1500},
    {"Langben", 4000},
    {"IOT Reklam", 1000}
};

int totalWeight = 14500;

int pickNextCustomer(int lastCustomer) {
    int selected = -1;

    do {
        int r = rand() % totalWeight;
        int sum = 0;

        for (int i = 0; i < static_cast<int>(customers.size()); i++) {
            sum += customers[i].weight;
            if (r < sum) {
                selected = i;
                break;
            }
        }
    } while (selected == lastCustomer);

    return selected;
}

AdMessage getMessageForCustomer(int customerIndex, int minutesSinceStart) {
    switch (customerIndex) {
        case 0: {
            int r = rand() % 3;
            if (r == 0) return {"Kop bil hos Harry", SCROLL_TEXT};
            if (r == 1) return {"En god bilaffar for Harry!", STATIC_TEXT};
            return {"Hederlige Harrys Bilar", BLINK_TEXT};
        }

        case 1: {
            int r = rand() % 2;
            if (r == 0) return {"Kop paj hos Farmor Anka", SCROLL_TEXT};
            return {"Skynda innan Marten atit alla pajer", STATIC_TEXT};
        }

        case 2: {
            if (minutesSinceStart % 2 == 0) {
                return {"Lat Petter bygga at dig", SCROLL_TEXT};
            } else {
                return {"Bygga svart? Ring Petter", STATIC_TEXT};
            }
        }

        case 3: {
            int r = rand() % 2;
            if (r == 0) return {"Mysterier? Ring Langben", STATIC_TEXT};
            return {"Langben fixar biffen", STATIC_TEXT};
        }

        case 4: {
            return {"Synas har? IOT:s Reklambyra", STATIC_TEXT};
        }

        default:
            return {"Error", STATIC_TEXT};
    }
}
