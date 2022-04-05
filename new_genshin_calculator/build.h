#ifndef BUILD_H
#define BUILD_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Build
{
    static std::vector<int> choices;
    static int build_count; //only declare that this variable exist, but doesn't allocate memory to store anything yet
    int atk, em; double crate, cdmg, eledmg; //stats input
    double stats_volume, avg_vape, avg_melt, creaction_vape, creaction_melt;
    public:
        void set_atk(int atk);
        void set_em(int em);
        void set_crate(double crate);
        void set_cdmg(double cdmg);
        void set_eledmg(double eledmg);
        void set_stats_volume();
        void set_avg_reaction();
        void set_creaction();

        double get_stats_volume();
        double get_avg_vape();
        double get_avg_melt();
        double get_creaction_vape();
        double get_creaction_melt();

        //constructor
        Build();
        Build(int atk, int em, double crate, double cdmg);
};


#endif