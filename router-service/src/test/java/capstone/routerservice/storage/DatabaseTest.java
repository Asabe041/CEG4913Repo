package capstone.routerservice.storage;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;

class DatabaseTest {

    private int ledState;
    private ArrayList<Double> raw_adc_values = new ArrayList<Double>();
    private ArrayList<Double> x_acc = new ArrayList<Double>();
    private ArrayList<Double> y_acc = new ArrayList<Double>();
    private ArrayList<Double> z_acc = new ArrayList<Double>();
    private ArrayList<Double> yaw = new ArrayList<Double>();
    private ArrayList<Double> roll = new ArrayList<Double>();
    private ArrayList<Double> pitch = new ArrayList<Double>();
    private ArrayList<Double> temp = new ArrayList<Double>();

    @Test
    void databaseConstructor(){
        //Given When Then
        ledState = 3;
        raw_adc_values.add(500.0);
        x_acc.add(3.0);
        y_acc.add(2.0);
        z_acc.add(1.0);
        yaw.add(5.0);
        roll.add(4.0);
        pitch.add(6.0);
        temp.add(20.0);

        Database database = new Database();
        database.getX_acc().add(3.0);
        database.getY_acc().add(2.0);
        database.getZ_acc().add(1.0);
        database.getRoll().add(4.0);
        database.getYaw().add(5.0);
        database.getPitch().add(6.0);
        database.getTemp().add(20.0);
        database.setLedState(3);
        database.getRaw_adc_values().add(500.0);

        assertEquals(database.getX_acc(), x_acc);
        assertEquals(database.getY_acc(), y_acc);
        assertEquals(database.getZ_acc(), z_acc);
        assertEquals(database.getRoll(), roll);
        assertEquals(database.getYaw(), yaw);
        assertEquals(database.getPitch(), pitch);
        assertEquals(database.getLedState(), ledState);
        assertEquals(database.getTemp(), temp);
    }

}