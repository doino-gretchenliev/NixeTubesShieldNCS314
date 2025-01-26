#define LEDsSpeed      1
#define LEDsBrightness 64  // Brightness value (0 to 255)
const int LEDsDelay = 10;

bool singleColorMode = true; // Enable/disable single color mode
int singleColor[3] = {0, 200, 60}; // RGB values for McIntosh-style green

void LEDsSetup() {}

void rotateFireWorks()
{
  if (tone1.isPlaying()) return;
  if (!RGBLedsOn)
  {
    analogWrite(RedLedPin, 0);
    analogWrite(GreenLedPin, 0);
    analogWrite(BlueLedPin, 0);
    return;
  }
  if (LEDsLock) return;

  if (singleColorMode)
  {
    // Display the single color
    analogWrite(RedLedPin, (singleColor[0] * LEDsBrightness) / 255);
    analogWrite(GreenLedPin, (singleColor[1] * LEDsBrightness) / 255);
    analogWrite(BlueLedPin, (singleColor[2] * LEDsBrightness) / 255);
    return;
  }

  // Normal firework rotation logic
  RedLight = RedLight + fireforks[rotator * 3];
  GreenLight = GreenLight + fireforks[rotator * 3 + 1];
  BlueLight = BlueLight + fireforks[rotator * 3 + 2];

  // Apply brightness scaling
  analogWrite(RedLedPin, (RedLight * LEDsBrightness) / 255);
  analogWrite(GreenLedPin, (GreenLight * LEDsBrightness) / 255);
  analogWrite(BlueLedPin, (BlueLight * LEDsBrightness) / 255);

  cycle = cycle + 1;
  if (cycle == 255)
  {
    rotator = rotator + 1;
    cycle = 0;
  }
  if (rotator > 5) rotator = 0;
}

void LEDsTest()
{
  analogWrite(RedLedPin, (255 * LEDsBrightness) / 255);
  delay(1000);
  analogWrite(RedLedPin, 0);
  analogWrite(GreenLedPin, (255 * LEDsBrightness) / 255);
  delay(1000);
  analogWrite(GreenLedPin, 0);
  analogWrite(BlueLedPin, (255 * LEDsBrightness) / 255);
  delay(1000); 
  analogWrite(BlueLedPin, 0);
}

void setLEDsFromEEPROM()
{
  int R, G, B;
  R = EEPROM.read(LEDsRedValueEEPROMAddress);
  G = EEPROM.read(LEDsGreenValueEEPROMAddress);
  B = EEPROM.read(LEDsBlueValueEEPROMAddress);

  if (RGBLedsOn)
  {
    analogWrite(RedLedPin, (R * LEDsBrightness) / 255);
    analogWrite(GreenLedPin, (G * LEDsBrightness) / 255);
    analogWrite(BlueLedPin, (B * LEDsBrightness) / 255);
  }
  else
  {
    analogWrite(RedLedPin, 0);
    analogWrite(GreenLedPin, 0);
    analogWrite(BlueLedPin, 0);
  }
}
