package capstone.routerservice.storage;

import org.springframework.stereotype.Repository;

import java.util.ArrayList;

@Repository
public class Database {

    private int ledState;
    private ArrayList<Double> raw_adc_values;
    private ArrayList<Double> x_acc;
    private ArrayList<Double> y_acc;
    private ArrayList<Double> z_acc;
    private ArrayList<Double> yaw;
    private ArrayList<Double> roll;
    private ArrayList<Double> pitch;
    private ArrayList<Double> temp;

    public Database(){
        ledState =0;
        raw_adc_values = new ArrayList<Double>();
        x_acc = new ArrayList<Double>();
        y_acc = new ArrayList<Double>();
        z_acc = new ArrayList<Double>();
        yaw = new ArrayList<Double>();
        roll = new ArrayList<Double>();
        pitch = new ArrayList<Double>();
        temp = new ArrayList<Double>();
    }

    public int getLedState() {
        return ledState;
    }

    public void setLedState(int ledState) {
        this.ledState = ledState;
    }

    public ArrayList<Double> getRaw_adc_values() {
        return raw_adc_values;
    }

    public ArrayList<Double> getX_acc() {
        return x_acc;
    }

    public ArrayList<Double> getY_acc() {
        return y_acc;
    }

    public ArrayList<Double> getZ_acc() {
        return z_acc;
    }

    public ArrayList<Double> getYaw() {
        return yaw;
    }

    public ArrayList<Double> getRoll() {
        return roll;
    }

    public ArrayList<Double> getPitch() {
        return pitch;
    }

    public ArrayList<Double> getTemp() {
        return temp;
    }

}
