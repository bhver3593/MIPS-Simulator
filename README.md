# MIPS-Simulator
MIPS-Simulator is a C++ application that simulates a pipelined MIPS processor by executing a list of instructions from an input assembly file and displaying the contents of the register file and memory after each instruction execution.


### How to compile program from Linux
`g++ -o mips -std=c++11 *.cpp`


### How to run program from Linux
`./mips assemblyfile.txt`


### How it works
- Register values (except the zero register and stack pointer) are initially set to -1
- Stack pointer in register 31 is set to 8
- Data memory contains randomly generated values between 1 and 100
- Control signals are set to false
- After running the application, the contents of instruction memory are presented
- Each instruction is executed in a consecutive manner

![InstructionMemory](https://media.git.txstate.edu/user/3111/files/68196fe8-6d0b-4228-8e17-647edfe74f16)

- After executing a load instruction, data from memory is loaded to a register
- To calculate the memory address, the stack pointer value from register 31 is added to the offset value
- Data from the calculated memory address is then written to the destination register

![LoadInstruction](https://media.git.txstate.edu/user/3111/files/ace36ee0-4dc1-45ee-a455-a67025897370)

- After executing an ALU instruction, the ALU operates on data values from two source registers and writes the result to the destination register

![ADDInstruction](https://media.git.txstate.edu/user/3111/files/2ce6826a-c6da-4c60-afec-ba19ba45fd11)

- After executing a branch instruction, the ALU compares the data values from two source registers
- If the two data values are equal, the offset value will be shifted by 2 and added to the program counter
- The value of the updated program counter will determine the next instruction executed from instruction memory

![BranchInstruction](https://media.git.txstate.edu/user/3111/files/23798438-443e-47d7-9ea0-c14bd75cccef)

- After executing a store instruction, data from a register is stored to memory
- To calculate the memory address, the stack pointer value from register 31 is added to the offset value
- Data from the source register is then written to the calculated memory address

![StoreInstruction](https://media.git.txstate.edu/user/3111/files/78420c2d-be67-4e69-ba52-4c7fe4b3bd4c)

- When DEBUG mode is enabled in main.cpp, the emitted control signals and the contents of the state registers are printed
- Additionally, controls signals are reset to false before the next instruction is executed

![DebugMode](https://media.git.txstate.edu/user/3111/files/5a703f23-cae8-4b7f-afb8-613ae11eb5aa)
