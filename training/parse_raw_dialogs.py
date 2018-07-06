# -*- coding: utf-8 -*-
import sys
import re

in_file = "./dialog_unformated.txt" # should exists
out_file = "./dialog.txt"

with open(in_file, 'r') as source:
    with open(out_file, 'a') as formated:
        for line in source:
            for pattern in [
                r'^(.*):\s',                
                r'^—\s',
                r'^-\s',
                chr(45), 
                chr(150), 
                chr(151),                 
                chr(45)+'\s', # минус
                chr(150)+'\s', # короткий дефис
                chr(151)+'\s' # длинный дефис
                ]:
                line = re.sub( 
                    pattern=pattern,    
                    repl='',
                    string=line, 
                    flags=
                        re.VERBOSE
                        | re.IGNORECASE 
                        | re.MULTILINE # Специальные символы ^ и $ соответствуют началу и концу каждой строки
                        | re.ASCII
                )
            formated.write(line)   
        formated.close()
    source.close()
