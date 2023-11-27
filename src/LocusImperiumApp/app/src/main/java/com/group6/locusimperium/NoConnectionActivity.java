package com.group6.locusimperium;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class NoConnectionActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_no_connection);

        Button reconnect = findViewById(R.id.reconnectButton);
        reconnect.setOnClickListener(new View.OnClickListener() {
            // reconnect button sends user back to connect activity
            @Override
            public void onClick(View view) {
                Intent intentGoToConnectionActivity = new Intent(NoConnectionActivity.this, ConnectActivity.class);
                startActivity(intentGoToConnectionActivity);
            }
        });
    }
}