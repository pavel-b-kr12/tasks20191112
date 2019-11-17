 //http://fastled.io/docs/3.1/group__lib8tion.html

#define		LED_p		4	
#define		LED_p2		5	
#define		btn_p		A5 //fade end
#define		btn2_p		A4 // bright mul

//------ default  more animate hue
#define		btn3_p		A3 // smaller animate hue, more violet
#define		btn4_p		A2 // purple
//------ 
#define		NUM_LEDS	120 //max 260 for atmega168
#define NUM_LEDS_type 	 byte //uint16_t

#include "FastLED.h"
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];
float k_len=135;
float k_len2=175;


CRGB gColor=  CRGB(155,155,255); //Orange


void clear()
{
	memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
	memset(leds2, 0, NUM_LEDS * sizeof(struct CRGB));
}

void setup(){
	//Serial.begin(1000000);

 
	FastLED.addLeds<WS2812B, LED_p, GRB>(leds, NUM_LEDS);
	FastLED.addLeds<WS2812B, LED_p2, GRB>(leds2, NUM_LEDS);
	FastLED.setBrightness( 155 );
	clear();
	FastLED.show();
	delay(800);

	pinMode(btn_p,INPUT_PULLUP);
	pinMode(btn2_p,INPUT_PULLUP);
	pinMode(btn3_p,INPUT_PULLUP);
	pinMode(btn4_p,INPUT_PULLUP);
}

//byte i_eff=0;
void loop()
{

 for(NUM_LEDS_type i =0;i<NUM_LEDS;i++)
 {
	 /*
	float t=millis();
	float t1=t/150;
	float t1b=t/150*k_len2/k_len;
	float t2=t/100;
	float t2b=t/100;
	float t3=t/4;
	float t3b=t/4;
	 
	//leds[i]=( triwave8(i+millis()/8 )*sin8(millis()/100) + triwave8(i+millis()/8 )*cos8(millis()/100) )/1024;  //nwp
	leds[i]=CHSV(190+sin8((byte)t1)/16, 205+sin8((byte)t2)/16, triwave8(i*8-(byte)t3 ) );
	leds2[i]=CHSV(190+sin8((byte)t1b)/16, 205+sin8((byte)t2b)/16, triwave8(i*8-(byte)t3b ) );
	*/
	//leds [i]=CHSV(0,0,128);
	
	byte b=triwave8(i*8-millis()/4 ); 

	byte b1=triwave8((int)(i*8.0*k_len/k_len2)-millis()/4 );
	
	byte h=211+sin8(millis()/200)/8; //as from violet to purple over 235ms*255 =1 min
	if(!digitalRead(btn3_p))
	{
		h=190+sin8(millis()/150)/16; //as violet
	}
	else
	if(!digitalRead(btn4_p))
	{
		h=230+sin8(millis()/150)/32; //as violet
	}
	
	if(!digitalRead(btn2_p))
	{
		b=b*b/255;
		b1=b1*b1/255;
	}
	
	
	leds [i]=CHSV(h, 215+sin8(millis()/200)/16, b );
	leds2[i]=CHSV(h, 215+sin8(millis()/200)/16,  b1);
 }
 //i_eff++;
 	
	if(!digitalRead(btn_p))
	{
		//if( i_eff%(1+millis()/200%60)<2 )
		{
			for (int i = 30; i < NUM_LEDS; ++i)
			{
				 //leds[i].fadeToBlackBy( i );
				 leds[i].fadeToBlackBy( map(i, 30,NUM_LEDS, 1, 250)  );
				 leds2[i].fadeToBlackBy( map(i, 30,NUM_LEDS, 1, 250)  );
			}
		}
	}
	
	FastLED.show();
	delay(1);
}
	
	
	
