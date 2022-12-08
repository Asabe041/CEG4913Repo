package capstone.routerservice.utils;

import org.json.JSONException;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class ParserTest {

    private String bodyMPU = "{\"x_axis\":1.2,\n" +
            "\"y_axis\": 2.12,\n" +
            "\"z_axis\": 3.2,\n" +
            "\"yaw\": 4.2,\n" +
            "\"roll\": 2.2,\n" +
            "\"pitch\": 4.2,\n" +
            "\"temperature\": 20.4}";
    private String bodyMCP = "{\"password\": \"abc\",\n" +
            "\"led_state\":3,\n" +
            "\"raw_adc_data\":1213.12}";

    private Parser parser;

    @Test
    void parseMPU() throws JSONException {
        //Given When Then
    parser.parseMPU(bodyMPU);

    assertEquals(parser.getX_acc(), 1.2);
    assertEquals(parser.getY_acc(), 2.12);
    assertEquals(parser.getZ_acc(), 3.2);
    assertEquals(parser.getYaw(), 4.2);
    assertEquals(parser.getRoll(), 2.2);
    assertEquals(parser.getPitch(), 4.2);
    assertEquals(parser.getTemp(), 20.4);
    }

    @Test
    void parseMCP() throws JSONException {
        //Given When Then
    parser.parseMCP(bodyMCP);
    assertEquals(parser.getLedState(), 3);
    assertEquals(parser.getRaw_adc_values(), 1213.12);
    }
}