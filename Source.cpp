#include"News.h"
#include<iostream>
using namespace std;
int main()
{
	News* first = new News(1,"Chelsea win against Everton",
					    	"Cole Palmer scoreed super hatrick",
							"sports",4.4,{ 59, 59, 14, 14, 4, 124});

	first->displayArticle();
	first->addComment("very informative article, congrats chelsea!!");
	first->displayComments();
	
}