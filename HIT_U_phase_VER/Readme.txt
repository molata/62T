-------- PROJECT GENERATOR --------
PROJECT NAME :	HIT_U_phase_VER
PROJECT DIRECTORY :	E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER
CPU SERIES :	RX600
CPU TYPE :	RX62T
TOOLCHAIN NAME :	Renesas RX Standard Toolchain
TOOLCHAIN VERSION :	1.2.0.0
GENERATION FILES :
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\dbsct.c
        Setting of B,R Section
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\typedefine.h
        Aliases of Integer Type
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\sbrk.c
        Program of sbrk
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\iodefine.h
        Definition of I/O Register
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\intprg.c
        Interrupt Program
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\vecttbl.c
        Initialize of Vector Table
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\vect.h
        Definition of Vector
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\resetprg.c
        Reset Program
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\HIT_U_phase_VER.c
        Main Program
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\sbrk.h
        Header file of sbrk file
    E:\rx_program\HIT_U_phase_VER\HIT_U_phase_VER\stacksct.h
        Setting of Stack area
START ADDRESS OF SECTION :
 H'1000	B_1,R_1,B_2,R_2,B,R,SU,SI
 H'FFFF8000	PResetPRG
 H'FFFF8100	C_1,C_2,C,C$*,D_1,D_2,D,P,PIntPRG,W*,L
 H'FFFFFFD0	FIXEDVECT

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start 0xFFFF8000.
* RAM start 0x1000.

SELECT TARGET :
    RX600 E1/E20 SYSTEM
DATE & TIME : 2012-10-23 11:39:12
