# Pipeline_Sim

This was a group project completed with Ohad Nir, Xavier Marshall, and Ayannah Vasquez. The program takes in a Forwarding command ("F" for Forwarding, "N" for no Forwarding) and a .txt file containing MIPS32 code. The program then prints a visualization of the MIPS32 processor pipeline as the instructions are parsed and executed. Register values are displayed with every iteration. Usage: python.exe sim.py Forwarding_instruction input.txt

# Files

- **CLA.py**: File that tests command line arguments

- **Control.py**: Processor Control class that tracks and checks for data hazards, control hazards, and branching flags

- **instruction.py**: Instruction class that prints the pipeline status of an instruction, moves an instruction down the pipeline, and can delay an instruction, pushing an "nop" duplicate in front of it

- **pipereg.py**: Pipereg class that tracks important information about given pipeline registers

- **p1-input.txt**: Sample input files
