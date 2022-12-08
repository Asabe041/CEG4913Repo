package capstone.routerservice.utils;

import org.json.JSONException;
import org.json.JSONObject;

public class Parser {

    private static int ledState;
    private static double raw_adc_value;
    private static double x_acc;
    private static double y_acc;
    private static double z_acc;
    private static double yaw;
    private static double roll;
    private static double pitch;
    private static double temp;
    private static String password;

    public Parser() {
    }

    public static void parseMPU(String jsonString) throws JSONException {
        JSONObject obj = new JSONObject(jsonString);
        x_acc = (double) obj.get("x_axis");
        y_acc = (double) obj.get("y_axis");
        z_acc = (double) obj.get("z_axis");
        roll = (double) obj.get("roll");
        yaw = (double) obj.get("yaw");
        pitch = (double) obj.get("pitch");
        temp = (double) obj.get("temperature");
        password = (String) obj.get("password");
    }
    public static void parseMCP(String jsonString) throws JSONException {
        JSONObject obj = new JSONObject(jsonString);
        ledState = (int) obj.get("led_state");
        raw_adc_value = (double)obj.get("raw_adc_data");
        password = (String) obj.get("password");

    }

    public static int getLedState() {
        return ledState;
    }

    public static double getRaw_adc_values() {
        return raw_adc_value;
    }

    public static double getX_acc() {
        return x_acc;
    }

    public static double getY_acc() {
        return y_acc;
    }

    public static double getZ_acc() {
        return z_acc;
    }

    public static double getYaw() {
        return yaw;
    }

    public static double getRoll() {
        return roll;
    }

    public static double getPitch() {
        return pitch;
    }

    public static double getTemp() {
        return temp;
    }

    public static String getPassword(){
        return password;
    }
}
