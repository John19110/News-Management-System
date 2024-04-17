#include<iostream>
#include<ctime>
#include<string>
#include<iomanip>
#include<sstream>
#include<map>
#include<list>
#include<vector>
using namespace std;
class News

{
public:
	string Title,Description,Category;
    float AvgRate;
    int ID;
	map<int,int> Ratings;
    int spamCount;
    list<string> Comments;
    vector<int> BookmarkIDs;
 	tm ArticleDateAndTime; // tm is a built-in struct, not a normal variable 

	// Initialize the date and time components
   // { 59, 59, 14, 14, 4, 124}= 2024-05-14 14:59:59

		public:

            //Constractor
			News(int ID, string Title ,string Description,string Category,float AvgRate,tm DateAndTime);

            //Getters
            string getTitle() const;
            string getDescription() const;
            string getCategory() const;
            float getAvgRate() ;
            string getArticleDateAndTime() const;
            int getID();
            int getSpamCount();
            vector<int> getBookmarkIDs();

            // Setters
            void setTitle(const string& Title);
            void setDescription(const string& Description);
            void setCategory(const string& Category);
            void setAvgRate(int AvgRate);
            void setArticleDateAndTime(const tm& DateAndTime);

            //others
            void displayArticle();
            void displayComments();
            void addUserRating(int,int);
            void addComment(string);
            float calculateAverageRating();
            void addBookmarkID(int);
            
}; 

