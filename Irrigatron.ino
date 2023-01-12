// O potenciômetro de cima simula o sensor de nível
// O potenciômetro mais a esquerda simula o sensor de umidade
// O relé vai conectado na porta 10

// variáveis do programa
const int pinoSensor = A0;
const int pinoNivel = A1;
const int pinoValvula = 10;
const int limiarSeco = 57;
int umidadeSolo = 0;
int nivel = 0;



void setup() {
  
  pinMode(pinoSensor, INPUT);
  pinMode(pinoNivel, INPUT);
  pinMode(pinoValvula, OUTPUT);
  // Desliga a válvula
  digitalWrite(pinoValvula, HIGH);

  Serial.begin(9600);


}

void loop() {
  // Mede a umidade a cada segundo. Faz isso durante uma hora (3600 segundos).
  for(int i=0; i < 3600; i++) {
    // Exibe a mensagem no Monitor serial
    Serial.println("Umidade: ");
    // Faz a leitura do sensor de umidade do solo
    umidadeSolo = analogRead(pinoSensor);
    // Faz a leitura do sensor de nível
    nivel = analogRead(pinoNivel);
    // Converte a variação do sensor de 0 a 1023 para 0 a 100
    umidadeSolo = map(umidadeSolo, 1023, 0, 0, 100);
    // Converte a variação do sensor de 0 a 1023 para 0 a 100
    nivel = map(nivel, 1023, 0, 4800, 3500);
    // Exibe a mensagem no Monitor serial:
    Serial.print(umidadeSolo);
    Serial.println(" %");
    Serial.println("Restante");
    Serial.print(nivel);
    Serial.println(" ml");
    // Espera um segundo
    delay(1000);
  }
  
  if(umidadeSolo < limiarSeco) {
    // Exibe a mensagem no Monitor serial:
    Serial.println("Regando");
    // Liga a válvula
    // Faz a leitura do sensor de nível
    umidadeSolo = analogRead(pinoSensor);
    // Converte a variação do sensor de 0 a 1023 para 0 a 100
     umidadeSolo = map(umidadeSolo, 1023, 0, 0, 100);
    do
    {
        digitalWrite(pinoValvula, LOW);
        // Faz a leitura do sensor de nível
      umidadeSolo = analogRead(pinoSensor);
      // Converte a variação do sensor de 0 a 1023 para 0 a 100
      umidadeSolo = map(umidadeSolo, 1023, 0, 0, 100);
    } while(umidadeSolo<limiarSeco);
    
    digitalWrite(pinoValvula, HIGH);
  }
  else {
    // Exibe a mensagem no Monitor serial:
    Serial.println("Solo Encharcado");
    // Espera o tempo estipulado
    delay(3000);
  }
}
