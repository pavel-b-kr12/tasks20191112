#define stripe_p3		3 //3904+150R irlz44+pull_up 75R
#define stripe_p9		9
#define stripe_p10		10
#define stripe_p11		11
#define stripe_p5		5
#define stripe_p6		6
//3, 5, 6, 9, 10, 11    490 Hz (pins 5 and 6: 980 Hz)   0 not fully turning off the output on pins 5 and 6.	//https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
	
#define pot_p			A4 //w A5 as GND

#define		btn_p		A0 //anim timings

#define STRIPE_ON		0
#define STRIPE_OFF		1

//don't need an optocoupler unless you need to isolate the signal ground from the bridge ground.

float val_10;
float val_11;
float val_5;
float val_6;
float pw_10=0;
float pw_11=100;
float pw_5=0;
float pw_6=100;
float avg_k=0.05;

float get_pot(float k)
{
	return ((float)constrain(map((analogRead(pot_p)+analogRead(pot_p))/2, 10, 700, 1,100),1,100))*k;
}

void setup() {
	pinMode(stripe_p10, OUTPUT);
	pinMode(stripe_p11, OUTPUT);
	pinMode(stripe_p3, OUTPUT);
	pinMode(stripe_p9, OUTPUT);
	pinMode(stripe_p5, OUTPUT);
	pinMode(stripe_p6, OUTPUT);
	
	pinMode(btn_p,INPUT_PULLUP);
	pinMode(A1,INPUT_PULLUP);
	
	pinMode(pot_p,INPUT_PULLUP);
	pinMode(A5,OUTPUT);

													//Serial.begin(57600);
	
	val_10=get_pot(0.0001);
	val_11=get_pot(0.00014);	
	val_5=get_pot(0.011);
	val_6=get_pot(0.016);
}


int il;

//12 0
byte ledLookupTable[] = {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8,8,9,9,9,10,10,11,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,23,23,24,24,25,26,26,27,28,28,29,30,30,31,32,32,33,34,35,35,36,37,38,38,39,40,41,42,42,43,44,45,46,47,47,48,49,50,51,52,53,54,55,56,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,73,74,75,76,77,78,79,80,81,82,84,85,86,87,88,89,91,92,93,94,95,97,98,99,100,102,103,104,105,107,108,109,111,112,113,115,116,117,119,120,121,123,124,126,127,128,130,131,133,134,136,137,139,140,142,143,145,146,148,149,151,152,154,155,157,158,160,162,163,165,166,168,170,171,173,175,176,178,180,181,183,185,186,188,190,192,193,195,197,199,200,202,204,206,207,209,211,213,215,217,218,220,222,224,226,228,230,232,233,235,237,239,241,243,245,247,249,251,253,255};


void loop()
{
	
	
	delay(18);
	
	// analogWrite(stripe_p10, 22);
	// analogWrite(stripe_p11, 22);
	
	// return;
	
	
	int v;
	v=millis()/12%512-256;
	v=abs(v);
	//Serial.print(v);	Serial.print(" ");
	analogWrite(stripe_p9, v);
	
	v=(int) ((sin(   (float)(millis())/1640.)+1)*127)  ;
	//Serial.print(v);	Serial.print(" ");
	//Serial.println();
	analogWrite(stripe_p3, v);
	

	val_10=val_10*(1.-avg_k)+ get_pot(0.0001)*avg_k;
	val_11=val_11*(1.-avg_k)+ get_pot(0.00014)*avg_k;	

	val_5=val_5*(1.-avg_k)+ get_pot(0.011)*avg_k;
	val_6=val_6*(1.-avg_k)+ get_pot(0.016)*avg_k;
	

	
	pw_10+=val_10;
	pw_11+=val_11;
	
	pw_5+=val_5;
	pw_6+=val_6;

	if(pw_10>TWO_PI)pw_10-=TWO_PI; 
	if(pw_11>TWO_PI)pw_11-=TWO_PI; 	
	
		
	if(pw_5>255)pw_5=-255; 
	if(pw_6>255)pw_6=-255;
	
	
	if(!digitalRead(btn_p)) //make both not <60
	{
	if(pw_5<0 ) //abs lowering
	{
		if(abs(pw_5)<60)
		{
			if(pw_6<0 && abs(pw_6)<70)
			{
				pw_6=-pw_6;
			}
		}
	}
	}
	
	 byte pwa_5=( (byte)abs(pw_5));
	 byte pwa_6=( (byte)abs(pw_6));
	
		
	byte pwa_10= (byte)(abs((sin(pw_10)+1)*127.));
	byte pwa_11= (byte)(abs((sin(pw_11)+1)*127.));
	
	
	//Serial.print(pw_10);	Serial.print(" ");
	
	//Serial.print(ledLookupTable[ pwa_5]);	Serial.print(" ");
	//Serial.print(ledLookupTable[ pwa_6]);	Serial.print(" ");
	//Serial.print(pwa_10);	Serial.print(" ");
	//Serial.print(pwa_11);	Serial.print(" ");
	//Serial.println();
	
		
		 if(!analogRead(A1))
		 {
	 analogWrite(stripe_p10, pwa_10);
	 analogWrite(stripe_p11, pwa_11);
		 }
		 else
		{
			analogWrite(stripe_p10, ledLookupTable[ pwa_5]);
			analogWrite(stripe_p11, ledLookupTable[pwa_6]);	
		}
	
	analogWrite(stripe_p5, pwa_5);
	analogWrite(stripe_p6, pwa_6);
	
	
}