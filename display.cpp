#include "display.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

static void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

static void showStaticText(const std::string& text, int durationSeconds) {
    clearScreen();
    std::cout << text << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(durationSeconds));
}

static void showBlinkText(const std::string& text, int durationSeconds) {
    int elapsedMs = 0;
    int intervalMs = 500;

    while (elapsedMs < durationSeconds * 1000) {
        clearScreen();
        std::cout << text << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        elapsedMs += intervalMs;

        if (elapsedMs >= durationSeconds * 1000) {
            break;
        }

        clearScreen();
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        elapsedMs += intervalMs;
    }
}

static void showScrollText(const std::string& text, int durationSeconds) {
    const int width = 16;
    std::string padding(width, ' ');
    std::string fullText = padding + text + padding;

    int elapsedMs = 0;
    int intervalMs = 300;

    while (elapsedMs < durationSeconds * 1000) {
        for (int i = 0; i <= static_cast<int>(fullText.size()) - width; i++) {
            clearScreen();
            std::cout << fullText.substr(i, width) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
            elapsedMs += intervalMs;

            if (elapsedMs >= durationSeconds * 1000) {
                break;
            }
        }
    }
}

void showAd(const AdMessage& ad, int durationSeconds) {
    switch (ad.mode) {
        case STATIC_TEXT:
            showStaticText(ad.text, durationSeconds);
            break;

        case BLINK_TEXT:
            showBlinkText(ad.text, durationSeconds);
            break;

        case SCROLL_TEXT:
            showScrollText(ad.text, durationSeconds);
            break;

        default:
            showStaticText("Unknown mode", durationSeconds);
            break;
    }
}
