#include "keyboard.h"
#include "io.h"
#include "../graph.h"

// Variáveis de controle de estado
static int shift_active = 0;

static int cursor_y = 0;
static int cursor_x = 0;
static int caps_lock = 0;
static int num_lock = 0;
static int extended = 0; // Para tratar o prefixo 0xE0


// Keymap ABNT2 corrigido para Scancode Set 1
static const char keymap[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t', 'q','w','e','r','t','y','u','i','o','p', 0x27, '[', '\n', // 0x27 é ' no ABNT2
    0, // Control
    'a','s','d','f','g','h','j','k','l', 0xE7, '~', ']', // 0xE7 é ç
    0, // Left Shift (0x2A)
    '\\', 'z','x','c','v','b','n','m', ',', '.', ';',
    0, // Right Shift (0x36)
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '/', // Tecla do teclado numérico ou / ao lado do Shift
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Shift map ABNT2
static const char shiftmap[128] = {
    0,  27, '!','@','#','$','%','^','&','*','(',')','_','+', '\b',
    '\t', 'Q','W','E','R','T','Y','U','I','O','P', '"', '{', '\n',
    0,
    'A','S','D','F','G','H','J','k','L', 0xC7, '^', '}', // 0xC7 é Ç
    0,
    '|', 'Z','X','C','V','B','N','M', '<', '>', ':',
    0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '?', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void keyboard_callback(registers_t *regs) {
    uint8_t scancode = inb(0x60);

    // 1. Trata o prefixo de teclas estendidas (Setas)
    if (scancode == 0xE0) {
        extended = 1;
        return;
    }

    if (extended) {
        extended = 0;
        switch(scancode) {
            case 0x48: /* Seta Cima */    cursor_y -= 16; break;
            case 0x50: /* Seta Baixo */   cursor_y += 16; break;
            case 0x4B: /* Seta Esquerda */ cursor_x -= 8;  break;
            case 0x4D: /* Seta Direita */  cursor_x += 8;  break;
        }
        return;
    }

    // 2. Trata teclas de interrupção (Release)
    if (scancode & 0x80) {
        uint8_t release_code = scancode & 0x7F;
        if (release_code == 0x2A || release_code == 0x36) shift_active = 0;
        return;
    }

    // 3. Teclas de Estado (Toggle)
    switch(scancode) {
        case 0x3A: caps_lock = !caps_lock; return;
        case 0x45: num_lock = !num_lock;   return;
        case 0x2A: 
        case 0x36: shift_active = 1;       return;
    }

    // 4. Lógica de tradução de texto
    char c = keymap[scancode];
    
    if (c >= 'a' && c <= 'z') {
        // Se Caps OU Shift estiverem ativos (mas não os dois ao mesmo tempo), fica Maiúscula
        if (caps_lock ^ shift_active) {
            c -= 32;
        }
    } else if (shift_active) {
        c = shiftmap[scancode];
    }

    if (c) {
        vesa_draw_char(cursor_x, cursor_y, c, 0xFFFFFF);
        cursor_x += 8;
    }
}