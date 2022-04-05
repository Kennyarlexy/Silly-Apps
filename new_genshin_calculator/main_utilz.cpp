#include "main_utilz.h"
#include "build.h"
#include <cmath>
#include <iomanip>

void compare_build(Build build_1, Build build_2)
{
    double stats_1 = build_1.get_stats_volume();
    double stats_2 = build_2.get_stats_volume();
    double result;
    if (stats_1 > stats_2) {
        result = (stats_1 / stats_2 - 1) * 100;
        std::cout << "Build 1 is " << std::fixed << std::setprecision(2) << result << "% better than Build 2\t\t(non-reaction)" << std::endl;
    } else if (stats_1 < stats_2) {
        result = (stats_2 / stats_1 - 1) * 100;
        std::cout << "Build 2 is " << std::fixed << std::setprecision(2) << result << "% better than Build 1\t\t(non-reaction)" << std::endl;
    } else {
        std::cout << "Build 1 is as good as Build 2\t(non-reaction)" << std::endl;
    }
    std::cout << std::endl;
}

void compare_reaction(Build build_1, Build build_2)
{
    double vape_1 = build_1.get_avg_vape();
    double vape_2 = build_2.get_avg_vape();
    double melt_1 = build_1.get_avg_melt();
    double melt_2 = build_2.get_avg_melt();
    double result_vape, result_melt;
    if (vape_1 > vape_2) {
        result_vape = (vape_1 / vape_2 - 1) * 100;
        result_melt = (melt_1 / melt_2 - 1) * 100;
        std::cout << "Build 1 is " << std::fixed << std::setprecision(2) << fmin(result_vape, result_melt) << "% - " << fmax(result_vape, result_melt) << "% better than Build 2\t(full reaction)" << std::endl;
    } else if (vape_1 < vape_2) {
        result_vape = (vape_2 / vape_1 - 1) * 100;
        result_melt = (melt_2 / melt_1 - 1) * 100;
        std::cout << "Build 2 is " << std::fixed << std::setprecision(2) << fmin(result_vape, result_melt) << "% - " << fmax(result_vape, result_melt) << "% better than Build 1\t(full reaction)" << std::endl;
    } else {
        std::cout << "Build 1 is as good as Build 2\t(full reaction)" << std::endl;
    }
    std::cout << std::endl;
}

void compare_creaction(Build build_1, Build build_2)
{
    double cvape_1 = build_1.get_creaction_vape();
    double cvape_2 = build_2.get_creaction_vape();
    double cmelt_1 = build_1.get_creaction_melt();
    double cmelt_2 = build_2.get_creaction_melt();
    double result_vape, result_melt;
    if (cvape_1 > cvape_2) {
        result_vape = (cvape_1 / cvape_2 - 1) * 100;
        result_melt = (cmelt_1 / cmelt_2 - 1) * 100;
        std::cout << "Build 1 is " << std::fixed << std::setprecision(2) << fmin(result_vape, result_melt) << "% - " << fmax(result_vape, result_melt) << "% better than Build 2\t(crit-only reaction)" << std::endl;
    } else if (cvape_2 > cvape_1) {
        result_vape = (cvape_2 / cvape_1 - 1) * 100;
        result_melt = (cmelt_2 / cmelt_1 - 1) * 100;
        std::cout << "Build 2 is " << std::fixed << std::setprecision(2) << fmin(result_vape, result_melt) << "% - " << fmax(result_vape, result_melt) << "% better than Build 1\t(crit-only reaction)" << std::endl;
    } else {
        std::cout << "Build 1 is as good as Build 2\t(crit-only reaction)" << std::endl;
    }
    std::cout << std::endl;
}