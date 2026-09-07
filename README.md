# Sistema Inteligente de Lubrificação por Dosagem

Projeto desenvolvido como Trabalho de Conclusão de Curso (TCC) do curso Técnico em Eletromecânica.

## Sobre o projeto

O projeto consiste no desenvolvimento de um sistema automático de lubrificação por dosagem, desenvolvido com o objetivo de realizar a aplicação controlada de graxa por meio de um sistema eletromecânico e eletrônico.

O sistema utiliza um ESP32 para realizar o controle do processo, um driver TB6600 para acionamento do motor de passo NEMA 17 e um mecanismo de fuso e êmbolo responsável pelo deslocamento da graxa.

## Objetivo

Desenvolver um protótipo compacto e de baixo custo capaz de realizar dosagens periódicas de graxa de forma automatizada, reduzindo a necessidade de intervenção manual no processo de lubrificação.

## Principais componentes

- ESP32 DevKit V1
- Driver TB6600
- Motor de passo NEMA 17 42HS48 PG14
- Redutor planetário 14:1
- Fuso roscado
- Êmbolo
- Reservatório de graxa
- Relé
- Fonte de alimentação 12 V / 5 A
- Conversor LM2596
- LED RGB
- Botão de acionamento

## Funcionamento

O ESP32 realiza o controle do sistema de dosagem.

A rotina de dosagem utiliza 5.500 pulsos enviados ao driver TB6600 para movimentar o motor de passo. O movimento do motor é transmitido ao fuso, provocando o deslocamento do êmbolo e a consequente aplicação da graxa.

O sistema possui um contador de pulsos armazenado na memória do ESP32. Quando o limite programado é atingido, novas dosagens são bloqueadas.

Também existe uma rotina de retorno do êmbolo acionada por botão, utilizando a quantidade de pulsos acumulados para determinar o movimento de retorno.

## Parâmetros de controle

- Pulsos por dosagem: 5.500
- Limite máximo: 198.000 pulsos
- Temporização do motor: 810 µs
- Intervalo entre dosagens: 10 segundos
- Motor: NEMA 17 42HS48 PG14
- Redução: 14:1
- Driver: TB6600
- Controlador: ESP32 DevKit V1

## Documentação

Os arquivos de documentação do projeto estão organizados nas seguintes pastas:

- `documentacao/fluxograma.md` — lógica de funcionamento do sistema
- `documentacao/pinagem.md` — identificação dos pinos e conexões
- `documentacao/parametros.md` — parâmetros utilizados no controle

## Código-fonte

O código-fonte do sistema está disponível na pasta:

`codigo/`

## Protótipo

Fotos do protótipo desenvolvido estão disponíveis na pasta:

`imagens/`

## Trabalho de Conclusão de Curso

Projeto desenvolvido no curso Técnico em Eletromecânica do Centro de Educação Profissional de Paragominas.

## Autor

  Elias Antony Conceição Silva  

