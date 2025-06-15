#include <Arduino.h>

const int LeftButton = 7;
const int RightButton = 8;
const int ResetButton = 13;

const int LeftLed = 2;
const int RightLed = 4;

const int ResetLed = 12;

unsigned long tempoPressionadoEsquerdo = 0;
unsigned long tempoPressionadoDireito = 0;

bool hasPressed;
bool debug;
bool checkTimes;

void setup()
{
	pinMode(LeftButton, INPUT_PULLUP);
	pinMode(RightButton, INPUT_PULLUP);
	pinMode(ResetButton, INPUT_PULLUP);

	pinMode(LeftLed, OUTPUT);
	pinMode(RightLed, OUTPUT);
	pinMode(ResetLed, OUTPUT);
	Serial.begin(115200);

	Serial.println("Tempo esquerdo: " + String(tempoPressionadoEsquerdo) + " | Tempo direito: " + String(tempoPressionadoDireito));
}

void loop()
{
	if (hasPressed == false)
	{
		RegisterTimeLeftPress();
		RegisterTimeRightPress();
		CheckWhichButtonHasFirstPress();
		digitalWrite(ResetLed, HIGH);
	}
	else
	{
		digitalWrite(ResetLed, LOW);
	}

	if (hasPressed && digitalRead(ResetButton) == LOW)
	{
		digitalWrite(RightLed, LOW);
		digitalWrite(LeftLed, LOW);
		hasPressed = false;
		checkTimes = false;
		debug = false;
		tempoPressionadoDireito = 0;
		tempoPressionadoEsquerdo = 0;
		Serial.println("------------------------ RESET --------------------------");
	}
}

void RegisterTimeLeftPress()
{
	if (digitalRead(LeftButton) == LOW)
	{
		Serial.println("Passou no esquerdo");
		tempoPressionadoEsquerdo = millis();
	}
}

void RegisterTimeRightPress()
{
	if (digitalRead(RightButton) == LOW)
	{
		Serial.println("Passou no direito");
		tempoPressionadoDireito = millis();
	}
}

void CheckWhichButtonHasFirstPress()
{
	if (checkTimes || tempoPressionadoDireito == 0 && tempoPressionadoEsquerdo == 0)
	{
		return;
	}

	checkTimes = true;

	if ((tempoPressionadoDireito > 0 || tempoPressionadoEsquerdo > 0) && debug == false)
	{
		debug = true;
		Serial.println("Tempo esquerdo: " + String(tempoPressionadoEsquerdo) + " | Tempo direito: " + String(tempoPressionadoDireito));
	}

	if (tempoPressionadoDireito == 0)
	{
		digitalWrite(LeftLed, HIGH);
	}
	else if (tempoPressionadoEsquerdo == 0)
	{
		digitalWrite(RightLed, HIGH);
	}
	else if (tempoPressionadoEsquerdo < tempoPressionadoDireito)
	{
		digitalWrite(LeftLed, HIGH);
	}
	else if (tempoPressionadoDireito < tempoPressionadoEsquerdo)
	{
		digitalWrite(RightLed, HIGH);
	}
	else if (tempoPressionadoDireito > 0 && tempoPressionadoEsquerdo > 0 && abs(tempoPressionadoDireito - tempoPressionadoEsquerdo) == 10)
	{
		digitalWrite(RightLed, HIGH);
		digitalWrite(LeftLed, HIGH);
	}

	hasPressed = true;
}
