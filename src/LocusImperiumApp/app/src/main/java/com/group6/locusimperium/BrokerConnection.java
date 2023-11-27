/****************************************************************************
 Code base on "DIT113MqttWorkshop".
 Author: Nicole Quinstedt
 Source: https://github.com/Quinstedt/DIT113MqttWorkshop/blob/main/SpeechToText/app/src/main/java/com/quinstedt/speechtotext/BrokerConnection.java
 *****************************************************************************/

package com.group6.locusimperium;

// includes for the mqtt client

import static com.group6.locusimperium.ConnectActivity.IPADDRESS;
import static com.group6.locusimperium.SettingsActivity.HUMIDITY;
import static com.group6.locusimperium.SettingsActivity.LOUDNESS;
import static com.group6.locusimperium.SettingsActivity.PEOPLE;
import static com.group6.locusimperium.SettingsActivity.SHARED_PREFS;
import static com.group6.locusimperium.SettingsActivity.TEMPERATURE;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import com.google.android.material.snackbar.Snackbar;
import android.view.View;

public class BrokerConnection extends AppCompatActivity {

    // Global predefined values
    private static final String SUBSCRIPTION_TOPIC = "LocusImperium/WIO/";
    private static final String PUBLISH_TOPIC = "LocusImperium/APP/";
    private static final String MAX_SETTINGS_PUBLISH_TOPIC = PUBLISH_TOPIC + "maxSettings";
    private static final String ADJUST_PEOPLE_COUNTER_TOPIC = PUBLISH_TOPIC + "AdjustPeopleCounter";
    private static final String CLIENT_ID = "LocusImperium-Application";
    private static final int QOS = 0; // For mqtt messaging; which quality of service to use.

    //Attributes
    private boolean isConnected = false;
    private MqttClient mqttClient;
    private Context context;

    //TextView elements to update on MainActivity
    public TextView peopleCount;
    public TextView temperatureValue;
    public TextView humidityValue;
    public TextView loudnessValue;

    public ConnectActivity connectActivity;

    /**
     * Constructor for BrokerConnection.
     *
     * @param context the context of the application
     */
    public BrokerConnection(Context context) {
        this.context = context;
        connectToMqttBroker();
    }

    /**
     * Establishes connection to the mqtt broker.
     *
     * @see MqttClient
     */
    public void connectToMqttBroker() {
        // If not connected, connect to the broker.
        if (!isConnected) {

            // Get the IP address from the SharedPreferences interface.
            SharedPreferences sharedPreferences = context.getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
            String LOCALHOST = sharedPreferences.getString(IPADDRESS, "");
            String MQTT_SERVER = "tcp://" + LOCALHOST + ":1883";
            mqttClient = new MqttClient(context, MQTT_SERVER, CLIENT_ID);

            // Connect to the broker.
            mqttClient.connect(CLIENT_ID, "", new IMqttActionListener() {
                @Override

                // If the connection is successful, subscribe to the topic.
                public void onSuccess(IMqttToken asyncActionToken) {
                    isConnected = true;
                    final String successfulConnection = "Connected to MQTT broker";
                    Log.i(CLIENT_ID, successfulConnection);
                    if(connectActivity != null){
                        connectActivity.displaySnackbar("Connected successfully");
                        connectActivity.stopProgressBar();
                    }
                    // Added "+ '#'" to subscribe to all subtopics under the super one.
                    mqttClient.subscribe(SUBSCRIPTION_TOPIC + '#', QOS, null);
                }

                // If the connection is unsuccessful, display a failure message.
                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    final String failedConnection = "Failed to connect to MQTT broker";
                    if (connectActivity != null)
                    {
                        connectActivity.displaySnackbar("Failed to connect");
                        connectActivity.stopProgressBar();
                    }
                    Log.e(CLIENT_ID, failedConnection);
                }
            }, new MqttCallback() {
                @Override
                public void connectionLost(Throwable cause) {
                    isConnected = false;
                    final String connectionLost = "Connection to MQTT broker lost";
                    Log.w(CLIENT_ID, connectionLost);
                }

                @Override
                public void messageArrived(String topic, MqttMessage message) {
                    // The message is in the form of a string, with the values separated by commas.
                    String messageMQTT = message.toString();
                    String[] topicArray = messageMQTT.split(",");
                    //The position of the different settings values are predefined in the array.
                    peopleCountArrived(topicArray[0]);
                    humidityValueArrived(topicArray[1]);
                    temperatureValueArrived(topicArray[2]);
                    loudnessValueArrived(topicArray[3]);
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {
                    Log.d(CLIENT_ID, "Message delivered");
                }
            });
        }
    }

    /**
     * Updates the people count textview value, color is gray if the value is below the max value, red if above. The max value is set in the settings.
     * @param message the message to be displayed
     */
    public void peopleCountArrived(String message) {
        peopleCount.setText(message);
        // If the people count is above the max value, set the text color to red.
        if (Integer.parseInt(message) > Integer.parseInt(getMaxPeople())) {
            peopleCount.setText(message);
            peopleCount.setTextColor(Color.RED);
        } else {
            peopleCount.setText(message);
            peopleCount.setTextColor(Color.GRAY);
        }
    }

