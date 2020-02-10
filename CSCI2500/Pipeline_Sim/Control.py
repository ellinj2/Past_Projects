'''
Create the Control class:
Deal with hazards
Forwarding
Branch handling
'''

class Control(object):
    def __init__(self, ForwardStatus):
        self.DataHazardFlag=False
        self.ControlHazardFlag=False
        self.forwardFlag=ForwardStatus

    '''
    Forward keys:
    0: Inactive
    1: Execution forward
    2: Memory forward
    '''
    def checkDataHazards(self, pipeline_registers):
        self.DataHazardFlag=False
        IDEX=1
        EXMEM=2
        MEMWB=3
        EXHazard=False
        if pipeline_registers[EXMEM].input is not None and pipeline_registers[EXMEM].input.full_instr != "nop":
            if pipeline_registers[EXMEM].input is not None and pipeline_registers[IDEX].input is not None and pipeline_registers[EXMEM].input.RD==pipeline_registers[IDEX].input.RS:
                self.DataHazardFlag=True
                EXHazard=True
            if pipeline_registers[EXMEM].input is not None and pipeline_registers[IDEX].input is not None and pipeline_registers[EXMEM].input.RD==pipeline_registers[IDEX].input.RT:
                self.DataHazardFlag=True
                EXHazard=True
        if pipeline_registers[MEMWB].input is not None and pipeline_registers[MEMWB].input.full_instr != "nop":
            if (not EXHazard) and pipeline_registers[MEMWB].input is not None and pipeline_registers[IDEX].input is not None and pipeline_registers[MEMWB].input.RD==pipeline_registers[IDEX].input.RS:
                self.DataHazardFlag=True
            if (not EXHazard) and pipeline_registers[MEMWB].input is not None and pipeline_registers[IDEX].input is not None and pipeline_registers[MEMWB].input.RD==pipeline_registers[IDEX].input.RT:
                self.DataHazardFlag=True

    def BranchValue(self, pipeline_registers, branch_labels):
        MEMWB=3
        instr=pipeline_registers[MEMWB].input
        if instr.operation=="beq" and instr.RS==instr.RT:
            return branch_labels[instr.RD]
        if instr.operation=="bne" and instr.RS!=instr.RT:
            return branch_labels[instr.RD]
        return -1

    def CheckBranch(self, pipeline_registers, branch_labels):
        MEMWB=3
        instr=pipeline_registers[MEMWB].input
        if instr is not None and instr.isBranch:
            return self.BranchValue(pipeline_registers, branch_labels)
        return -1
