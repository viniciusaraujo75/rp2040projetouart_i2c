# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================


set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

# Nome correto do projeto
project(rp2040projetouarti2c C CXX ASM)

# Definição dos padrões
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Inicializa o SDK do Pico
pico_sdk_init()

# Adiciona os arquivos principais (ajustando para a pasta "src/")
add_executable(rp2040projetouarti2c
    src/main.c
    src/ssd1306.c

)

# Vincula as bibliotecas necessárias
target_link_libraries(rp2040projetouarti2c 
    pico_stdlib
    hardware_i2c
    hardware_uart
    hardware_gpio
    hardware_irq
)
