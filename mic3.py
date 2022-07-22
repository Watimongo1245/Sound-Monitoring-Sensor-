import pyaudio
import audioop
import math
import wave
from time import sleep
import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish

chunk = 1024 * 2 
format1 = pyaudio.paInt16
channels1 = 1
rate1 = 44100
record_secs = 2
#dev_index = 1
wav_output_filename = 'waves.wav'

Broker = "192.168.43.141"
sub_topic = "mic/spldb"

p = pyaudio.PyAudio()

stream = p.open(format=format1,
                channels= channels1,
                rate = rate1,
                input = True,
                frames_per_buffer=chunk)
print("Startin....")
frames = []

for i in range(0,int(rate1/chunk*record_secs)):
    data = stream.read(chunk,exception_on_overflow=False)
    print('Appending')
    frames.append(data)
    rms = audioop.rms(data,2)
    db = 20*math.log10(rms/20)
    db = round(db,2)
    SPLdb = -52+db+94-30
    SPLdb = round(SPLdb,2)
    print(rms)
    #print(SPLdb)
    mqttc = mqtt.Client("node-red")
    mqttc.connect(Broker,1883,60)
    mqttc.publish(sub_topic,db)
print('Stop..')    
stream.stop_stream()
stream.close()
p.terminate()

wavefile=wave.open(wav_output_filename,'wb')
wavefile.setnchannels(channels1)
wavefile.setsampwidth(p.get_sample_size(pyaudio.paInt16))
wavefile.setframerate(rate1)
wavefile.writeframes(b''.join(frames))
wavefile.close()
