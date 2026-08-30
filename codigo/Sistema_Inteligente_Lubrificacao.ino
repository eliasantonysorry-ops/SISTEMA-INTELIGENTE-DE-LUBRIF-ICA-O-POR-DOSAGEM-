#include <Preferences.h>

/* =====================================================
   ADICIONADO — WI-FI E SERVIDOR WEB
   ===================================================== */

#include <WiFi.h>
#include <WebServer.h>

const char* SSID = "NOME_DA_SUA_REDE";
const char* SENHA = "SENHA_DA_SUA_REDE";

WebServer server(80);


/* =====================================================
   CÓDIGO ORIGINAL
   ===================================================== */

Preferences prefs;

#define STEP_PIN 18
#define DIR_PIN 19
#define RELE_PIN 23
#define BOTAO_RESET 4

#define LED_R 25
#define LED_G 26
#define LED_B 27

const long PASSOS_DOSAGEM = 5500;
const long PASSOS_MAXIMOS = 198000;
const int VELOCIDADE_US = 810;
const unsigned long INTERVALO = 10000;

long contadorPassos = 0;
bool reservatorioVazio = false;


/* =====================================================
   ADICIONADO — CONTROLE DO TEMPO
   ===================================================== */

unsigned long ultimaDosagem = 0;

String horarioUltimaDosagem = "--:--:--";


/* =====================================================
   LED RGB — ORIGINAL
   ===================================================== */

void ledAzul()
{
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, HIGH);
}


void ledVerde()
{
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, LOW);
}


void ledVermelho()
{
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}


/* =====================================================
   MEMÓRIA — ORIGINAL
   ===================================================== */

void salvarContador()
{
  prefs.putLong("contador", contadorPassos);
}


void carregarContador()
{
  contadorPassos =
    prefs.getLong("contador", 0);
}


/* =====================================================
   RETORNAR ÊMBOLO — ORIGINAL
   ===================================================== */

void retornarEmbolo()
{
  if (contadorPassos <= 0)
    return;

  digitalWrite(RELE_PIN, LOW);

  delay(500);

  // Amarelo = vermelho + verde
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, LOW);

  digitalWrite(DIR_PIN, LOW);

  for(long i = 0; i < contadorPassos; i++)
  {
    digitalWrite(STEP_PIN, HIGH);

    delayMicroseconds(VELOCIDADE_US);

    digitalWrite(STEP_PIN, LOW);

    delayMicroseconds(VELOCIDADE_US);
  }

  digitalWrite(RELE_PIN, HIGH);

  contadorPassos = 0;

  reservatorioVazio = false;

  salvarContador();

  ledAzul();
}


/* =====================================================
   DOSAGEM — ORIGINAL
   ===================================================== */

void executarDosagem()
{
  digitalWrite(RELE_PIN, LOW);

  delay(500);

  ledVerde();

  digitalWrite(DIR_PIN, HIGH);

  for(long i = 0; i < PASSOS_DOSAGEM; i++)
  {
    digitalWrite(STEP_PIN, HIGH);

    delayMicroseconds(VELOCIDADE_US);

    digitalWrite(STEP_PIN, LOW);

    delayMicroseconds(VELOCIDADE_US);
  }

  digitalWrite(RELE_PIN, HIGH);

  contadorPassos += PASSOS_DOSAGEM;

  salvarContador();

  if(contadorPassos >= PASSOS_MAXIMOS)
  {
    reservatorioVazio = true;

    ledVermelho();
  }
  else
  {
    ledAzul();
  }
}


/* =====================================================
   ADICIONADO — PERCENTUAL DO RESERVATÓRIO
   ===================================================== */

int percentualReservatorio()
{
  long restante =
    PASSOS_MAXIMOS - contadorPassos;

  if(restante < 0)
    restante = 0;

  return
    (restante * 100L) /
    PASSOS_MAXIMOS;
}


/* =====================================================
   ADICIONADO — PÁGINA HTML
   ===================================================== */

