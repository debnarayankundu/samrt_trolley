
# 🛒 Smart Trolley with Automated Billing

This project demonstrates a **Smart Trolley System** using **RFID** technology, an **Arduino Uno**, **LCD display**, **Bluetooth module**, and **buttons** to automate item addition/removal and billing in a retail store. It’s powered using a portable power bank.

## 📸 Project Overview

![Smart Trolley Hardware]


![WhatsApp Image 2025-04-09 at 21 21 03_d50fa4c1](https://github.com/user-attachments/assets/c7f0bb7f-0645-42ad-9c4a-b5ffd7e3c9ab)

---

## 🔧 Components Used

- Arduino Uno
- RFID-RC522 Reader
- RFID Tags
- 16x2 LCD Display
- Bluetooth Module (SoftwareSerial via A2, A3)
- Push Buttons (Add & Remove)
- Buzzer (optional)
- Breadboard & Jumper Wires
- Power Bank for portability

---

## ⚙️ How It Works

1. **Scan RFID Tag:** When a tag is scanned, it checks if it matches a predefined item (e.g., Salt, Milk).
2. **Add/Remove Option:** LCD shows “Add / Remove”. Press the respective button:
   - **Add Button:** Adds item to cart and updates total.
   - **Remove Button:** Removes item from cart if previously added.
3. **LCD Display:** Shows the item added/removed and total bill.
4. **Bluetooth Output:** Sends billing updates to a connected Bluetooth device (e.g., phone).
5. **Persistent Tracking:** Avoids double-counting same RFID unless removed first.

---

## 🧠 Code Functionality

- `struct Item`: Stores item name, RFID tag ID, and price.
- Uses RFID UID to identify and validate items.
- Buttons control item operations.
- Total bill updates in real time and displays via LCD & Bluetooth.
- Scanned items are tracked to ensure correct billing and removal.

---

## 💻 Arduino Libraries Used

```cpp
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
```

---

## 🛠️ Setup Instructions

1. Connect components as per the circuit.
2. Upload the provided Arduino code.
3. Power the circuit using USB or a power bank.
4. Scan tags and test add/remove functions.
5. Monitor total on LCD or via Bluetooth terminal app.

---

## 📽️ Demo Video

📹 Video file uploaded separately as ("/demostration.mp4").

---

## 📋 Future Improvements

- Support for multiple trolleys (multi-cart system)
- Integration with cloud database 
- Barcode/QR support
- Auto-checkout with payment gateway

---
## bluetooth app 

![image](https://github.com/user-attachments/assets/ab48aad8-0ba8-4356-a085-3b6d0d1bccbc)


![image](https://github.com/user-attachments/assets/8d3853cd-0ef9-4595-8608-6f47f5dd50e8)





