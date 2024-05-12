#pragma once
#include<iostream>
#include<ctime>
#include<string>
#include<iomanip>
#include<sstream>
#include<map>
#include<list>
#include<vector>
using namespace std;
//4
class News {
public:
    string Title, Description, Category;
    float AvgRate;
    int ID,spamCount;
    map<string, float> ratings;
    vector<pair<string, string>> comments;
    vector<int> BookmarkIDs;
    vector<int> spamIDs;
    string ArticleDateAndTime; 
    // tm is a built-in struct, not a normal variable 

    // Initialize the date and time components
   // { 59, 59, 14, 14, 4, 124}= 2024-05-14 14:59:59

public:

    //Constractor
    News(int ID, string Title, string Description, string Category,map<string,float>ratings, float AvgRate, vector<pair<string, string>> comments ,int spamcount,string DateAndTime);
    News();
    //Getters
    string getTitle() const;
    string getDescription() const;
    string getCategory() const;
    float getAvgRate();
    string getArticleDateAndTime() const;
    int getID();
    int getSpamCount();
    vector<int> getBookmarkIDs();
    string toString() const;

    // Setters
    void setTitle(const string& Title);
    void setDescription(const string& Description);
    void setCategory(const string& Category);
    void setAvgRate(float AvgRate);
    void setArticleDateAndTime(string DateAndTime);
    void setID(int ID);

    //others
    void displayArticle();
    void displayComments();
    void addUserRating(string,float);
    void addComment(string,string);
    float calculateAverageRating();
    void addBookmarkID(int);
    void reportSpam(int);
    void displayRatings();
};

