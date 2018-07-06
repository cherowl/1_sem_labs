import speech_recognition as sr
import os
r = sr.Recognizer()
m = sr.Microphone()

systemMode = False
voiceOrder = " "
order = False

script_dir = (os.getcwd())


def getOrder():
    voiceOrder = " "

    try:
        #with m as source:
        #    r.adjust_for_ambient_noise(source)
        #print("Energy Threshold = {}".format(r.energy_threshold))
        #os.system('aplay {}/en/audio/record/record.wav'.format(script_dir))
        with m as source:
            print('Listening')
            audio = r.listen(source, timeout =2, phrase_time_limit=2)
        print("Recognizing your order...")
            # recognize speech using Google Speech Recognition
        #os.system('aplay {}/en/audio/record/record.wav'.format(script_dir))

        voiceOrder = r.recognize_google(audio).__str__();
        #print(111)
        voiceOrder = voiceOrder.lower()
        print('voiceOrder = {}'.format(voiceOrder))

        return voiceOrder
    except:
        print("UnknownValueError")
        return "None"
if __name__ == '__main__':
    for i in range(100):
        print('message '+getOrder())
