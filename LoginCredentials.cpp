#include <iostream>
#include <regex>
using namespace std;

class LoginCredentials{
    private:
        string confirmPassword;
    protected:
        string email, password;
    public:
        LoginCredentials(){}
        /*prosljeđujemo email, password i confirm password*/
        LoginCredentials(const string&  e,const string& pass,const string& cpass): email(e), password(pass), confirmPassword(cpass){}
        
        bool validEmail() const;
        friend ostream&operator<<(ostream&, const LoginCredentials&);
        
};
bool LoginCredentials::validEmail()const{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}
ostream&operator<<(ostream& os, const LoginCredentials& lc)
{
    os << "Email: " << lc.email <<"     password: " << lc.password<< endl;
    return os;
}
class Account : public LoginCredentials{
    protected:
        string username;
    public:
        Account();
        /*prosljeđujemo username, email i password*/
        Account(const string& user, const string& mail, const string& pass){
            username = user;
            LoginCredentials::email = mail;
            LoginCredentials::password = pass;
        };
        string getUsername(){return username;};
        string getEmail(){return email;};
        friend ostream&operator<<(ostream& buffer, const Account&);
};
ostream&operator<<(ostream& os, const Account& a)
{
    os << "Username: " << a.username << "   email: " << a.email << endl;
}

int main (void){
    Account A1("filipVukovic", "filipvukovic1@gmail.com", "password123");
    cout << A1;
    LoginCredentials C1 ("fvukovic123@gmail.com","passpass","passpass");

    cout << A1.getEmail() << endl;
    cout << A1.getUsername() << endl;
    
    // cout << A1.validEmail() << endl; // ne radi mi u c++11, ali radi na nekom od online c++ commpilera :)
    return 0; 
}