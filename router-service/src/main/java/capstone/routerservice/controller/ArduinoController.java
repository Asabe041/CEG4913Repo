package capstone.routerservice.controller;

import capstone.routerservice.service.ArduinoService;
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
    public String mpuController(@RequestBody String body){
        return arduinoService.mpuService(body);
    }

    @PostMapping("mcp")
    public String mcpController(@RequestBody String body){
        return arduinoService.mcpService(body);
    }

}
