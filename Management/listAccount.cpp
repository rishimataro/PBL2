#include "./Single/Account.h"
#include "../Template/LinkedList.cpp"

class listAccount : public LinkedList<Account>
{
    public:
        // * Constructor
        listAccount();
        ~listAccount();

        // Create: add
        void signUp(Account &a, int &k);
};

