#include"News.h"
int main()
{
	News* first = new News("Chelsea win against Everton",
					    	"Cole Palmer scoreed super hatrick",
							"sports",5,{ 59, 59, 14, 14, 4, 121});

	
	first->displayThisArticle();

	


}