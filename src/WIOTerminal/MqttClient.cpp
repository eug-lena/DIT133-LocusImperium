/****************************************************************************
  Code based on "MQTT Example for SeeedStudio Wio Terminal".
  Author: Salman Faris
  Source: https://www.hackster.io/Salmanfarisvp/mqtt-on-wio-terminal-4ea8f8
*****************************************************************************/

// Libraries
#include <PubSubClient.h>
#include <rpcWiFi.h>

// Local header files
#include "Buzzer.hpp"
#include "MqttClient.hpp"
#include "Screen.hpp"
#include "Settings.hpp"
#include "Util.hpp"
#include "WifiDetails.h"

// Wi-Fi details
const char *ssid = SSID;          // WiFi Name
const char *password = PASSWORD;  // WiFi Password

// MQTT details
const char *BROKER_ADDRESS = brokerAddress;                  // Broker URL
const char *SUBSCRIPTION_TOPIC_ALL = "LocusImperium/APP/#";  // Topic to subscribe to
const String CLIENT_ID = "WioTerminal";                      // Client ID used on broker

// MQTT subscription topics
const char *MAX_SETTINGS_PUBLISH_TOPIC = "LocusImperium/APP/maxSettings";
const char *ADJUST_PEOPLE_COUNTER_TOPIC = "LocusImperium/APP/AdjustPeopleCounter";

// MQTT publish topics
const char *ROOM_DATA_PUBLISH_TOPIC = "LocusImperium/WIO/roomData";

// For alert
bool haveAlerted;

// State of connection, used to draw it on the screen.
bool wifiConnection;
bool mqttConnection;

WiFiClient wioClient;
PubSubClient client(wioClient);

/**
 * Initializes mqtt connection. Calls setup_wifi().
 *
 * @return void
 */
void mqttInit() {
    Serial.begin(115200);
    startUpImg("Connecting to WiFi...");
    setupWifi();
    client.setServer(BROKER_ADDRESS, 1883);  // Connect the MQTT Server
    client.setCallback(callback);
    startUpImg("Connecting to broker...");
    setupMqtt();
    haveAlerted = false;
    wifiConnection = true;
    mqttConnection = true;
}

/**
 * Sets up the wifi connection to the network entered in the WifiDetails.h file.
 * Will loop until it is successful.
 *
 * @return void
 */
void setupWifi() {
    WiFi.begin(ssid, password);  // Connecting WiFi

    while (WiFi.status() != WL_CONNECTED) {
        // To not attempt to often.
        delay(1000);
    }
    delay(100);
}

/**
 * Sets up the mqtt connection to the broker specified in the WifiDetails.h file.
 * Will loop until it is successful.
 *
 * @return void
 */
void setupMqtt() {
    while (!client.connected()) {
        // Attempt to connect
        if (client.connect(CLIENT_ID.c_str())) {
            client.subscribe(SUBSCRIPTION_TOPIC_ALL);
        }
        // To not attempt to often.
        delay(1000);
    }
}

/**
 * Check if client is still connected to the broker, if not, calls reconnect().
 * Otherwise, proceeds to run the mqtt client loop and publishes room data.
 *
 * @return void
 */
void mqttLoop() {
    if (!client.connected()) {
        // Reconnect if not connected.
        reconnect();
    } else {
        // Connection works.
        wifiConnection = true;
        mqttConnection = true;

        // Too play alert if it loses connection.
        haveAlerted = false;

        // Mqtt loop for the library.
        client.loop();

        // Publish room data.
        publishMessage(ROOM_DATA_PUBLISH_TOPIC, String(getPeople()) + ',' + String(getHumidity()) + ',' + String(getTemperature()) + ',' + String(getLoudness()));
    }
}

/**
 * Whenever a mqtt message is published to the broker that the client is subscribed to, callback() is called automatically.
 * When called, will check the topic of the message and set the corresponding value dependent on the topic.
 *
 * @param topic the mqtt topic of the message received.
 * @param payload the payload of the message received.
 * @param length the length of the message.
 * @return void
 */
