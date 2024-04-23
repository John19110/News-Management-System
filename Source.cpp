#include "News.h"
#include "User.h"
#include <iostream>
#include <stack>
#include<algorithm>
using namespace std;
//2
vector<User> readUsers()
{
    vector<User> users;
    ifstream file("users.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file: " << "users.txt" << endl;
        return users; // Return empty vector if file cannot be opened
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id;
        string username, userpassword, categories;

        // Extracting data from each line
        if (ss >> id >> username >> userpassword) {
            // Extract the remaining part of the line as categories
            size_t pos = line.find(userpassword) + userpassword.length() + 1;
            categories = line.substr(pos, line.length() - pos);

            istringstream categoriesStream(categories);
            string category;
            vector<string> preferredCategories;
            while (getline(categoriesStream, category, ',')) {
                preferredCategories.push_back(category);
            }
            // Create a User object and add it to the vector
            users.emplace_back(id, username, userpassword, preferredCategories);
        }
        else {
            cerr << "Invalid format in line: " << line << endl;
        }
    }
    file.close();
    return users;
}

vector<News> readNews() {
    vector<News> newsList;
    ifstream file("news.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file: news.txt" << endl;
        return newsList;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int ID;
        string Title, Description, Category;
        float AvgRate;
        string DateAndTime; // Using string for date and time

        // Parse ID, Title, Description, Category, AvgRate, and DateAndTime
        if (!(getline(ss, token, ',') && (stringstream(token) >> ID) &&
            getline(ss, Title, ',') &&
            getline(ss, Description, ',') &&
            getline(ss, Category, ',') &&
            (ss >> AvgRate) &&
            getline(ss, DateAndTime))) {
            cerr << "Invalid format in line: " << line << endl;
            continue;
        }

        // Create News object and add it to the list
        News news(ID, Title, Description, Category, AvgRate, DateAndTime);
        newsList.push_back(news);
    }

    file.close();
    return newsList;
}

