import serial
import csv
import time

port = "COM4"
baud_rate = 115200
output_file = "raw_ppg_1.csv"

ser = serial.Serial(port, baud_rate)
time.sleep(2)

with open(output_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "IR Value"])

    try:
        print("Penyimpanan akan dimulai setelah 10 detik...")
        time.sleep(10)
        print("Penyimpanan dimulai...")

        start_time = time.time()
        while time.time() - start_time < 60:
            line = ser.readline().decode('utf-8').strip()
            print(line)

            data = line.split(",")

            timestamp = round(time.time() - start_time, 2)
            writer.writerow([timestamp] + data)

        print("Penyimpanan selesai.")
    except KeyboardInterrupt:
        print("Penyimpanan dihentikan oleh pengguna.")
    finally:
        ser.close()
