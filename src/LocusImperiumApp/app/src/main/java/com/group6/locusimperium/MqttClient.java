/****************************************************************************
 Code base on "DIT113MqttWorkshop".
 Author: Nicole Quinstedt
 Source: https://github.com/Quinstedt/DIT113MqttWorkshop/blob/main/SpeechToText/app/src/main/java/com/quinstedt/speechtotext/MqttClient.java
 *****************************************************************************/

package com.group6.locusimperium;

import android.content.Context;

import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import info.mqtt.android.service.*;

public class MqttClient {

    private MqttAndroidClient mqttClient;

    public MqttClient(Context context, String serverUrl, String clientId) {
        mqttClient = new MqttAndroidClient(context, serverUrl, clientId, Ack.AUTO_ACK);
    }

    /**
     * Connects to a mqtt broker.
     *
     * @param username what the broker will now the device as
     * @param password if a password is desired, otherwise set as empty ("")
     */
    public void connect(String username, String password, IMqttActionListener connectionCallback, MqttCallback clientCallback) {

        mqttClient.setCallback(clientCallback);
        MqttConnectOptions options = new MqttConnectOptions();
        options.setUserName(username);
        options.setPassword(password.toCharArray());
        options.setAutomaticReconnect(true);
        options.setCleanSession(true);

        try {
            mqttClient.connect(options, null, connectionCallback);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Disconnects from the broker.
     *
     * @note disconnectionCallback: set as null
     */
    public void disconnect(IMqttActionListener disconnectionCallback) {
        try {
            mqttClient.disconnect(null, disconnectionCallback);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Subscribes to a specific topic from the mqtt broker.
     *
     * @param topic topic of the message
     * @param qos   which quality of service to use
     * @note subscriptionCallback: set as null
     */
    public void subscribe(String topic, int qos, IMqttActionListener subscriptionCallback) {
        try {
            mqttClient.subscribe(topic, qos, null, subscriptionCallback);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Unsubscribes from a certain topic from the mqtt broker.
     *
     * @param topic topic of the message
     * @note unsubscriptionCallback: set as null
     */
    public void unsubscribe(String topic, IMqttActionListener unsubscriptionCallback) {
        try {
            mqttClient.unsubscribe(topic, null, unsubscriptionCallback);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Publishes a message to the mqtt broker.
     *
     * @param topic   topic of the message
     * @param message payload of the message
     * @param qos     which mqtt quality of service to use
     * @note publishCallback: set as null
     */
    public void publish(String topic, String message, int qos, IMqttActionListener publishCallback) {
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setPayload(message.getBytes());
        mqttMessage.setQos(qos);

        try {
            mqttClient.publish(topic, mqttMessage, null, publishCallback);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}