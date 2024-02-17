.global EcallAndExceptionsWrapper
.global TimerInterruptWrapper
.global ConsoleInterruptWrapper

.extern EcallAndExceptionsTable
.extern TimerInterrupt
.extern HardwareInterrupt

.macro PUSH_REGISTERS_EcallAndExceptions
addi sp,sp,-256
.irp index, 1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
sd x\index, \index * 8(sp)
.endr
.endm

.macro POP_REGISTERS_EcallAndExceptions
.irp index, 1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
ld x\index, \index * 8(sp)
.endr
addi sp,sp,256
.endm

.macro PUSH_REGISTERS_Timer
addi sp,sp,-256
.irp index, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
sd x\index, \index * 8(sp)
.endr
.endm

.macro POP_REGISTERS_Timer
.irp index, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
ld x\index, \index * 8(sp)
.endr
addi sp,sp,256
.endm


.macro PUSH_REGISTERS_Console
addi sp,sp,-256
.irp index, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
sd x\index, \index * 8(sp)
.endr
.endm

.macro POP_REGISTERS_Console
.irp index, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
ld x\index, \index * 8(sp)
.endr
addi sp,sp,256
.endm

.macro push_sys_reg reg
addi sp, sp, -8
csrr t0, \reg
sd t0, 0(sp)
.endm

.macro pop_sys_reg reg
ld t0, 0(sp)
csrw \reg, t0
addi sp, sp, 8
.endm

// -------------------------------------------------------------------

EcallAndExceptionsWrapper:
    PUSH_REGISTERS_EcallAndExceptions

    csrr t0, sepc
    addi t0, t0, 0x04
    csrw sepc, t0
    csrc sip, 0x02

    push_sys_reg sepc
    push_sys_reg sstatus

    call EcallAndExceptionsTable

    pop_sys_reg sstatus
    pop_sys_reg sepc

    POP_REGISTERS_EcallAndExceptions
    sret

TimerInterruptWrapper:
    PUSH_REGISTERS_Timer

    li t0, 0x02
    csrc sip, t0

    push_sys_reg sepc
    push_sys_reg sstatus

    call TimerInterrupt

    pop_sys_reg sstatus
    pop_sys_reg sepc

    POP_REGISTERS_Timer
    sret

ConsoleInterruptWrapper:
    PUSH_REGISTERS_Console

    li t0, 0x200
    csrc sip, t0

    push_sys_reg sepc
    push_sys_reg sstatus

    call HardwareInterrupt

    pop_sys_reg sstatus
    pop_sys_reg sepc

    POP_REGISTERS_Console
    sret