String paginaHTML()
{
  int percentual =
    percentualReservatorio();

  String status;

  if(reservatorioVazio)
    status = "🔴 Reservatório vazio";
  else
    status = "🟢 Sistema operando";


  String html = R"rawliteral(

<!DOCTYPE html>

<html lang="pt-BR">

<head>

<meta charset="UTF-8">

<meta name="viewport"
content="width=device-width, initial-scale=1.0">

<meta http-equiv="refresh" content="3">

<title>
Lubrificador Inteligente
</title>

<style>

body{

font-family:Arial;

background:#111827;

color:white;

margin:0;

padding:20px;

}

.container{

max-width:900px;

margin:auto;

}

h1{

text-align:center;

}

.subtitulo{

text-align:center;

color:#9ca3af;

margin-bottom:25px;

}

.status{

background:#1f2937;

padding:20px;

border-radius:15px;

text-align:center;

font-size:22px;

margin-bottom:20px;

}

.grid{

display:grid;

grid-template-columns:
repeat(auto-fit,minmax(210px,1fr));

gap:15px;

}

.card{

background:#1f2937;

padding:20px;

border-radius:15px;

}

.titulo{

color:#9ca3af;

font-size:14px;

}

.valor{

font-size:25px;

font-weight:bold;

margin-top:10px;

}

.barra{

height:30px;

background:#374151;

border-radius:20px;

overflow:hidden;

margin-top:15px;

}

.progresso{

height:100%;

background:#22c55e;

width:)rawliteral";

  html += String(percentual);

  html += R"rawliteral(%;

}

.botoes{

display:grid;

grid-template-columns:
repeat(auto-fit,minmax(200px,1fr));

gap:15px;

margin-top:20px;

}

button{

width:100%;

padding:18px;

border:0;

border-radius:12px;

font-size:16px;

font-weight:bold;

color:white;

cursor:pointer;

}

.dosagem{

background:#16a34a;

}

.retorno{

background:#d97706;

}

.reset{

background:#dc2626;

}

.info{

background:#1f2937;

padding:20px;

border-radius:15px;

margin-top:20px;

}

</style>

</head>


<body>

<div class="container">


<h1>

LUBRIFICADOR INTELIGENTE

</h1>


<div class="subtitulo">

SISTEMA AUTOMÁTICO DE LUBRIFICAÇÃO POR DOSAGEM

</div>


<div class="status">

)rawliteral";

  html += status;

  html += R"rawliteral(

</div>


<div class="card">

<div class="titulo">

RESERVATÓRIO

</div>

<div class="barra">

<div class="progresso"></div>

</div>

<div class="valor">

)rawliteral";

  html += String(percentual);

  html += R"rawliteral( %

</div>

</div>


<br>


<div class="grid">


<div class="card">

<div class="titulo">

DOSAGENS REALIZADAS

</div>

<div class="valor">

)rawliteral";

  html += String(
    contadorPassos /
    PASSOS_DOSAGEM
  );

  html += R"rawliteral(

</div>

</div>


<div class="card">

<div class="titulo">

PASSOS ACUMULADOS

</div>

<div class="valor">

)rawliteral";

  html += String(contadorPassos);

  html += R"rawliteral(

</div>

</div>


<div class="card">

<div class="titulo">

ÚLTIMA LUBRIFICAÇÃO

</div>

<div class="valor">

)rawliteral";

  html += horarioUltimaDosagem;

  html += R"rawliteral(

</div>

</div>


<div class="card">

<div class="titulo">

INTERVALO

</div>

<div class="valor">

10 segundos

</div>

</div>


<div class="card">

<div class="titulo">

MOTOR

</div>

<div class="valor">

Desligado

</div>

</div>


<div class="card">

<div class="titulo">

TB6600

</div>

<div class="valor">

OK

</div>

</div>


</div>


<div class="botoes">


<a href="/dosar">

<button class="dosagem">

REALIZAR DOSAGEM

</button>

</a>


<a href="/retornar">

<button class="retorno">

RETORNAR ÊMBOLO

</button>

</a>


<a href="/reset">

<button class="reset">

RESETAR CONTADOR

</button>

</a>


</div>


<div class="info">

<b>Wi-Fi:</b>

Conectado

<br><br>

<b>ESP32:</b>

Online

<br><br>

<b>Endereço IP:</b>

)rawliteral";

  html += WiFi.localIP().toString();

  html += R"rawliteral(

</div>


</div>

</body>

</html>

)rawliteral";


  return html;
}


