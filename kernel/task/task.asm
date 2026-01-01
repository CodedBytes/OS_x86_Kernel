global context_switch
context_switch:
    ; No padrão C (cdecl): [esp+4] é old_ctx, [esp+8] é new_ctx
    mov edi, [esp + 4] ; EDI = old_ctx
    mov esi, [esp + 8] ; ESI = new_ctx

    test edi, edi
    jz skip_save

    ; Salva registradores gerais
    mov [edi + 0x00], eax
    mov [edi + 0x04], ebx
    mov [edi + 0x08], ecx
    mov [edi + 0x0C], edx
    mov [edi + 0x10], esi
    mov [edi + 0x14], edi
    mov [edi + 0x18], ebp
    
    ; Salva o ESP atual (ajustado para ignorar o endereço de retorno do call)
    mov eax, esp
    add eax, 4         ; Ajusta para o ESP que a task tinha antes do 'call'
    mov [edi + 0x20], eax

    ; Salva o endereço de retorno real (EIP) que está no topo da stack
    mov eax, [esp]
    mov [edi + 0x1C], eax

skip_save:
    ; Restaura o contexto de ESI (new_ctx)
    ; Precisamos restaurar o ESP primeiro para mudar de stack
    mov esp, [esi + 0x20]
    
    ; Empurra o novo EIP para a stack para usar o 'ret' como salto
    mov eax, [esi + 0x1C]
    push eax

    ; Restaura os outros registradores
    mov eax, [esi + 0x00]
    mov ebx, [esi + 0x04]
    mov ecx, [esi + 0x08]
    mov edx, [esi + 0x0C]
    mov ebp, [esi + 0x18]
    mov edi, [esi + 0x14]
    ; Por último, restauramos o ESI que usamos como base
    mov esi, [esi + 0x10]

    ret ; Salta para o EIP que colocamos na stack
