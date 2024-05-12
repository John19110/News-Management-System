#include "News.h"
#include "User.h"
#include "Admin.h"
#include <iostream>
#include <stack>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;

vector<News> news;
vector<User> users;

vector<User> readUsers()
{
   ifstream file("users.txt");
if (!file.is_open())
{
    cerr << "Unable to open file: " << "users.txt" << endl;
    return users; // Return empty vector if file cannot be opened
}
for (int i = 0; i < 4; i++) 
{
    int id, NumberOfCategories;
    string username, userpassword;
    string preferredCategory;
    vector<string> preferredCategories;

    file >> id;
    file >> username;
    file >> userpassword;
    

   

    User u(id, username, userpassword, preferredCategories);
    users.push_back(u);
    
    }
    
    int i;
    for (i = 0; i < 3; ++i)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    i = i + 3;


    return users;
        }
vector<News> readArticle(const string& filename) {
    vector<News> articles;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return articles;
    }

   
   
    
        for (int i = 0; i < 10; i++)
        {
        string title, description,category,DateAndTime;
        int id, spamCount;
        float averageRating;
        map<string, float> ratings;
        vector<pair<string, string>> comments;

        file >> id;
        file >> title;
        replace(title.begin(), title.end(), '@', ' ');
        file >> description;
        replace(description.begin(), description.end(), '@', ' ');
        file >> category;
        int ratingCount;
        file >> ratingCount;
        for (int i = 0; i < ratingCount; i++) 
        {
            string username;
            float rating;
            file >> username >> rating;
            ratings[username] = rating;
        }
        // Read comments
        int commentCount;
        file >> commentCount;
        file.ignore(); // Ignore newline character
        for (int i = 0; i < commentCount; ++i)
        {
            string username, comment;
            file >> username >> comment;
            replace(comment.begin(), comment.end(), '@', ' ');
           
            comments.push_back(make_pair(username, comment));
        }

        // Read average rating
        file >> averageRating;

        // Read spam count
        file >> spamCount;
        //Read date and time
        file >> DateAndTime;
        replace(DateAndTime.begin(), DateAndTime.end(), '@', ' ');

        // Create Article object and store in vector
        News n (id, title, description, category, ratings, averageRating, comments, spamCount, DateAndTime);
        articles.push_back(n);

        
    

    
        }
        int i;
        for ( i = 1; i < 14; ++i)
        {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        i = i + 14;
    return articles;
}
void WriteArticls()
{
    ofstream outFile("ArticlesOUTPUT.txt"); // Open file for writing

    if (outFile.is_open()) {


        // Writing to the file using stream insertion operators
        outFile << "Articles: ";
        for (News Article : news)
        {
            outFile << "Articls : " << Article.toString();
            outFile << "===============================================" << endl;
            outFile << "===============================================" << endl;
            outFile << "===============================================" << endl;
        }



        outFile.close(); // Close the file
        cout << "Data has been written to the file." << endl;
    }
    else {
        cerr << "Unable to open file!" << endl;
    }


}
void WriteUsers()
{

    ofstream outFile("UsersOUTPUT.txt"); // Open file for writing

    if (outFile.is_open()) {


        // Writing to the file using stream insertion operators
        outFile << "Usere: ";
        for (User User : users)
        {
            outFile  << User.toString();
            outFile << "===============================================" << endl;
            outFile << "===============================================" << endl;
            outFile << "===============================================" << endl;
        }



        outFile.close(); // Close the file
        cout << "Data has been written to the file." << endl;
    }
    else {
        cerr << "Unable to open file!" << endl;
    }

}

