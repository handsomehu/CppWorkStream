#include "funcheader.h"
void nameage()
{
    std::string name{""};
    int age{0};
    std::cout << "please input a name:" << std::endl;
    std::cin >> name  ;
    std::cout << "please input age:" << std::endl;
    std::cin >> age  ;
    std::cout << "name:" << name << " age:" << age;

}

void vecint()
{
    std::vector<int> vi{5, 9, -1,200, 0};
    for(auto i:vi)
        std::cout << i << std::endl;
    std::sort(vi.begin(),vi.end());
    for(auto i:vi)
        std::cout << i << std::endl;

}

void vecstr()
{
    std::vector<std::string> vs{"Kant", "Plato", "Aristotle","Kierkegard", "Hume"};
    for(auto i:vs)
        std::cout << i << std::endl;
    std::sort(vs.begin(),vs.end());
    for(auto i:vs)
        std::cout << i << std::endl;

}

void writeint()
{
    std::ofstream ofile("test1.txt");
    for(auto i=0;i<200;++i)
    {
        ofile <<  i << std::endl ;

    }
}

void readint()
{
    std::ifstream ifile("test1.txt");
    std::string linecont{""};
    while(ifile>>linecont)
        std::cout << linecont << std::endl;
}


void thw()
{
    //std::thread h{hello};
    //std::thread w{world};
    //h.join();
    //w.join();
}

void findnum()
{
    std::string fname{"./twothread.cpp"};
    std::ifstream infile{fname};
    std::string line;
    std::string regstr{"[-+]?[0-9]*\\.?[0-9]+"};
    std::regex r(regstr);
    int i{0};
    while (std::getline(infile, line))
    {
        //std::cout << ++i << std::endl;
        std::smatch m;
        std::regex_search(line, m, r);

        for(auto v: m)
            std::cout << v << std::endl;
    }

}

void charsign()
{
    char c = 255;
    int i = c;
    if (i == 255)
        std::cout << "Unsigned" << std::endl;
    else if (i == -1)
    {
        std::cout << "signed" << std::endl;
    }
    else
        std::cout << "what's the char?" << std::endl;
}
