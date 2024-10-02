# Nanoleaf
A ideia desse projeto é utilizar uma fita led endereçável WS2812 dentro de painéis feitos na impressora 3D. Criar um aplicativo ou web server para fazer o controle desses painéis com infinitas possibilidades de cores e efeitos.

## Estrutura
O projeto está estruturado da seguinte forma:

- `lib/effects/effect.h` Pasta onde encontra-se o arquivo de código de efeitos e cores da Nanoleaf
- `src/main.cpp` Código principal para o ESP32


## Desenvolvimento
para auxiliar no desenvolvimento do projeto utilizamos os softwares:

- `Visual Studio Code`: Auxílio nos códigos
- `PlatformIO IDE` Extensão para compilar código no ESP32 pelo vscode
- `Arduino IDE`: Auxílio nos códigos
- `FreeCad`: Ferramenta de Modelagem 3D
- `SolidWorks`: Ferramenta de Modelagem 3D
- `Ultimaker Cura`: Ferramenta para Impressora 3D

No arquivo de configuração `platformio.ini` incluímos a biblioteca FastLED, apenas inserindo:
```c
lib_deps = fastled/FastLED@^3.5.0
```