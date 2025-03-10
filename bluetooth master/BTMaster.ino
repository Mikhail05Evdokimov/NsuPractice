#include "BluetoothSerial.h"

String device_name = "ESP32-watch";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name, true);  //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  //Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

static bool connected = false;
uint8_t address[6] = { 0x30, 0xC9, 0x22, 0x31, 0xF0, 0xAE }; 
//30:C9:22:31:F0:AE

void loop() {
  
  if (connected) {
    Serial.println("connected");
    SerialBT.write('a');
  }
  else {
    connected = SerialBT.connect(address);//("ESP-32");
  }
  //if (Serial.available()) {
    //SerialBT.write(Serial.read());
  //}
  Serial.println("not connected");
  
  //delay(100);
}
