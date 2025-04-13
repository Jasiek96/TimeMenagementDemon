#include <DateTime.h>
#include <iostream>
#include <sstream>

int main(){
    DateTime dt(2025, 2, 30, 14, 30, 45);
    dt.display();


    std::cout << "Program testujący klasę DateTime" << std::endl;

    std::cout << "Tworzenie obiektu DateTime z domyślnymi wartościami (aktualna data i czas):" << std::endl;
    DateTime dt1;

    std::cout << "Domyślna data i czas: " << "+ test wyświetlania" << std::endl;
    dt1.display();

    std::cout << "Wpisanie sensownej daty w nowy obiekt " << std::endl;
    DateTime dt2(2023, 8, 15);
    dt2.display();

    std::cout << "Wpisanie sensownej daty i czasu w nowy obiekt " << std::endl;
    DateTime dt3(2023, 1, 15, 14, 30, 45);
    dt3.display();

    std::cout << "konstruktur kopiujący" << std::endl;
    DateTime dt4(dt3);
    dt4.display();

    std::cout << "Operator =" << std::endl;
    DateTime dt5= dt3;
    dt5.display();

    std::cout << "Test geterów " << dt5.get_year() << " "<< dt5.get_month() << " "<< dt5.get_day() << " "
                << dt5.get_hour() << " "<< dt5.get_minute() << " "<< dt5.get_second() << std::endl;

    std::cout << "Test seterów"<< std::endl;
    DateTime dt6;
    dt6.display();
    dt6.set_date_time(2036, 03, 15, 15, 15, 15);
    dt6.display();

    std::cout << "Test toString(), jak cokoliwek wczesniej sie wyświetliło to działa"<< std::endl;

    std::cout << "Test operatorów porównania 1 - True 0- False" <<std::endl;
    dt1.display();
    dt3.display();
    std::cout << "(dt1 < dt3): " << (dt1 < dt3) << std::endl;
    std::cout << "(dt1 > dt3): " << (dt1 > dt3) << std::endl;
    std::cout << "(dt1 == dt3): " << (dt1 == dt3) << std::endl;
    std::cout << "(dt1 != dt3): " << (dt1 != dt3) << std::endl;

    std::cout << "Test funkcji fromString()" << std::endl;
    DateTime dt7 = DateTime::fromString("2023-08-15 14:30:45");
    std::cout << "From string: ";
    dt7.display();

    std::cout << "Test funkcji isValid()" <<std::endl;
    DateTime dt8(2025, 4, 30, 14, 14, 14);
    std::cout << "dt8" << " poprawny"<<std::endl;
    dt8.display();
    DateTime dt9(2025, 4, 31, 14, 14, 14);
    std::cout << "dt9"<<" niepoprawny" <<std::endl;
    dt9.display();
    DateTime dt10(2024, 2, 28, 14, 14, 14);
    std::cout << "dt10" << " poprawny" <<std::endl;
    dt10.display();
    DateTime dt11(2024, 2, 29, 14, 14, 14);
    std::cout << "dt11"<< " poprawny"<<std::endl;
    dt11.display();
    DateTime dt12(2025, 2, 29, 14, 14, 14);
    std::cout << "dt12"<<" niepoprawny" <<std::endl;
    dt12.display();
    DateTime dt13(2025, 2, 30, 14, 14, 14);
    std::cout << "dt13"<<" niepoprawny" <<std::endl;
    dt13.display();
    DateTime dt14(2025, 2, 31, 14, 14, 14);
    std::cout << "dt14"<<" niepoprawny" <<std::endl;
    dt14.display();
    DateTime dt15(2025, 2, 32, 14, 14, 14);
    std::cout << "dt15"<<" niepoprawny" <<std::endl;
    dt15.display();
    DateTime dt16(2025, 5, 32, 14, 14, 14);
    std::cout << "dt16"<<" niepoprawny" <<std::endl;
    dt16.display();
    DateTime dt17(2025, 5, 10, 25, 14, 14);
    std::cout << "dt17"<<" niepoprawny" <<std::endl;
    dt17.display();
    DateTime dt18(2025, 5, 10, 14, 64, 14);
    std::cout << "dt18"<<" niepoprawny" <<std::endl;
    dt18.display();
    DateTime dt19(2025, 5, 10, 14, 4, 70);
    std::cout << "dt19"<<" niepoprawny" <<std::endl;
    dt19.display();
    DateTime dt20(2025, 5, 10, 14, -54, 14);
    std::cout << "dt20"<<" niepoprawny" <<std::endl;
    dt20.display();

    std::cout << "Test implemantacji funkcji isValid() używająć seterów" << std::endl;
    dt20.set_date_time(2024,2,29, 23,15,50);

    DateTime dt21(2025, 12, 32, 15,15,15);
    dt21.display();

    std::cout << "Test operatorów >> oraz <<" << std::endl;
    DateTime dt22;
    std::cin >> dt22;
    std::cout << dt22 << std::endl;
    return 0;
}