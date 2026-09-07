# Fluxograma do Sistema

## Lógica de dosagem

INÍCIO

↓

Inicializa ESP32

↓

Carrega contador da memória

↓

Verifica botão

↓

Verifica limite de 198.000 pulsos

↓

Executa dosagem

↓

Aciona relé

↓

LED verde

↓

Define direção

↓

Envia 5.500 pulsos ao TB6600

↓

Motor movimenta o fuso

↓

Êmbolo avança

↓

Atualiza contador

↓

Salva contador

↓

Aguarda 10 segundos

↓

Nova dosagem

## Lógica de retorno

BOTÃO PRESSIONADO

↓

Lê contador de passos

↓

Aciona relé

↓

LED amarelo

↓

Inverte direção

↓

Retorna a quantidade de passos acumulados

↓

Êmbolo retorna

↓

Zera contador

↓

Salva na memória

↓

LED azul
