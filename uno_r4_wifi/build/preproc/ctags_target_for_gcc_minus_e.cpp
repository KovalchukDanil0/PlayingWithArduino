# 1 "/home/gomofob/Projects/Arduino/uno_r4_wifi/uno_r4_wifi.ino"
/*

  Rui Santos

  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/



  Permission is hereby granted, free of charge, to any person obtaining a copy

  of this software and associated documentation files.



  The above copyright notice and this permission notice shall be included in all

  copies or substantial portions of the Software.

*/
# 12 "/home/gomofob/Projects/Arduino/uno_r4_wifi/uno_r4_wifi.ino"
# 13 "/home/gomofob/Projects/Arduino/uno_r4_wifi/uno_r4_wifi.ino" 2

# 15 "/home/gomofob/Projects/Arduino/uno_r4_wifi/uno_r4_wifi.ino" 2

const char *ssid = "O2-Internet-052";
const char *password = "dCPCCPGBAX";

// Your Domain name with URL path or IP address with path
String serverName = "http://192.168.1.106:1880/update-sensor";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
// unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

# 31 "/home/gomofob/Projects/Arduino/uno_r4_wifi/uno_r4_wifi.ino" 2

ArduinoLEDMatrix matrix;

byte wifiConnected[8][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void setup()
{
    _UART1_.begin(115200);

    matrix.begin();
    WiFi.begin(ssid, password);
    _UART1_.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        _UART1_.print(".");
    }
    _UART1_.println("");
    _UART1_.print("Connected to WiFi network with IP Address: ");
    _UART1_.println(WiFi.localIP());

    _UART1_.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop()
{
    // Send an HTTP POST request every 10 minutes
    if ((millis() - lastTime) > timerDelay)
    {
        // Check WiFi connection status
        if (WiFi.status() == WL_CONNECTED)
        {
            matrix.loadPixels(&wifiConnected[0][0], 8*12);
        }
        else
        {
            _UART1_.println("WiFi Disconnected");
        }
        lastTime = millis();
    }
}
