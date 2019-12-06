//#include <Adafruit_NeoPixel.h>  // Library Manager > Adafruit NeoPixel Version >= 1.2.2
#include <WS2812FX.h>             // Library Manager > WS2812FX >= 1.1.9

//Led strip WS2812
#define WS2812PIN 3
#define WS2812PIXELS 20
#define POTMIN 20
#define POTMAX 1010

int potLightLevelLast = -10;

WS2812FX ws2812fx = WS2812FX(WS2812PIXELS, WS2812PIN, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(115200);
	Serial.println("Start Elements light");
	ws2812fx.init();
	ws2812fx.setBrightness(100);
	ws2812fx.setSpeed(1200);
	ws2812fx.setColor(0xFF6600);
	ws2812fx.setMode(FX_MODE_FIRE_FLICKER_INTENSE);
	ws2812fx.start();
}

void checkLightLevelPot() {
	int potLightLevel = analogRead(A6);
	// Cap input
	if (potLightLevel < POTMIN) {
		potLightLevel = POTMIN;
	}
	if (potLightLevel > POTMAX) {
		potLightLevel = POTMAX;
	}
	potLightLevel = map(potLightLevel, POTMIN, POTMAX, 0, 255);
	// To avaoid flicker, only change level if +/-4 steps
	if ((potLightLevelLast-potLightLevel > 4) || (potLightLevelLast-potLightLevel < -4)) {
		Serial.print("Light level changed to ");
		Serial.println(potLightLevel);
		ws2812fx.setBrightness(potLightLevel);
		potLightLevelLast = potLightLevel;
	}
}

void tick() {
	ws2812fx.service();
}

void loop() {
	checkLightLevelPot();
	tick();
	delay(20);
}
