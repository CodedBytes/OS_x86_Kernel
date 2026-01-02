# OS_x86_Kernel
Kernel experimental para processadores x86_64 mais precisamente 32bits por hora.
Atualmente, é capas de se comunicar com o hardware real para exibição de graficos em 768px com driver basico VESA, driver basico de teclado.
Vale lembrar que esse kernel é basico, focado em bare-metal/firmware, que implementa boot, grub e algumas outras coisas de forma basica, sendo necesário ajustes.

Para as partes de comunicação com o hardware foram usadas assembly pois quis ser o mais proximo possivel do hardware, usando também C em conjunto com o assembly. 

# Braches
Sobre as branches, eu vou trabalhar com 3 branches aqui (firmware de 64bits ainda vou alinha com o tempo, junto da x86_64 tbm):
- Uma branch para 32bits
- Uma branch para 64bits
- Uma branch para firmware 32bits

# Instalação
A instalação requer algumas dependencias que podem ser adiquiridas a seguir:
```bash
sudo apt install build-essential nasm gcc make git qemu-system libsdl2-dev libpci-dev gcc-multilib grub-pc-bin mtools xorriso
```
Para todas as branches isso é necessario.

# WIP
- Controle de memória
- Controle de multitarefas com round-robin / scheduler com comportamento parecido com o de consoles.
- Controle de de tarefas usando semaforos (talvez eu troque isso).

# Ideias
Transformar isso em um MSDOS da vida ou um kernel x86 para adaptação de um OS simples futuramente.
