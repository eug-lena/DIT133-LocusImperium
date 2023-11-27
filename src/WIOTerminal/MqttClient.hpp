#ifndef MQTTCLIENT_HPP
#define MQTTCLIENT_HPP

// Libraries
#include <PubSubClient.h>
#include <rpcWiFi.h>

// Local header files
#include "Screen.hpp"
#include "Buzzer.hpp"
#include "Util.hpp"
#include "WifiDetails.h"
#include "Settings.hpp"

void mqttInit();

void setupWifi();

void setupMqtt();

void mqttLoop();

void playConnectionLostAlert();

void callback(char* topic, byte* payload, unsigned int length);

void reconnect();

void publishMessage(const char* topic, const char* message);

void publishMessage(const char* topic, String message);

bool getWifiConnection();

bool getMqttConnection();

#endif