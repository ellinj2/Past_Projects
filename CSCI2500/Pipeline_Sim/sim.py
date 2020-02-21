global register_data, pipeline_registers, pipeline_history, all_instructions, cycle_count, max_cycle_count, next_instruction_index, control, branch_labels
import sys
import CLA
from instruction import Instruction
from Control import Control
from pipereg import PipeReg

register_data = {
        "$s0": 0,
        "$s1": 0,
        "$s2": 0,
        "$s3": 0,
        "$s4": 0,
        "$s5": 0,
        "$s6": 0,
        "$s7": 0,
        "$t0": 0,
        "$t1": 0,
        "$t2": 0,
        "$t3": 0,
        "$t4": 0,
        "$t5": 0,
        "$t6": 0,
        "$t7": 0,
        "$t8": 0,
        "$t9": 0
    } 
branch_labels = dict()
pipeline_registers = list()
pipeline_history = list()
all_instructions = list()

cycle_count = -1
max_cycle_count = 16
next_instruction_index = -1


def ALU(instr):
    #print("Running:", instr.full_instr)
    if instr.dead:
        return
    if instr.full_instr == "nop":
        return
    if instr is None:
        return
    if type(instr) is not Instruction:
        raise Exception ("The variable being passed into the ALU is not an instruction!")

    first=0
    second=0
    if instr.RS=="$zero":
        first=0
    elif instr.RS not in register_data:
        first=int(instr.RS)
    else:
        first=int(register_data[instr.RS])
    if instr.RT=="$zero":
        second=0
    elif instr.RT not in register_data:
        second=int(instr.RT)
    else:
        second=int(register_data[instr.RT])
    if instr.operation not in ("beq", "bne"):
        if instr.operation=="add" or instr.operation=="addi":
            register_data[instr.RD]=first+second
        elif instr.operation=="and" or instr.operation=="andi":
            register_data[instr.RD]=first&second
        elif instr.operation=="or" or instr.operation=="ori":
            register_data[instr.RD]=first|second
        elif instr.operation=="slt" or instr.operation=="slti":
            register_data[instr.RD]=int(first<second)
        elif instr.operation=="beq":
            register_data[instr.RD]=int(first==second)
        elif instr.operation=="bne":
            register_data[instr.RD]=int(first!=second)
        else:
            raise Exception ("The operation is not supported by the ALU")


def read_file():
    #reads input file
    return "inst"

def make_pipeline(filename):
    next_index = 0
    
    file = open(filename, 'r', encoding = "utf-8")
    for line in file:
        #HIT A LABEL (All labels end in ':')
        line = line.strip()
        if line[-1] == ':':
            line = line[:-1] 
            branch_labels[line] = next_index
            continue
        
        all_instructions.append(Instruction(line.strip()))
        next_index += 1
    
    file.close()
    return

def make_pipereg():
    IFID=PipeReg(None, None, "IF", "ID")
    IDEX=PipeReg(None, None, "ID", "EX")
    EXMEM=PipeReg(None, None, "EX", "MEM")
    MEMWB=PipeReg(None, None, "MEM", "WB")
    return [IFID, IDEX, EXMEM, MEMWB]

#I'm assuming this is the function to print the entire pipeline
def print_register():
    print("{:20s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{:4s}{}".format
    ("CPU Cycles ===>","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"))
    for instr in pipeline_history:
        print(instr)
    
    print("")
    i = 1
    for reg in register_data.keys():
        if i == len(register_data.keys()): #Last val
            print(reg + " = " + str(register_data[reg]), sep = "", end = "\n")
        elif i % 4 != 0: #Common case
            print("{:20s}".format(reg + " = " + str(register_data[reg])), sep = "", end = "")
        else: #Last on line
            print(reg + " = " + str(register_data[reg]), sep = "", end = "\n")
        i += 1

    print("-" * 82)
    return
    
if __name__ == '__main__':

    CLA.run_error_check() #DEBUG
    isForwarding = (sys.argv[1] == "F")
    make_pipeline(sys.argv[2])
    control=Control(isForwarding)
    print("START OF SIMULATION (" + ("no " if not isForwarding else "") + "forwarding)" )
    print("-" * 82)

    pipeline_registers=make_pipereg()
    while cycle_count < max_cycle_count:
        temp = control.CheckBranch(pipeline_registers, branch_labels)
        if temp != -1: 
            next_instruction_index = temp
            pipeline_registers[-1].output.update(cycle_count, "WB")
            for register in pipeline_registers:
                if(register.input != None):
                    register.input.till_dead = 1
        else:
            next_instruction_index += 1
        
        if pipeline_registers[-1].output is not None:
            ALU(pipeline_registers[-1].output) #output is the current instruction in the wb pipreg object. Varable can chance based on chosen object varable.
            pipeline_registers[-1].output.update(cycle_count, "WB")
        
        pipeline_registers[-1].output=None
        control.checkDataHazards(pipeline_registers)
        
        for index in reversed(range(len(pipeline_registers))):
            if pipeline_registers[index].input:
                if pipeline_registers[index].input.till_dead != -1:
                    if pipeline_registers[index].input.till_dead == 0:
                        pipeline_registers[index].input.dead = True
                    pipeline_registers[index].input.till_dead -= 1
                #print("SAFTY:", control.DataHazardFlag, " " , not control.forwardFlag, " " , index == 1)
                if control.DataHazardFlag and not control.forwardFlag and index == 1:
                    pipeline_registers[1].input.delayed=True
                    nop = pipeline_registers[index].input.make_nop(cycle_count)
                    pipeline_registers[index+1].input = nop
                    pipeline_registers[index].output = nop

                pipeline_registers[index].input.update(cycle_count, pipeline_registers[index].input_name)
                if pipeline_registers[index].input.full_instr=="nop" and pipeline_registers[1].input and pipeline_registers[1].input.delayed:
                    insert_index = pipeline_history.index(pipeline_registers[1].input)
                    pipeline_history.insert(insert_index, pipeline_registers[2].input)
                    pipeline_registers[1].input.delayed=False
                if pipeline_registers[index].output is None:
                    #print("Moving:", pipeline_registers[index].input.full_instr)
                    pipeline_registers[index].output = pipeline_registers[index].input
                    pipeline_registers[index].input = None
                    if index != 0:
                        pipeline_registers[index-1].output=None
                    if index != len(pipeline_registers)-1:
                        pipeline_registers[index + 1].input = pipeline_registers[index].output

        if cycle_count != -1:
            print_register()

        if next_instruction_index != -1:
            if next_instruction_index<len(all_instructions):
                
                if all_instructions[next_instruction_index] in pipeline_history:
                    temp_instr = Instruction(all_instructions[next_instruction_index].full_instr)
                    pipeline_history.append(temp_instr)
                else:
                    pipeline_history.append(all_instructions[next_instruction_index])
                
                pipeline_registers[0].input = pipeline_history[-1]


        #update all registers after they moved to their new pipeline register
        if pipeline_registers[0].input is None and pipeline_registers[1].input is None and pipeline_registers[2].input is None and pipeline_registers[3].input is None and pipeline_registers[3].output is None:
            break
        cycle_count+=1

    print("END OF SIMULATION")
