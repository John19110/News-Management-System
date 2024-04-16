#include<iostream>
#include<ctime>
#include<string>
#include<iomanip>
#include<sstream>
#include<map>
using namespace std;
class News

{
public:
	string Title,Description,Category;
    int AvgRate;
	map<int,int> Rates;
 	tm ArticleDateAndTime; // it is a builtin struct not a normal varible 

	// Initialize the date and time components
   // { 59, 59, 14, 14, 4, 121}= 2021-05-14 14:59:59

		public:

            //Constractor
			News(string Title ,string Description,string Category,int AvgRate,tm DateAndTime);

            //Getters
            string getTitle() const;
            string getDescription() const;
            string getCategory() const;
            int getAvgRate() ;
            string getArticleDateAndTime() const;

            // Setters
            void setTitle(const string& Title);
            void setDescription(const string& Description);
            void setCategory(const string& Category);
            void setAvgRate(int AvgRate);
            void setArticleDateAndTime(const tm& DateAndTime);
            void displayThisArticle();
}; 

