#include <iostream>

int main()
{
    int edad = 5;

    std::cout << "Mi edad es:" <<edad << std::endl;

    if(edad >18){
        std::cout <<"Es mayor de edad" << std::endl;
    }else{
        std::cout <<"Es menor de edad" << std::endl;

    }

    for(int i=0; i<5; i++){
        std::cout << "El valor de i es: " << i << std::endl;

    }

    return 0;

}