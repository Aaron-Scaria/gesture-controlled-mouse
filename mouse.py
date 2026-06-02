import serial
import pyautogui

ser = serial.Serial('COM11', 9600)

pyautogui.FAILSAFE = True

while True:
    try:
        line = ser.readline().decode().strip()
        print(line)

        if "X:" in line:

            data = line.split(',')

            ax = float(data[0].split(':')[1])
            ay = float(data[1].split(':')[1])
            btn = int(data[3].split(':')[1])

            move_x = int(ax * 50)
            move_y = int(ay * 50)

            pyautogui.moveRel(move_x, -move_y)

            # RIGHT CLICK
            if btn == 0:
                pyautogui.leftClick()

    except:
        pass
