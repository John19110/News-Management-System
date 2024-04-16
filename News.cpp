#include "News.h"

News::News(string Title, string Description, string Category, int AvgRate, tm DateAndTime)

	{
	this->Title = Title;
	this ->Description = Description;
	this->Category = Category;
	this ->AvgRate = AvgRate;
	ArticleDateAndTime = DateAndTime;
	

	}

void News::  displayThisArticle()
 {
    cout << " Title " <<getTitle()<<"\n";
    cout << " AvgRate " << getAvgRate() << "\n";
    cout << " Category " << getCategory() << "\n";
    cout << " Descreption " << getDescription() << "\n";
    cout << " Date and time " << getArticleDateAndTime() << "\n";
 }

string News::getTitle() const {
    return Title;
}

string News::getDescription() const {
    return Description;
}

string News::getCategory() const {
    return Category;
}

int News::getAvgRate()  {
    return AvgRate;
}

string News::getArticleDateAndTime() const {
    ostringstream oss;
    oss << put_time(&ArticleDateAndTime, "%Y-%m-%d %H:%M:%S");
    string articleDateStr = oss.str();
    return articleDateStr;
}

// Setters
void News::setTitle(const std::string& Title) {
    this->Title = Title;
}

void News::setDescription(const std::string& Description) {
    this->Description = Description;
}

void News::setCategory(const std::string& Category) {
    this->Category = Category;
}

void News::setAvgRate(int AvgRate) {
    this->AvgRate = AvgRate;
}

void News::setArticleDateAndTime(const tm& DateAndTime) {
    ArticleDateAndTime = DateAndTime;
}
