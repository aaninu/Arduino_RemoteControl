//////////////////////////////////////////////////////////////////////
void DebugMode_Msg(String text);
void DebugMode_Msg(String text, char* valoare);
void Radio_Setup();
void Radio_Receiver();

//////////////////////////////////////////////////////////////////////
void Radio_Setup(){
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(PIN_tx);
  vw_setup(Radio_Speed);
  vw_rx_start();
  DebugMode_Msg("Radio > Activ.");
}

void Radio_Receiver(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

   if (vw_get_message(buf, &buflen)){
    if(buf[0]=='C'){ digitalWrite(13,1); } 
    if(buf[0]=='M'){ digitalWrite(13,0); }

    for (int i = 0; i < buflen; i++){
      Serial.print(char(buf[i]));
      Serial.print(", ");
    }
    Serial.println("S-a gasit");
  }
}

void Radio_Send(char *Value){
  vw_send((uint8_t *)Value, strlen(Value));
  vw_send((uint8_t *)Value, strlen(Value));
  vw_wait_tx();
  DebugMode_Msg("Radio_Send()", Value);
}

