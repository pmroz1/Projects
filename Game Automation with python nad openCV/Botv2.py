import pyautogui as pg 
import ctypes
import time
from PIL import Image
from PIL import ImageGrab
import random
import cv2
import numpy as np
from mss import mss

print("Succesful module import")
SendInput = ctypes.windll.user32.SendInput
W = 0x11
A = 0x1E
S = 0x1F
D = 0x20
P = 0x19
Q = 0x10
E = 0x12
R = 0x13
# C struct redefinitions 
PUL = ctypes.POINTER(ctypes.c_ulong)
class KeyBdInput(ctypes.Structure):
    _fields_ = [("wVk", ctypes.c_ushort),
                ("wScan", ctypes.c_ushort),
                ("dwFlags", ctypes.c_ulong),
                ("time", ctypes.c_ulong),
                ("dwExtraInfo", PUL)]

class HardwareInput(ctypes.Structure):
    _fields_ = [("uMsg", ctypes.c_ulong),
                ("wParamL", ctypes.c_short),
                ("wParamH", ctypes.c_ushort)]

class MouseInput(ctypes.Structure):
    _fields_ = [("dx", ctypes.c_long),
                ("dy", ctypes.c_long),
                ("mouseData", ctypes.c_ulong),
                ("dwFlags", ctypes.c_ulong),
                ("time",ctypes.c_ulong),
                ("dwExtraInfo", PUL)]

class Input_I(ctypes.Union):
    _fields_ = [("ki", KeyBdInput),
                 ("mi", MouseInput),
                 ("hi", HardwareInput)]

class Input(ctypes.Structure):
    _fields_ = [("type", ctypes.c_ulong),
                ("ii", Input_I)]

# Actuals Functions

def PressKey(hexKeyCode):
    extra = ctypes.c_ulong(0)
    ii_ = Input_I()
    ii_.ki = KeyBdInput( 0, hexKeyCode, 0x0008, 0, ctypes.pointer(extra) )
    x = Input( ctypes.c_ulong(1), ii_ )
    ctypes.windll.user32.SendInput(1, ctypes.pointer(x), ctypes.sizeof(x))

def ReleaseKey(hexKeyCode):
    extra = ctypes.c_ulong(0)
    ii_ = Input_I()
    ii_.ki = KeyBdInput( 0, hexKeyCode, 0x0008 | 0x0002, 0, ctypes.pointer(extra) )
    x = Input( ctypes.c_ulong(1), ii_ )
    ctypes.windll.user32.SendInput(1, ctypes.pointer(x), ctypes.sizeof(x))

if __name__ == '__main__':
    PressKey(0x11)
    time.sleep(1)
    ReleaseKey(0x11)
    time.sleep(1)

print("C structures initialilzed")
print("Video Capture")

def ChampSelect():
    while(True):
        bot_v =  ImageGrab.grab(bbox=(0,0,1280,719))
        rgb = np.array(bot_v)
        captured = cv2.cvtColor(rgb, cv2.COLOR_BGR2GRAY)
        cv2.imwrite('captured.png',captured)

        img_bgr = cv2.imread('captured.png')
        img_grey = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)
        template = cv2.imread('olaf.png', 0)

        w,h = template.shape[::-1]
        w,h = shop.shape[::-1]

        res = cv2.matchTemplate(img_grey,template,cv2.TM_CCOEFF_NORMED)

        threshold = 0.8
        loc = np.where(res >= threshold)

        for pt in zip(*loc[::-1]):
            cv2.rectangle(img_bgr, pt, (pt[0]+w, pt[1]+h), (0,255,255), 2)


        printscreen_numpy =  np.array(bot_v,  np.uint8)\
        .reshape((bot_v.size[1],bot_v.size[0],3))
        cv2.imshow('Bot_vision',img_bgr)

        posx = loc[0]
        posy = loc[1]
    
        click_pos = (posy[1] + 15,posx[0] + 15)

        print(click_pos)
        if cv2.waitKey(25) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            break

    pg.moveTo(click_pos)

def Game():
    while(True):
        bot_v =  ImageGrab.grab(bbox=(0,0,1024,768))
        rgb = np.array(bot_v)
        captured = cv2.cvtColor(rgb, cv2.COLOR_BGR2GRAY)

        cv2.imwrite('captured.png',captured)
        img_bgr = cv2.imread('captured.png')
        img_grey = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)
        player = cv2.imread('minionhp.png', 0)

        w,h = player.shape[::-1]

        res = cv2.matchTemplate(img_grey,player,cv2.TM_CCOEFF_NORMED)
        threshold = 0.9
        loc = np.where(res >= threshold)
        
        for pt in zip(*loc[::-1]):
            #Acts for every detection
            posx = loc[0]
            posy = loc[1]
            pg.doubleClick()
            pg.moveTo(posy[1] + 15,posx[0] + 15)
            PressKey(A)
            ReleaseKey(A)
            cv2.rectangle(img_bgr, pt, (pt[0]+w, pt[1]+h), (0,255,255), 2)
            print(pt)


        printscreen_numpy =  np.array(bot_v,  np.uint8)\
        .reshape((bot_v.size[1],bot_v.size[0],3))
        cv2.imshow('Bot_vision',img_bgr)

        if cv2.waitKey(25) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            break

Game()