/* =====================================================
   ADICIONADO — SERVIDOR WEB
   ===================================================== */

void paginaPrincipal()
{
  server.send(
    200,
    "text/html",
    paginaHTML()
  );
}


/* =====================================================
   ADICIONADO — BOTÃO DOSAGEM DA PÁGINA
   ===================================================== */

void comandoDosagem()
{
  executarDosagem();

  horarioUltimaDosagem =
    obterHora();

  server.sendHeader(
    "Location",
    "/"
  );

  server.send(303);
}


/* =====================================================
   ADICIONADO — BOTÃO RETORNO
   ===================================================== */

void comandoRetorno()
{
  retornarEmbolo();

  server.sendHeader(
    "Location",
    "/"
  );

  server.send(303);
}


/* =====================================================
   ADICIONADO — BOTÃO RESET
   ===================================================== */

void comandoReset()
{
  contadorPassos = 0;

  reservatorioVazio = false;

  salvarContador();

  ledAzul();

  server.sendHeader(
    "Location",
    "/"
  );

  server.send(303);
}


/* =====================================================
   ADICIONADO — OBTENÇÃO DO HORÁRIO
   ===================================================== */

String obterHora()
{
  struct tm timeinfo;

  if(!getLocalTime(&timeinfo))
  {
    return "--:--:--";
  }

  char hora[10];

  strftime(
    hora,
    sizeof(hora),
    "%H:%M:%S",
    &timeinfo
  );

  return String(hora);
}


/* =====================================================
   SETUP — ORIGINAL + WI-FI
   ===================================================== */

void setup()
{
  Serial.begin(115200);


  pinMode(
    STEP_PIN,
    OUTPUT
  );

  pinMode(
    DIR_PIN,
    OUTPUT
  );

  pinMode(
    RELE_PIN,
    OUTPUT
  );


  pinMode(
    BOTAO_RESET,
    INPUT_PULLUP
  );


  pinMode(
    LED_R,
    OUTPUT
  );

  pinMode(
    LED_G,
    OUTPUT
  );

  pinMode(
    LED_B,
    OUTPUT
  );


  digitalWrite(
    RELE_PIN,
    HIGH
  );


  prefs.begin(
    "lubrificador",
    false
  );

  carregarContador();


  if(contadorPassos >= PASSOS_MAXIMOS)
  {
    reservatorioVazio = true;

    ledVermelho();
  }
  else
  {
    ledAzul();
  }


  /* =================================================
     ADICIONADO — CONEXÃO WI-FI
     ================================================= */

  WiFi.begin(
    SSID,
    SENHA
  );

  Serial.println();

  Serial.print(
    "Conectando ao Wi-Fi"
  );


  while(
    WiFi.status() != WL_CONNECTED
  )
  {
    delay(500);

    Serial.print(".");
  }


  Serial.println();

  Serial.println(
    "Wi-Fi conectado!"
  );


  Serial.print(
    "Endereço IP: "
  );

  Serial.println(
    WiFi.localIP()
  );


  /* =================================================
     ADICIONADO — ROTAS DO SERVIDOR
     ================================================= */

  server.on(
    "/",
    paginaPrincipal
  );


  server.on(
    "/dosar",
    comandoDosagem
  );


  server.on(
    "/retornar",
    comandoRetorno
  );


  server.on(
    "/reset",
    comandoReset
  );


  server.begin();


  Serial.println(
    "Servidor web iniciado!"
  );
}


/* =====================================================
   LOOP — ORIGINAL ADAPTADO PARA SERVIDOR WEB
   ===================================================== */

void loop()
{

  /* ADICIONADO */

  server.handleClient();


  /* ORIGINAL */

  if(
    digitalRead(BOTAO_RESET)
    == LOW
  )
  {
    retornarEmbolo();

    delay(500);
  }


  if(reservatorioVazio)
  {
    return;
  }


  /*
   * ALTERAÇÃO NECESSÁRIA:
   *
   * O delay(INTERVALO) original
   * foi substituído por millis()
   * para permitir que o servidor
   * web continue funcionando.
   */

  if(
    millis() - ultimaDosagem
    >= INTERVALO
  )
  {
    executarDosagem();

    ultimaDosagem =
      millis();

    horarioUltimaDosagem =
      obterHora();
  }
}