    /**
     * Updates the humidity textview value, color is gray if the value is below the max value, red if above. The max value is set in the settings.
     * @param message the message to be displayed
     */
    public void humidityValueArrived(String message) {
        humidityValue.setText(message);
        // If the humidity is above the max value, set the text color to red.
        if (Integer.parseInt(message) > Integer.parseInt(getMaxHumidity())) {
            humidityValue.setText(message);
            humidityValue.setTextColor(Color.RED);
        } else {
            humidityValue.setText(message);
            humidityValue.setTextColor(Color.GRAY);
        }
    }

    /**
     * Updates the temperature textview value, color is gray if the value is below the max value, red if above. The max value is set in the settings.
     * @param message the message to be displayed
     */
    public void temperatureValueArrived(String message) {
        temperatureValue.setText(message);
        // If the temperature is above the max value, set the text color to red.
        if (Integer.parseInt(message) > Integer.parseInt(getMaxTemperature())) {
            temperatureValue.setText(message);
            temperatureValue.setTextColor(Color.RED);
        } else {
            temperatureValue.setText(message);
            temperatureValue.setTextColor(Color.GRAY);
        }
    }

    /**
     * Updates the loudness textview value, color is gray if the value is below the max value, red if above. The max value is set in the settings.
     * @param message the message to be displayed
     */
    public void loudnessValueArrived(String message) {
        int loudness = 0;
        if (getMaxLoudness().equals("Quiet")) {
            loudness = 50;
        } else if (getMaxLoudness().equals("Moderate")) {
            loudness = 60;
        } else if (getMaxLoudness().equals("Loud")) {
            loudness = 70;
        }

        if (Integer.parseInt(message) < loudness) {
            loudnessValue.setText(message);
            loudnessValue.setTextColor(Color.GRAY);
        } else {
            loudnessValue.setText(message);
            loudnessValue.setTextColor(Color.RED);
        }
    }
    
    /**
     * Publishes the adjustment to the people counter to the broker.
     * @param adjustment the adjustment to be published
     */
    public void publishPeopleCounter(String adjustment) {
        // If not connected, display a message.
        if (!isConnected) {
            final String notConnected = "Not connected (yet)";
            Log.e(CLIENT_ID, notConnected);
            Toast.makeText(context, notConnected, Toast.LENGTH_SHORT).show();
        } else {
            final String connected = "Connected";
            Log.e(CLIENT_ID, connected);
            mqttClient.publish(ADJUST_PEOPLE_COUNTER_TOPIC, adjustment, QOS, null);
        }
    }
    
    /**
     * Publishes the maximum settings to the broker.
     */
    public void publishSettings() {
        if (!isConnected) {
            final String notConnected = "Not connected (yet)";
            Log.e(CLIENT_ID, notConnected);
            //Toast.makeText(context, notConnected, Toast.LENGTH_SHORT).show();
            return;
        } else {
            final String connected = "Connected";
            Log.e(CLIENT_ID, connected);
            mqttClient.publish(MAX_SETTINGS_PUBLISH_TOPIC, getMaxPeople() + "," + getMaxHumidity() + "," + getMaxTemperature() + "," + getMaxLoudness(), QOS, null);
        }
    }

    /**
     * Gets the corresponding MqttClient object of the BrokerConnection object.
     *
     * @return MqttClient object
     */
    public MqttClient getMqttClient() {
        return mqttClient;
    }

    // Methods to link TextView object to actual element on the screen on startup.

    /**
     * Updates the text of the peopleCount TextView.
     *
     * @param textView the new text
     */
    public void setPeopleCount(TextView textView) {
        this.peopleCount = textView;
    }

    /**
     * Updates the text of the temperatureValue TextView.
     *
     * @param textView the new text
     */
    public void setTemperatureValue(TextView textView) {
        this.temperatureValue = textView;
    }

    /**
     * Updates the text of the humidityValue TextView.
     *
     * @param textView the new text
     */
    public void setHumidityValue(TextView textView) {
        this.humidityValue = textView;
    }

    /**
     * Updates the text of the loudnessValue TextView.
     *
     * @param textView the new text
     */
    public void setLoudnessValue(TextView textView) {
        this.loudnessValue = textView;
    }

    // Helper methods to calculate if current readings are above maximum values.

    /**
     * Gets the maximumed allowed of people from the SharedPreferences interface.
     *
     * @return String
     */
    public String getMaxPeople() {
        SharedPreferences sharedPreferences = context.getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
        return sharedPreferences.getString(PEOPLE, "");
    }

    /**
     * Gets the maximumed allowed loudness from the SharedPreferences interface.
     *
     * @return String
     */
    public String getMaxLoudness() {
        SharedPreferences sharedPreferences = context.getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
        return sharedPreferences.getString(LOUDNESS, "");
    }

    /**
     * Gets the maximumed allowed humidity from the SharedPreferences interface.
     *
     * @return String
     */
    public String getMaxHumidity() {
        SharedPreferences sharedPreferences = context.getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
        return sharedPreferences.getString(HUMIDITY, "");
    }

    /**
     * Gets the maximumed allowed temperature from the SharedPreferences interface.
     *
     * @return String
     */
    public String getMaxTemperature() {
        SharedPreferences sharedPreferences = context.getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
        return sharedPreferences.getString(TEMPERATURE, "");
    }

    /**
     * Gets the current connection status
     *
     * @return boolean
     */
    public boolean getConnectionStatus() {
        return isConnected;
    }

    /**
     * Sets the connection status.
     * Only used by tests to "manipulate" the connection. This since the display changes dependant on if it is connected or not.
     */
    public void setConnectionStatus(boolean status) {
        isConnected = status;
    }
}