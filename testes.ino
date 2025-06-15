#include <Arduino.h>

const int LeftButton = 7;
const int RightButton = 8;
const int ResetButton = 13;

const int LeftLed = 2;
const int RightLed = 4;

unsigned long tempoPressionadoEsquerdo = 0;
unsigned long tempoPressionadoDireito = 0;

bool hasPressed;

void setup()
{
	pinMode(LeftButton, INPUT_PULLUP);
	pinMode(RightButton, INPUT_PULLUP);
	pinMode(ResetButton, INPUT_PULLUP);

	pinMode(LeftLed, OUTPUT);
	pinMode(RightLed, OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	if (hasPressed == false)
	{
		RegisterTimeLeftPress();
		RegisterTimeRightPress();
		CheckWhichButtonHasFirstPress();
	}

	if (hasPressed && digitalRead(ResetButton) == LOW)
	{
		digitalWrite(RightLed, LOW);
		digitalWrite(LeftLed, LOW);
		hasPressed = false;
	}
}

void RegisterTimeLeftPress()
{
	if (digitalRead(LeftButton) && tempoPressionadoEsquerdo == 0)
	{
		tempoPressionadoEsquerdo = millis();
	}
}

void RegisterTimeRightPress()
{
	if (digitalRead(RightButton) == LOW && tempoPressionadoDireito == 0)
	{
		tempoPressionadoDireito = millis();
	}
}

void CheckWhichButtonHasFirstPress()
{
	Serial.println("Tempo esquerdo: " + String(tempoPressionadoEsquerdo) + " | Tempo direito: " + String(tempoPressionadoDireito));
	hasPressed = true;

	if (tempoPressionadoEsquerdo < tempoPressionadoDireito)
	{
		digitalWrite(LeftLed, HIGH);
		return;
	}
	else if (tempoPressionadoDireito < tempoPressionadoEsquerdo)
	{
		digitalWrite(RightLed, HIGH);
		return;
	}

	digitalWrite(RightLed, HIGH);
	digitalWrite(LeftLed, HIGH);
}
