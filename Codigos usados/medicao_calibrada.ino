#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int numSamples = 100;
int16_t accelX, accelY, accelZ;
int16_t gyroX, gyroY, gyroZ;

int32_t accelXSum = 0, accelYSum = 0, accelZSum = 0;
int32_t gyroXSum = 0, gyroYSum = 0, gyroZSum = 0;



//MEDIA DAS AMOSTRAS MEDIDOS EXPERIMENTALMENTE
float Ax_P  = 0.95;
float Ax_N  = -1.04;
float Ay_P  = 1.01;
float Ay_N  = -0.99;
float Az_P  = 0.64;
float Az_N  = -1.40;

//MEDIDA DE REFERENCIA
float accel_ref_X, accel_ref_Y,accel_ref_Z =0 ;


//VARIAVEL PARA O GANHO
float ganhox, ganhoy, ganhoz = 0;

//VARIAVEL PARA O Aoffset
float Aoffsetx , Aoffsety, Aoffsetz= 0; 

//VARIAVEL PARA A SAIDA REAL
float saida_x, saida_y, saida_z =0;

//VARIAVEL PARA O ANGULO
float angulo = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  mpu.initialize();
}


void loop() {
   //COLETANDO AMOSTRAS NA ORIENTAÇÃO POSITIVA (MESMO SENTIDO DA GRAVIDADE) - EIXO X

  Serial.println("Inicializando o sistema, posicione o sensor....");
  
  //delay(5000);

// ============================================================ REALIZANDO AS MEDIÇÕES MÉDIAS ============================================================

  mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);

  //OBTENDO O VALOR DE MEDIDA DE REFERÊNCIA, ONDE DIVIDIMOS POR 16384.0 POR CONTA DA ESPECIFICAÇÃO DO DATASHEET DA MPU 
  accel_ref_X = accelX/16384.0;
  accel_ref_Y = accelY/16384.0;
  accel_ref_Z = accelZ/16384.0;

  //CALCULO DO GANHO PARA CADA EIXO
  ganhox = (Ax_P - Ax_N)/2 ;
  ganhoy = (Ay_P - Ay_N)/2 ;
  ganhoz = (Az_P - Az_N)/2 ;

  //CALCULO DO Aoffset PARA CADA EIXO
  Aoffsetx = (Ax_P + Ax_N)/2 ;
  Aoffsety = (Ay_P + Ay_N)/2 ;
  Aoffsetz = (Az_P + Az_N)/2 ;

  Serial.println("Ganhox : " + String(ganhox) + "   Aoffsetx : " + String(Aoffsetx));
  Serial.println("Ganhoy : " + String(ganhoy) + "   Aoffsety : " + String(Aoffsetx));
  Serial.println("Ganhoz : " + String(ganhoz) + "   Aoffsetz : " + String(Aoffsetx));

  //CALCULO DA SAIDA REAL
  saida_x = (ganhox * accel_ref_X) + Aoffsetx;
  saida_y = (ganhoy * accel_ref_Y) + Aoffsety;
  saida_z = (ganhoz * accel_ref_Z) + Aoffsetz;


  Serial.println("saida real X (Com compensação) : " + String(saida_x) + " Saida sem compensação X : " + String(accel_ref_X));
  Serial.println("saida real Y (Com compensação): " + String(saida_y) + " Saida sem compensação Y : " + String(accel_ref_Y));
  Serial.println("saida real Z (Com compensação): " + String(saida_z) + " Saida sem compensação Z : " + String(accel_ref_Z));

  delay(5000);
}