void callback(char *topic, byte *payload, unsigned int length) {
    // Convert message from byte to char
    char buff_p[length];
    for (int i = 0; i < length; i++) {
        buff_p[i] = (char)payload[i];
    }
    buff_p[length] = '\0';  // Message as char

    // Convert message from char to String
    String msg_p = String(buff_p);  // Message as String

    if (strcmp(topic, ADJUST_PEOPLE_COUNTER_TOPIC) == 0) {
        if (getPeople() + msg_p.toInt() >= 0) {
            setPeople(getPeople() + msg_p.toInt());
        }
    }

    if (strcmp(topic, MAX_SETTINGS_PUBLISH_TOPIC) == 0) {
        String topicArray[4];
        int topicSize = sizeof(topicArray) / sizeof(String);  // Size of array

        for (int i = 0; i < topicSize; i++) {
            if (msg_p.indexOf(",")) {
                topicArray[i] = msg_p.substring(0, msg_p.indexOf(","));
                msg_p = msg_p.substring(msg_p.indexOf(",") + 1);
            } else {
                topicArray[i] = msg_p;
            }
        }
        // The position of the different settings values are predefined in the array.
        setMaxPeople(topicArray[0].toInt());
        setMaxHumidity(topicArray[1].toInt());
        setMaxTemperature(topicArray[2].toInt());

        if (topicArray[3].equals("Quiet")) {
            setMaxLoudness(50);
        } else if (topicArray[3].equals("Moderate")) {
            setMaxLoudness(60);
        } else if (topicArray[3].equals("Loud")) {
            setMaxLoudness(70);
        }
    }
}
/**
 * Attemps to:
 * First reconnect to the Wi-Fi if not connected.
 * Secondly reconnect to the broker if not connected.
 *
 * @return void
 */
void reconnect() {
    // If reconnect() gets called, mqtt connection have already been lost.
    mqttConnection = false;

    // Play alert if not already played
    if (!haveAlerted) {
        playConnectionLostAlert();
    }

    // If WiFi is not connected, reconnect to it.
    if (WiFi.status() != WL_CONNECTED) {
        wifiConnection = false;
        WiFi.reconnect();
    } else if (!client.connected()) {
        // Attempt to connect to the broker, will loop forever due to how the library works.
        if (client.connect(CLIENT_ID.c_str())) {
            client.subscribe(SUBSCRIPTION_TOPIC_ALL);
        }
    }
}

/**
 * Publishes a payload to the predefined mqtt broker.
 *
 * @param topic The mqtt publish address.
 * @param message The payload to publish.
 * @return void
 */
void publishMessage(const char *topic, const char *message) {
    client.publish(topic, message);
}

/**
 * Publishes a payload to the predefined mqtt broker.
 * Converts the string message to const char* before publishing.
 *
 * @param topic The mqtt publish address.
 * @param message The payload to publish.
 * @return void
 */
void publishMessage(const char *topic, String message) {
    char const *pchar = message.c_str();
    publishMessage(topic, pchar);
}

/**
 * Plays an alert sound with the buzzer if connection is lost.
 *
 * @return void
 */
void playConnectionLostAlert() {
    /*
    Unfortunately, due to how the mqtt library works, we cannot use the ordinary alert method (buzzerLoop()).
    Since the mqtt reconnecting loop is blocking (it is a infinite loop til it succeeds),
    we cannot call the alert method from the loop. Instead, we have to directly call turnOnBuzzer() and turnOffBuzzer().
    */
    haveAlerted = true;
    turnOnBuzzer();
    delay(500);
    turnOffBuzzer();
}

/**
 * State of the WiFi connection.
 *
 * @return bool, true if wifi is connected, else false.
 */
bool getWifiConnection() {
    return wifiConnection;
}

/**
 * State of the mqtt broker connection.
 *
 * @return bool, true if mqtt is connected, else false.
 */
bool getMqttConnection() {
    return mqttConnection;
}
