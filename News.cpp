#include "News.h"
//4
News::News(int ID, string Title, string Description, string Category, float AvgRate, string DateAndTime)

{
    this->ID = ID;
    this->Title = Title;
    this->Description = Description;
    this->Category = Category;
    this->AvgRate = AvgRate;
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
    displayComments();
}
void News::displayComments() {
    if (Comments.size() == 0) {
        cout << " No Comments Yet!\n";
    }
    else {
        cout << " Comments (" << Comments.size() << "):\n\n";
        for (string& str : Comments) {
            cout << "* " << str << endl;
        }
    }
    cout << "=================================================================================\n";
}

void News::addComment(string comment) {
    Comments.push_front(comment);
}

void News::addUserRating(int userId, int rating) {
    Ratings.insert(make_pair(userId, rating));
    cout << "Rating Submitted Successfully!\n";
}
float News::calculateAverageRating() {
    if (Ratings.empty()) {
        setAvgRate(AvgRate);
        return AvgRate;
    }

    else {
        int totalRating = 0;
        int numRatings = Ratings.size();

        for (const auto& pair : Ratings) {
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
    if (Ratings.empty()) {
        cout << "No Ratings Added to This Article Yet!";
    }
    else {
        cout << "User ID\tRating\n";
        for (auto it = Ratings.begin(); it != Ratings.end(); ++it) {
            // Access the key using it->first and the value using it->second
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