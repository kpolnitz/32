#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here

class Investment {
    
public:
    Investment(string name, int price);
    virtual ~Investment();
    virtual string name() const
    {
        return m_name;
    }
    virtual bool fungible() const
    {
        return false;
    }
    virtual string description() const=0;
 
    virtual int purchasePrice() const
    {
        return m_price;
    }
    
    
private:
    string m_name;
    string m_description;
    int m_price;
};

Investment::~Investment(){

}
Investment::Investment(string name, int price)
{
    m_name=name;
    m_price=price;
    
}

string Investment:: description() const
{
    return m_description;
}
class Painting: public Investment {

public:
    virtual ~Painting();
    Painting(string name, int price);
    virtual string description() const
    {
        return "painting";
    }
};

Painting::~Painting(){

    cout << "Destroying " << name() << ", a painting" << endl;
}
Painting::Painting(string name, int price)
:Investment(name,price)
{
}

class Stock: public Investment {
    
public:
    virtual ~Stock();
    Stock(string name, int price, string company);
    virtual string description() const
    {
        return "stock";
    }
    virtual bool fungible() const
    {
        return true;
    }
};

Stock::~Stock() {
   cout << "Destroying " << name() << ", a stock holding" << endl;
}

Stock::Stock(string name, int price, string company)
: Investment(name, price){
    
}

class House: public Investment {
    
    
public:
    House(string name, int price);
    virtual ~House();
    virtual string description() const
    {
        return "house";
    }

private:
};
House::House(string name, int price)
:Investment(name,price)
{}
House::~House()
{

    cout << "Destroying the house "  << name() << endl;
}


//DO NOT CHANGE IMPLEMENTATIONS
/*
void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}
*/


/*
//DO NOT CHANGE IMPLEMENTATIONS
int main()
{
    //Investment *P = new Investment("hello",12); //PROBLEM
    
    Investment* portfolio[4];
    portfolio[0] = new Painting("Salvator Mundi", 450300000);
    // Stock holdings have a name, value, and ticker symbol
    portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
    portfolio[2] = new Stock("Symantec", 50000, "SYMC");
    portfolio[3] = new House("4 Privet Drive", 660000);
    
    for (int k = 0; k < 4; k++)
        display(portfolio[k]);
    
    // Clean up the investments before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete portfolio[k];
}
*/
 
/* Output:

 Salvator Mundi: painting bought for $450300000
 Alphabet (fungible): stock trading as GOOGL bought for $100000
 Symantec (fungible): stock trading as SYMC bought for $50000
 4 Privet Drive: house bought for $660000
 Cleaning up
 Destroying Salvator Mundi, a painting
 Destroying Alphabet, a stock holding
 Destroying Symantec, a stock holding
 Destroying the house 4 Privet Drive

*/
