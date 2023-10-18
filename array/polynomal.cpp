#include <iostream>
#include <string>

class Polynomial;

class Term
{
public:
    friend Polynomial;
    friend std::ostream& operator<<(std::ostream& os, Polynomial const& p);

private: 
    int degree; 
    float coef; 

};

class Polynomial
{
public:
    Polynomial(std::string const& initpoly)
    : terms{0}, capacity{10}
    {
        termarray = new Term[capacity - 1];
        std::string temp_string = initpoly;
        termarray[terms].degree = stoi(temp_string.substr(temp_string.find('*') + 3, 1));
        termarray[terms].coef = stoi(temp_string.substr(0, temp_string.find('*')));
        terms++;

        do
        {
            temp_string = temp_string.substr(temp_string.find('+') + 1);

            if (terms == capacity)
            {
                //add more capacity
            }
            else
            {
            termarray[terms].degree = stoi(temp_string.substr(temp_string.find('*') + 3, 1));
            termarray[terms].coef = stoi(temp_string.substr(0, temp_string.find('*')));
            terms++;
            }
        } while (temp_string.find('+') != std::string::npos);
    }
    Polynomial()
    :  terms{0}, capacity{10}
    {
        termarray = new Term[capacity - 1];
    }
    ~Polynomial()
    {
        delete termarray;
    }
    Polynomial operator+(Polynomial const& rhs)
    {
        int a_pos{0};
        int b_pos{0};

        Polynomial c{};
        while(a_pos < terms && b_pos < rhs.terms)
        {
            if (termarray[a_pos].degree == rhs.termarray[b_pos].degree)
            {
                c.termarray[c.terms].coef = termarray[a_pos].coef + termarray[b_pos].coef;
                c.termarray[c.terms].degree = rhs.termarray[b_pos].degree;
                c.terms++;
                a_pos++;
                b_pos++;
            }
            else if(termarray[a_pos].degree > rhs.termarray[b_pos].degree)
            {
                c.termarray[c.terms].coef = termarray[a_pos].coef;
                c.termarray[c.terms].degree = termarray[a_pos].degree;
                c.terms++;
                a_pos++;

            }
            else if(termarray[a_pos].degree < rhs.termarray[b_pos].degree)
            {
                c.termarray[c.terms].coef = rhs.termarray[b_pos].coef;
                c.termarray[c.terms].degree = rhs.termarray[b_pos].degree;
                c.terms++;
                b_pos++;

            }
            for (;a_pos < terms; a_pos++)
            {
                c.termarray[c.terms].coef = termarray[a_pos].coef;
                c.termarray[c.terms].degree = termarray[a_pos].degree;
                c.terms++;
                a_pos++;
            }
            for(;b_pos < b_pos; b_pos++)
            {
                c.termarray[c.terms].coef = rhs.termarray[b_pos].coef;
                c.termarray[c.terms].degree = rhs.termarray[b_pos].degree;
                c.terms++;
                b_pos++;                
            }
        }
            return c;
        
    }

    friend std::ostream& operator<<(std::ostream& os, Polynomial const& p);


private:
    Term* termarray;
    int capacity;
    int terms;

};

std::ostream& operator<<(std::ostream& os, Polynomial const& p)
    {
        os << p.termarray[0].coef << "*x^"<< p.termarray[0].degree;
        for (int i = 1; i < p.terms; i++ )
        {
            os << " + " << p.termarray[i].coef << "*x^"<< p.termarray[i].degree;
        }
        os << std::endl;
        return os;
        
    }


int main()
{
    std::cout << "Hello from polynomial class file" << std::endl;
    Polynomial a{"10*x^4 + 2*x^2 + 3*x^1 + 1*x^0"};
    Polynomial b{"10*x^4 + 1*x^3 + 2*x^1"};
    Polynomial easy{"10*x^5 + 2*x^2 + 3*x^1 + 1*x^0"};

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << a << " + " << b << " = " <<  a + b << std::endl;
    std::cout << a << " + " << easy << " = " << a + easy << std::endl;


    
    return 0;
}