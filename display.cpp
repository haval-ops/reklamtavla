#include "display.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

static void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

static std::string modeToString(DisplayMode mode) {
    switch (mode) {
        case STATIC_TEXT: return "STATIC";
        case SCROLL_TEXT: return "SCROLL";
        case BLINK_TEXT:  return "BLINK";
        default: return "UNKNOWN";
    }
}

static void printFrame(const std::string& customer, const std::string& text, DisplayMode mode) {
    std::cout << "==============================\n";
    std::cout << " KUND: " << customer << "\n";
    std::cout << " MODE: " << modeToString(mode) << "\n";
    std::cout << "------------------------------\n";
    std::cout << " " << text << "\n";
    std::cout << "==============================\n";
}

static void showStaticText(const std::string& customer, const AdMessage& ad, int durationSeconds) {
    clearScreen();
    printFrame(customer, ad.text, ad.mode);
    std::this_thread::sleep_for(std::chrono::seconds(durationSeconds));
}

static void showBlinkText(const std::string& customer, const AdMessage& ad, int durationSeconds) {
    int elapsedMs = 0;
    int intervalMs = 500;

    while (elapsedMs < durationSeconds * 1000) {
        clearScreen();
        printFrame(customer, ad.text, ad.mode);
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        elapsedMs += intervalMs;

        if (elapsedMs >= durationSeconds * 1000) break;

        clearScreen();
        printFrame(customer, " ", ad.mode);
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        elapsedMs += intervalMs;
    }
}

static void showScrollText(const std::string& customer, const AdMessage& ad, int durationSeconds) {
    const int width = 16;
    std::string padding(width, ' ');
    std::string fullText = padding + ad.text + padding;

    int elapsedMs = 0;
    int intervalMs = 300;

    while (elapsedMs < durationSeconds * 1000) {
        for (int i = 0; i <= static_cast<int>(fullText.size()) - width; i++) {
            clearScreen();

            std::string visible = fullText.substr(i, width);
            printFrame(customer, visible, ad.mode);

            std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
            elapsedMs += intervalMs;

            if (elapsedMs >= durationSeconds * 1000) break;
        }
    }
}

void showAd(const AdMessage& ad, const std::string& customerName, int durationSeconds) {
    switch (ad.mode) {
        case STATIC_TEXT:
            showStaticText(customerName, ad, durationSeconds);
            break;

        case BLINK_TEXT:
            showBlinkText(customerName, ad, durationSeconds);
            break;

        case SCROLL_TEXT:
            showScrollText(customerName, ad, durationSeconds);
            break;

        default:
            showStaticText(customerName, ad, durationSeconds);
            break;
    }
}
