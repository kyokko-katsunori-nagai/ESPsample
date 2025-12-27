# AWS IoT EduKit LED点灯サンプルプログラム

## 概要
このプロジェクトは、AWS IoT EduKitに搭載されているRGB LEDを制御するサンプルプログラムです。
各色のLEDを順番に点滅させ、デバイスの動作確認を行います。

## 必要な環境
- AWS IoT EduKit（ESP32ベース）
- ESP-IDF v4.4以降
- USB Type-Cケーブル

## ハードウェア仕様
- 使用デバイス: AWS IoT EduKit
- マイコン: ESP32-WROVER
- LED: RGB LED（共通アノード）
  - 赤色LED: GPIO4
  - 緑色LED: GPIO5
  - 青色LED: GPIO6

## ビルド方法

### 1. ESP-IDFの環境設定
```bash
# Windows PowerShell
. $env:IDF_PATH\export.ps1
```

### 2. プロジェクトのビルド
```bash
cd c:\workspace\testESP
idf.py build
```

### 3. デバイスへの書き込み
```bash
idf.py -p COMx flash monitor
```
※ COMxは実際のシリアルポート番号に置き換えてください

## 動作説明
プログラムを実行すると、以下の順序でLEDが1秒間隔で点灯します：

1. 赤色LED点灯
2. 緑色LED点灯
3. 青色LED点灯
4. 白色（全色）点灯
5. 黄色（赤+緑）点灯
6. シアン（緑+青）点灯
7. マゼンタ（赤+青）点灯
8. 全LED消灯

このパターンを繰り返します。

## カスタマイズ
`led_sample.c`内の以下の定数を変更することで、動作をカスタマイズできます：

- `BLINK_INTERVAL_MS`: LED点滅間隔（ミリ秒）
- `LED_RED_GPIO`, `LED_GREEN_GPIO`, `LED_BLUE_GPIO`: LEDのGPIOピン番号

## トラブルシューティング

### デバイスが認識されない
- USBケーブルが正しく接続されているか確認
- デバイスドライバがインストールされているか確認

### ビルドエラー
- ESP-IDFが正しくインストールされているか確認
- 環境変数が正しく設定されているか確認

## ライセンス
MIT License

## 作成日
2025年12月27日
