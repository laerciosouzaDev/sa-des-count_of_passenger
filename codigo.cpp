// projeto S.A

#include <Adafruit_LiquidCrystal.h>

// C++ code
//
const int PIN_ECHO = 12;
const int PIN_TRIGG = 13;
const int PIN_ECHO_SAIDA = 2;
const int PIN_TRIGG_SAIDA = 3;
const int LedVerde = 5;
const int LedVermelho = 4;
const int botaoGratuidade = 8;
const int ledAzul = 6;
const int BotaoFimDia = 7;
int passageirosDia = 0;
int passageiro = 0;
int perda = 0;
float arrecadacaoDia = 0;
float valorPassagem = 6.00;
int gratuidade = 0;
int teste = 0;
int estadoBotao = 0;
//bool npaga = false;

bool objetoPresente = false;
bool objetoPresenteSaida = false;
bool fim = false;

Adafruit_LiquidCrystal lcd(0);

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIGG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_ECHO_SAIDA, INPUT);
  pinMode(PIN_TRIGG_SAIDA, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedVermelho, OUTPUT);
  pinMode(botaoGratuidade, INPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(BotaoFimDia, INPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("contagem");
  lcd.setCursor(0, 1);
  lcd.print(passageiro);

  lcd.setCursor(10, 0);
  lcd.print("perda");
  lcd.setCursor(0, 1);
  lcd.print(perda);
}

void loop() {
  teste = digitalRead(BotaoFimDia);


  BotaoFim();
  delay(100);
  if (!fim) {
      estadoBotao = digitalRead(botaoGratuidade);
  delay(100);
    SensorEntrada();
    delay(100);
    SensorSaida();
    delay(100);
    Serial.println("gratuidade " + String(gratuidade));
  }

  Serial.println(gratuidade);
}

void SensorEntrada() {
  digitalWrite(PIN_TRIGG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGG, LOW);
  long duracao = pulseIn(PIN_ECHO, HIGH);

  float distancia = (0.0342 / 2) * duracao;

  if (distancia < 330 && !objetoPresente) {
    objetoPresente = true;
    Serial.println("entrou");
  } else if (distancia >= 330 && objetoPresente) {
    objetoPresente = false;
    if (passageiro <= 6) {
      if (estadoBotao == 1) {
        gratuidade++;
        estadoBotao = false; // Resetar o estado de gratuidade
        digitalWrite(ledAzul, LOW);
      }
      passageiro++;
      passageirosDia++;
      digitalWrite(LedVermelho, LOW);
      digitalWrite(LedVerde, HIGH);
    } else {
      perda++;
      digitalWrite(LedVermelho, HIGH);
      digitalWrite(LedVerde, LOW);
    }
    Serial.println("Objeto Passou - contador: " + String(passageiro));
    Serial.println("Perda : " + String(perda));

    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print("Passageiros" + String(passageiro));
  }
}

void SensorSaida() {
  digitalWrite(PIN_TRIGG_SAIDA, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGG_SAIDA, LOW);
  long duracao = pulseIn(PIN_ECHO_SAIDA, HIGH);
  float distancia = (0.0342 / 2) * duracao;

  if (distancia < 330 && !objetoPresenteSaida) {
    objetoPresenteSaida = true;
    Serial.println("saiu");
  } else if (distancia >= 330 && objetoPresenteSaida) {
    objetoPresenteSaida = false;
    if (passageiro > 0) {
      passageiro--;

      if (passageiro <= 6) {
        digitalWrite(LedVermelho, LOW);
        digitalWrite(LedVerde, HIGH);
      }
    }
    Serial.println("Objeto Saiu - contador: " + String(passageiro));
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print("Passageiros" + String(passageiro));
  }
}

void BotaoFim() {
  int valor = digitalRead(BotaoFimDia);
  delay(100);
  if (valor == HIGH && !fim) {
    fim = true;
  } else if (valor == HIGH && fim) {
    fim = false;
  }
}

/*void botaoGratuito() {
  int estadoBotao = digitalRead(botaoGratuidade);
  delay(100);
  if (estadoBotao == HIGH && !nPaga) {
    nPaga = true;
    digitalWrite(ledAzul, HIGH);
  } else if (estadoBotao == HIGH && nPaga) {
    nPaga = false;
    digitalWrite(ledAzul, LOW);
  }
}*/// Mexi aqui pensei em fazer com a leitura do botão.
	 
  

    // arrecadacaoDia = (passageiros - gratuidade) * valorPassagem;
//if ((perda/2)> arrecadacaoDia){
//Serial.print(" Criar uma nova linha");
//
  


