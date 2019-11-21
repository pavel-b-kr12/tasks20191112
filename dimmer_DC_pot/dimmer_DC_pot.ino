#define stripe_p		5 //3904+150R irlz44+pull_up 75R
#define stripe_p2		6
#define pot_p			A4



void setup() {
	pinMode(stripe_p, OUTPUT);
	pinMode(stripe_p2, OUTPUT);
	
	pinMode(pot_p,INPUT_PULLUP);
	pinMode(A5,OUTPUT);
	
	pinMode(A0,INPUT_PULLUP);
	pinMode(A1,OUTPUT);

	//Serial.begin(57600);
}


//int il;
void loop()
{
	delay(10);

	
	analogWrite(stripe_p, constrain(map(analogRead(pot_p), 10, 600, 0,255),0,255));
	
	analogWrite(stripe_p2, constrain(map(analogRead(A0), 10, 600, 0,255),0,255));
	
	//Serial.print(analogRead(pot_p)); Serial.print(" ");
	//Serial.println(map(analogRead(pot_p), 0, 1023, 10,250));

	
}