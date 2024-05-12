#pragma once
#include "News.h"

News::News(int ID, string Title, string Description, string Category,map<string,float>ratings, float AvgRate, vector<pair<string, string>> comments,int spamCount,string DateAndTime)

{
    this->ID = ID;
    this->Title = Title;
    this->Description = Description;
    this->Category = Category;
    this->ratings = ratings;
    this->AvgRate = AvgRate;
    this->comments = comments;
    this->spamCount = spamCount;
    this->ArticleDateAndTime = DateAndTime;


}

News::News() {

}

void News::displayArticle()
{
    cout << "=================================================================================\n";
    cout << " Article ID: " << getID() << "\n";
    cout << " Title: " << getTitle() << "\n";
    cout << " Description: " << getDescription() << "\n";
    cout << " Average Rating: " << getAvgRate() << "\n";
    cout << " Category: " << getCategory() << "\n";
    cout << " Date and Time: " << getArticleDateAndTime() << "\n";
    cout << " Spam Reports: " << getSpamCount() << "\n";
    cout << "=================================================================================\n";
    displayRatings();
    displayComments();
}
void News::displayComments() {
    if (comments.size() == 0) {
        cout << " No Comments Yet!\n";
    }
    else {
        cout << "Comments for the  article \n'";
        for (const auto& comment : comments) {
            cout << "User: " << comment.first << endl;
            cout << "Comment: " << comment.second << endl << endl;
        }
    }
    cout << "=================================================================================\n";
}

void News::addComment(string username, string comment)
{
    comments.push_back(make_pair(username, comment));
}

void News::addUserRating(string username, float rating) 
{
    ratings.insert(make_pair(username, rating));
    cout << "Rating Submitted Successfully!\n";
}
float News::calculateAverageRating() {
    if (ratings.empty()) {
        setAvgRate(AvgRate);
        return AvgRate;
    }

    else {
        int totalRating = 0;
        int numRatings = ratings.size();

        for (const auto& pair : ratings) {
            totalRating += pair.second; // Add up all ratings
        }

        // Calculate the average rating
        float avg = (numRatings > 0) ? static_cast<float>(totalRating) / numRatings : 0.0f;
        setAvgRate(avg);

        return avg;
    }
}


void News::addBookmarkID(int userID) {
    BookmarkIDs.push_back(userID);
    cout << "Article Bookmarked Successfully!\n";
}

void News::displayRatings() {
    if (ratings.empty()) {
        cout << "No Ratings Added to This Article Yet!";
    }
    else {
        cout << "User name\tRating\n";
        for (auto it = ratings.begin(); it != ratings.end(); ++it) 
        {
            
            std::cout << it->first << "\t" << it->second << std::endl;
        }
    }
}

//getters
string News::getTitle() const {
    return Title;
}

string News::getDescription() const {
    return Description;
}

string News::getCategory() const {
    return Category;
}

float News::getAvgRate() {
    AvgRate = calculateAverageRating();
    return AvgRate;
}

int News::getID() {
    return ID;
}

int News::getSpamCount() {
    return spamCount;
}

string News::getArticleDateAndTime() const {
    return ArticleDateAndTime;
}

vector<int> News::getBookmarkIDs() {
    return BookmarkIDs;
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

void News::setAvgRate(float AvgRate) {
    this->AvgRate = AvgRate;
}

void News::setArticleDateAndTime(string DateAndTime) {
    ArticleDateAndTime = DateAndTime;
}

void News::reportSpam(int userId) {
    spamCount++;
    spamIDs.push_back(userId);
}
void News::setID(int ID) {
    this->ID = ID;
}
// Function to get all data as string
string News::toString() const {
    std::string result;
    result += "ID: " + to_string(ID) + "\n";
    result += "Article Date and Time: " + ArticleDateAndTime + "\n";
    result += "Title: " + Title + "\n";
    result += "Category: " + Category + "\n";
    result += "Description: " + Description + "\n";
    result += "Average Rating: " + std::to_string(AvgRate) + "\n";
    result += "Ratings:\n";
    for (const auto& rating : ratings) 
    {
        result += "  User naem: " + rating.first + ", Rating: " + to_string(rating.second) + "\n";
    }
    result += "Spam Count: " + std::to_string(spamCount) + "\n";
    result += "Comments:\n";
    for (const auto& comment : comments) 
    {
        result += "  User: " + comment.first + ", Comment: " + comment.second + "\n";
    }
    return result;
};
