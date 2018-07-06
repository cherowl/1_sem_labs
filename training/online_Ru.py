import speech_recognition as sr
import os
r = sr.Recognizer()
m = sr.Microphone()

systemMode = False
voiceOrder = " "
order = False



def getOrder():
    voiceOrder = " "
   
    try:
        #with m as source:
        #    r.adjust_for_ambient_noise(source)
        #print("Energy Threshold = {}".format(r.energy_threshold))
        #os.system('aplay en/audio/record/record.wav')
        with m as source:
            print('Listening')
            audio = r.listen(source, timeout =4)
        print("Recognizing your order...")
            # recognize speech using Google Speech Recognition
        #os.system('aplay en/audio/record/record.wav')
        voiceOrder = r.recognize_google(audio, language='ru-RU').__str__();
        print('voiceOrder = {}'.format(voiceOrder))
        voiceOrder = voiceOrder.lower()

        return voiceOrder
    except:
        print("UnknownValueError")
        return "None"
if __name__ == '__main__':
    print('message '+getOrder())