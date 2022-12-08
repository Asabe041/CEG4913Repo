package capstone.routerservice.service;

import capstone.routerservice.storage.Database;
import capstone.routerservice.utils.Parser;
import org.json.JSONException;
import org.springframework.stereotype.Service;

@Service
public class ArduinoService {

    private final Parser parser;
    private final Database database;

    ArduinoService(Database database){
        this.database = database;
        parser = new Parser();
    };

    public String mpuService(String body) throws JSONException {
        System.out.println(body);
        parser.parseMPU(body);
        if(!parser.getPassword().equals("fvwaebyiuoafeiwbhlyiyw")){
            return "";
        }
        database.getX_acc().add(parser.getX_acc());
        database.getY_acc().add(parser.getY_acc());
        database.getZ_acc().add(parser.getZ_acc());
        database.getRoll().add(parser.getRoll());
        database.getYaw().add(parser.getYaw());
        database.getPitch().add(parser.getPitch());
        database.getTemp().add(parser.getTemp());
        return "MPU Data Received without error";
    }

    public String mcpService(String body) throws JSONException {
        System.out.println(body);
        parser.parseMCP(body);
        if(!parser.getPassword().equals("fvwaebyiuoafeiwbhlyiyw")){
            return "";
        }
        database.setLedState(parser.getLedState());
        database.getRaw_adc_values().add(parser.getRaw_adc_values());
        return "MCP Data Received without error";
    }

    public int stateService() {
        System.out.println("Getting led state from application with state:" + database.getLedState());
        return database.getLedState();
    }
}
