# OS_x86_Kernel
Kernel experimental para processadores x86_64.
Atualmente capas de se comunicar com o hardware real para exibição de graficos em 768px com driver basico VESA, driver basico de teclado.
Vale lembrar que esse kernel é basico, focado em bare-metal e implementa boot, grub e algumas outras coisas de forma basica, sendo necesário ajustes.

Para as partes de comunicação com o hardware foram usadas assembly pois quis ser o amis proximo possivel do hardware, usando também C em conjunto com o assembly. 

# Instalação
A instalação requer algumas dependencias que podem ser adiquiridas no .sh disponivel no repositório, mas de forma geral são esses :
```bash
sudo apt install build-essential nasm gcc make git qemu-system libsdl2-dev libpci-dev gcc-multilib

# WIP
- Controle de memória
- Controle de multitarefas com round-robin / scheduler com comportamento parecido com o de consoles.
- Controle de de tarefas usando semaforos (talvez eu troque isso).

# Ideias
Transformar isso em um MSDOS da vida ou um kernel x86 para adaptação de um OS simples futuramente.
