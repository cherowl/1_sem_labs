# -*- coding: utf-8 -*-
import os
import sys
import random
import speech_recognition as sr
# import logging

from chatterbot.trainers import ListTrainer, ChatterBotCorpusTrainer
from chatterbot import ChatBot
from chatterbot.comparisons import synset_distance, levenshtein_distance

r = sr.Recognizer()

# Enable info level logging
# logging.basicConfig(level=logging.INFO)

ifdontknow = open('ifdontknow.txt', 'r').read().splitlines()
# for i in ifdontknow:
#     print(i)

chatbot = ChatBot('Bot')
try:
    choice = input("To train press 1, to start conversation - 2: ")
    if(int(choice) == 1):
        chatbot = ChatBot(
            'Bot', 
            database='./my.sqlite3',
            logic_adapters=[
                {
                    'import_path': "chatterbot.logic.BestMatch"
                }
            ],
            response_selection='chatterbot.get-first-get_random_response'
        )
        chatbot.set_trainer(ChatterBotCorpusTrainer)
        chatbot.train('chatterbot.corpus.russian')

        chatbot.set_trainer(ListTrainer)
        for file in ['dialog.txt', 'learning.txt', 'hurtful.txt', 'joke.txt']:
        # for file in ['add.txt', 'learning.txt' ]:    
            chats = open(file,'r').readlines()
            chatbot.train(chats)

    if(int(choice) == 2):
        chatbot = ChatBot(
            'Bot', 
            trainer='chatterbot.trainers.ListTrainer',
            database='./my.sqlite3',
            logic_adapters=[
                {
                    'import_path': "chatterbot.logic.BestMatch"
                # 'import_path':"chatterbot.logic.MathematicalEvaluation",
                # 'import_path':"chatterbot.logic.TimeLogicAdapter",
                },
                # {
                    # 'import_path': 'chatterbot.logic.LowConfidenceAdapter',
                    # 'threshold': 0.7,
                    # 'default_response': random.choice(ifdontknow),
                # },
            ],
            response_selection='chatterbot.get-first-get_random_response',
            read_only = True
        )
        # Let's start a conversation
        while True:
            try:       
                phrase = input("Person: ")
                response = chatbot.get_response(phrase)  
                if response.confidence > 0.70:
                    print('Bot: {}'.format(response))

                else:
                    print('Bot: {}'.format(random.choice(ifdontknow)))
            except (KeyboardInterrupt, EOFError, SystemExit):
                break
    
except UnDefinedError:
    print("Something going wrong")
    sys.exit(1)