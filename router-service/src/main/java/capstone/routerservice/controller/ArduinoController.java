package capstone.routerservice.controller;

import capstone.routerservice.service.ArduinoService;
import org.json.JSONException;
import org.springframework.web.bind.annotation.*;


@RestController
@RequestMapping("/")
//@CrossOrigin(origins = "*", allowedHeaders = "*")
public class ArduinoController {

    private final ArduinoService arduinoService;

    ArduinoController(ArduinoService arduinoService) {
        this.arduinoService = arduinoService;
    }

    @PostMapping("mpu")
    public String mpuController(@RequestBody String body) throws JSONException {
        return arduinoService.mpuService(body);
    }

    @PostMapping("mcp")
    public String mcpController(@RequestBody String body) throws JSONException {
        return arduinoService.mcpService(body);
    }

    @GetMapping("ledstate")
    public int ledStateController(){
        return arduinoService.stateService();
    }
}
