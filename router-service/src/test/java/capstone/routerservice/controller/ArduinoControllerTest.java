package capstone.routerservice.controller;

import org.json.JSONException;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertEquals;

@ExtendWith(MockitoExtension.class)
@SpringBootTest
@AutoConfigureMockMvc
class ArduinoControllerTest {
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

    @Autowired
    private ArduinoController controller;

    @Test
    public void contextLoads() throws Exception {
        assertThat(controller).isNotNull();
    }

    @Test
    void mpuControllerTest() throws Exception {
        //Given //While //Then
        String expected = "MPU Data Received without error";
        String returned = controller.mpuController(bodyMPU);
        assertEquals(returned, expected);
    }

    @Test
    void mcpControllerTest() throws JSONException {
        //Given //While //Then
        String expected = "MCP Data Received without error";
        String returned = controller.mcpController(bodyMCP);
        assertEquals(returned, expected);
    }

    @Test
    void ledStateControllerTest(){
        int expected = 3;
        int returned = controller.ledStateController();
        assertEquals(returned, expected);
    }
}