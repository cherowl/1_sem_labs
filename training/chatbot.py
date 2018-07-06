# -*- coding: utf-8 -*-
from chatterbot.trainers import ListTrainer
from chatterbot import ChatBot
#import logging

import speech_recognition as sr
import os
import tts_Engin
import online_En
import online_Ru
r = sr.Recognizer()
m = sr.Microphone()

systemMode = False
voiceOrder = " "
order = False
script_dir = (os.getcwd())


def getOrder():
    voiceOrder = " "

'''
This is an example showing how to train a chat bot using the
ChatterBot Corpus of conversation dialog.
'''
# Enable info level logging
#logging.basicConfig(level=logging.INFO)

chatbot = ChatBot(
    'SkyCenterBot', 
    #trainer='chatterbot.trainers.ListTrainer'
    # database='./db_SkyBot.sqlite3',
    database='./db.sqlite3',
    # logic_adapters=[
    #     "chatterbot.logic.MathematicalEvaluation",
    #     "chatterbot.logic.TimeLogicAdapter",
    #     "chatterbot.logic.BestMatch"
    # ],
    #input_adapter="chatterbot.input.TerminalAdapter",
    #output_adapter="chatterbot.output.TerminalAdapter"
)

chatbot.set_trainer(ListTrainer)

# Start by training our bot with the ChatterBot corpus data
# for file in ['corpus.txt', 'learning.txt', 'dialog.txt']:
#     chats = open(file,'r').readlines()
#     chatbot.train(chats)

# Now let's get a response to a greeting
while True:
    try:
        input = online_Ru.getOrder()
        response = chatbot.get_response(input)
        # phrase = input("Person: ")
        # response = chatbot.get_response(phrase)   
        if response.confidence > 0.50:
            print('Bot : {}'.format(response))
            
            tts_Engin.play('{}'.format(response),'ru')
        else:
            print("Bot: Не знаю, что и сказать")
            tts_Engin.play('Не знаю, что и сказать','ru')    
    except (KeyboardInterrupt, EOFError, SystemExit):
        break