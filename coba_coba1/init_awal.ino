void init_awal() {

  
  pinMode(led_r, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_g, OUTPUT);
  delay(100);
  digitalWrite(led_r, HIGH);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, LOW);

  esp.begin(9600);
  WiFi.init(&esp);
  delay(20);

  if (WiFi.status() == WL_NO_SHIELD)
  {
  Serial.println(WiFi.status());
  asm volatile ("jmp=0");
  }

  while ( status != WL_CONNECTED)
  {
    Serial.println(WiFi.status());
    status = WiFi.begin(ssid, pass);
  }
}
