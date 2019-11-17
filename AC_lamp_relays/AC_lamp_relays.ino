byte lampHor0_p=5;
byte lampE=3;
bool change_direction=false;
//----------- default 3x switch
#define btn_3x_move_p		A3  // move by 1px
	bool b3x_move=false;
#define btn_1x_p		A2  	//
//-----------

#define btn_change_dir_p		A5  //jumper to GND to inverse change_direction

/*
#define fix_hi_lo_relay_set	//lagasy setup with different hi-level and lo-level relays...
#define lampE 10 //TOTO flash
#define change_direction	true


*/
#define btn_fast_p		A4  //fast


bool bLampNegative=false; //or hi/low level relay

void setLamp(byte p, bool on)
{
	#ifdef fix_hi_lo_relay_set
	bool state=(p==5||p==6)?on:!on; //!  fix hi-lo level
	#else
	bool state=!on; 
	#endif
	
	if(bLampNegative) state=!state;
	
	digitalWrite(p,state);
	
	//Serial.print(p);	Serial.print("   "); Serial.println( state);
}

void setup() {

	 //pinMode(stripe_p, OUTPUT);
	 pinMode(btn_change_dir_p, INPUT_PULLUP);
	 pinMode(btn_fast_p, INPUT_PULLUP);
	 pinMode(btn_3x_move_p, INPUT_PULLUP);
	 pinMode(btn_1x_p, INPUT_PULLUP);
	 
											//Serial.begin(57600);

	delay(1);	
	if(change_direction==false)
	{
		if(!digitalRead(btn_1x_p))
		{
			lampE=9; //set default, without jumper
			lampHor0_p=2;
		}
		
		if(!digitalRead(btn_3x_move_p))
		{
			b3x_move=true;
		}
	}
		
	
	for(byte i=lampHor0_p;i<lampHor0_p+9;i++)
	{
		setLamp(i,0);
		pinMode(i, OUTPUT);
	}

}

byte lampN=0;


byte lampN_last=0;
byte lampN_last2=0;
byte lampN_last3=0;
long sw_to_next_lamp_t=500;

bool bStripeAct=false;
byte d_on=1;
byte d_off=1;
byte d_=1;

int lampN_incr=-1;
void loop()
{
	delay(20);
					//bLampNegative=millis()/20000%2;
				
	if(change_direction ^(!digitalRead(btn_change_dir_p)) )
	{																
		if(millis()>sw_to_next_lamp_t)
		{															//digitalWrite(13,!digitalRead(13));
	
			long d=500;
			if(!digitalRead(btn_fast_p)) d=155;
			
			sw_to_next_lamp_t=millis()+d;//155;
			
			if(b3x_move)
			{
				setLamp(lampHor0_p+lampN_last3,0);
			}
			else
			{
				setLamp(lampHor0_p+lampN_last,0);
			}
			setLamp(lampHor0_p+lampN,1);

			//if(lampN==15 || lampN==0) lampN_incr=-lampN_incr;
			if(lampN==0) lampN_incr=1;
			else
			if(lampN>=lampE-1) lampN_incr=-1;
			
			lampN_last3=lampN_last2;
			lampN_last2=lampN_last;
			lampN_last=lampN;
			
			
			lampN+=lampN_incr;
		}
	}
	else
	{
		if(millis()>sw_to_next_lamp_t)
		{
			long d=1000;
			if(!digitalRead(btn_fast_p)) d=2000;
			
			sw_to_next_lamp_t=millis()+d;
			
			
			if(b3x_move)
			{
				setLamp(lampHor0_p+lampN_last3,0);
			}
			else
			{
				setLamp(lampHor0_p+lampN_last,0);
			}
			
			if(lampN<lampE)
			{
				setLamp(lampHor0_p+lampN,1);
			}

			lampN_last3=lampN_last2;
			lampN_last2=lampN_last;
			lampN_last=lampN;
			lampN++;
			//if(lampN==lampE){}  //this last emply lamp slot
			if(lampN>lampE) lampN=0;
		}
	}

}