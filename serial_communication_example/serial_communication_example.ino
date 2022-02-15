#define MAX_BUFF_LEN  255
/* inspired by https://www.youtube.com/watch?v=I-3cRo7lId8 */

char c;
char str[MAX_BUFF_LEN];
uint8_t idx = 0;

void setup(){
  Serial.begin(115200);
}

void loop(){
  if(Serial.available()>0){
    c = Serial.read();
    if(c != '\n')
      str[idx++] = c;
    else{
      str[idx] =  '\0';
      idx = 0;

      Serial.print("Recieved: ");
      Serial.println(str);
    }
  }
}
