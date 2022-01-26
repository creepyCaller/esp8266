/** 
 *  数字针脚(Digital Pin):
 *  *只有两个状态: 开(3.3V)、关(0V|GND)
 *  D0  = 16
 *  D1  = 5
 *  D2  = 4
 *  D3  = 0 // 上拉
 *  D4  = 2 // 上拉
 *  D5  = 14
 *  D6  = 12
 *  D7  = 13
 *  D8  = 15 // 下拉
 *  D9  = 3
 *  D10 = 1
 *  控制函数:
 *  int Enum Mode {INPUT = 0, OUTPUT = 1}
 *  int Enum Value {LOW = 0, HIGH = 1}
 *  
 *  void pinMode(int 针脚序号, Mode 模式)
 *  void digitalWirte(int 针脚序号, Value 值)
 *  Value digitalRead(int 针脚序号)
 *  
 *  pinMode(d0, OUTPUT) // 定义D0针脚定义为输出
 *  digitalWrite(d0, HIGH) // 令针脚D0通电
 *  digitalWrite(d0, LOW) // 令针脚D0不通电
 *  pinMode(d0, INPUT) // 定义D0针脚定义为输入
 *  int d0_status = digitalRead(d0) // 读取针脚D0的状态
 *  思想:
 *  ESP主要是负责控制，不直接为设备工作供电着想，针脚提供的电流极小。
 *  使用继电器，它将连接供电线路。ESP连接控制电路。
 *  注意：
 *  数字针脚收到高电平信号，值变为1之后，不连接地的话是不会变成0的，如果要实现自动重置，则需要下拉电阻，这块板只有d8是有下拉电阻。
 *  下拉电阻连接到地。
 *  上拉电阻连接到3.3V
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//#define USE_MDNS

#ifndef STASSID
#define STASSID "wifi_ssid"
#define STAPSK "wifi_pass"
#endif

const char* WiFiSSID = STASSID;
const char* WiFiPSK = STAPSK;
const unsigned long BAUD_RATE = 115200;

ESP8266WebServer server(80);

void initWiFi();
void initmDNS();
void setController();

void initWiFi() {
  Serial.print("starting connect WiFi");
  WiFi.begin(WiFiSSID, WiFiPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected, IP address=");
  Serial.println(WiFi.localIP());
}

void initmDNS() {
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  } else {
    Serial.println("MDNS responder start failed");
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // 这个灯的低电平是开高电平是关
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(BAUD_RATE);
  Serial.println();
  initWiFi();
  #ifdef USE_MDNS
  initmDNS();
  #endif
  setController();
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  server.handleClient();
  #ifdef USE_MDNS
  MDNS.update();
  #endif
}
