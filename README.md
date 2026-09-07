# SISTEMA-INTELIGENTE-DE-LUBRIFICAO-POR-DOSAGEM-
Código-fonte desenvolvido para o protótipo do Sistema Inteligente de Lubrificação por Dosagem, como parte do TCC do curso Técnico em Eletromecânica.

 
Projeto desenvolvido como Trabalho de Conclusão de Curso (TCC) do curso Técnico em Eletromecânica.

## Descrição

Este repositório contém o código utilizado no protótipo do Sistema Inteligente de Lubrificação por Dosagem, desenvolvido para realizar o controle automatizado do sistema de acionamento, dosagem, sinalização e supervisão do equipamento.

## Controlador

- ESP32 DevKit V1 (ESP32-WROOM-32)

O ESP32 é responsável pelo processamento da lógica de funcionamento do sistema, controle do motor de passo, acionamento do relé, sinalização por LED RGB, leitura dos comandos e comunicação Wi-Fi.

## Componentes eletrônicos e elétricos

### 1. ESP32 DevKit V1
- Modelo: ESP32-WROOM-32
- Função: Controlador principal do sistema
- Wi-Fi integrado
- Bluetooth integrado

### 2. Driver de motor de passo TB6600
- Função: Controle do acionamento do motor de passo
- Recebe os sinais STEP e DIR provenientes do ESP32
- Responsável pelo controle da potência enviada ao motor

### 3. Motor de passo NEMA17 42HS48 PG14
- Tipo: Bipolar
- Passo: 1,8°
- Redução planetária: 14:1
- Função: Acionamento do fuso e deslocamento do êmbolo

### 4. Fonte chaveada 12 V / 5 A
- Tensão de entrada: 110/220 V AC
- Tensão de saída: 12 V DC
- Corrente: 5 A
- Potência: 60 W
- Função: Alimentação elétrica do sistema

### 5. Conversor DC-DC LM2596
- Tensão de entrada: 4 a 35 V DC
- Tensão de saída: ajustada para 5 V DC
- Função: Redução da tensão de 12 V para 5 V para alimentação dos componentes que necessitam dessa tensão

### 6. Relé SRD-05VDC-SL-C
- Tensão da bobina: 5 V DC
- Corrente máxima de contato: 10 A
- Função: Realizar o chaveamento elétrico previsto no circuito

### 7. Interruptor KCD1-105
- Tensão: até 250 V AC
- Corrente: até 10 A
- Função: Liga e desliga a alimentação geral do equipamento

### 8. Cabo de força tripolar
- Seção dos condutores: 3 × 1,00 mm²
- Tensão: 127/220 V AC
- Corrente indicada: 10 A
- Função: Conexão da alimentação da rede elétrica com a fonte do sistema

### 9. Módulo LED RGB de 3 canais
- Canais: R, G e B
- Alimentação: 5 V DC
- Função: Sinalização visual do estado de funcionamento do sistema

### 10. Cabos Jumper macho-fêmea
- Tipo: Macho-Fêmea
- Função: Interligação entre os componentes eletrônicos e o ESP32 durante a montagem e prototipagem do circuito

### 11. Botão tátil (Tact Switch)
- Tipo: contato momentâneo normalmente aberto (NA)
- 4 pinos
- Função: Permitir o acionamento manual do sistema e entrada de comandos ao ESP32

## Sistema de acionamento

O acionamento mecânico do protótipo é realizado pelo conjunto formado pelo motor de passo NEMA17 42HS48 PG14, com redução planetária de 14:1, e pelo driver TB6600.

O ESP32 envia os sinais de controle ao TB6600, que realiza o acionamento do motor de passo. O movimento do motor é transmitido ao fuso, responsável pelo deslocamento do êmbolo e, consequentemente, pela realização da dosagem.

## Principais funções do sistema

- Controle do motor de passo;
- Dosagem por quantidade de pulsos;
- Contagem dos pulsos acumulados;
- Retorno do êmbolo;
- Sinalização do funcionamento por LED RGB;
- Acionamento do relé;
- Acionamento manual por botão;
- Controle da alimentação por interruptor;
- Armazenamento do contador na memória do ESP32;
- Comunicação Wi-Fi;
- Interface Web;
- Supervisão das informações de funcionamento do sistema.

## Parâmetros principais

- Motor: NEMA17 42HS48 PG14;
- Passo do motor: 1,8°;
- Redução planetária: 14:1;
- Micropasso utilizado: 1/2;
- Pulsos por volta do motor: 400;
- Pulsos por volta do eixo de saída: 5.600;
- Passo do fuso: 1,5 mm;
- Pulsos por dosagem: 5.500;
- Limite do reservatório: 198.000 pulsos;
- Intervalo entre dosagens: 10 s;
- Velocidade configurada: 810 µs.

## Comunicação e IoT

O ESP32 possui comunicação Wi-Fi integrada e é utilizado para estabelecer a comunicação do sistema com a rede. A interface Web permite a supervisão das informações do protótipo por meio de um navegador.

A arquitetura de comunicação utiliza o ESP32, a rede Wi-Fi, o broker MQTT e a interface Web para possibilitar o monitoramento e, conforme implementado no programa, o envio de comandos ao sistema.

## Sinalização por LED RGB

O módulo LED RGB é utilizado para indicar visualmente diferentes estados de funcionamento do protótipo.

- Verde: lubrificando;
- Azul: circuito ligado;
- Amarelo: retorno do êmbolo;
- Vermelho: cilindro vazio:

## Projeto acadêmico

Trabalho de Conclusão de Curso – Técnico em Eletromecânica.

Projeto: Sistema Inteligente de Lubrificação por Dosagem.

autor: Elias Antony Conceição silva 
