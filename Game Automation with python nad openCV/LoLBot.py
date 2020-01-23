import pyautogui as pg 
import ctypes
import time
import PIL as p
import random



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

def LevelUp():
    PressKey(0x1D)
    PressKey(Q)
    ReleaseKey(Q)
    PressKey(0x12)
    ReleaseKey(0x12)
    PressKey(0x11)
    ReleaseKey(0x11)
    PressKey(0x13)
    ReleaseKey(0x13)
    PressKey(0x1D)
    ReleaseKey(0x1D)

#to test
def RepeatAcceptMatch():
    x=0
    while(x<25):
        pg.moveTo(1000,700) # accept match
        pg.click()
        x=x+1
        pg.sleep(1)

def Move():
    PressKey(A)
    ReleaseKey(A)
    

def Click():
    pg.rightClick()
    pg.doubleClick()
    PressKey(0x101)
    ReleaseKey(0x101)

def UseSkills():
    pg.moveTo(1500,500)
    PressKey(Q)
    ReleaseKey(Q)
    pg.sleep(1)
    PressKey(E)
    ReleaseKey(E)
    PressKey(W)
    ReleaseKey(W)
    
    PressKey(R)
    ReleaseKey(R)

def GetStartingItems():
    PressKey(P)
    ReleaseKey(P)
    pg.sleep(0.25)
    pg.moveTo(400, 220)
    Click()
    pg.sleep(0.5)
    pg.rightClick()
    pg.rightClick()
    pg.sleep(2)
    pg.doubleClick()
    PressKey(P)
    ReleaseKey(P)
    pg.sleep(0.25)
    pg.moveTo(450, 220)
    Click()
    pg.sleep(0.5)
    pg.rightClick()
    pg.rightClick()
    pg.doubleClick()

def findMatch():
    pg.moveTo(450,200) # play
    pg.click()
    pg.sleep(2)
    pg.moveTo(450,250) # bot game
    pg.click()
    pg.sleep(1)
    pg.click(900,860) # find match
    pg.sleep(2)
    pg.click(900,860)
    pg.moveTo(1000,700) # accept match
    RepeatAcceptMatch()
    ChampSelect()

#champ select
def ChampSelect():
    pg.moveTo(1190,489) # random champ
    pg.click()
    pg.sleep(1)
    pg.moveTo(1000,750) # accept match
    pg.click()
    pg.moveTo(685,300) # random champ
    pg.click()
    pg.sleep(200)
    inGame()

def GameLoop():
    x = 1690
    y = 835
    x1 = 1710
    y1 = 850
    i=0
    while True:
        print(i)
        LevelUp()
        rand = random.uniform(0.1,1.2)
        randx1 = random.randint(x,x1)
        randx2 = random.randint(x,x1)
        randy1 = random.randint(y,y1)
        randy2 = random.randint(y,y1)
        pg.moveTo(randx1,randy1)
        Move()
        pg.sleep(rand)
        pg.moveTo(randx2,randy2)
        Move()
        pg.sleep(rand)
        if i%50 == 0:
            LevelUp()
            if(i>390):
                x=x+30
                x1=x1+30
        if i%10 == 0:
            UseSkills()
            a = pg.locateOnScreen('lol.png')
            if a != None:
                pg.sleep(4)
                pg.moveTo(1111,518)
                pg.doubleClick()
                pg.sleep(2)
                pg.moveTo(860,803)
                pg.doubleClick()
                findMatch()
        if i%100 == 0:
            pg.moveTo(x,y+30)
            PressKey(A)
            ReleaseKey(A)
            pg.sleep(5)
            PressKey(0x30)
            ReleaseKey(0x30)
            pg.sleep(9)
            GetItems()
        i=i+1
        print(i)

def GetItems():
    pg.sleep(4)
    PressKey(P)
    ReleaseKey(P)
    pg.sleep(1)
    pg.moveTo(370, 220)
    pg.sleep(1)
    Click()
    pg.sleep(1)
    pg.moveTo(500,500)
    PressKey(A)
    ReleaseKey(A)
    pg.sleep(2)
    PressKey(P)
    ReleaseKey(P)
    pg.sleep(1)
    pg.moveTo(450, 220)
    pg.sleep(2)
    Click()
    pg.sleep(2)
    pg.moveTo(500,500)

def inGame():
    pg.sleep(4)
    GetStartingItems()
    pg.sleep(2)
    GameLoop()


#main body
findMatch()
#ChampSelect()
#GetItems()
#inGame()


