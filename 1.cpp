#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <iomanip>

using namespace std;

struct Date {
  int year;
  int month;
  int day;
  Date(){}
  Date (int new_year, int new_month, int new_day){
    year = new_year;
    if (new_month > 12 || new_month < 1){
      cout << "Month value is invalid: " << new_month;
      throw exception();
    }
    month = new_month;
    if (new_day > 31 || new_day < 1){
      cout << "Day value is invalid: " << new_day;
      throw exception();
    }
    day = new_day;
  }
};


ostream& operator<<(ostream& stream,const Date& date){
  stream << setw(4) << setfill('0') << date.year << "-" << setw(2) << setfill('0') << date.month << "-" << setw(2) << setfill('0')<< date.day;
  return stream;
}
bool operator>(const Date& date1,const Date& date2){
  if (date1.year > date2.year){
    return 1;
  }
  if (date1.year == date2.year){
    if (date1.month > date2.month){
      return 1;
    }
    else if (date1.month == date2.month){
      if (date1.day > date2.day){
        return 1;
      }
      else{
        return 0;
      }
      }
      else{
        return 0;
      }
    }
    else{
      return 0;
    }
  }
bool operator<(const Date& date1,const Date& date2){
  if (date1.year < date2.year){
    return 1;
  }
  if (date1.year == date2.year){
    if (date1.month < date2.month){
      return 1;
    }
    else if (date1.month == date2.month){
      if (date1.day < date2.day){
        return 1;
      }
      else{
        return 0;
      }
      }
      else{
        return 0;
      }
    }
    else{
      return 0;
    }
  }
bool operator==(const Date& data1, const Date& data2){
  if (data1.year == data2.year && data1.month == data2.month && data1.day == data2.day){
    return 1;
  }
  else return 0;
}

class Database {
public: 
  void AddEvent(const Date& date, const string& event){
    database[date].insert(event);
  }
  bool DeleteEvent(Date& date, const string& event){
    for (auto& item : database){
      if (item.first == date){
        for (auto& item2 : item.second){
          if (item2 == event){
            item.second.erase(item2);
            return true;
          }
        }
      }
    }
    return false;
  }
  int  DeleteDate(Date& date){
    int n;
    n = database[date].size();
    database.erase(date);
    return n;

  }
  void Find(const Date& date) {
    if (database.count(date) > 0){
    for (const auto& item : database[date]){
        cout << item << endl;
      }
    }
  }
  void Print() {
    for (const auto& item: database) {
      if (item.second.size() > 0){
      for (const auto& items : item.second){
        cout << item.first <<" " << items << endl;
      }
      }
  }
  } 
private:
  map<Date, set<string>> database; 
};

Date ReadDate(const string& str){
  stringstream s(str);
  string e;
  int year;
  s >> year;
  if (s.peek() != '-'){
    cout << "Wrong date format: " << str;
    throw exception();
  }
  s.ignore();
  int month;
  s >> month;
    if (s.peek() != '-'){
    cout << "Wrong date format: " << str;
    throw exception();
  }
  s.ignore(1);
  int day;

  if (s >> day){;}
  else {
      cout << "Wrong date format: " << str;
    throw exception();
 
  }
   if (!s.eof()) {
    cout << "Wrong date format: " << str;
    throw exception();
 
  }
  return Date(year, month, day);
}


int main() {
  try{
  Database db;
  for (string s; getline(cin, s);) {
    stringstream stream(s);
    string command, dayyear, sobitie;
    Date date;
    string event;
    stream >> command;
    if (command == ""){
      continue;
    }
    if (command == "Add" || command == "\nAdd"){
      stream >> dayyear >> event;
     date = ReadDate(dayyear);
      db.AddEvent(date, event);
    }
    else if (command == "Del" || command == "\nDel"){
      stream >> dayyear >> event;
      date = ReadDate(dayyear);


      if (event == ""){
        cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
      }
      else {
        bool suc = db.DeleteEvent(date, event);
          if (suc){
            cout << "Deleted successfully" << endl;
          }
          else{
            cout << "Event not found" << endl;
          }
      }
    }
    else if (command == "Find" || command == "\nFind"){
      stream >> dayyear;
      date = ReadDate(dayyear);
      db.Find(date);
    }
    else if (command == "Print" || command == "\nPrint"){
     db.Print();
    }
    else {
      cout << "Unknown command: " << command << endl; 
      throw exception();
    }
  }
  }catch(exception& ex){
    ;
  }
  return 0;
}