int main()
{
    cout << "\t\t\t\tWELCOME TO FCIS NEWS!\n";
    cout << "*********************************************************************************************************************\n";
    vector<User> users = readUsers();
    vector<News> news = readNews();
    vector<News> newsOfCategory, bookmarkedArticles,foundArticles;
    
    stack<News> latestNews;
    int userChoice = 1, id, newID;
    string category,comment,word,newUsername,newPassword,newCategory;
    int loggedInUserChoice=1;
    bool articleFound = false, found=false;
    News articleToBeBookmarked;
    News articleToBeSpammed;
    News foundArticle;
    while (userChoice == 1 || userChoice == 2 || userChoice == 3) {
        cout << "Press:\n\t1 to Login as User\n\t2 to Login as Admin\n\t3 to Register as a New User\n\t4 to Exit Program\n";
        cin >> userChoice;
        string user, pass;
        User loggedInUser;
        switch (userChoice)
        {
        case 1:
        {
            cout << "Please Enter Your Username and Password:" << endl;
            cout << "UserName: ";
            cin >> user;
            cout << "Password: ";
            cin >> pass;

            bool success = false;

            for (int i = 0; i < users.size(); i++) {
                success = users[i].Login(user, pass);
                if (success) {
                    loggedInUser = users[i];
                    break;
                }
            }
            if (success)
                while (loggedInUserChoice > 0 && loggedInUserChoice < 10) {
                    {
                        cout << "Your Username is " << loggedInUser.getUserName() << " and ID is " << loggedInUser.getID() << endl;
                        cout << "Press:\n";
                        cout << "\t 1 to Display Latest Articles\n";
                        cout << "\t 2 to Rate Article\n";
                        cout << "\t 3 to Add a Preferred News Category\n";
                        cout << "\t 4 to Display Trending News Articles\n";
                        cout << "\t 5 to Bookmark an Article\n";
                        cout << "\t 6 to Report an Article as Spam\n";
                        cout << "\t 7 to Add a Comment To an Article\n";
                        cout << "\t 8 to Show News Artcles Belonging to a Specific Category\n";
                        cout << "\t 9 to Display Bookmarked Articles\n";
                        cout << "\t 10 to Search for an Article\n";
                        cout << "\t 11 to Display Article by ID\n";
                        cout << "\t 12 to Display Articles Belonging to your preferred Categories\n";
                        cin >> loggedInUserChoice;
                        switch (loggedInUserChoice)
                        {
                        case 1:
                        {
                            for (int i = 0; i < news.size(); i++) {
                                bool isSpam = false;
                                for (int j = 0; j < news[i].spamIDs.size(); j++) {
                                    if (news[i].spamIDs[j] == loggedInUser.getID()) {
                                        isSpam = true;
                                        break;  // No need to continue checking if the user ID is found
                                    }
                                }
                                if (!isSpam) {
                                    latestNews.push(news[i]);
                                }
                            }

                            while (!latestNews.empty()) {
                                latestNews.top().displayArticle();
                                latestNews.pop();
                            }
                            break;
                        }
                        case 2:
                        {
                            int rating, id;
                            cout << "Enter ID of the Article You Want to Rate\t";
                            cin >> id;

                            News articleToBeRated;
                            bool articleFound = false; // Flag to indicate if the article is found

                            for (int i = 0; i < news.size(); i++) {
                                if (id == news[i].getID()) {
                                    articleToBeRated = news[i];
                                    articleFound = true; // Set flag to true if article is found
                                    break;
                                }
                            }

                            // Check if an article with the given ID was found
                            if (articleFound) {
                                while (true) {
                                    cout << "Enter Rating of the Article (1 to 5)\t";
                                    cin >> rating;
                                    if (rating < 1 || rating>5)continue;
                                    else break;
                                }
                                articleToBeRated.addUserRating(loggedInUser.getID(), rating);
                            }
                            else {
                                cout << "No Article Matches the given ID\n";
                            }
                            break;
                        }
                        case 3:
                            cout << "Enter Category\t";
                            cin >> category;
                            loggedInUser.preferredCategories.push_back(category);
                            cout << "Category Added Successfully";
                            break;
                        case 4:

                            sort(news.begin(), news.end(), [](News& a, News& b) {
                                return a.getAvgRate() > b.getAvgRate(); // Compare in descending order
                                });;
                            for (auto& article : news) {
                                if (article.getAvgRate() > 2)
                                    article.displayArticle(); // Call displayArticle for each article
                                else continue;
                            }
                            break;
                        case 5:

                            articleFound = false;
                            cout << "Enter the ID of the Article You Want Bookmarked\t";
                            cin >> id;
                            for (int i = 0; i < news.size(); i++) {
                                if (id == news[i].getID()) {
                                    articleToBeBookmarked = news[i];
                                    articleFound = true; // Set flag to true if article is found
                                    break;
                                }
                            }
                            if (articleFound) {

                                articleToBeBookmarked.addBookmarkID(loggedInUser.getID());
                            }
                            else {
                                cout << "No Article Matches the given ID\n";
                            }
                            break;
                        case 6:
                            articleFound = false;
                            cout << "Enter the ID of the Article You Want Bookmarked\t";
                            cin >> id;
                            for (int i = 0; i < news.size(); i++) {
                                if (id == news[i].getID()) {
                                    articleToBeSpammed = news[i];
                                    articleFound = true; // Set flag to true if article is found
                                    break;
                                }
                            }
                            if (articleFound) {

                                articleToBeSpammed.reportSpam(loggedInUser.getID());
                            }
                            else {
                                cout << "No Article Matches the given ID\n";
                            }
                            break;
                        case 7:
                            articleFound = false;
                            cout << "Enter the ID of the Article You Want to Comment on\t";
                            cin >> id;
                            for (int i = 0; i < news.size(); i++) {
                                if (id == news[i].getID()) {
                                    articleToBeSpammed = news[i];
                                    articleFound = true; // Set flag to true if article is found
                                    break;
                                }
                            }
                            if (articleFound) {
                                cout << "Enter Your Comment\n";
                                cin >> comment;
                                articleToBeSpammed.addComment(comment);
                            }
                            else {
                                cout << "No Article Matches the given ID\n";
                            }
                            break;
                        case 8:
                            cout << "Enter Category:\t";
                            cin >> category;
                            for (int i = 0; i < news.size(); i++) {
                                if (news[i].getCategory() == category) newsOfCategory.push_back(news[i]);
                            }
                            if (newsOfCategory.size() == 0) {
                                cout << "No articles Matched the Given Category!\n";
                            }
                            else {
                                for (int i = 0; i < newsOfCategory.size(); i++) {
                                    newsOfCategory[i].displayArticle();
                                }
                            }

                            break;
                        case 9:
                            for (int i = 0; i < news.size(); i++) {
                                for (int j = 0; j < news[i].BookmarkIDs.size(); j++) {
                                    if (news[i].BookmarkIDs[j] == loggedInUser.getID()) {
                                        bookmarkedArticles.push_back(news[1]);
                                    }
                                }
                            }
                            if (bookmarkedArticles.size() != 0) {
                                for (int i = 0; i < bookmarkedArticles.size(); i++) {
                                    bookmarkedArticles[i].displayArticle();
                                }
                            }
                            else {
                                cout << "You Don't Have Any Bookmarked Articles!\n";
                            }
                            break;
                        case 10:
                            cout << "Enter Keyword:\t";
                            cin >> word;
                            for (auto& article : news) {
                                if (article.getTitle().find(word) != std::string::npos) {
                                    // If found, call the display function for the current article
                                    article.displayArticle();
                                    found = true;
                                }
                            }
                            if (!found) {
                                cout << "'" << word << "'" << "was not Found in Any Article\n";
                            }
                            break;
                        case 11:
                            found = false;
                            cout << "Enter Article ID:\t";
                            cin >> id;
                            for (int i = 0; i < news.size(); i++) {
                                if (news[i].getID() == id) {
                                    found = true;
                                    foundArticle = news[i];
                                    break;
                                }
                            }
                            if (found) {
                                foundArticle.displayArticle();
                            }
                            else {
                                cout << "No Article Matches the ID provided\n";
                            }
                            break;
                        case 12:
                            for (int i = 0; i < loggedInUser.preferredCategories.size(); i++)
                            {
                                for (int j = 0; i < news.size(); j++) {
                                    if (news[j].getCategory() == loggedInUser.preferredCategories[j]) {
                                        foundArticles.push_back(news[j]);
                                    }
                                }
                            }
                            if (foundArticles.empty()) {
                                cout << "No Articles Match Your Preferred Categories\n";
                            }
                            else {
                                for (auto& article : foundArticles) {
                                    article.displayArticle();
                                }
                            }
                            break;

                        default:
                            break;
                        } //end of switch loggedInUserChoice               
                    }
                }
            else {
                cout << "Login Failed!\n";
            }

            break;
        }
        case 2:
        {
            //Admin Login
            break;
        }
        case 3:
        {
            //Register user
            cout << "Enter Username:\t";
            cin >> newUsername;
            cout << "Enter Password:\t";
            cin >> newPassword;
            newID = users.size() + 1;
            cout << "Enter Preferred Category:\t";
            cin >> newCategory;
            vector<string> newPreferredcategories;
            newPreferredcategories.push_back(newCategory);
            User newUser(newID, newUsername, newPassword, newPreferredcategories);
            cout << "User Registered Successfully!\n";
            break;
        }
        default:
        {
            cout << "\tThank You for Using FCIS News, See You Later!\n\n\n\n\n\n";
            break;
        }
        }
    }
   
    return 0;
}
