````markdown
# Servidor Web e Acesso ao Sistema por Wi-Fi

## 1. Objetivo

O sistema possui um servidor Web integrado ao ESP32, permitindo o monitoramento e o controle do sistema de lubrificação por meio de um computador ou smartphone conectado à mesma rede Wi-Fi do ESP32.

O servidor Web é executado diretamente pelo ESP32 utilizando a biblioteca `WebServer` e a porta 80.

---

## 2. Configuração da rede Wi-Fi

Para utilizar o servidor Web, o ESP32 deve estar conectado a uma rede Wi-Fi.

No código do sistema são definidos o nome e a senha da rede:

```cpp
const char* SSID = "NOME_DA_SUA_REDE";
const char* SENHA = "SENHA_DA_SUA_REDE";
````

Antes de utilizar o sistema, esses campos devem ser preenchidos com os dados da rede Wi-Fi que será utilizada.

Exemplo:

```cpp
const char* SSID = "MinhaRede";
const char* SENHA = "MinhaSenha";
```

A senha real da rede não deve ser publicada no repositório.

---

## 3. Conexão do ESP32 à rede Wi-Fi

Após o ESP32 ser ligado e o programa ser iniciado, o sistema tenta estabelecer uma conexão com a rede Wi-Fi configurada.

Enquanto a conexão não é estabelecida, o programa permanece aguardando:

```cpp
while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}
```

Quando a conexão é estabelecida, o programa informa no Monitor Serial:

```text
Wi-Fi conectado!
```

Em seguida, o ESP32 apresenta o endereço IP recebido pela rede.

---

## 4. Identificação do endereço IP

O endereço IP é necessário para acessar o servidor Web do ESP32.

O programa apresenta esse endereço no Monitor Serial utilizando:

```cpp
Serial.print("Endereço IP: ");
Serial.println(WiFi.localIP());
```

Após a conexão, o Monitor Serial poderá apresentar algo semelhante a:

```text
Conectando ao Wi-Fi...
..........
Wi-Fi conectado!
Endereço IP: 192.168.1.100
```

O endereço:

```text
192.168.1.100
```

é apenas um exemplo.

O endereço real deve ser o número apresentado pelo próprio ESP32 no Monitor Serial.

---

## 5. Abertura do Monitor Serial

Para identificar o endereço IP do ESP32, deve-se:

1. Conectar o ESP32 ao computador.
2. Abrir a Arduino IDE.
3. Carregar o programa no ESP32.
4. Abrir o Monitor Serial.
5. Configurar a velocidade para **115200 baud**.
6. Reiniciar o ESP32.
7. Aguardar a conexão com a rede Wi-Fi.
8. Localizar a mensagem:

```text
Endereço IP: xxx.xxx.xxx.xxx
```

9. Anotar ou copiar o endereço IP apresentado.

---

## 6. Conexão do computador ou smartphone

O computador ou smartphone utilizado para acessar o sistema deve estar conectado à **mesma rede Wi-Fi do ESP32**.

Por exemplo:

```text
             REDE WI-FI
                 │
        ┌────────┴────────┐
        │                 │
        ▼                 ▼
      ESP32          Celular/PC
        │                 │
        │                 │
        └──── mesma rede ─┘
```

O dispositivo não precisa estar conectado fisicamente ao ESP32.

A comunicação ocorre pela rede Wi-Fi local.

---

## 7. Acesso ao painel pelo navegador

Depois de identificar o endereço IP do ESP32:

1. Conectar o celular ou computador à mesma rede Wi-Fi.
2. Abrir um navegador de Internet.
3. Digitar o endereço IP do ESP32 na barra de endereço.
4. Utilizar o formato:

```text
http://IP_DO_ESP32
```

Por exemplo, se o Monitor Serial apresentar:

```text
Endereço IP: 192.168.1.100
```

deve-se digitar no navegador:

```text
http://192.168.1.100
```

5. Pressionar **Enter**.

Após o acesso, o navegador deverá apresentar a interface Web disponibilizada pelo ESP32.

Como o servidor utiliza a porta 80, não é necessário informar `:80` no endereço.

---

## 8. Representação completa do procedimento

```text
┌──────────────────────────────┐
│        LIGAR O ESP32         │
└──────────────┬───────────────┘
               ↓
┌──────────────────────────────┐
│  ESP32 inicia o programa     │
└──────────────┬───────────────┘
               ↓
┌──────────────────────────────┐
│ ESP32 tenta conectar ao      │
│        Wi-Fi configurado     │
└──────────────┬───────────────┘
               ↓
        ┌───────────────┐
        │ Wi-Fi         │
        │ conectado?    │
        └───────┬───────┘
                │
          ┌─────┴─────┐
          │           │
         NÃO         SIM
          │           │
          ↓           ↓
     ┌────────┐  ┌─────────────────────┐
     │Aguardar│  │ ESP32 obtém o IP    │
     └────────┘  └──────────┬──────────┘
                            ↓
                 ┌─────────────────────┐
                 │ Monitor Serial      │
                 │                     │
                 │ Endereço IP:        │
                 │ 192.168.1.100       │
                 └──────────┬──────────┘
                            ↓
                 ┌─────────────────────┐
                 │ Conectar celular ou │
                 │ computador à mesma  │
                 │ rede Wi-Fi          │
                 └──────────┬──────────┘
                            ↓
                 ┌─────────────────────┐
                 │ Abrir o navegador   │
                 └──────────┬──────────┘
                            ↓
                 ┌─────────────────────┐
                 │ Digitar o IP        │
                 │                     │
                 │ http://192.168.1.100│
                 └──────────┬──────────┘
                            ↓
                 ┌─────────────────────┐
                 │ Pressionar ENTER    │
                 └──────────┬──────────┘
                            ↓
                 ┌─────────────────────┐
                 │     PAINEL WEB      │
                 │       DO ESP32      │
                 └─────────────────────┘
