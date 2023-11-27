package com.group6.locusimperium;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ProgressBar;
import android.widget.Toast;

import static com.group6.locusimperium.SettingsActivity.SHARED_PREFS;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.navigation.NavigationBarView;
import com.google.android.material.snackbar.Snackbar;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import maes.tech.intentanim.CustomIntent;

public class ConnectActivity extends AppCompatActivity implements NavigationBarView.OnItemSelectedListener {
    private BrokerConnection brokerConnection;
    private Button saveIPButton;
    private EditText inputIP;
    private String ipaddress;
    
    public static final String IPADDRESS = "ipaddress";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connect);

        // get broker connection from global app
        App globalApp = (App) getApplicationContext();
        brokerConnection = globalApp.getBrokerConnection();
        brokerConnection.connectActivity = this;

        // get IP address from shared preferences
        inputIP = findViewById(R.id.inputIPAddress);
        saveIPButton = findViewById(R.id.saveIP);
        saveIPButton.setOnClickListener(new View.OnClickListener() {
            /**
             * saves data when save button is clicked
             */
            @Override
            public void onClick(View view) {
                saveIP();
            }
        });

        // load IP address from shared preferences
        loadIP();
        updateIP();

        // bottom navigation bar selections
        BottomNavigationView bottomNavigationView = findViewById(R.id.bottom_navigation);
        bottomNavigationView.setSelectedItemId(R.id.connectButton);
        bottomNavigationView.setOnItemSelectedListener(this);

        // set up the progress bar
        ProgressBar progressBar = (ProgressBar) findViewById(R.id.progressBar);
        progressBar.setVisibility(View.INVISIBLE);
    }

    @SuppressLint("NonConstantResourceId")
    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {
        // if connected to broker, allow navigation
        if(brokerConnection.getConnectionStatus()) {
            // navigation bar selections
            switch (item.getItemId()) {
                case R.id.homeButton:
                    Intent intentLoadMainActivity = new Intent(ConnectActivity.this, MainActivity.class);
                    startActivity(intentLoadMainActivity);
                    CustomIntent.customType(ConnectActivity.this, "fadein-to-fadeout");
                    return true;
                case R.id.connectButton:
                    return true;
                case R.id.settingsButton:
                    Intent intentLoadSettingsActivity = new Intent(ConnectActivity.this, SettingsActivity.class);
                    startActivity(intentLoadSettingsActivity);
                    CustomIntent.customType(ConnectActivity.this, "fadein-to-fadeout");
                    return true;
            }
        } else {
            displaySnackbar("Not connected to broker yet");
        }

        return false;
    }

    /**
     * saves IP address to shared preferences and disconnect from broker to reconnect with new IP
     */
    public void saveIP() {
        ProgressBar progressBar = (ProgressBar) findViewById(R.id.progressBar);
        progressBar.setVisibility(View.VISIBLE);
        SharedPreferences sharedPreferences = getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putString(IPADDRESS, inputIP.getText().toString());
        editor.apply();

        brokerConnection.getMqttClient().disconnect(null);

        // display a snack-bar to show that the IP address has been saved
        View contextView = findViewById(R.id.connect);
        Snackbar.make(contextView, "IP address saved", Snackbar.LENGTH_SHORT).setAnchorView(R.id.bottom_navigation).show();

        brokerConnection.connectToMqttBroker();
    }

    public void loadIP() {
        SharedPreferences sharedPreferences = getSharedPreferences(SHARED_PREFS, MODE_PRIVATE);
        ipaddress = sharedPreferences.getString(IPADDRESS, "");
    }

    public void updateIP() {
        inputIP.setText(ipaddress);
    }

    /**
     * displays a snackbar message
     * @param message
     */
    public void displaySnackbar(String message) {
        try {
            View contextView = findViewById(R.id.connect);
            Snackbar.make(contextView, message, Snackbar.LENGTH_SHORT).setAnchorView(R.id.bottom_navigation).show();
        } catch (Exception e) {
            return;
        }

    }

    /** 
     * Starts the progress bar
     */
    public void startProgressBar() {
        try {
            ProgressBar progressBar = (ProgressBar) findViewById(R.id.progressBar);
            progressBar.setVisibility(View.VISIBLE);
        } catch (Exception e) {
            return;
        }

    }

    /**
     * Stops the progress bar
     */
    public void stopProgressBar() {
        try {
            ProgressBar progressBar = (ProgressBar) findViewById(R.id.progressBar);
            progressBar.setVisibility(View.INVISIBLE);
        } catch (Exception e) {
            return;
        }
    }

}
