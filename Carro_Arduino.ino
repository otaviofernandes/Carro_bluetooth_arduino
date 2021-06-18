#define tempo 10
const int a1  = 11;   
const int a2  = 10;   
const int b1  = 9;  
const int b2  = 6;
const int led_esquerda  = 3;
const int led_direita  = 5; 
int Pinofalante = 8;
const int BTState = 2;

int i = 0;
int j = 0;
int state_rec;
int vSpeed = 255;
int frequencia = 0;  
char state;

void setup() {
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(led_esquerda, OUTPUT);
  pinMode(led_direita, OUTPUT); 
  pinMode(Pinofalante, OUTPUT);
  pinMode(BTState, INPUT);

  Serial.begin(9600);
}


void loop() {
  // Para o carro quando a conexão com Bluetooth é perdida ou desconectada.
  if (digitalRead(BTState) == LOW) {
    state_rec = 'S';
  }
  // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
  }
  if (state != 'S') {
    Serial.print(state);
  }
  if (state == 'B') { // Movimenta para frente.
    analogWrite(b1, vSpeed);
    analogWrite(a1, vSpeed);
    analogWrite(a2, 0);
    analogWrite(b2, 0);
  }
  else if (state == 'F') { // Movimenta para trás.
    analogWrite(a1, 0);
    analogWrite(b1, 0);
    analogWrite(b2, vSpeed);
    analogWrite(a2, vSpeed);
  }
  else if (state == 'L') {   // Movimenta para esquerda.
    digitalWrite(led_esquerda, HIGH);
    analogWrite(a1, 0);
    analogWrite(a2, vSpeed);
    analogWrite(b1, vSpeed);
    analogWrite(b2, 0);
  }
  else if (state == 'R') {   // Movimenta para direita.
    digitalWrite(led_direita, HIGH);
    analogWrite(a1, vSpeed);
    analogWrite(a2, 0);
    analogWrite(b1, 0);
    analogWrite(b2, vSpeed);
  }
  else if (state == 'S') {   // Permanece parado.
    analogWrite(a1, 0);
    analogWrite(a2, 0);
    analogWrite(b1, 0);
    analogWrite(b2, 0);
    digitalWrite(led_esquerda, LOW);
    digitalWrite(led_direita, LOW);
  }
  else if (state == 'V') {
    if (j == 0) {
        for (frequencia = 150; frequencia < 1800; frequencia += 1){
          tone(Pinofalante, frequencia, tempo);
          delay(1);
        }  
        for (frequencia = 1800; frequencia > 150; frequencia -= 1)   
        {    
          tone(Pinofalante, frequencia, tempo);
          delay(1);
        }      
      j = 1;
    }
    else if (j == 1) {
      noTone(Pinofalante);
      j = 0;
    }
    state = 'n';
  }
}
