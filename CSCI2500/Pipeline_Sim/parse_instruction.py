# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 13:47:00 2019

@author: Xerox
Script that will read in each instruction
"""

from instruction import Instruction


#Return an array of instruction objects read in from a file
#Filename should be read in from command line
def parse_instructions(filename):
    instructions_list = []
    next_index = 1
    
    file = open(filename, 'r', encoding = "utf-8")
    for line in file:
        #HIT A LABEL (All labels end in ':')
        if line.strip()[-1] == ':': 
            #Do Shit with the labels dictionary
            continue
        
        instructions_list.append(Instruction(line.strip()))
        next_index-=-1
    file.close()
    return instructions_list
        

if __name__ == "__main__":
    filename = input("Filename ==> ")
    l = parse_instructions(filename)
    for instr in l:
        print(instr)
    