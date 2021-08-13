//============================================================================
// Name        : head-first-simulator.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://learning.oreilly.com/library/view/head-first-design/0596007124/
//============================================================================

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

/*
 * A class is made abstract by declaring at least one of its functions as pure virtual function
 */
class Observer {
public:
    Observer(){ };
    virtual ~Observer(){}
    /*
    Observer& operator=(const Observer &rhs) {
        id = rhs.id;
        return *this;
    }
    bool operator== (const Observer &o2)
    {
        return (id == o2.id);
    }
    bool operator!= (const Observer &o2)
    {
        return !(id == o2.id);
    }
    */
    virtual void update(float temp, float humidity, float pressure) = 0;
    virtual string getName() = 0;
};

class Subject {
public:
    // Note: Constructors are never Virtual, only Destructors can be Virtual.
    Subject(){};
    virtual ~Subject(){};

    virtual void removeObserver(Observer *o) = 0;
    virtual void registerObserver(Observer *o) = 0;
    virtual void notifyObservers() = 0;
};

/*
 * Class WeatherData
 */
class WeatherData: public Subject {
    vector<Observer *> observers;
    //deque<int> observer_ids {1,2,3,4,5,6,7,8,9,10};
    //unordered_map<int, Observer *> observers_map;
    float temperature;
    float humidity;
    float pressure;
public:
    WeatherData() {
        temperature = 0;
        humidity = 0;
        pressure = 0;
    };
    /*
    WeatherData& operator=(const WeatherData &rhs) {
        temperature = rhs.temperature;
        humidity = rhs.humidity;
        pressure = rhs.pressure;
        return *this;
    }
    */
    void registerObserver(Observer *o) override {
        // traditional method:
        cout << "Registering " << o->getName() << endl;
        observers.push_back(o);
        return;

        /* another way...
        if(!observer_ids.size()) {
            return; //0;
        }
        int next_id = observer_ids.back();
        observers_map.emplace(next_id, o);
        observer_ids.pop_back();
        return; // next_id;
        */
    }

    void removeObserver(Observer *o) override {
        // traditional method:
        cout << "Removing " << o->getName() << endl;
        auto it = std::find(observers.begin(), observers.end(), o);
        if(it != observers.end()) {
            observers.erase(it);
        }

        /* another way...
        int remove_id = o->id;
        auto map_it = observers_map.find(remove_id);
        if(map_it != observers_map.end()) {
            observers_map.erase(remove_id);
            observer_ids.push_front(remove_id);
        }
        */
    }

    void notifyObservers() override {
        // traditional method:
        cout << "Calling notify..." << endl;
        for(Observer *ob : observers) {
            cout << "Notifying " << ob->getName() << endl;
            ob->update(temperature, humidity, pressure);
        }
        /* another way...
        for (auto& ob_map : observers_map) {
            ob = ob_map.second;
            ob->update(temperature, humidity, pressure);
        }
        */
    }

    void measurementsChanged() {
        notifyObservers();
    }

    // aka setState(...)
    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }

    float getTemperature() {
        return temperature;
    }

    float getHumidity() {
        return humidity;
    }

    float getPressure() {
        return pressure;
    }

};

class DisplayElement {
public:
    DisplayElement() {};
    virtual ~DisplayElement() {};

    virtual void display() = 0;
};

class CurrentConditionsDisplay: public Observer, DisplayElement {
    int display_id;
    float temperature;
    float humidity;
    string displayName;

public:
    CurrentConditionsDisplay(WeatherData wd) {
        display_id = 0;
        temperature = 0;
        humidity = 0;
        displayName = "Current Conditions";
    }

    void update(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }

    void display() {
        cout << "Current conditions: " << temperature
            << "F degrees and " << humidity << "% humidity" << endl;
    }

    string getName() {
        return displayName;
    }
};

class StatisticsDisplay: public Observer, DisplayElement {
    int display_id;
    float maxTemp;
    float minTemp;
    float tempSum;
    int numReadings;
    //WeatherData weatherData;
    string displayName;

public:
    StatisticsDisplay(WeatherData wd) {
        display_id = 0;
        maxTemp = 0;
        minTemp = 200;
        tempSum = 0;
        numReadings = 0;
        displayName = "Statistics";
    }

    void update(float temp, float humidity, float pressure) {
        tempSum += temp;
        numReadings++;

        if (temp > maxTemp) {
            maxTemp = temp;
        }

        if (temp < minTemp) {
            minTemp = temp;
        }

        display();
    }

    void display() {
        cout << "Avg/Max/Min temperature = " << (tempSum / numReadings)
                    << "/" << maxTemp << "/" << minTemp << endl;
    }

    string getName() {
        return displayName;
    }
};

class ForecastDisplay: public Observer, DisplayElement {
    int display_id;
    float currentPressure;
    float lastPressure;
    string displayName;

public:
    ForecastDisplay(WeatherData wd) {
        currentPressure = 29.92;
        lastPressure = currentPressure;
        display_id = 0;
        displayName = "Forecast";
    }

    void update(float temp, float humidity, float pressure) {
        lastPressure = currentPressure;
        currentPressure = pressure;

        display();
    }

    void display() {
        cout << "Forecast: ";
        if (currentPressure > lastPressure) {
            cout << "Improving weather on the way!" << endl;
        } else if (currentPressure == lastPressure) {
            cout << "More of the same" << endl;
        } else if (currentPressure < lastPressure) {
            cout << "Watch out for cooler, rainy weather" << endl;
        }
    }

    string getName() {
        return displayName;
    }
};

class HeatIndexDisplay: public Observer, DisplayElement {
    float heatIndex = 0.0f;
    string displayName;
public:
    HeatIndexDisplay(WeatherData wd) {
        displayName = "Heat Index";
    }

    void update(float t, float rh, float pressure) {
        heatIndex = computeHeatIndex(t, rh);
        display();
    }

    float computeHeatIndex(float t, float rh) {
        float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh)
            + (0.00941695 * (t * t)) + (0.00728898 * (rh * rh))
            + (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
            (0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *
            (rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
            (0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
            0.000000000843296 * (t * t * rh * rh * rh)) -
            (0.0000000000481975 * (t * t * t * rh * rh * rh)));
        return index;
    }

     void display() {
        cout << "Heat index is " << heatIndex << endl;
    }

    string getName() {
        return displayName;
    }
};

class WeatherStation {
    WeatherData wd;
public:

    WeatherStation() {
    };

    void reportWeather() {

        CurrentConditionsDisplay ccd(wd);
        StatisticsDisplay stats(wd);
        ForecastDisplay forecast(wd);
        HeatIndexDisplay heat(wd);

        wd.registerObserver(&ccd);
        wd.registerObserver(&stats);
        wd.registerObserver(&forecast);
        wd.registerObserver(&heat);

        wd.setMeasurements(80, 65, 30.4f);
        wd.setMeasurements(82, 70, 29.2f);
        wd.setMeasurements(78, 90, 27.2f);
        wd.removeObserver(&heat);
        wd.setMeasurements(65, 72, 31.5f);
    }
};

/*
 *
 */
int main() {
	cout << "https://learning.oreilly.com/library/view/head-first-design/0596007124/" << endl;
	WeatherStation WS;
	WS.reportWeather();

	return 0;
}