```

---

## 9. Servidor Web

O servidor Web é criado no código por meio da seguinte instrução:

```cpp
WebServer server(80);
```

A porta utilizada pelo servidor é a porta **80**, padrão para comunicação HTTP.

Após a conexão com a rede Wi-Fi, o servidor é iniciado por:

```cpp
server.begin();
```

Durante a execução do programa, o ESP32 verifica continuamente se existem novas solicitações feitas pelo navegador por meio de:

```cpp
server.handleClient();
```

Essa função é executada dentro da função `loop()`.

---

## 10. Página principal

A página principal do sistema é disponibilizada pela rota:

```text
/
```

No código:

```cpp
server.on("/", paginaPrincipal);
```

Quando o usuário acessa o endereço IP do ESP32, a função `paginaPrincipal()` gera e envia a interface Web para o navegador.

Exemplo:

```text
http://192.168.1.100/
```

---

## 11. Comando de dosagem

O sistema possui a rota:

```text
/dosar
```

Configurada no código por:

```cpp
server.on("/dosar", comandoDosagem);
```

Essa rota executa a função responsável pelo processo de dosagem.

---

## 12. Comando de retorno do êmbolo

O sistema possui a rota:

```text
/retornar
```

Configurada no código por:

```cpp
server.on("/retornar", comandoRetorno);
```

Essa rota executa a função responsável pelo retorno do êmbolo.

---

## 13. Comando de reset

O sistema possui a rota:

```text
/reset
```

Configurada no código por:

```cpp
server.on("/reset", comandoReset);
```

Essa função realiza o procedimento de reset do contador utilizado pelo sistema.

---

## 14. Rotas do servidor Web

As principais rotas implementadas no servidor são:

| Rota        | Função                         |
| ----------- | ------------------------------ |
| `/`         | Exibe a página principal       |
| `/dosar`    | Executa uma dosagem            |
| `/retornar` | Executa o retorno do êmbolo    |
| `/reset`    | Reinicia o contador do sistema |

---

## 15. Fluxo de comunicação

O funcionamento da comunicação entre o usuário e o sistema pode ser representado da seguinte maneira:

```text
┌──────────────────────┐
│   CELULAR / PC       │
│                      │
│      Navegador       │
└──────────┬───────────┘
           │
           │ Solicitação HTTP
           │ pela rede Wi-Fi
           ↓
┌──────────────────────┐
│        ESP32         │
│                      │
│    Servidor Web      │
│      Porta 80        │
└──────────┬───────────┘
           │
           ↓
┌──────────────────────┐
│ Sistema Inteligente  │
│ de Lubrificação      │
│                      │
│ • Dosagem            │
│ • Retorno            │
│ • Reset              │
│ • Monitoramento      │
└──────────────────────┘
```

---

## 16. Informações disponibilizadas pela interface

A interface Web desenvolvida no ESP32 apresenta informações relacionadas ao funcionamento do sistema, incluindo:

* percentual estimado do reservatório;
* quantidade de dosagens;
* quantidade de passos acumulados;
* horário da última lubrificação;
* próxima lubrificação;
* estado do motor;
* estado do driver TB6600;
* estado da conexão Wi-Fi;
* identificação do ESP32;
* endereço IP do dispositivo.

A interface também disponibiliza os comandos implementados para controle do sistema.

---

## 17. Painel Web publicado no GitHub Pages

O projeto também possui uma interface Web publicada no GitHub Pages para apresentação e demonstração do sistema.

Essa interface possui finalidade de apresentação do projeto e não substitui o servidor Web executado diretamente pelo ESP32.

O controle físico do protótipo é realizado pelo servidor Web embarcado no ESP32.

Assim, o funcionamento pode ser dividido em:

```text
┌─────────────────────────────────┐
│       SISTEMA WEB DO PROJETO    │
└────────────────┬────────────────┘
                 │
        ┌────────┴────────┐
        │                 │
        ▼                 ▼
┌───────────────┐  ┌────────────────┐
│ GitHub Pages  │  │ Servidor Web   │
│               │  │ do ESP32       │
│ Demonstração  │  │                │
│ do projeto    │  │ Controle real  │
│               │  │ do protótipo   │
└───────────────┘  └────────────────┘
```

O acesso ao servidor Web responsável pelo controle do protótipo deve ser realizado pelo endereço IP apresentado pelo ESP32 no Monitor Serial.

---

## 18. Resumo do procedimento de acesso

O procedimento completo pode ser resumido em:

```text
LIGAR O ESP32
      ↓
CONECTAR AO WI-FI
      ↓
ABRIR O MONITOR SERIAL
      ↓
IDENTIFICAR O ENDEREÇO IP
      ↓
CONECTAR CELULAR/COMPUTADOR
À MESMA REDE WI-FI
      ↓
ABRIR O NAVEGADOR
      ↓
DIGITAR O IP DO ESP32
      ↓
http://192.168.1.100
      ↓
PRESSIONAR ENTER
      ↓
ACESSAR O PAINEL WEB
      ↓
MONITORAR E CONTROLAR
O SISTEMA
```

O endereço IP utilizado no exemplo é apenas ilustrativo. Para cada utilização, deve ser utilizado o endereço IP apresentado pelo ESP32 no Monitor Serial.

```
```
