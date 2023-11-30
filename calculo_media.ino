#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int numSamples = 100;
int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;

int32_t accelXSum = 0, accelYSum = 0, accelZSum = 0;
int32_t gyroXSum = 0, gyroYSum = 0, gyroZSum = 0;


//VARIAVEIS PARA COLETAR AS 100 AMOSTRAS PARA REALIZAR A CALIBRAÇÃO -> ACELERAÇÃO NEGATIVA (EIXO NO SENTIDO OPOSTO DA GRAVIDADE)
float accelX_N = 0, accelY_N = 0, accelZ_N = 0;

//VARIAVEIS PARA COLETAR AS 100 AMOSTRAS PARA REALIZAR A CALIBRAÇÃO -> ACELERAÇÃO POSITIVA (EIXO NO MESMO SENTIDO DA GRAVIDADE)
float accelX_P = 0, accelY_P = 0, accelZ_P = 0;


void setup() {
  Serial.begin(9600);

  Wire.begin();
  mpu.initialize();
}


void loop() {
   //COLETANDO AMOSTRAS NA ORIENTAÇÃO POSITIVA (MESMO SENTIDO DA GRAVIDADE) - EIXO X

// ============================================================ EIXO X POSITIVO ============================================================
  Serial.println("Coletando amostras do eixo X positivo, posicione o sensor adequadamente....");
  delay(20000);
  Serial.println("Iniciando as medidas de +X");

  for (int i = 0; i < numSamples; i++) {
    //MEDIDA X POSITIVA
    mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);

    Serial.println("Accel +X: " + String(accelX/16384.0)); //DIVIDIMOS POR 16384.0 POR CONTA DA ESPECIFICAÇÃO DO DATASHEET DA MPU 
    accelX_P += accelX/16384.0;
    delay(10);
  }
  
  accelX_P = accelX_P/100 ; //CALCULANDO A MÉDIA DAS AMOSTRAS PARA COLETAR A+g,x 

// ============================================================ EIXO X NEGATIVO ============================================================

  Serial.println("Coletando amostras do eixo X negativo, posicione o sensor adequadamente....");
  delay(20000);
  Serial.println("Iniciando as medidas de -X");
  
  //COLETANDO AMOSTRAS NA ORIENTAÇÃO NEGATIVA (SENTIDO OPOSTO DA GRAVIDADE) - EIXO X
  Serial.println("Coletando amostras do eixo X negativo");
  for (int i = 0; i < numSamples; i++) {
    mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);
    Serial.println("Accel -X: " + String(accelX/16384.0));
    accelX_N += accelX/16384.0;
    delay(10);
  }
  
  accelX_N = accelX_N/100 ; //CALCULANDO A MÉDIA DAS AMOSTRAS PARA COLETAR A-g,x 

// ============================================================ EIXO Y POSITIVO ============================================================

  //COLETANDO AMOSTRAS NA ORIENTAÇÃO POSITIVA (MESMO SENTIDO DA GRAVIDADE) - EIXO Y

  Serial.println("Coletando amostras do eixo Y positivo, posicione o sensor adequadamente....");
  delay(20000);
  Serial.println("Iniciando as medidas de +Y");
  
  for (int i = 0; i < numSamples; i++) {
    mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);
    Serial.println("Accel +Y: " + String(accelY/16384.0));
    accelY_P += accelY/16384.0;
    delay(10);
  }
  accelY_P = accelY_P/100 ; //CALCULANDO A MÉDIA DAS AMOSTRAS PARA COLETAR A+g,y 

// ============================================================ EIXO Y NEGATIVO ============================================================

  Serial.println("Coletando amostras do eixo Y negativo, posicione o sensor adequadamente....");
  delay(20000);
  Serial.println("Iniciando as medidas de -Y");
  
  for (int i = 0; i < numSamples; i++) {
    mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);
    Serial.println("Accel -Y: " + String(accelY/16384.0));
    accelY_N += accelY/16384.0;
    delay(10);
  }
  accelY_N = accelY_N/100 ; //CALCULANDO A MÉDIA DAS AMOSTRAS PARA COLETAR A-g,y 

// ============================================================ EIXO Z POSITIVO ============================================================

  //COLETANDO AMOSTRAS NA ORIENTAÇÃO POSITIVA (MESMO SENTIDO DA GRAVIDADE) - EIXO Z

  Serial.println("Coletando amostras do eixo Z positivo, posicione o sensor adequadamente....");
  delay(20000);
  Serial.println("Iniciando as medidas de +Z");
  
  for (int i = 0; i < numSamples; i++) {
    mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);
    Serial.println("Accel +Z: " + String(accelZ/16384.0));
    accelZ_P += accelZ/16384.0;
    delay(10);
  }
  accelZ_P = accelZ_P/100 ; //CALCULANDO A MÉDIA DAS AMOSTRAS PARA COLETAR A+g,Z

// ============================================================ EIXO Z NEGATIVO ============================================================

  Serial.println("Coletando amostras do eixo Z negativo, posicione o sensor adequadamente....");
  delay(20000);
  Serial.println("Iniciando as medidas de -Z");
  
  for (int i = 0; i < numSamples; i++) {
    mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);
    Serial.println("Accel -Z: " + String(accelZ/16384.0));
    accelZ_N += accelZ/16384.0;
    delay(10);
  }
  accelZ_N = accelZ_N/100 ; //CALCULANDO A MÉDIA DAS AMOSTRAS PARA COLETAR A-g,Z 




  Serial.println("VALOR MEDIO DO -X: " + String(accelX_N));
  Serial.println("VALOR MEDIO DO +X: " + String(accelX_P));
  Serial.println("VALOR MEDIO DO -Y: " + String(accelY_N));
  Serial.println("VALOR MEDIO DO +Y: " + String(accelY_P));
  Serial.println("VALOR MEDIO DO -Z: " + String(accelZ_N));
  Serial.println("VALOR MEDIO DO +Z: " + String(accelZ_P));


  while (true) {
  ;

  }
}
