BITS 32
global isr_stub_table

isr_stub_table:
%assign i 0
%rep 256
    dd isr_stub_%+i
%assign i i+1
%endrep

%assign i 0
%rep 256
isr_stub_%+i:
    cli
    iret
%assign i i+1
%endrep
