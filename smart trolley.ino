#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


#define SS_PIN 10
#define RST_PIN A0
MFRC522 mfrc522(SS_PIN, RST_PIN);


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


SoftwareSerial BTSerial(A2, A3);  // RX, TX

#define ADD_BUTTON 8
#define REMOVE_BUTTON 9


struct Item {
  String name;
  String rfid;
  int price;
};

const int itemCount = 2;
Item itemList[itemCount] = {
  {"Salt", "73 62 02 29", 100},
  {"Milk", "03 06 DB 13", 50},
};

int totalBill = 0;
String scannedItems[10];
int scannedCount = 0;

void setup() {
  Serial.begin(9600);        
  BTSerial.begin(9600);      
  SPI.begin();               
  mfrc522.PCD_Init();

  lcd.begin(16, 2);
  showMessage("Smart Trolley", "");
  delay(2000);
  lcd.clear();

  pinMode(ADD_BUTTON, INPUT_PULLUP);
  pinMode(REMOVE_BUTTON, INPUT_PULLUP);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String tagID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    tagID += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    tagID += String(mfrc522.uid.uidByte[i], HEX);
  }
  tagID.toUpperCase();
  tagID.trim();

  bool itemFound = false;
  for (int i = 0; i < itemCount; i++) {
    if (tagID == itemList[i].rfid) {
      itemFound = true;
      showMessage("Scan: " + itemList[i].name, "Add / Remove");

      bool decisionMade = false;
      while (!decisionMade) {
        if (digitalRead(ADD_BUTTON) == LOW) {
          totalBill += itemList[i].price;
          scannedItems[scannedCount++] = tagID;

          showMessage(itemList[i].name + " Added", "");
          BTSerial.println(itemList[i].name + " Added:  Rs "+itemList[i].price);
          BTSerial.println(": ₹" + String(totalBill));

          decisionMade = true;
          delay(1000);
        } else if (digitalRead(REMOVE_BUTTON) == LOW) {
          if (isItemScanned(tagID)) {
            totalBill -= itemList[i].price;
            removeScannedItem(tagID);

            showMessage(itemList[i].name + " Removed", "");
            BTSerial.println(itemList[i].name + " Removed:  Rs "+itemList[i].price);
            BTSerial.println(": " + String(totalBill));
          } else {
            showMessage("Item Not Found", "In Cart");
          }
          decisionMade = true;
          delay(1000);
        }
      }
      break;
    }
  }

  if (!itemFound) {
    showMessage("Unknown Item", "");
    delay(1500);
  }

  showMessage("Total: Rs " + String(totalBill), "");
  delay(1500);
}

void showMessage(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void removeScannedItem(String tagID) {
  for (int i = 0; i < scannedCount; i++) {
    if (scannedItems[i] == tagID) {
      for (int j = i; j < scannedCount - 1; j++) {
        scannedItems[j] = scannedItems[j + 1];
      }
      scannedCount--;
      break;
    }
  }
}

bool isItemScanned(String tagID) {
  for (int i = 0; i < scannedCount; i++) {
    if (scannedItems[i] == tagID) {
      return true;
    }
  }
  return false;
}
