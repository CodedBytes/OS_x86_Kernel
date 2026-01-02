; context_switch(uint32_t *old_esp, uint32_t new_esp)
context_switch:
    ; Salva registradores que o C não salva automaticamente (callee-saved)
    push ebp
    push ebx
    push esi
    push edi

    mov eax, [esp + 20]    ; old_esp (ajustado pelo push dos 4 reg acima + retorno)
    mov [eax], esp         ; Salva ESP atual no old->esp

    mov eax, [esp + 24]    ; new_esp
    mov esp, eax           ; Troca para o stack da nova task

    ; Restaura registradores da nova task
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret