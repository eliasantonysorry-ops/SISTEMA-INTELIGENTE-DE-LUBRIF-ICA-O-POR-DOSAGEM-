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

Antes de utilizar o sistema, esses campos devem ser preenchidos com os dados da rede Wi-Fi que será utilizada.


Exemplo:

const char* SSID = "MinhaRede";
const char* SENHA = "MinhaSenha";

A senha real da rede não deve ser publicada no repositório.

3. Conexão do ESP32 à rede Wi-Fi

Após o ESP32 ser ligado e o programa ser iniciado, o sistema tenta estabelecer uma conexão com a rede Wi-Fi configurada.

Enquanto a conexão não é estabelecida, o programa permanece aguardando:

while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}

Quando a conexão é estabelecida, o programa informa no Monitor Serial:

Wi-Fi conectado!

Em seguida, o ESP32 apresenta o endereço IP recebido pela rede.

4. Identificação do endereço IP

O endereço IP é necessário para acessar o servidor Web do ESP32.

O programa apresenta esse endereço no Monitor Serial utilizando:

Serial.print("Endereço IP: ");
Serial.println(WiFi.localIP());

Após a conexão, o Monitor Serial poderá apresentar algo semelhante a:

Conectando ao Wi-Fi...
..........
Wi-Fi conectado!
Endereço IP: 192.168.1.100

O endereço:

192.168.1.100

é apenas um exemplo.

O endereço real deve ser o número apresentado pelo próprio ESP32 no Monitor Serial.