string toLower(const string& str) {
    string result;
    result.reserve(str.size());
    std::transform(str.begin(), str.end(), back_inserter(result),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}


int main() 
{
    cout << "\t\t\t\tWELCOME TO FCIS NEWS!\n";
    cout << "*********************************************************************************************************************\n";
    users = readUsers();
    news = readArticle("articles.txt");
    vector<News> newsOfCategory, bookmarkedArticles, foundArticles;
    Admin loggedInAdmin;
    stack<News> latestNews;
    int ID;
    string Title, Description, Category, DateAndTime;
    float AvgRate;
    int userChoice = 1, id, newID, adminChoice = 1;
    string category, comment, word, newUsername, newPassword, newCategory;
    vector<string> newPreferredcategories;
    int loggedInUserChoice = 1, index, updateChoice;
    bool articleFound = false, found = false, loginSuccess = false;
    News articleToBeBookmarked, articleToBeCommented;
    News articleToBeSpammed, newArticle;
    News foundArticle;
    string title, description;
    auto it = news.begin();
    vector<News> newsCategory;

    while (userChoice == 1 || userChoice == 2 || userChoice == 3) {
        cout << "Press:\n\t1 to Login as User\n\t2 to Login as Admin\n\t3 to Register as a New User\n\t4 to Exit Program\n";
        cin >> userChoice;
        string user, pass;
        User loggedInUser;

        switch (userChoice) {
        case 1: {
            cout << "Please Enter Your Username and Password:" << endl;
            cout << "Username: ";
            cin >> user;
            cout << "Password: ";
            cin >> pass;

            bool success = false;

            for (int i = 0; i < users.size(); i++) {
                success = users[i].Login(user, pass);
                if (success) {
                    loggedInUser = users[i];
                    loggedInUserChoice = 1;
                    break;
                }
            }

            if (success) {
                while (loggedInUserChoice > 0 && loggedInUserChoice < 14) {
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
                    cout << "\t 13 to Display All Ratings of an Article\n";
                    cout << "\t 14 to Logout\n";
                    cin >> loggedInUserChoice;

                    switch (loggedInUserChoice) {
                    case 1: {
                        for (int i = 0; i < news.size(); i++) {
                            bool isSpam = false;
                            for (int j = 0; j < news[i].spamIDs.size(); j++) {
                                if (news[i].spamIDs[j] == loggedInUser.getID()) {
                                    isSpam = true;
                                    break;
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
                    case 2: {
                        int  id;
                        float rating;
                        cout << "Enter ID of the Article You Want to Rate\t";
                        cin >> id;
                        News articleToBeRated;
                        bool articleFound = false;

                        for (int i = 0; i < news.size(); i++) {
                            if (id == news[i].getID()) {
                                articleToBeRated = news[i];
                                index = i;
                                articleFound = true;
                                break;
                            }
                        }

                        if (articleFound) 
                        {
                            while (true) {
                                cout << "Enter Rating of the Article (1 to 5)\t";
                                cin >> rating;
                                if (rating < 1 || rating > 5) continue;
                                else break;
                            }
                            news[index].addUserRating(loggedInUser.getUserName(), rating);
                        }
                        else {
                            cout << "No Article Matches the given ID\n";
                        }
                        break;
                    }
                    case 3: {
                        cout << "Enter Category\t";
                        cin >> category;
                        loggedInUser.preferredCategories.push_back(category);
                        cout << "Category Added Successfully";
                        break;
                    }
                    case 4: {
                        sort(news.begin(), news.end(), [](News& a, News& b) 
                            {
                            return a.getAvgRate() > b.getAvgRate();
                            });

                        for (auto& article : news) {
                            if (article.getAvgRate() > 4.00)
                                article.displayArticle();
                            else continue;
                        }
                        break;
                    }
                    case 5: {
                        articleFound = false;
                        cout << "Enter the ID of the Article You Want Bookmarked\t";
                        cin >> id;
                        for (int i = 0; i < news.size(); i++) {
                            if (id == news[i].getID()) {
                                articleToBeBookmarked = news[i];
                                index = i;
                                articleFound = true;
                                break;
                            }
                        }

                        if (articleFound) {
                            news[index].addBookmarkID(loggedInUser.getID());
                        }
                        else {
                            cout << "No Article Matches the given ID\n";
                        }
                        break;
                    }
                    case 6: {
                        articleFound = false;
                        cout << "Enter the ID of the Article You Want To Report as Spam\t";
                        cin >> id;
                        for (int i = 0; i < news.size(); i++) {
                            if (id == news[i].getID()) {
                                articleToBeSpammed = news[i];
                                index = i;
                                articleFound = true;
                                break;
                            }
                        }

                        if (articleFound) {
                            news[index].reportSpam(loggedInUser.getID());
                        }
                        else {
                            cout << "No Article Matches the given ID\n";
                        }
                        break;
                    }
                    case 7: {
                        articleFound = false;
                        cout << "Enter the ID of the Article You Want to Comment on\t";
                        cin >> id;
                        for (int i = 0; i < news.size(); i++) {
                            if (id == news[i].getID()) {
                                articleToBeCommented = news[i];
                                articleFound = true;
                                index = i;
                                break;
                            }
                        }

                        if (articleFound) {
                            
                            cout << "Enter Your Comment:\t";
                            cin.ignore();
                            getline(cin, comment);
                            news[index].addComment(loggedInUser.getUserName(), comment);
                            news[index].displayComments();
                        }
                        else {
                            cout << "No Article Matches the given ID\n";
                        }
                        break;
                    }
                    case 8: {
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
                    }
                    case 9: {
                        for (int i = 0; i < news.size(); i++) {
                            for (int j = 0; j < news[i].BookmarkIDs.size(); j++) {
                                if (news[i].BookmarkIDs[j] == loggedInUser.getID()) {
                                    bookmarkedArticles.push_back(news[i]);
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
                    }
                    case 10: {
                        cout << "Enter Keyword:\t";
                        cin >> word;
                        bool anyArticlesFound = false;
                        for (auto& article : news) {
                            found = false;
                            string lowercaseTitle = toLower(article.getTitle());
                            string lowercaseDescription = toLower(article.getDescription());
                            string lowercaseWord = toLower(word);
                            if (lowercaseTitle.find(lowercaseWord) != string::npos) {

                                found = true;
                            }
                            if (lowercaseDescription.find(lowercaseWord) != string::npos) {

                                found = true;
                            }
                            if (found) {
                                anyArticlesFound = true;
                                article.displayArticle();
                            }
                        }
                        if (!anyArticlesFound) {
                            cout << "'" << word << "'" << "was not Found in Any Article\n";
                        }
                        break;
                    }
                    case 11: {
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
                    }
                    case 12: {
                        for (int i = 0; i < loggedInUser.preferredCategories.size(); i++) {
                            for (int j = 0; j < news.size(); j++) {
                                if (news[j].getCategory() == loggedInUser.preferredCategories[i]) {
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
                    case 13:
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
                            foundArticle.displayRatings();
                        }
                        else {
                            cout << "No Article Matches the ID provided\n";
                        }
                    }
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
        case 2: {
            //ADMIN
            loginSuccess = false;
            cout << "Enter Username\t";
            cin >> user;
            cout << "Enter Password\t";
            cin >> pass;

            if (user == "admin" && pass == "admin")
            {
                loginSuccess = 1;
                cout << "\t Admin Login Successfull!\n";

            }

            if (loginSuccess) {
                while (adminChoice > 0 && adminChoice < 5) {
                    cout << "Press:\n";
                    cout << "\t1 to Add an Article\n";
                    cout << "\t2 to Remove an Article\n";
                    cout << "\t3 to Update an Article\n";
                    cout << "\t4 to Calculate the Average Rate of a Specific News Category\n";
                    cout << "\t5 to Logout\n";
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1: {
                        cin.ignore(); // Ignore any remaining newline characters from previous inputs

                        cout << "Enter Title: ";
                        getline(cin, Title);
                        newArticle.setTitle(Title);

                        cout << "Enter Description: ";
                        getline(cin, Description);
                        newArticle.setDescription(Description);

                        cout << "Enter Category: ";
                        getline(cin, Category);
                        newArticle.setCategory(Category);

                        cout << "Enter Date And Time: ";
                        getline(cin, DateAndTime);
                        newArticle.setArticleDateAndTime(DateAndTime);

                        // Input validation for AvgRate
                        while (true) {
                            cout << "Enter Default Rating (1 to 5): ";
                            if (cin >> AvgRate && AvgRate >= 1 && AvgRate <= 5) {
                                break; // Exit loop if input is valid
                            }
                            else {
                                cout << "Invalid input. Please enter a rating between 1 and 5.\n";
                                cin.clear(); // Clear error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                        }
                        newArticle.setAvgRate(AvgRate);

                        ID = news.size() + 1;
                        newArticle.setID(ID);

                        news.push_back(newArticle);
                        cout << "Article Added Successfully!\n";
                        break;
                    }

                    case 2: {
                        found = false;
                        cout << "Enter Article ID to be Removed:\t";
                        cin >> id;
                        for (it = news.begin(); it != news.end(); ++it) {
                            if (it->getID() == id) {
                                news.erase(it);
                                found = true;
                                cout << "Article Removed Successfully!\n";
                                break;
                            }
                        }
                        if (!found) {
                            cout << "No Article Matches the ID provided\n";
                        }
                        break;
                    }
                    case 3: {
                        found = false;
                        cout << "Enter ID of Article: ";
                        cin >> id;
                        cin.ignore(); // Clear input buffer

                        for (int i = 0; i < news.size(); i++) {
                            if (news[i].getID() == id) {
                                found = true;
                                index = i;
                                break;
                            }
                        }

                        if (found) {
                            cout << "Press:\n";
                            cout << "\t1 to Update Title\n";
                            cout << "\t2 to Update Description\n";
                            cout << "\t3 to Update Category\n";
                            cin >> updateChoice;
                            cin.ignore(); // Clear input buffer

                            switch (updateChoice) {
                            case 1: {
                                cout << "Enter New Title: ";
                                getline(cin, Title);
                                news[index].setTitle(Title);
                                cout << "Article Title Updated Successfully\n";
                                break;
                            }
                            case 2: {
                                cout << "Enter New Description: ";
                                getline(cin, Description);
                                news[index].setDescription(Description);
                                cout << "Article Description Updated Successfully\n";
                                break;
                            }
                            case 3: {
                                cout << "Enter New Category: ";
                                getline(cin, Category);
                                news[index].setCategory(Category);
                                cout << "Article Category Updated Successfully\n";
                                break;
                            }
                            default:
                                cout << "Invalid choice\n";
                                break;
                            }
                        }
                        else {
                            cout << "No Article Matches that ID\n";
                        }
                        break;
                    }

                    case 4: {
                        cout << "Enter Category\t";
                        cin >> category;
                        newsCategory.clear();
                        for (int i = 0; i < news.size(); i++) {
                            if (news[i].getCategory() == category) {
                                newsCategory.push_back(news[i]);
                            }
                        }
                        if (!newsCategory.empty()) {
                            float sum = 0, average = 0;
                            int count = 0;
                            for (int i = 0; i < newsCategory.size(); i++) {
                                sum += newsCategory[i].getAvgRate();
                                count++;
                            }
                            average = sum / count;
                            cout << "\t The Average of the '" << category << "' category is: " << average << endl;
                        }
                        else {
                            cout << "No Articles match the Category: '" << category << "'\n";
                            break;
                        }
                        break;
                    }

                    }
                }
            }
            else {
                cout << "Login Failed!\n";
            }
            break;
        }
        case 3:
        {
            //Register user
            cout << "Enter Username:\t";
            cin >> newUsername;
            for (User user : users)
            {
                if (newUsername == user.getUserName())

                {
                    do
                    {

                        cout << "this username already used before ... please enter another user name \n";
                        cin >> newUsername;

                    } while (newUsername == user.getUserName());
                }
            }
            cout << "Enter Password:\t";
            cin >> newPassword;
            newID = users.size() + 1;
            newPreferredcategories.push_back(newCategory);
            User newUser(newID, newUsername, newPassword, newPreferredcategories);
            users.push_back(newUser);
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
    WriteArticls();
    WriteUsers();
    return 0;
}
