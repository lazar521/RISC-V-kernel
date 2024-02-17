.global setjump

setjump:
    sd x1,8(a0)             // save all the registers except a0 since it is the function argument
    sd x2,16(a0)            // a0 needs to return 0x00  when saving the registers
    sd x3,24(a0)
    sd x4, 32(a0)
    sd x5, 40(a0)
    sd x6, 48(a0)
    sd x7, 56(a0)
    sd x8, 64(a0)
    sd x9, 72(a0)
    sd x11, 88(a0)
    sd x12, 96(a0)
    sd x13, 104(a0)
    sd x14, 112(a0)
    sd x15, 120(a0)
    sd x16, 128(a0)
    sd x17, 136(a0)
    sd x18, 144(a0)
    sd x19, 152(a0)
    sd x20, 160(a0)
    sd x21, 168(a0)
    sd x22, 176(a0)
    sd x23, 184(a0)
    sd x24, 192(a0)
    sd x25, 200(a0)
    sd x26, 208(a0)
    sd x27, 216(a0)
    sd x28, 224(a0)
    sd x29, 232(a0)
    sd x30, 240(a0)
    sd x31, 248(a0)

    csrr t0,sstatus         //save sstatus and sepc
    sd t0,256(a0)

    csrr t0,sepc
    sd t0,264(a0)

    li x10, 0x00            //put return value into x10
    ret