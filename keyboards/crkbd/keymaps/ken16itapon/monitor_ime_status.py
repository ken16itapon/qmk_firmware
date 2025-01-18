import time
import ctypes
from ctypes import wintypes
import pystray
from pystray import MenuItem as item
from PIL import Image, ImageDraw
import threading
import hid  # HIDライブラリ

# Windows APIの設定
user32 = ctypes.WinDLL('user32', use_last_error=True)
imm32 = ctypes.WinDLL('imm32', use_last_error=True)

# HIMCを定義
HIMC = ctypes.c_void_p

user32.GetForegroundWindow.restype = wintypes.HWND
imm32.ImmGetContext.restype = HIMC
imm32.ImmGetConversionStatus.argtypes = [HIMC, ctypes.POINTER(wintypes.DWORD), ctypes.POINTER(wintypes.DWORD)]

def get_ime_status():
    """IMEのオン/オフ状態を取得"""
    hwnd = user32.GetForegroundWindow()
    hIMC = imm32.ImmGetContext(hwnd)
    if not hIMC:
        return None
    conversion = wintypes.DWORD()
    sentence = wintypes.DWORD()
    result = imm32.ImmGetConversionStatus(hIMC, ctypes.byref(conversion), ctypes.byref(sentence))
    imm32.ImmReleaseContext(hwnd, hIMC)
    if result:
        return "ON" if conversion.value & 1 else "OFF"
    return None

def send_to_qmk(status):
    """QMKキーボードに状態を送信"""
    try:
        # QMKのHIDデバイスを開く（VIDとPIDはQMK側で設定されたものに変更）
        device = hid.device()
        device.open(0x4653, 0x0004)  # 仮のVID/PID、実際の値に置き換える
        device.write([0x00, 0x01 if status == "ON" else 0x00])  # IME ON=0x01, OFF=0x00
        device.close()
        print(f"QMKに送信しました: {status}")
    except Exception as e:
        print(f"通信エラー: {e}")

class IMEWatcher:
    def __init__(self):
        self.last_status = None
        self.running = True

    def monitor(self):
        """IME状態を監視"""
        while self.running:
            current_status = get_ime_status()
            if current_status != self.last_status:
                print(f"IME Status Changed: {current_status}")
                send_to_qmk(current_status)
                self.last_status = current_status
            time.sleep(0.5)  # チェック間隔を0.5秒に設定

    def stop(self):
        """監視を停止"""
        self.running = False

def create_image():
    """システムトレイアイコンを生成"""
    image = Image.new('RGB', (64, 64), (255, 255, 255))
    draw = ImageDraw.Draw(image)
    draw.rectangle((0, 0, 64, 64), fill=(0, 128, 255))
    return image

def main():
    watcher = IMEWatcher()
    thread = threading.Thread(target=watcher.monitor)
    thread.daemon = True

    def on_start(icon):
        print("IME監視を開始します...")
        thread.start()

    def on_stop(icon):
        print("IME監視を停止します...")
        watcher.stop()
        icon.stop()

    icon = pystray.Icon(
        "IME Monitor",
        create_image(),
        menu=pystray.Menu(
            item("Start Monitoring", on_start),
            item("Quit", on_stop)
        )
    )
    icon.run()

if __name__ == "__main__":
    main()
