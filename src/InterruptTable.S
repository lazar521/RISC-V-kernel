.extern EcallAndExceptionsWrapper
.extern TimerInterruptWrapper
.extern ConsoleInterruptWrapper


.global interruptTable
.align 4
interruptTable:
    .org  interruptTable + 0*4
    j EcallAndExceptionsWrapper
    .org interruptTable + 1*4
    j TimerInterruptWrapper
    .org interruptTable + 9*4
    j ConsoleInterruptWrapper