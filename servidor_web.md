# Servidor Web do Sistema

## 1. Descrição

O sistema utiliza o recurso de servidor Web embarcado do ESP32 para disponibilizar uma interface de controle e acompanhamento do protótipo por meio de um navegador conectado à mesma rede Wi-Fi.

A comunicação é realizada utilizando as bibliotecas `WiFi.h` e `WebServer.h`, com o ESP32 atuando como servidor Web na porta 80.

## 2. Conexão Wi-Fi

Durante a inicialização, o ESP32 realiza a conexão com a rede Wi-Fi configurada no programa.

As credenciais da rede são definidas no código por meio das variáveis:

```cpp
const char* SSID = "NOME_DA_SUA_REDE";
const char* SENHA = "SENHA_DA_SUA_REDE";

