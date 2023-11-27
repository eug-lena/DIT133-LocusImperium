/**
 * Tests to check if the text and visual elements of the different screens are being displayed
 */

package com.group6.locusimperium;

import static androidx.test.core.app.ApplicationProvider.getApplicationContext;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.matcher.ViewMatchers.withId;

import androidx.test.core.app.ActivityScenario;
import androidx.test.espresso.Espresso;
import androidx.test.espresso.action.ViewActions;
import androidx.test.espresso.matcher.ViewMatchers;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
public class DisplayTest{
    // test to check if the text and visual elements are being displayed
    @Test
    public void checkPeopleCounterDisplay(){
        ActivityScenario<MainActivity> activityScenario = ActivityScenario.launch(MainActivity.class);
        App globalApp = (App) getApplicationContext();
        globalApp.getBrokerConnection().setConnectionStatus(true);
        Espresso.onView(withId(R.id.people_textview)).check(matches(isDisplayed())); //check if the counter is displayed

    }
    @Test
    public void checkTemperatureDisplay(){
        ActivityScenario<MainActivity> activityScenario = ActivityScenario.launch(MainActivity.class);
        App globalApp = (App) getApplicationContext();
        globalApp.getBrokerConnection().setConnectionStatus(true);
        Espresso.onView(withId(R.id.temperature_textview)).check(matches(ViewMatchers.isDisplayed()));
    }

    @Test
    public void checkHumidityDisplay(){
        ActivityScenario<MainActivity> activityScenario = ActivityScenario.launch(MainActivity.class);
        App globalApp = (App) getApplicationContext();
        globalApp.getBrokerConnection().setConnectionStatus(true);
        Espresso.onView(withId(R.id.humidity_textview)).check(matches(ViewMatchers.isDisplayed()));
    }

    @Test
    public void checkSettingsButton(){
        ActivityScenario<MainActivity> activityScenario = ActivityScenario.launch(MainActivity.class);
        App globalApp = (App) getApplicationContext();
        globalApp.getBrokerConnection().setConnectionStatus(true);
        Espresso.onView(withId(R.id.settingsButton)).check(matches(ViewMatchers.isDisplayed())); //check if the settings button is displayed
        Espresso.onView(withId(R.id.settingsButton)).perform(ViewActions.click()); //click the settings button
        Espresso.onView(withId(R.id.settings)).check(matches(ViewMatchers.isDisplayed()));
    }
    @Test
    public void CheckConnectButton(){
        ActivityScenario<MainActivity> activityScenario = ActivityScenario.launch(MainActivity.class);
        App globalApp = (App) getApplicationContext();
        globalApp.getBrokerConnection().setConnectionStatus(true);
        Espresso.onView(withId(R.id.connectButton)).check(matches(ViewMatchers.isDisplayed()));
        Espresso.onView(withId(R.id.connectButton)).perform(ViewActions.click());
        Espresso.onView(withId(R.id.connect)).check(matches(ViewMatchers.isDisplayed()));
    }

    @Test
    public void checkNoConnectionScreen() throws InterruptedException {
        ActivityScenario<MainActivity> activityScenario = ActivityScenario.launch(MainActivity.class);
        App globalApp = (App) getApplicationContext();
        globalApp.getBrokerConnection().setConnectionStatus(false);
        // Takes 1000ms for it to pop up NoConnectionActivity screen
        Thread.sleep(2000);
        Espresso.onView(withId(R.id.noConnectionAct)).check(matches(ViewMatchers.isDisplayed()));
        Espresso.onView(withId(R.id.noConnectionMsg)).check(matches(ViewMatchers.isDisplayed()));
    }

    @Test
    public void checkReconnectButton() throws InterruptedException {
        ActivityScenario<MainActivity> activityScenario = ActivityScenario.launch(MainActivity.class);
        App globalApp = (App) getApplicationContext();
        globalApp.getBrokerConnection().setConnectionStatus(false);
        // Takes 1000ms for it to pop up NoConnectionActivity screen
        Thread.sleep(2000);
        Espresso.onView(withId(R.id.reconnectButton)).perform(ViewActions.click());
        Espresso.onView(withId(R.id.connect)).check(matches(ViewMatchers.isDisplayed()));
    }

}
    
