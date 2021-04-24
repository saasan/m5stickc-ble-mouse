#include <M5StickC.h>
#include <BleMouse.h>

// -----------------------------------------------------------------------------
// 定数
// -----------------------------------------------------------------------------
// 電源ボタンが1秒未満押された
const uint8_t AXP_WAS_PRESSED = 2;

// -----------------------------------------------------------------------------
// 変数
// -----------------------------------------------------------------------------
// ESP32-BLE-Mouse
BleMouse bleMouse;
// Bluetooth接続済み
bool isConnected = false;

// -----------------------------------------------------------------------------
// 関数
// -----------------------------------------------------------------------------
// 画面を消去する
void clearScreen() {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(0, 0);
}

void setup() {
    M5.begin();

    // 画面の表示設定
    M5.Lcd.setRotation(1);
    M5.Lcd.setTextFont(2);
    clearScreen();
    M5.Lcd.println("M5StickC-BLE-Mouse");

    // Bluetooth接続
    bleMouse.begin();
}

void loop() {
    M5.update();

    // 電源ボタンが押されたらリセット
    if (M5.Axp.GetBtnPress() == AXP_WAS_PRESSED) {
        esp_restart();
    }

    if (bleMouse.isConnected()) {
        // Bluetooth接続済みの場合

        if(!isConnected) {
            // Bluetooth接続されたらメッセージを表示
            clearScreen();
            M5.Lcd.println("Connected!");
            isConnected = true;
        }

        // マウスを動かす
        bleMouse.move(1, 0);
        delay(100);
        bleMouse.move(-1, 0);

        // 60秒待つ
        delay(60 * 1000);
    }
    else {
        // Bluetooth未接続の場合

        if(isConnected) {
            // Bluetooth切断されたら画面をクリア
            clearScreen();
            isConnected = false;
        }

        // Bluetooth未接続の場合は5秒待つ
        M5.Lcd.println("Waiting 5 seconds...");
        delay(5000);
    }
}
