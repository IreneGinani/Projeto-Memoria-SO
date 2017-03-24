#ifndef _GPIO_H_
#define _GPIO_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <sstream>

class AlterarGPIO{

	public:

		AlterarGPIO(std::string GPIO, std::string direction){

			this->GPIO = GPIO;
			this->direction = direction;
			std::ofstream info;
			info.open("../../../../sys/class/gpio/" + GPIO + "/direction");
			info << direction;

		}
		
		~AlterarGPIO(){
			this->direction = "in";
		}
	
		void setDirection(std::string direcao){

			std::ofstream info;
			info.open("../../../../sys/class/gpio/" + GPIO + "/direction");
			info << direcao;


		}

		void setValue(std::string value){

			std::ofstream info;
			info.open("../../../../sys/class/gpio/" + GPIO + "/value");
			info << value;
			
			
		}


		std::string getDirection(){


			std::ifstream info("../../../../sys/class/gpio/" + GPIO + "/direction");
			std::string line;


			while(!info.eof()){
				getline(info,line);
			}

			return line;

		}

		std::string getValue(){

			std::ifstream info("../../../../sys/class/gpio/" + GPIO + "/value");
			std::string line;


			while(!info.eof()){
				getline(info,line);
			}

			return line;
		}

	private:

		std::string GPIO;
		std::string direction;

};

#endif
