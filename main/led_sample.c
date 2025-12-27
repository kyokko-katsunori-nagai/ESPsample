/*
 * AWS IoT EduKit LED点灯サンプルプログラム
 * 
 * このプログラムは、AWS IoT EduKitに搭載されているLEDを制御します。
 * ボード上のLEDを点滅させ、動作確認を行います。
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

// AWS IoT EduKitのLED GPIO定義
#define LED_RED_GPIO    GPIO_NUM_4
#define LED_GREEN_GPIO  GPIO_NUM_5
#define LED_BLUE_GPIO   GPIO_NUM_6

// 点滅間隔（ミリ秒）
#define BLINK_INTERVAL_MS 1000

static const char *TAG = "LED_SAMPLE";

/**
 * @brief LED GPIOの初期化
 * 
 * LED用のGPIOピンを出力モードに設定し、初期状態をOFFにします。
 */
void led_init(void)
{
    ESP_LOGI(TAG, "LED GPIO初期化開始");
    
    // GPIOの設定構造体
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_RED_GPIO) | (1ULL << LED_GREEN_GPIO) | (1ULL << LED_BLUE_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    
    // GPIOの設定を適用
    gpio_config(&io_conf);
    
    // 初期状態：全てのLEDをOFF
    gpio_set_level(LED_RED_GPIO, 0);
    gpio_set_level(LED_GREEN_GPIO, 0);
    gpio_set_level(LED_BLUE_GPIO, 0);
    
    ESP_LOGI(TAG, "LED GPIO初期化完了");
}

/**
 * @brief 指定したLEDをON/OFFする
 * 
 * @param gpio_num LEDのGPIO番号
 * @param state LEDの状態（1: ON, 0: OFF）
 */
void led_set(gpio_num_t gpio_num, uint8_t state)
{
    gpio_set_level(gpio_num, state);
}

/**
 * @brief RGB LEDの色を設定
 * 
 * @param red 赤色LED（1: ON, 0: OFF）
 * @param green 緑色LED（1: ON, 0: OFF）
 * @param blue 青色LED（1: ON, 0: OFF）
 */
void led_set_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    gpio_set_level(LED_RED_GPIO, red);
    gpio_set_level(LED_GREEN_GPIO, green);
    gpio_set_level(LED_BLUE_GPIO, blue);
}

/**
 * @brief LED点滅タスク
 * 
 * 各色のLEDを順番に点滅させます。
 * - 赤色LED点灯
 * - 緑色LED点灯
 * - 青色LED点灯
 * - 白色（全色）点灯
 * - 黄色（赤+緑）点灯
 * - シアン（緑+青）点灯
 * - マゼンタ（赤+青）点灯
 * 
 * @param pvParameter タスクパラメータ（未使用）
 */
void led_blink_task(void *pvParameter)
{
    ESP_LOGI(TAG, "LED点滅タスク開始");
    
    uint8_t pattern = 0;
    
    while (1) {
        switch (pattern) {
            case 0:
                // 赤色LED点灯
                ESP_LOGI(TAG, "赤色LED点灯");
                led_set_rgb(1, 0, 0);
                break;
            case 1:
                // 緑色LED点灯
                ESP_LOGI(TAG, "緑色LED点灯");
                led_set_rgb(0, 1, 0);
                break;
            case 2:
                // 青色LED点灯
                ESP_LOGI(TAG, "青色LED点灯");
                led_set_rgb(0, 0, 1);
                break;
            case 3:
                // 白色（全色）点灯
                ESP_LOGI(TAG, "白色LED点灯");
                led_set_rgb(1, 1, 1);
                break;
            case 4:
                // 黄色（赤+緑）点灯
                ESP_LOGI(TAG, "黄色LED点灯");
                led_set_rgb(1, 1, 0);
                break;
            case 5:
                // シアン（緑+青）点灯
                ESP_LOGI(TAG, "シアンLED点灯");
                led_set_rgb(0, 1, 1);
                break;
            case 6:
                // マゼンタ（赤+青）点灯
                ESP_LOGI(TAG, "マゼンタLED点灯");
                led_set_rgb(1, 0, 1);
                break;
            case 7:
                // 全消灯
                ESP_LOGI(TAG, "全LED消灯");
                led_set_rgb(0, 0, 0);
                break;
        }
        
        // 次のパターンへ
        pattern = (pattern + 1) % 8;
        
        // 待機
        vTaskDelay(BLINK_INTERVAL_MS / portTICK_PERIOD_MS);
    }
}

/**
 * @brief アプリケーションのメインエントリポイント
 */
void app_main(void)
{
    ESP_LOGI(TAG, "AWS IoT EduKit LED点灯サンプル起動");
    
    // LED初期化
    led_init();
    
    // LED点滅タスクの作成
    xTaskCreate(
        led_blink_task,      // タスク関数
        "led_blink_task",    // タスク名
        2048,                // スタックサイズ
        NULL,                // パラメータ
        5,                   // 優先度
        NULL                 // タスクハンドル
    );
    
    ESP_LOGI(TAG, "LED点滅タスク作成完了");
}
