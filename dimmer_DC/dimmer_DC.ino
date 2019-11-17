#define stripe_p		5 //3904+150R irlz44+pull_up 75R
#define stripe_p2		6


#define STRIPE_ON		0
#define STRIPE_OFF		1

#define		btn_p		A5 //anim timings

int on_d=9000;
int on_d2=13000;

int off_d=7000;
int off_d2=7000;


bool bStripeActive=true;
bool bStripeActive2=true;

bool bStripe_PWM_ON=true;


long changed_t=0;
long changed_t2=0;


void setup() {
	pinMode(stripe_p, OUTPUT);
	pinMode(stripe_p2, OUTPUT);
	
	pinMode(btn_p,INPUT_PULLUP);

	//Serial.begin(57600);
}


//int il;
void loop()
{
	delay(1);
	//il++;
	
	if(!digitalRead(btn_p))
	{
		int on_d=4000+ 1000* millis()/30000%5;
		int on_d2=6000+ 1000* millis()/30000%6;

		int off_d=3000+ 1000* millis()/20000%5; // from 2...to 5s  over 20*3s
		int off_d2=3000+ 1000* millis()/22000%8;
	}

	
	//----------------------
	
	if(bStripeActive) //wait
	{
		if(millis()>changed_t+on_d)
		{
			changed_t=millis();
			
			bStripeActive=false;
													//Serial.println( "dim1");
		}
	}
	else
	{
		if(millis()>changed_t+off_d)  //turn ON
		{
			changed_t=millis();
			bStripeActive=true;						//Serial.println( "on1");
			digitalWrite(stripe_p,STRIPE_ON);
		}
		else //fade
		{
			float t=(millis()-changed_t);
			t= abs(t-off_d/2);//1000...0...1000
			t=constrain(t, off_d/6, off_d/2);
			byte d_on= map(t,off_d/6,off_d/2,255,0); //dt/10; //100..0..100
			//d_off=255-t;
			
			if(STRIPE_ON==1)
			{
				d_on=255-d_on;
			}
			analogWrite(stripe_p, d_on);

		}
	}
	
	//----------------------

	if(bStripeActive2) //wait
	{
		if(millis()>changed_t2+on_d2)
		{
			changed_t2=millis();
			bStripeActive2=false;					//Serial.println( "dim2");
		}
	}
	else
	{
		if(millis()>changed_t2+off_d2)  //turn ON
		{
			changed_t2=millis();
			bStripeActive2=true;					//	Serial.println( "on2");
			digitalWrite(stripe_p2,STRIPE_ON);
		}
		else //fade
		{
			float t=(millis()-changed_t2);
			t=constrain(t, off_d2/6, off_d2/2);
			byte d_on= map(t,off_d2/6,off_d2/2,255,0); //255..0..255
			
			if(STRIPE_ON==1)
			{
				d_on=255-d_on;
			}
			
			analogWrite(stripe_p2, d_on);
		}
	}
	
}