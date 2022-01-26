void setController() {
  
  server.on("/", [] () {
    int value = digitalRead(LED_BUILTIN);
    String resp;
    if (HIGH == value) {
      resp = "<!doctype html><html><head><title>Swich</title></head><body><h1>Swith</h1><br/>status: off<br/><a href=\"led/on\">ON</a><br/><a href=\"led/off\">OFF</a></body></html>";
    } else if (LOW == value) {
      resp = "<!doctype html><html><head><title>Swich</title></head><body><h1>Swith</h1><br/>status: on<br/><a href=\"led/on\">ON</a><br/><a href=\"led/off\">OFF</a></body></html>";
    }
    server.send(200, "text/html", resp);
  });
  
  server.on("/led/on", [] () {
    ledTurnOn();
    server.send(200, "application/json", "{\"success\":true, \"message\":\"turn on success!\"}");  
  });
  
  server.on("/led/off", [] () {
    ledTurnOff();
    server.send(200, "application/json", "{\"success\":true, \"message\":\"turn off success!\"}");
  });
  
  server.onNotFound([] () {
    server.send(404, "text/html", "<!doctype html><html><head><title>404 Not Found</title></head><body><h1>ERROR::NOT_FOUND</h1></body></html>");  
  });
  
  server.begin();
}
