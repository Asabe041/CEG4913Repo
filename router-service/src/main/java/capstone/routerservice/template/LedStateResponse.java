package capstone.routerservice.template;

public class LedStateResponse {
    private int led_state;

    public LedStateResponse (int led_state){
        this.led_state = led_state;
    }
    public int isLed_state() {
        return led_state;
    }

    public void setLed_state(int led_state) {
        this.led_state = led_state;
    }
}
