#include "build.h"

//getter, setter, constructor
void Build::set_atk(int atk)
{
    this->atk = atk;
}

void Build::set_em(int em)
{
    this->em = em;
}

void Build::set_crate(double crate)
{
    this->crate = crate;
}

void Build::set_cdmg(double cdmg)
{
    this->cdmg = cdmg;
}

void Build::set_eledmg(double eledmg)
{
    this->eledmg = eledmg;
}

void Build::set_stats_volume()
{
    stats_volume = atk * ((1 - crate / 100) + (crate / 100 * (1 + cdmg / 100))) * (1 + eledmg / 100);
}

void Build::set_avg_reaction()
{
    double embonus = 278.0 * em / (1400 + em) / 100;
    avg_vape = stats_volume * (1 + embonus + 0.5);
    avg_melt = stats_volume * (2 + embonus);
}

void Build::set_creaction()
{
    double embonus = 278.0 * em / (1400 + em) / 100;
    creaction_vape = atk * (1 + cdmg / 100) * (1 + embonus + 0.5);
    creaction_melt = atk * (1 + cdmg / 100) * (2 + embonus);
}


double Build::get_stats_volume()
{
    return stats_volume;
}

double Build::get_avg_vape()
{
    return avg_vape;
}

double Build::get_avg_melt()
{
    return avg_melt;
}

double Build::get_creaction_vape()
{
    return creaction_vape;
}

double Build::get_creaction_melt()
{
    return creaction_melt;
}


Build::Build(int atk, int em, double crate, double cdmg)
{
    if (crate > 100) {
		crate = 100;
    }

    set_atk(atk);
    set_em(em);
    set_crate(crate);
    set_cdmg(cdmg);

    set_stats_volume();
    set_avg_reaction();
    set_creaction();
}

int Build::build_count = 0;
std::vector<int> Build::choices;

Build::Build()
{
    int atk = 2000, em = 0;
    double crate = 50, cdmg = 100, eledmg = 0;
    if (build_count == 0) {
        std::string choice_stream;
        int choice;
        std::cout   << "Enter the stats to include!\n"
                    << "1. Attack\n"
                    << "2. Critical Rate\n"
                    << "3. Critical Damage\n"
                    << "4. Elemental Mastery\n"
                    << "5. Elemental Dmg\n" 
                    << "Input space-separated number: ";
        
        std::getline(std::cin, choice_stream);
        while (choice_stream.back() == ' ') {
            choice_stream.pop_back();
        }
        std::stringstream ss(choice_stream);
        while (!ss.eof())
        {
            ss >> choice;
            choices.push_back(choice);
        }
    }

    std::cout << "\nEnter the stats for build " << (build_count++ % 2) + 1 << "!" << std::endl;
    for (int i = 0; i < choices.size(); i++)
    {
        std::cout << i + 1;
        switch (choices[i]) //read all choices in the vector
        {  
            case 1:
                std::cout << ". Attack = ";                std::cin >> atk;
                std::cin.ignore(10, '\n');
                break;
            case 2:
                std::cout << ". Critical Rate(%) = ";      std::cin >> crate;
                break;
            case 3:
                std::cout << ". Critical Damage(%) = ";    std::cin >> cdmg;
                break;
            case 4:
                std::cout << ". Elemental Mastery = ";     std::cin >> em;
                std::cin.ignore(10, '\n');
                break;
            case 5:
                std::cout << ". Elemental Dmg(%) = ";      std::cin >> eledmg;
                break;
        }  
    }    
    
    if (crate > 100) {
		crate = 100;
    }

    set_atk(atk);
    set_crate(crate);
    set_cdmg(cdmg);
    set_em(em);
    set_eledmg(eledmg);

    set_stats_volume();
    set_avg_reaction();
    set_creaction();
}
