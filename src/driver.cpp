#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include <chrono>
#include <stdlib.h>
#include <chrono>
#include <iterator>
#include <thread>
#include "sys/types.h"
#include <csignal>
#include <cstdio>
#include "unistd.h"
#include "gpio.h"

static unsigned long long totalmem, memfree;
double porcentagem;

void init() 
{
        FILE* arquivo = fopen("/proc/meminfo", "r");
        rewind(arquivo);

        fscanf(arquivo, "MemTotal: %llu kB\n", &totalmem);
        fscanf(arquivo,"MemFree: %llu kB", &memfree);
                
        
        fclose(arquivo);
}


void identificandoProcesso(std::vector<int> &dados){


	system("ps -e -o pid,%mem,%cpu --sort=-pmem,-pcpu | head -2 >> dados.txt");

	std::string input;
	std::ifstream file("dados.txt");
	int counter = 0;
	int informacao = 0;
	

	while(std::getline(file, input)) {
    	std::istringstream ss(input);
        std::string token;
        while(getline(ss, token, ' ')) {
            if (counter == 1){
            	std::stringstream aux(token);
            	informacao = atoi(aux.str().c_str());
            	dados.push_back(informacao);
            }
        }

        counter++;

    }

}
void acenderLeds(std::vector<int> &dados){
		
	init();

	porcentagem = 100.0 -  memfree*100/ totalmem;
	std::cout << porcentagem << "%\n";

	AlterarGPIO ledVerm("gpio50","in");
	AlterarGPIO ledVerd("gpio15","in");
	AlterarGPIO ledAm("gpio14","in");
	AlterarGPIO botao("gpio115","in");
	int counter = 0;

	if(porcentagem <= 25.0){
		ledVerd.setDirection("out");
		ledAm.setValue("0");
		ledVerm.setValue("0");
		ledVerd.setValue("1");
	}else if ((porcentagem > 25.0) && (porcentagem <= 50.0)){
		ledVerd.setDirection("out");
		ledAm.setDirection("out");
		ledVerd.setValue("1");
		ledAm.setValue("1");
	}else if ((porcentagem> 50.0) && (porcentagem <= 75.0)){
		ledAm.setDirection("out");
		ledVerm.setDirection("in");
		ledVerd.setDirection("out");
		ledVerm.setValue("1");
		ledAm.setValue("1");
		ledVerd.setValue("1");
	}else if(porcentagem > 75.0){

		ledVerd.setDirection("in");
		ledAm.setDirection("in");
		ledVerm.setDirection("in");

		std::this_thread::sleep_for (std::chrono::milliseconds(200));

		ledVerd.setDirection("out");
		ledAm.setDirection("out");
		ledVerm.setDirection("out");

		ledVerd.setValue("1");
		ledAm.setValue("1");
		ledVerm.setValue("1");

		if (botao.getValue() == "1"){

			kill(dados[1], SIGKILL);

                	ledVerd.setValue("0");
               		ledAm.setValue("0");
                	ledVerm.setValue("0");
			counter++;
			std::this_thread::sleep_for (std::chrono::milliseconds(200));
		

		}
		if(counter == 1) {

			ledVerd.setValue("0");
			ledAm.setValue("0");
			ledVerm.setValue("0");
			 std::this_thread::sleep_for (std::chrono::milliseconds(2000));
		}
	}

	

}

int main(){
	std::vector<int> dados;
		while(true){
			identificandoProcesso(dados);
			acenderLeds(dados);
			sleep(1);
		}

}



