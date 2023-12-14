int main(){
    double height, weight;
    std::cout << "height(m) >";
    std::cin >> height;
    std::cout << "\n";

    std::cout << "weight(kg) >";
    std::cin >> weight;
    std::cout << "\n";

    double bmi = weight / (height * height);
    std::cout << "BMI=" << bmi << "\n";

    // bool b{};
    // std::cin >> std::boolalpha >> b;
    // std::cout << std::boolalpha << b;

    auto status = [](double bmi){
        if(bmi < 18.5) return "UnderWeight.";
        else if(bmi < 25.0) return "Normal.";
        else if(bmi < 30.0) return "OverWeight.";
        else return "Obese.";
    };

    std::cout << status(bmi) << "\n";
}
// ./convert < bmi.txt | ./bmi
//cat bmi.txt | ./convert | ./bmi
//パイプで標準出力を標準入力にする