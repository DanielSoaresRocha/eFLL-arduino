#include <Fuzzy.h>

// Instantiating a Fuzzy object
Fuzzy *fuzzy = new Fuzzy();

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
   /*----------------------------------------------------
                       Entrada
   -----------------------------------------------------*/
   //variável linguistica 1
   FuzzyInput *sensor1 = new FuzzyInput(1); 
  
   //conjuntos
   FuzzySet *baixo1 = new FuzzySet(250, 250, 327, 405);
   FuzzySet *medio1 = new FuzzySet(327, 405, 405, 482);
   FuzzySet *alto1 = new FuzzySet(405, 482, 560, 560);

   //adicionando conjuntos ao sensor1
   sensor1->addFuzzySet(baixo1);
   sensor1->addFuzzySet(medio1);
   sensor1->addFuzzySet(alto1);

   //adicionando sensor1 ao fuzzy
   fuzzy->addFuzzyInput(sensor1);
   
   //----------------------------------------------------
   
   //variável linguistica 2
   FuzzyInput *sensor2 = new FuzzyInput(2); 
  
   //conjuntos
   FuzzySet *baixo2 = new FuzzySet(250, 250, 327, 405);
   FuzzySet *medio2 = new FuzzySet(327, 405, 405, 482);
   FuzzySet *alto2 = new FuzzySet(405, 482, 560, 560);

   //adicionando conjuntos ao sensor2
   sensor2->addFuzzySet(baixo2);
   sensor2->addFuzzySet(medio2);
   sensor2->addFuzzySet(alto2);

   //adicionando sensor2 ao fuzzy
   fuzzy->addFuzzyInput(sensor2);

   //----------------------------------------------------
   
   //variável linguistica 3
   FuzzyInput *sensor3 = new FuzzyInput(3); 
  
   //conjuntos
   FuzzySet *baixo3 = new FuzzySet(250, 250, 327, 405);
   FuzzySet *medio3 = new FuzzySet(327, 405, 405, 482);
   FuzzySet *alto3 = new FuzzySet(405, 482, 560, 560);

   //adicionando conjuntos ao sensor3
   sensor3->addFuzzySet(baixo3);
   sensor3->addFuzzySet(medio3);
   sensor3->addFuzzySet(alto3);

   //adicionando sensor3 ao fuzzy
   fuzzy->addFuzzyInput(sensor3);

   //----------------------------------------------------
   
   //variável linguistica 4
   FuzzyInput *fase = new FuzzyInput(4); 
  
   //conjuntos
   FuzzySet *fase1 = new FuzzySet(1, 1, 1, 1);
   FuzzySet *fase2 = new FuzzySet(2, 2, 2, 2);
   FuzzySet *fase3 = new FuzzySet(3, 3, 3, 3);

   //adicionando conjuntos a fase
   fase->addFuzzySet(fase1);
   fase->addFuzzySet(fase2);
   fase->addFuzzySet(fase3);

   //adicionando fase ao fuzzy
   fuzzy->addFuzzyInput(fase);

   /*----------------------------------------------------
                       Saída
   -----------------------------------------------------*/
   FuzzyOutput *umidade = new FuzzyOutput(1);

   //conjuntos
   FuzzySet *seco = new FuzzySet(0, 0, 25, 50);
   FuzzySet *umido = new FuzzySet(25, 50, 50, 75);
   FuzzySet *encharcado = new FuzzySet(40, 75, 100, 100);

   //adicionando conjuntos umidade
   umidade->addFuzzySet(seco);
   umidade->addFuzzySet(umido);
   umidade->addFuzzySet(encharcado);

   //adicionando saida umidade ao fuzzy
   fuzzy->addFuzzyOutput(umidade);
    
   /*----------------------------------------------------
                       Regras
   -----------------------------------------------------*/
   //----------------------------REGRA 1--------------------------------------
   //se a fase é 1 e sensor1 é baixo: a umidade é seca
   FuzzyRuleAntecedent *seFase1Esensor1Baixo = new FuzzyRuleAntecedent();
   seFase1Esensor1Baixo->joinWithAND(fase1, baixo1);//ANTECEDENTE

   FuzzyRuleConsequent *umidadeSeco = new FuzzyRuleConsequent();
   umidadeSeco->addOutput(seco);//CONSEQUENTE

   FuzzyRule *fuzzyRule1 = new FuzzyRule(1, seFase1Esensor1Baixo, umidadeSeco);
   fuzzy->addFuzzyRule(fuzzyRule1);

   
   //---------------------------REGRA 2-------------------------------------
   //se a fase é fase1 e sensor1 é médio então umidade é umido
   FuzzyRuleAntecedent *seFase1Esensor1Medio = new FuzzyRuleAntecedent();
   seFase1Esensor1Baixo->joinWithAND(fase1, medio1);//ANTECEDENTE

   FuzzyRuleConsequent *umidadeUmido = new FuzzyRuleConsequent();
   umidadeUmido->addOutput(umido);//CONSEQUENTE

   FuzzyRule *fuzzyRule2 = new FuzzyRule(2, seFase1Esensor1Medio, umidadeUmido);
   fuzzy->addFuzzyRule(fuzzyRule2);
   
   //---------------------------REGRA 3--------------------------------------
   //se a fase é 1 e sensor1 é alto então umidade é encharcado
   FuzzyRuleAntecedent *seFase1Esensor1Alto = new FuzzyRuleAntecedent();
   seFase1Esensor1Alto->joinWithAND(fase1, alto1);//ANTECEDENTE

   FuzzyRuleConsequent *umidadeEncharcado = new FuzzyRuleConsequent();
   umidadeEncharcado->addOutput(encharcado);//CONSEQUENTE

   FuzzyRule *fuzzyRule3 = new FuzzyRule(3, seFase1Esensor1Alto, umidadeEncharcado);
   fuzzy->addFuzzyRule(fuzzyRule3);

   //---------------------------REGRA 4--------------------------------------
   //se a fase é 2, e sensor1 é baixo, e sensor2 é baixo então umidade é seco
   FuzzyRuleAntecedent *seFase2Esensor1baixo = new FuzzyRuleAntecedent();
   seFase2Esensor1baixo->joinWithAND(fase2, baixo1);//ANTECEDENTE

   FuzzyRuleAntecedent *sensor2Baixo = new FuzzyRuleAntecedent();
   sensor2Baixo->joinSingle(baixo2);//ANTECEDENTE

   FuzzyRuleAntecedent *seFase2Esensor1BaixoEsensor2Baixo = new FuzzyRuleAntecedent();
   seFase2Esensor1BaixoEsensor2Baixo->joinWithAND(seFase2Esensor1baixo, sensor2Baixo);//ANTECEDENTE

   FuzzyRuleConsequent *umidadeSeco2 = new FuzzyRuleConsequent();
   umidadeSeco2->addOutput(seco);//CONSEQUENTE

   FuzzyRule *fuzzyRule4 = new FuzzyRule(4, seFase2Esensor1BaixoEsensor2Baixo, umidadeSeco2);
   fuzzy->addFuzzyRule(fuzzyRule4);

   //---------------------------REGRA 5--------------------------------------
   //se a fase é 2 e sensor1 é medio e sensor2 é medio então umidade é umido
   FuzzyRuleAntecedent *seFase2Esensor1Medio = new FuzzyRuleAntecedent();
   seFase2Esensor1Medio->joinWithAND(fase2, medio1);//ANTECEDENTE

   FuzzyRuleAntecedent *sensor2Medio = new FuzzyRuleAntecedent();
   sensor2Medio->joinSingle(medio2);//ANTECEDENTE

   FuzzyRuleAntecedent *seFase2Esensor1MedioEsensor2Medio = new FuzzyRuleAntecedent();
   seFase2Esensor1MedioEsensor2Medio->joinWithAND(seFase2Esensor1Medio, sensor2Medio);//ANTECEDENTE

   FuzzyRuleConsequent *umidadeUmido2 = new FuzzyRuleConsequent();
   umidadeUmido2->addOutput(umido);//CONSEQUENTE

   FuzzyRule *fuzzyRule5 = new FuzzyRule(5, seFase2Esensor1MedioEsensor2Medio, umidadeUmido2);
   fuzzy->addFuzzyRule(fuzzyRule5);

   //---------------------------REGRA 6---------------------------(outra forma de fazer)
   //se a fase é 2 e sensor1 é alto e sensor2 é alto então umidade é encharcado
   FuzzyRuleAntecedent *seFase2Esensor1Alto = new FuzzyRuleAntecedent();
   seFase2Esensor1Alto->joinWithAND(fase2, alto1);//ANTECEDENTE

   FuzzyRuleAntecedent *seFase2Esensor1AltoEsensor2Alto = new FuzzyRuleAntecedent();
   seFase2Esensor1AltoEsensor2Alto->joinWithAND(seFase2Esensor1Alto, alto2);//ANTECEDENTE //passagem direta(ver documentação)

   FuzzyRuleConsequent *umidadeEncharcado2 = new FuzzyRuleConsequent();
   umidadeEncharcado2->addOutput(encharcado);//CONSEQUENTE

   FuzzyRule *fuzzyRule6 = new FuzzyRule(6, seFase2Esensor1AltoEsensor2Alto, umidadeEncharcado2);
   fuzzy->addFuzzyRule(fuzzyRule6);

   //---------------------------REGRA 7---------------------------
   //se fase é 3 e sensor1 é baixo e sensor2 é baixo, e sensor3 é baixo então umidade é seco
   FuzzyRuleAntecedent *seFase3Esensor1Baixo = new FuzzyRuleAntecedent();
   seFase3Esensor1Baixo->joinWithAND(fase3, baixo1);//ANTECEDENTE

   FuzzyRuleAntecedent *seSensor2BaixoEsensor3Baixo = new FuzzyRuleAntecedent();
   seSensor2BaixoEsensor3Baixo->joinWithAND(baixo2, baixo3);//ANTECEDENTE

   FuzzyRuleAntecedent *seFase3Esensor1BaixoESensor2BaixoEsensor3Baixo = new FuzzyRuleAntecedent();
   seFase3Esensor1BaixoESensor2BaixoEsensor3Baixo->joinWithAND(seFase3Esensor1Baixo,seSensor2BaixoEsensor3Baixo);//ANTECEDENTE

   FuzzyRuleConsequent *umidadeSeco3 = new FuzzyRuleConsequent();
   umidadeSeco3->addOutput(seco);//CONSEQUENTE

   FuzzyRule *fuzzyRule7 = new FuzzyRule(7, seFase3Esensor1BaixoESensor2BaixoEsensor3Baixo, umidadeSeco3);
   fuzzy->addFuzzyRule(fuzzyRule7);

   //---------------------------REGRA 8---------------------------
   //se fase é 3, e sensor1 é medio e sensor2 é medio e sendor3 é medio então umidade é umido;
   FuzzyRuleAntecedent *seFase3Esensor1Medio = new FuzzyRuleAntecedent();
   seFase3Esensor1Medio->joinWithAND(fase3, medio1);//ANTECEDENTE

   FuzzyRuleAntecedent *seSensor2MedioEsensor3Medio = new FuzzyRuleAntecedent();
   seSensor2MedioEsensor3Medio->joinWithAND(medio2, medio3);//ANTECEDENTE

   FuzzyRuleAntecedent *seFase3Esensor1MedioESensor2MedioEsensor3Medio = new FuzzyRuleAntecedent();
   seFase3Esensor1MedioESensor2MedioEsensor3Medio->joinWithAND(seFase3Esensor1Medio,seSensor2MedioEsensor3Medio);//ANTECEDENTE

   FuzzyRuleConsequent *umidadeUmido3 = new FuzzyRuleConsequent();
   umidadeUmido3->addOutput(seco);//CONSEQUENTE

   FuzzyRule *fuzzyRule8 = new FuzzyRule(8, seFase3Esensor1MedioESensor2MedioEsensor3Medio, umidadeUmido3);
   fuzzy->addFuzzyRule(fuzzyRule8);

   //---------------------------REGRA 9---------------------------
   //se fase é fase3 e sensor1 é alto e sensor2 é alto e sensor3 é alto então umidade é encharcado
   FuzzyRuleAntecedent *seFase3Esensor1Alto = new FuzzyRuleAntecedent();
   seFase3Esensor1Alto->joinWithAND(fase3, alto1);//ANTECEDENTE

   FuzzyRuleAntecedent *seSensor2AltoEsensor3Alto = new FuzzyRuleAntecedent();
   seSensor2AltoEsensor3Alto->joinWithAND(alto2, alto3);//ANTECEDENTE

   FuzzyRuleAntecedent *seFase3Esensor1AltoESensor2AltoEsensor3Alto = new FuzzyRuleAntecedent();
   seFase3Esensor1AltoESensor2AltoEsensor3Alto->joinWithAND(seFase3Esensor1Alto,seSensor2AltoEsensor3Alto);//ANTECEDENTE

   FuzzyRuleConsequent *umidadeEncharcado3 = new FuzzyRuleConsequent();
   umidadeEncharcado3->addOutput(encharcado);//CONSEQUENTE

   FuzzyRule *fuzzyRule9 = new FuzzyRule(9, seFase3Esensor1AltoESensor2AltoEsensor3Alto, umidadeEncharcado3);
   fuzzy->addFuzzyRule(fuzzyRule9);

}

