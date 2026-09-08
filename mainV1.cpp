#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <ranges>

//struct definition for moving averages
struct movingaverage{
        double fiftyday;
        double twohundredday;  //edited so that it no longer has a date entry
};
//struct definition for original relevant data
struct PriceRecord{
        int date;
        double price;
    };

int parseDate(const std::string& dateTime);
double calculateStartSums(std::vector<PriceRecord> dataVector);
std::vector<double> calculate_averages(int nDayRollingAverage, std::vector<PriceRecord> dataVector);


int main(){
    //variable intitialization
    const int lower = 50;    //change these variables for different rolling average lengths
    const int higher = 200;
    const int length_of_csv_file = 6564;
    std::string token;
    std::string strInput{};
    std::vector<PriceRecord> marketData;
    std::vector<movingaverage> averagedata;
    marketData.reserve(length_of_csv_file);
    averagedata.reserve(length_of_csv_file);
    std::ifstream inf{"ftse100_data.csv"};   //data headers: date,open,high,low,close,volume
    int count = 0;
    int datevar;
    double closeprice;

    // exits if file doesn't exist/is already open.
    if(!inf){
        std::cerr <<"Couldn't be read from";
        return 1;
    }    
        
    while (std::getline(inf,strInput)){
    std::stringstream ss(strInput);
    count = 0;

    while(std::getline(ss,token,',')){
        
        switch(count){
            case 0:
                try{datevar = parseDate(token);}
                catch(const std::exception& e){
                    std::cout <<"error with data";
                    return 1;  
                };
                break;
            case 4:
                try{closeprice = stof(token);} 
                catch(const std::exception& e){
                    std::cout << "error with data";
                    return 1;
                }
                break;
            }
            count++;
    }
    marketData.push_back({datevar,closeprice});
}

//calculating 200 day moving average
// need to edit the numbers 

    const auto fiftyDayAverages = calculate_averages(lower, marketData);
    std::vector<double> intermediate2(
        fiftyDayAverages.begin() + (higher - lower), // removes the first entries from the array of the n-day average with the smaller n
        fiftyDayAverages.end());
    std::vector<double> intermediate1 = calculate_averages(higher,marketData);

//placing averages into vector
    for(auto&& [fiftyday,twohundredday] : std::views::zip(intermediate2,intermediate1)){
        averagedata.emplace_back(fiftyday,twohundredday);
    }

    count = 0;
    for(const auto& case1 : averagedata){
        if(count != 0 && case1.fiftyday > case1.twohundredday &&averagedata[count-1].fiftyday < averagedata[count-1].twohundredday){
            std::cout << "Positive Cross on: " << marketData[count+higher].date << "\n";
        }
        count ++;
    }
    return 0;
}

//extracting relevant data from csv file
int parseDate(const std::string& dateTime) {
    std::string year = dateTime.substr(0, 4);
    std::string month = dateTime.substr(5, 2);
    std::string day = dateTime.substr(8, 2);
    
    return std::stoi(year + month + day);
}

//createt the starting sums to then calculate the rolling average.
double calculateStartSums(std::vector<PriceRecord> dataVectorSubset){
    double sum = 0;
    for(int i = 0;i<dataVectorSubset.size();i++){
        sum+= dataVectorSubset[i].price;
    }
    return sum;
    
}

//calculate the rolling averages
std::vector<double> calculate_averages(int nDayRollingAverage, std::vector<PriceRecord> dataVector){
    std::vector<double> finalaverages;
    double startingSum = calculateStartSums(std::vector<PriceRecord> (dataVector.begin(),dataVector.begin()+nDayRollingAverage));
    
    for(int i = nDayRollingAverage;i<dataVector.size();i++){
        finalaverages.push_back(startingSum/nDayRollingAverage);
        startingSum-= dataVector[i-nDayRollingAverage].price;
        startingSum+= dataVector[i].price;
    }
    
return finalaverages;
}