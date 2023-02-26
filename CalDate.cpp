#include <iostream>

using namespace std;

class Data
{
    private:
        int year_;
        int month_;
        int day_;

    public:
        void SetData(int year, int month, int date)
        {
            year_ = year;
            month_ = month;
            day_ = date;
        }
        void AddDay(int inc)
        {
            day_ += inc;
            
            if (month_ == 2 && day_ > 28) {
                day_ = day_ - 28;
                month_++;
            }else if (month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11 && day_ > 30) {
                day_ = day_ - 30;
                month_++;
            }else if(day_ > 31) {
                day_ = day_ - 31;
                month_++;
            }
        }    
            
        void AddMonth(int inc)
        {
            month_ += inc;
            if(month_ > 12) {
                month_ = month_ - 12;
                year_++;
            }
        }
        void AddYear (int inc)
        {
            year_ += inc;
        }
        void ShowDate()
        {
            std::cout << year_ << "년" << month_ <<"월" << day_<<"일" << std::endl;
        }
};

int main()
{
    Data data;
    int inc;
    int menu;
    
    while(1){
        cout << endl;
        cout <<endl;
        cout << "메뉴" << endl;
        cout << "1. 오늘의 날짜는?" << endl;
        cout << "2. add day" << endl;
        cout << "3. add month" << endl;
        cout << "4. add year" << endl;
        cout << "5. show data" << endl;
        cout << "6. end" << endl;
        cout <<endl;
        cout <<endl;

        cout << "input menu : " <<endl;
        cin >> menu;
        cout << endl;
        cout << endl;

        switch (menu)
        {
            case 1:
                int year, month, date;

                std::cout << "set today year : ";
                std::cin >> year;
                std::cout << "set today month : ";
                std::cin >> month;
                std::cout << "set today date : ";
                std::cin >> date;

                data.SetData(year, month, date);

                break;

            case 2:
                cout << "input you want add date : ";
                cin >> inc;
                data.AddDay(inc);
                break;

            case 3:
                cout << "input you want add month : ";
                cin >> inc;
                data.AddMonth(inc);
                break;

            case 4:
                cout << "input you want add date : ";
                cin >> inc;
                data.AddYear(inc);
                break;

            case 5:
                data.ShowDate();   
                break;

            case 6:
                cout << "프로그램 종료" << endl;
                exit(1);
                        
            default:
                break;
        }
    }
     
    return 0;
}
