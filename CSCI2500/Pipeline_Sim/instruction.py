# -*- coding: utf-8 -*-
"""
Created on Mon Nov 25 13:28:40 2019

@author: Xerox
Basic class for storing standardized instruction data
"""
from copy import deepcopy
#I'm not sure that we need this, so I'll prob just delete later
R_Types = ["add, and, or, slt"]

#"add $t0,$s2,$s3"
#loop:
#sub $s1,$t0,5899898798
#bne $t8,$zero,loop

#Convert $zero to '0' when found
class Instruction(object):

    def __init__(self, instr_string):
        self.delayed=False
        self.cycle_states = ['.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'] #Size of max cycles
        self.full_instr = instr_string
        self.till_dead = -1
        self.dead = False
        if instr_string != "nop":
            split_instr = instr_string.split(" ")
            self.operation = split_instr[0]

            split_regs = split_instr[1].split(",")
            
            #DEFAULT NOTATION
            if self.operation not in ("beq", "bne"):
                self.isBranch = False
                self.RD = split_regs[0]
                self.RS = split_regs[1]

                if(len(split_regs) == 3):
                    self.RT = split_regs[2]
                else:
                    self.RT = ""

            #BRANCH NOTATION
            else:
                self.isBranch = True
                self.RD = split_regs[2]
                self.RS = split_regs[0]
                self.RT = split_regs[1]

            self.type = None

            if self.RS == "$zero":
                self.RS = "0"
            if self.RT == "zero":
                self.RS = "0"
        else:
            self.isBranch = False
            self.RD = 0
            self.RS = 0
            self.RT = 0


    def __str__(self):
        instr_string = "{:20s}".format(self.full_instr)
        
        for state in range(len(self.cycle_states)):
            if state < len(self.cycle_states) - 1:
                instr_string += "{:4s}".format(self.cycle_states[state])
            else:
                instr_string += self.cycle_states[state]
        return instr_string
    
    def update(self, cycle, stage):  # cycle is an int, stage is a string
        if self.dead == True:
            to_add = "*"
        else:
            to_add = stage

        self.cycle_states[cycle] = to_add

    def make_nop(self, cycle):  # for when we push nops, the plan is to copy the instruction its based on and then nop it
        temp = Instruction("nop")
        temp.dead = True
        temp.cycle_states = deepcopy(self.cycle_states)
        temp.cycle_states[cycle]="ID"
        return temp


