void detectcard() {
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  byte buffer2[8];
  block = 1;
  len = 18;
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) 
  {
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) 
  {
    
  }
  else
  {

  }
  //PRINT LAST NAME
  for (uint8_t i = 0; i < 7; i++) {
    mystring1 += (char)buffer2[i];
    
  }
  //depannya 0 absen 1 kontener 2 docking
  delay(100);
  //  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
