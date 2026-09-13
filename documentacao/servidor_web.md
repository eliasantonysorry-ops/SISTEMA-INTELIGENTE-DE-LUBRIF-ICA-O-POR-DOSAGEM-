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

## 10. Procedimento para acesso ao painel Web pelo endereço IP

O sistema utiliza o servidor Web integrado ao ESP32 para disponibilizar uma interface de controle e monitoramento por meio da rede Wi-Fi. Para acessar essa interface, é necessário primeiro identificar o endereço IP atribuído ao ESP32.

### 10.1 Identificação do endereço IP

Após carregar o programa no ESP32, abrir o **Monitor Serial da Arduino IDE** e configurar a velocidade para **115200 baud**.

Ao reiniciar o ESP32, o programa realiza a conexão com a rede Wi-Fi configurada. Quando a conexão é estabelecida, o endereço IP do dispositivo é apresentado no Monitor Serial.

A informação poderá aparecer de maneira semelhante à apresentada abaixo:

```text
Conectando ao Wi-Fi...
..........
Wi-Fi conectado!
Endereço IP: 192.168.1.100
