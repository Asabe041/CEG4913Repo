package capstone.routerservice.service;

import org.springframework.stereotype.Service;

@Service
public class ArduinoService {

    ArduinoService(){};

    public String mpuService(String body){
        System.out.println("mpu body: " + body);
        return "mpu_service: " + body;
    }

    public String mcpService(String body){
        System.out.println("mcp body: " + body);
        return "mcp_service: " + body;
    }
}
