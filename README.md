# Overview

This project was done as a part of my operating systems class. The goal was to create a basic kernel for Risc-V architecture that implements continous memory allocation, multithreading and the console.<br>
The kernel provides both C and C++ interfaces for programs that run in user mode. User mode and kernel mode are separate by an ABI layer.
<br>It also supports both synchronous and asynchronous context switching. 


<hr>

### List of the implemented system calls:


**Memory allocation**:
- mem_alloc
- mem_free

<br>

**Threads**:
- thread_create 
- thread_exit
- thread_dispatch
- thread_join

<br>

**Semaphores**:
- sem_open
- sem_close
- sem_wait
- sem_signal

<br>

**Timer**:
- time_sleep

<br>

**Console**:
- getc
- putc

<br>

## Testing
The project can be tested using qemu by running:
```
make qemu
```
The project was built using Ubuntu VM provided by the University. The Ubuntu VM can be downloaded [here](https://drive.google.com/file/d/1edGYFcvdnV0pbKws_1G1vePtEec0qC0G/view).

<br>

Project setup instructions can be found [here](http://os.etf.bg.ac.rs/OS1/projekat/Projektni%20zadatak%202023.%20v1.0.pdf) .

## Disclaimer
All of the files aside from the **src** and the **inc** directories (including all of their contents) were provided by the University.