void loop() {
  int inputSensor1 = random(250, 560);
  int inputSensor2 = random(250, 560);
  int inputSensor3 = random(250, 560);
  int inputFase = random(1, 3);

  Serial.print("Sensor 1 = ");
  Serial.println(inputSensor1);
  Serial.print("Sensor 2 = ");
  Serial.println(inputSensor2);
  Serial.print("Sensor 3 = ");
  Serial.println(inputSensor3);
  Serial.print("Fase = ");
  Serial.println(inputFase);

  fuzzy->setInput(1, inputSensor1);
  fuzzy->setInput(2, inputSensor2);
  fuzzy->setInput(3, inputSensor3);
  fuzzy->setInput(4, inputFase);

  fuzzy->fuzzify();
  verifica();

  float output = fuzzy->defuzzify(1);//int

  Serial.print("Umidade: ");
  Serial.println(output);
  // wait 10 seconds
  delay(10000);
  Serial.println();
  Serial.println("_________________________________________________");
  
}

void verifica(){
   int j = 0;
    for (int i = 1; i <= 9; i++) {
        bool wasTheRulleFired = fuzzy->isFiredRule(i);
        if (wasTheRulleFired == 1) {
          Serial.print("regra ");
          Serial.print(i);
          Serial.println(" foi atingida");
          j++;
        }    
    }
    if(j==0)
    Serial.println("Nenhuma regra foi atingida ");
}
