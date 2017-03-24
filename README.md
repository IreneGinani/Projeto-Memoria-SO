#Projeto de Sistemas Operacionais

###Descrição...

Fazer um visualializador de memória onde acende o led verde para utilização menor que 25%, o led amarelo e o verde entre 25% e 50%, entre 50% e 75% os leds amarelo, verde e vermelho, entre 75% e 100% todos os leds piscam até apertar o botão e matar o processo que está consumindo memória...

##Compilação e execução

**Compilação**
```shell
g++ -std=c++11 -pedantic -I include/ src/driver.cpp -o bin/run
```

**Execução**
```shell
sh run.sh
```