section .multiboot
align 8

multiboot_header:
    dd 0xE85250D6                ; Magic number
    dd 0                         ; Arquitetura 32-bit (i386)
    dd header_end - multiboot_header ; Tamanho total
    dd -(0xE85250D6 + 0 + (header_end - multiboot_header)) ; Checksum

    ; --- TAG: Framebuffer Request ---
    align 8
    dw 5                         ; TIPO 5 (Muitas implementações usam 5 para vídeo, 3 é informação de console)
    dw 0                         ; Flags (0)
    dd 20                        ; Tamanho da tag (exatos 20 bytes)
    dd 1024                      ; Largura (evite 0 em alguns emuladores)
    dd 768                       ; Altura
    dd 32                        ; BPP
    ; Note: Sem padding extra aqui dentro, o alinhamento vem na próxima tag

    ; --- TAG: End ---
    align 8
    dw 0                         ; type 0
    dw 8                         ; size 8
header_end:
