// Arduino libraries
#include <TFT_eSPI.h>

// Local header files
#include "Buzzer.hpp"
#include "MqttClient.hpp"
#include "Screen.hpp"
#include "Settings.hpp"

bool room_full_iteration;
uint32_t room_full_iteration_time;
const uint32_t room_full_iteration_frequency = 2000;

TFT_eSPI tft;

/**
 * Initialize the screen.
 * @return void
 */
void screenInit() {
    room_full_iteration = true;
    room_full_iteration_time = 0;
    tft.begin();
    tft.setRotation(3);
    tft.setCursor(0, 0);
    startUpImg();
}

/**
 * Screen loop.
 *
 * @return void
 */
void updateScreen() {
    // Set background and draws the upper lines to separate sections
    tft.fillScreen(TFT_WHITE);
    tft.drawFastHLine(0, 50, 320, TFT_BLACK);
    tft.drawFastVLine(70, 0, 50, TFT_BLACK);
    tft.drawFastVLine(140, 0, 50, TFT_BLACK);

    // Wifi, if connected, will be green, otherwise red
    tft.setTextSize(2);
    if (getWifiConnection()) {
        tft.setTextColor(TFT_GREEN);
    } else {
        tft.setTextColor(TFT_RED);
        buzzerAlert();
    }
    tft.drawString("WiFi", (70 - tft.textWidth("WiFi")) / 2, 15);

    // MQTT, if connected, will be green, otherwise red
    if (getMqttConnection()) {
        tft.setTextColor(TFT_GREEN);
    } else {
        tft.setTextColor(TFT_RED);
        buzzerAlert();
    }
    tft.drawString("MQTT", (70 - tft.textWidth("MQTT")) / 2 + 70, 15);

    // Room capacity
    tft.setTextColor(TFT_BLACK);
    String capacityDisplay = "Capacity:" + String(getMaxPeople());
    tft.drawString(capacityDisplay, (180 - tft.textWidth(capacityDisplay)) / 2 + 140, 15);

    // For when the room is full:
    // To iterate between "ROOM IS FULL" and displaying the number of people in the room every "room_full_iteration_frequency" milliseconds
    if (getCurrentTime() - room_full_iteration_time > room_full_iteration_frequency) {
        room_full_iteration_time = getCurrentTime();
        room_full_iteration = !room_full_iteration;
    }

    // Used to only draw one of the two iterations
    bool roomTextDrawn = false;

    // Iteration 1: "ROOM IS FULL"
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(4);
    if (getPeople() >= getMaxPeople()) {
        tft.fillRect(0, 50, 320, 140, TFT_RED);
        if (room_full_iteration) {
            tft.drawString("ROOM IS FULL", (320 - tft.textWidth("ROOM IS FULL")) / 2, 100);
            roomTextDrawn = true;
        }
    }

    // Iteration 2: Number of people in the room
    // Also the regular one when the room is not full
    if (!roomTextDrawn) {
        tft.setTextSize(7);
        tft.drawString(String(getPeople()), (320 - tft.textWidth(String(getPeople()))) / 2 - 40, 100);
        tft.setTextSize(3);
        tft.drawString("People", 200, 130);
    }

    tft.setTextSize(2);
    // Draw lower lines to separate sections
    tft.drawFastHLine(0, 190, 320, TFT_BLACK);
    tft.drawFastVLine(106, 190, 50, TFT_BLACK);
    tft.drawFastVLine(212, 190, 50, TFT_BLACK);

    // Temperature, if below max, will be black, otherwise red
    if (getTemperature() < getMaxTemperature()) {
        tft.setTextColor(TFT_BLACK);
    } else {
        tft.setTextColor(TFT_RED);
        buzzerAlert();
    }
    String temperatureDisplay = "T:" + String(getTemperature()) + (String)(char(248)) + "C";
    tft.drawString(temperatureDisplay, (106 - tft.textWidth(temperatureDisplay)) / 2, 50 + 140 + 15);
    // char(248) is the closest to the degree symbol

    // Humidity, if below max, will be black, otherwise red
    if (getHumidity() < getMaxHumidity()) {
        tft.setTextColor(TFT_BLACK);
    } else {
        tft.setTextColor(TFT_RED);
        buzzerAlert();
    }
    String humidityDisplay = "H:" + String(getHumidity()) + "%";
    tft.drawString(humidityDisplay, (106 - tft.textWidth(humidityDisplay)) / 2 + 106, 50 + 140 + 15);

    // Loudness, if below max, will be black, otherwise red
    if (getLoudness() < getMaxLoudness()) {
        tft.setTextColor(TFT_BLACK);
    } else {
        tft.setTextColor(TFT_RED);
        buzzerAlert();
    }
    String loudnessDisplay = "L:" + String(getLoudness()) + "%";
    tft.drawString(loudnessDisplay, (106 - tft.textWidth(loudnessDisplay)) / 2 + 212, 50 + 140 + 15);
}

/**
 * Startup screen (without display message)
 *
 * @return void
 */
void startUpImg() {
    startUpImg("");
}

/**
 * Startup screen
 *
 * @return void
 */
void startUpImg(String displayMessage) {
    tft.fillScreen(TFT_WHITE);
    tft.fillRect(0, 50, 320, 140, TFT_PURPLE);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(5);
    tft.drawString("Locus", (320 - tft.textWidth("Locus")) / 2, 80);
    tft.drawString("Imperium", (320 - tft.textWidth("Imperium")) / 2, 120);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.drawString("By: Group 6", (320 - tft.textWidth("By: Group 6")) / 2, 200);
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLACK);
    tft.drawString(displayMessage, (320 - tft.textWidth(displayMessage)) / 2, 15);
}